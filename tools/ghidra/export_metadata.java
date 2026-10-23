// Scoped, structured observations of curated RE metadata for tools/re_metadata.py
// (called through `tools/ghidra_refdb.py metadata-*`; docs/re_metadata.md).
//
//   -postScript export_metadata.java observe  <request.json> <out.json>
//   -postScript export_metadata.java baseline <request.json> <out.json> <binding.json>
//
// `observe` reads only: the functions, types, comments and namespaces a request
// names, plus the program identity, the effective analyzer options and the
// managed-state record. `baseline` runs once, in the import session of a fresh
// project (the program has never been saved), and records the untouched
// auto-analysis state of the requested functions in the program itself; a plan
// may replace a body only where it still equals that record. A project that was
// ever saved cannot acquire a baseline afterwards.
//
// This class is also the projection library apply_metadata.java extends, so an
// observation and a post-apply verification are computed by the same code.
// Canonical JSON (sorted keys, no whitespace, integers only, Python's escaping)
// must stay byte-identical with re_metadata.canonical().
//@category Export
import java.io.File;
import java.math.BigDecimal;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonNull;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonPrimitive;

import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.framework.options.Options;
import ghidra.program.database.data.EnumSignedState;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.data.AbstractFloatDataType;
import ghidra.program.model.data.AbstractIntegerDataType;
import ghidra.program.model.data.Array;
import ghidra.program.model.data.BooleanDataType;
import ghidra.program.model.data.CharDataType;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeComponent;
import ghidra.program.model.data.Enum;
import ghidra.program.model.data.Pointer;
import ghidra.program.model.data.Structure;
import ghidra.program.model.data.TypeDef;
import ghidra.program.model.data.Undefined;
import ghidra.program.model.data.VoidDataType;
import ghidra.program.model.data.WideChar16DataType;
import ghidra.program.model.data.Union;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.CommentType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Parameter;
import ghidra.program.model.listing.Program;
import ghidra.program.model.listing.VariableStorage;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.pcode.Varnode;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolType;

public class export_metadata extends GhidraScript {
	protected static final String OPTIONS = "RE Metadata";
	protected static final String STATE = "state";
	protected static final String BASELINE = "baseline";
	protected static final String TYPE_ROOT = "/ReMetadata";
	protected long base;

	// ------------------------------------------------------------ canonical JSON

	protected static String canon(JsonElement e) {
		StringBuilder b = new StringBuilder();
		canon(e, b);
		return b.toString();
	}

	private static void canon(JsonElement e, StringBuilder b) {
		if (e == null || e.isJsonNull()) {
			b.append("null");
		}
		else if (e.isJsonObject()) {
			TreeMap<String, JsonElement> sorted = new TreeMap<>();
			for (Map.Entry<String, JsonElement> m : e.getAsJsonObject().entrySet()) {
				sorted.put(m.getKey(), m.getValue());
			}
			b.append('{');
			boolean first = true;
			for (Map.Entry<String, JsonElement> m : sorted.entrySet()) {
				if (!first) {
					b.append(',');
				}
				first = false;
				quote(m.getKey(), b);
				b.append(':');
				canon(m.getValue(), b);
			}
			b.append('}');
		}
		else if (e.isJsonArray()) {
			b.append('[');
			boolean first = true;
			for (JsonElement x : e.getAsJsonArray()) {
				if (!first) {
					b.append(',');
				}
				first = false;
				canon(x, b);
			}
			b.append(']');
		}
		else {
			JsonPrimitive p = e.getAsJsonPrimitive();
			if (p.isBoolean()) {
				b.append(p.getAsBoolean() ? "true" : "false");
			}
			else if (p.isNumber()) {
				// Integers only: a float has no portable canonical spelling.
				b.append(new BigDecimal(p.getAsString()).toBigIntegerExact().toString());
			}
			else {
				quote(p.getAsString(), b);
			}
		}
	}

	private static void quote(String s, StringBuilder b) {
		b.append('"');
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			switch (c) {
				case '"': b.append("\\\""); break;
				case '\\': b.append("\\\\"); break;
				case '\n': b.append("\\n"); break;
				case '\r': b.append("\\r"); break;
				case '\t': b.append("\\t"); break;
				case '\b': b.append("\\b"); break;
				case '\f': b.append("\\f"); break;
				default:
					if (c < 0x20) {
						b.append(String.format("\\u%04x", (int) c));
					}
					else {
						b.append(c);
					}
			}
		}
		b.append('"');
	}

	protected static String sha256(String text) throws Exception {
		return sha256(text.getBytes(StandardCharsets.UTF_8));
	}

	protected static String sha256(byte[] bytes) throws Exception {
		MessageDigest md = MessageDigest.getInstance("SHA-256");
		StringBuilder b = new StringBuilder();
		for (byte x : md.digest(bytes)) {
			b.append(String.format("%02x", x & 0xff));
		}
		return b.toString();
	}

	protected static String digest(JsonElement e) throws Exception {
		return sha256(canon(e));
	}

	protected static JsonElement readJson(String path) throws Exception {
		return JsonParser.parseString(Files.readString(new File(path).toPath(), StandardCharsets.UTF_8));
	}

	protected static void writeJson(String path, JsonElement e) throws Exception {
		File f = new File(path);
		if (f.getParentFile() != null) {
			f.getParentFile().mkdirs();
		}
		Files.writeString(f.toPath(), canon(e) + "\n", StandardCharsets.UTF_8);
	}

	protected static JsonArray arr(String... items) {
		JsonArray a = new JsonArray();
		for (String s : items) {
			a.add(s);
		}
		return a;
	}

	// ------------------------------------------------------------ addresses

	protected String rva(Address a) {
		return String.format("0x%08x", a.getOffset() - base);
	}

	protected String rvaOf(long offset) {
		return String.format("0x%08x", offset - base);
	}

	protected Address addr(String rvaText) {
		if (!rvaText.matches("0x[0-9a-f]{8}")) {
			throw new IllegalArgumentException("malformed rva " + rvaText);
		}
		return currentProgram.getAddressFactory().getDefaultAddressSpace()
				.getAddress(base + Long.parseLong(rvaText.substring(2), 16));
	}

	/** [[start, end_exclusive], ...] in address order. */
	protected JsonArray ranges(AddressSetView set) {
		JsonArray out = new JsonArray();
		for (AddressRange r : set.getAddressRanges()) {
			out.add(arr(rva(r.getMinAddress()), rvaOf(r.getMaxAddress().getOffset() + 1)));
		}
		return out;
	}

	/** The address set of half-open ranges, or an exception naming the defect. */
	protected AddressSet addressSet(JsonArray ranges) {
		AddressSet set = new AddressSet();
		long last = Long.MIN_VALUE;
		for (JsonElement e : ranges) {
			JsonArray r = e.getAsJsonArray();
			long s = Long.parseLong(r.get(0).getAsString().substring(2), 16);
			long x = Long.parseLong(r.get(1).getAsString().substring(2), 16);
			if (x <= s || s < last || x > 0xffffffffL) {
				throw new IllegalArgumentException("malformed interval " + r);
			}
			last = x;
			set.add(addr(r.get(0).getAsString()), addr(r.get(1).getAsString()).subtract(1));
		}
		return set;
	}

	/** null when every range lies in initialized, executable memory, else the defect. */
	protected String mappedDefect(AddressSetView set) {
		for (AddressRange r : set.getAddressRanges()) {
			MemoryBlock b = currentProgram.getMemory().getBlock(r.getMinAddress());
			if (b == null || !b.contains(r.getMaxAddress())) {
				return "range " + rva(r.getMinAddress()) + " is not inside one memory block";
			}
			if (!b.isInitialized() || !b.isExecute()) {
				return "range " + rva(r.getMinAddress()) + " is not initialized executable memory";
			}
		}
		return null;
	}

	// ------------------------------------------------------------ types

	protected static String typePath(DataType dt) {
		return dt.getCategoryPath().getPath().equals("/") ? "/" + dt.getName()
				: dt.getCategoryPath().getPath() + "/" + dt.getName();
	}

	protected static boolean managedPath(String path) {
		return path.startsWith(TYPE_ROOT + "/");
	}

	protected static JsonObject prim(String name) {
		JsonObject o = new JsonObject();
		o.addProperty("prim", name);
		return o;
	}

	/** The portable reference to a data type, as tools/re_metadata.py spells it. */
	protected JsonObject typeRef(DataType dt) {
		if (dt == null) {
			return prim("undefined");
		}
		if (dt instanceof Pointer) {
			JsonObject o = new JsonObject();
			o.add("ptr", typeRef(((Pointer) dt).getDataType()));
			if (dt.getLength() != currentProgram.getDefaultPointerSize()) {
				o.addProperty("size", dt.getLength());
			}
			return o;
		}
		if (dt instanceof Array) {
			Array a = (Array) dt;
			JsonObject o = new JsonObject();
			o.add("array", typeRef(a.getDataType()));
			o.addProperty("count", a.getNumElements());
			return o;
		}
		String path = typePath(dt);
		if (managedPath(path)) {
			JsonObject o = new JsonObject();
			o.addProperty("named", path);
			return o;
		}
		if (dt instanceof TypeDef) {
			JsonObject o = new JsonObject();
			o.addProperty("typedef", path);
			o.add("of", typeRef(((TypeDef) dt).getBaseDataType()));
			return o;
		}
		if (dt instanceof VoidDataType) {
			return prim("void");
		}
		if (dt instanceof BooleanDataType) {
			return prim("bool8");
		}
		if (dt instanceof CharDataType) {
			return prim("char8");
		}
		if (dt instanceof WideChar16DataType) {
			return prim("wchar16");
		}
		if (dt instanceof AbstractIntegerDataType) {
			return prim((((AbstractIntegerDataType) dt).isSigned() ? "i" : "u") + (8 * dt.getLength()));
		}
		if (dt instanceof AbstractFloatDataType) {
			return prim("f" + (8 * dt.getLength()));
		}
		if (dt instanceof Undefined) {
			return prim("undefined" + dt.getLength());
		}
		JsonObject o = new JsonObject();
		o.addProperty("foreign", path);
		o.addProperty("kind", dt instanceof Structure ? "struct" : dt instanceof Union ? "union"
				: dt instanceof Enum ? "enum" : dt.getClass().getSimpleName());
		o.addProperty("size", dt.getLength());
		return o;
	}

	/** The semantic projection of a managed type, or null when absent. */
	protected JsonObject typeProjection(DataType dt) {
		if (dt == null) {
			return null;
		}
		JsonObject o = new JsonObject();
		// A typedef reports its target's description and cannot hold its own.
		String desc = dt instanceof TypeDef ? "" : dt.getDescription();
		o.addProperty("description", desc == null ? "" : desc);
		if (dt instanceof Structure) {
			Structure s = (Structure) dt;
			o.addProperty("kind", "struct");
			o.addProperty("size", s.isZeroLength() ? 0 : s.getLength());
			o.addProperty("packing", s.isPackingEnabled());
			JsonArray fields = new JsonArray();
			for (DataTypeComponent c : s.getDefinedComponents()) {
				JsonObject f = new JsonObject();
				f.addProperty("offset", c.getOffset());
				f.addProperty("size", c.getLength());
				f.add("name", c.getFieldName() == null ? JsonNull.INSTANCE : new JsonPrimitive(c.getFieldName()));
				f.add("type", typeRef(c.getDataType()));
				f.addProperty("comment", c.getComment() == null ? "" : c.getComment());
				if (c.isBitFieldComponent()) {
					f.addProperty("bitfield", true);
				}
				fields.add(f);
			}
			o.add("fields", fields);
		}
		else if (dt instanceof Enum) {
			Enum e = (Enum) dt;
			o.addProperty("kind", "enum");
			o.addProperty("size", e.getLength());
			EnumSignedState st = e.getSignedState();
			o.addProperty("signed_state", st == EnumSignedState.SIGNED ? "signed"
					: st == EnumSignedState.UNSIGNED ? "unsigned" : st == EnumSignedState.NONE ? "either" : "invalid");
			TreeMap<String, Long> byName = new TreeMap<>();
			for (String n : e.getNames()) {
				byName.put(n, e.getValue(n));
			}
			JsonArray values = new JsonArray();
			byName.entrySet().stream()
					.sorted((a, b) -> a.getValue().equals(b.getValue()) ? a.getKey().compareTo(b.getKey())
							: Long.compare(a.getValue(), b.getValue()))
					.forEach(m -> {
						JsonArray v = new JsonArray();
						v.add(m.getKey());
						v.add(m.getValue());
						values.add(v);
					});
			o.add("values", values);
		}
		else if (dt instanceof TypeDef) {
			o.addProperty("kind", "typedef");
			o.add("target", typeRef(((TypeDef) dt).getDataType()));
		}
		else {
			o.addProperty("kind", "unsupported:" + dt.getClass().getSimpleName());
			o.addProperty("size", dt.getLength());
		}
		return o;
	}

	protected DataType managedType(String path) {
		return currentProgram.getDataTypeManager().getDataType(path);
	}

	// ------------------------------------------------------------ functions

	protected JsonArray namespacePath(Namespace ns) {
		List<String> parts = new ArrayList<>();
		while (ns != null && !ns.isGlobal()) {
			parts.add(0, ns.getName());
			ns = ns.getParentNamespace();
		}
		JsonArray a = new JsonArray();
		for (String p : parts) {
			a.add(p);
		}
		return a;
	}

	protected JsonObject nameProjection(Function f) {
		JsonObject o = new JsonObject();
		o.addProperty("name", f.getName());
		o.add("namespace", namespacePath(f.getParentNamespace()));
		return o;
	}

	protected JsonArray storage(VariableStorage vs) {
		JsonArray out = new JsonArray();
		if (vs == null || vs.isVoidStorage() || vs.isUnassignedStorage()) {
			return out;
		}
		for (Varnode v : vs.getVarnodes()) {
			JsonObject o = new JsonObject();
			if (v.isRegister()) {
				Register r = currentProgram.getRegister(v);
				o.addProperty("reg", r == null ? ("0x" + Long.toHexString(v.getOffset())) : r.getName());
			}
			else if (v.getAddress().isStackAddress()) {
				o.addProperty("stack", v.getAddress().getOffset());
			}
			else {
				o.addProperty("space", v.getAddress().getAddressSpace().getName());
				o.addProperty("offset", "0x" + Long.toHexString(v.getOffset()));
			}
			o.addProperty("size", v.getSize());
			out.add(o);
		}
		return out;
	}

	/** Structured signature: logical parameters apart from compiler-generated ones. */
	protected JsonObject signatureProjection(Function f) {
		JsonObject o = new JsonObject();
		o.addProperty("convention", f.getCallingConventionName());
		o.addProperty("variadic", f.hasVarArgs());
		o.addProperty("storage_mode", f.hasCustomVariableStorage() ? "custom" : "dynamic");
		JsonObject ret = new JsonObject();
		ret.add("type", typeRef(f.getReturnType()));
		ret.add("storage", storage(f.getReturn().getVariableStorage()));
		o.add("return", ret);
		JsonArray params = new JsonArray();
		JsonArray autos = new JsonArray();
		for (Parameter p : f.getParameters()) {
			JsonObject q = new JsonObject();
			if (p.isAutoParameter()) {
				q.addProperty("role", p.getAutoParameterType().name().toLowerCase());
				q.add("storage", storage(p.getVariableStorage()));
				autos.add(q);
			}
			else {
				q.addProperty("name", p.getName());
				q.add("type", typeRef(p.getDataType()));
				q.add("storage", storage(p.getVariableStorage()));
				params.add(q);
			}
		}
		o.add("params", params);
		o.add("auto_params", autos);
		return o;
	}

	/** Informational only: the type Ghidra gave each automatic parameter. */
	protected JsonArray autoParamTypes(Function f) {
		JsonArray out = new JsonArray();
		for (Parameter p : f.getParameters()) {
			if (p.isAutoParameter()) {
				JsonObject q = new JsonObject();
				q.addProperty("role", p.getAutoParameterType().name().toLowerCase());
				q.add("type", typeRef(p.getDataType()));
				out.add(q);
			}
		}
		return out;
	}

	protected JsonObject functionObservation(Function f) {
		JsonObject o = new JsonObject();
		o.addProperty("entry_rva", rva(f.getEntryPoint()));
		o.add("name", nameProjection(f));
		o.addProperty("name_source", f.getSymbol().getSource().toString());
		o.add("body", ranges(f.getBody()));
		o.add("signature", signatureProjection(f));
		o.addProperty("signature_source", f.getSignatureSource().toString());
		o.add("auto_param_types", autoParamTypes(f));
		o.addProperty("thunk", f.isThunk());
		return o;
	}

	// ------------------------------------------------------------ comments

	protected static CommentType commentType(String kind) {
		switch (kind) {
			case "eol": return CommentType.EOL;
			case "pre": return CommentType.PRE;
			case "post": return CommentType.POST;
			case "plate": return CommentType.PLATE;
			case "repeatable": return CommentType.REPEATABLE;
			default: throw new IllegalArgumentException("unsupported comment kind " + kind);
		}
	}

	protected String comment(String rvaText, String kind) {
		return currentProgram.getListing().getComment(commentType(kind), addr(rvaText));
	}

	// ------------------------------------------------------------ state records

	protected JsonObject optionJson(String key) {
		Options opts = currentProgram.getOptions(OPTIONS);
		String text = opts.getString(key, null);
		return text == null || text.isEmpty() ? null : JsonParser.parseString(text).getAsJsonObject();
	}

	protected JsonObject analysisOptions() {
		Options opts = currentProgram.getOptions(Program.ANALYSIS_PROPERTIES);
		JsonObject o = new JsonObject();
		List<String> names = new ArrayList<>(opts.getOptionNames());
		java.util.Collections.sort(names);
		for (String n : names) {
			Object v = opts.getObject(n, null);
			o.addProperty(n, v == null ? "" : v.toString());
		}
		return o;
	}

	protected JsonObject programIdentity() {
		JsonObject o = new JsonObject();
		o.addProperty("name", currentProgram.getName());
		o.addProperty("executable_sha256", currentProgram.getExecutableSHA256());
		o.addProperty("image_base", String.format("0x%08x", base));
		o.addProperty("address_space", currentProgram.getAddressFactory().getDefaultAddressSpace().getName());
		o.addProperty("pointer_size", currentProgram.getDefaultPointerSize());
		o.addProperty("language_id", currentProgram.getLanguageID().toString());
		o.addProperty("compiler_spec_id", currentProgram.getCompilerSpec().getCompilerSpecID().toString());
		o.addProperty("ghidra_version", Application.getApplicationVersion());
		o.addProperty("ghidra_revision", Application.getApplicationProperty("application.revision.ghidra"));
		o.addProperty("java_version", System.getProperty("java.runtime.version"));
		return o;
	}

	/** Functions whose bodies intersect `set`, other than the one at `entry`. */
	protected JsonArray overlapping(AddressSetView set, Address entry) {
		JsonArray out = new JsonArray();
		Iterator<Function> it = currentProgram.getFunctionManager().getFunctionsOverlapping(set);
		while (it.hasNext()) {
			Function g = it.next();
			if (entry == null || !g.getEntryPoint().equals(entry)) {
				out.add(rva(g.getEntryPoint()));
			}
		}
		return out;
	}

	/** Every non-namespace symbol and function named like a desired namespace component. */
	protected JsonObject namespaceProbe(JsonArray path) {
		JsonObject o = new JsonObject();
		Namespace ns = currentProgram.getGlobalNamespace();
		JsonArray kinds = new JsonArray();
		boolean missing = false;
		for (JsonElement e : path) {
			String part = e.getAsString();
			if (missing) {
				kinds.add("absent");
				continue;
			}
			Namespace next = currentProgram.getSymbolTable().getNamespace(part, ns);
			List<String> clashes = new ArrayList<>();
			for (Symbol s : currentProgram.getSymbolTable().getSymbols(part, ns)) {
				SymbolType t = s.getSymbolType();
				if (t != SymbolType.NAMESPACE && t != SymbolType.CLASS) {
					clashes.add(t.toString());
				}
			}
			if (!clashes.isEmpty()) {
				kinds.add("clash:" + String.join("+", clashes));
				missing = next == null;
				if (next != null) {
					ns = next;
				}
				continue;
			}
			if (next == null) {
				kinds.add("absent");
				missing = true;
			}
			else {
				kinds.add(next.getSymbol().getSymbolType() == SymbolType.CLASS ? "class" : "namespace");
				ns = next;
			}
		}
		o.add("path", path);
		o.add("kinds", kinds);
		return o;
	}

	/** Functions (by entry RVA) carrying exactly this name in exactly this namespace. */
	protected JsonArray nameHolders(JsonArray path, String name) {
		JsonArray out = new JsonArray();
		Namespace ns = currentProgram.getGlobalNamespace();
		for (JsonElement e : path) {
			ns = currentProgram.getSymbolTable().getNamespace(e.getAsString(), ns);
			if (ns == null) {
				return out;
			}
		}
		for (Symbol s : currentProgram.getSymbolTable().getSymbols(name, ns)) {
			if (s.getSymbolType() == SymbolType.FUNCTION) {
				out.add(rva(s.getAddress()));
			}
		}
		return out;
	}

	/**
	 * Named types whose layout embeds `dt` by value, through arrays and typedefs.
	 * A pointer to `dt` is not a consumer: its size does not depend on dt's layout.
	 */
	protected void consumers(DataType dt, List<String> out, java.util.Set<String> seen) {
		for (DataType p : dt.getParents()) {
			if (p instanceof Pointer || !seen.add(typePath(p))) {
				continue;
			}
			if (p instanceof Array || p instanceof TypeDef) {
				consumers(p, out, seen);
			}
			else {
				out.add(typePath(p));
			}
		}
	}

	/** The observation a request asks for. */
	protected JsonObject observe(JsonObject request) throws Exception {
		JsonObject out = new JsonObject();
		out.addProperty("schema", "re-metadata-observation/1");
		out.add("program", programIdentity());
		out.add("analysis_options", analysisOptions());
		JsonObject functions = new JsonObject();
		for (JsonElement e : request.getAsJsonArray("functions")) {
			JsonObject q = e.getAsJsonObject();
			String entryText = q.get("entry_rva").getAsString();
			Address entry = addr(entryText);
			Function f = currentProgram.getFunctionManager().getFunctionAt(entry);
			JsonObject o = f == null ? new JsonObject() : functionObservation(f);
			o.addProperty("exists", f != null);
			if (f == null) {
				Function containing = currentProgram.getFunctionManager().getFunctionContaining(entry);
				o.add("containing", containing == null ? JsonNull.INSTANCE : new JsonPrimitive(rva(containing.getEntryPoint())));
			}
			if (q.has("probe_body")) {
				JsonObject probe = new JsonObject();
				try {
					AddressSet set = addressSet(q.getAsJsonArray("probe_body"));
					String defect = mappedDefect(set);
					probe.add("unmapped", defect == null ? JsonNull.INSTANCE : new JsonPrimitive(defect));
					probe.add("overlaps", overlapping(set, entry));
					probe.addProperty("defined_data", currentProgram.getListing().getDefinedData(set, true).hasNext());
				}
				catch (IllegalArgumentException ex) {
					probe.addProperty("unmapped", ex.getMessage());
					probe.add("overlaps", new JsonArray());
				}
				o.add("probe", probe);
			}
			if (q.has("probe_name")) {
				JsonObject n = q.getAsJsonObject("probe_name");
				JsonObject probe = namespaceProbe(n.getAsJsonArray("namespace"));
				probe.add("holders", nameHolders(n.getAsJsonArray("namespace"), n.get("name").getAsString()));
				o.add("name_probe", probe);
			}
			functions.add(entryText, o);
		}
		out.add("functions", functions);
		JsonObject types = new JsonObject();
		for (JsonElement e : request.getAsJsonArray("types")) {
			String path = e.getAsString();
			DataType dt = managedType(path);
			JsonObject t = new JsonObject();
			t.add("projection", typeProjection(dt));
			JsonArray parents = new JsonArray();
			if (dt != null) {
				List<String> ps = new ArrayList<>();
				consumers(dt, ps, new java.util.HashSet<>());
				java.util.Collections.sort(ps);
				for (String p : ps) {
					parents.add(p);
				}
			}
			t.add("parents", parents);
			types.add(path, t);
		}
		out.add("types", types);
		// Every type under the managed root: a suffixed duplicate (".conflict") shows here.
		JsonArray managed = new JsonArray();
		List<String> paths = new ArrayList<>();
		Iterator<DataType> all = currentProgram.getDataTypeManager().getAllDataTypes();
		while (all.hasNext()) {
			DataType t = all.next();
			String p = typePath(t);
			if (managedPath(p) && !(t instanceof Pointer) && !(t instanceof Array)) {
				paths.add(p);
			}
		}
		java.util.Collections.sort(paths);
		for (String p : paths) {
			managed.add(p);
		}
		out.add("managed_type_paths", managed);
		JsonObject comments = new JsonObject();
		for (JsonElement e : request.getAsJsonArray("comments")) {
			JsonObject q = e.getAsJsonObject();
			String key = q.get("address_rva").getAsString() + ":" + q.get("kind").getAsString();
			String text = comment(q.get("address_rva").getAsString(), q.get("kind").getAsString());
			comments.add(key, text == null ? JsonNull.INSTANCE : new JsonPrimitive(text));
		}
		out.add("comments", comments);
		JsonObject state = optionJson(STATE);
		out.add("state", state == null ? JsonNull.INSTANCE : state);
		JsonObject baseline = optionJson(BASELINE);
		out.add("baseline", baseline == null ? JsonNull.INSTANCE : baseline);
		return out;
	}

	/** True only inside the import session of a program never saved before. */
	protected boolean freshImport() {
		return currentProgram.getDomainFile().getVersion() == -1
				&& currentProgram.getDomainFile().getLastModifiedTime() == 0;
	}

	protected JsonObject baseline(JsonObject request, JsonObject binding, JsonObject observation) throws Exception {
		if (!freshImport()) {
			throw new IllegalStateException("baseline refused: the program was saved before; an auto-analysis "
					+ "baseline is recorded only in the import session of a fresh project");
		}
		if (optionJson(BASELINE) != null || optionJson(STATE) != null) {
			throw new IllegalStateException("baseline refused: the program already carries RE metadata records");
		}
		if (!binding.get("executable_sha256").getAsString().equals(currentProgram.getExecutableSHA256())) {
			throw new IllegalStateException("baseline refused: executable hash differs from the binding");
		}
		JsonObject b = new JsonObject();
		b.addProperty("schema", "re-metadata-baseline/1");
		b.add("binding", binding);
		b.addProperty("analysis_options_sha256", digest(observation.getAsJsonObject("analysis_options")));
		JsonObject fns = new JsonObject();
		for (Map.Entry<String, JsonElement> m : observation.getAsJsonObject("functions").entrySet()) {
			JsonObject f = m.getValue().getAsJsonObject();
			JsonObject r = new JsonObject();
			r.addProperty("exists", f.get("exists").getAsBoolean());
			if (f.get("exists").getAsBoolean()) {
				r.addProperty("body_sha256", digest(f.get("body")));
				r.addProperty("signature_sha256", digest(f.get("signature")));
				r.addProperty("signature_source", f.get("signature_source").getAsString());
				r.addProperty("name_sha256", digest(f.get("name")));
			}
			fns.add(m.getKey(), r);
		}
		b.add("functions", fns);
		return b;
	}

	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		base = currentProgram.getImageBase().getOffset();
		if (args.length == 3 && args[0].equals("observe")) {
			writeJson(args[2], observe(readJson(args[1]).getAsJsonObject()));
			println("export_metadata: observation written");
			return;
		}
		if (args.length == 4 && args[0].equals("baseline")) {
			JsonObject request = readJson(args[1]).getAsJsonObject();
			JsonObject observation = observe(request);
			JsonObject b = baseline(request, readJson(args[3]).getAsJsonObject(), observation);
			currentProgram.getOptions(OPTIONS).setString(BASELINE, canon(b));
			observation.add("baseline", b);
			writeJson(args[2], observation);
			println("export_metadata: baseline recorded");
			return;
		}
		throw new IllegalArgumentException(
			"usage: observe <request.json> <out.json> | baseline <request.json> <out.json> <binding.json>");
	}
}
