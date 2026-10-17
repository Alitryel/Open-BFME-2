// Validated, transactional replay of a curated RE metadata plan
// (tools/ghidra_refdb.py metadata-apply; docs/re_metadata.md):
//
//   -postScript apply_metadata.java apply <plan.json> <evidence_root> <result.json> [fail-after=N]
//   -postScript apply_metadata.java selftest <vectors.json> <out.json>
//
// The plan is not trusted because a coordinator produced it. Before any write
// this script recomputes the plan digest and every operation id, checks the
// executable hash, image base, language, compiler spec and address model, the
// in-program baseline and managed-state digests the plan was made against, and
// every operation's expected current value. A name operation must carry a tier
// (export / ilt / reloc) that the named evidence row, re-read here from
// <evidence_root>, actually satisfies under the rules of
// tools/ghidra_refdb.py evidence_names(): a well-formed digest over an
// ineligible row is refused. All writes then happen in one nested transaction;
// any conflict, verification mismatch, exception or the test hook fail-after=N
// aborts it, which rolls the whole batch back (the headless script transaction
// commits even when a script throws, so only an aborted nested transaction
// guarantees rollback). The result file says what happened; the caller reports
// the save separately from analyzeHeadless's own log.
//@category Symbol
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonNull;
import com.google.gson.JsonObject;
import com.google.gson.JsonPrimitive;

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.data.ArrayDataType;
import ghidra.program.model.data.BooleanDataType;
import ghidra.program.model.data.ByteDataType;
import ghidra.program.model.data.CategoryPath;
import ghidra.program.model.data.CharDataType;
import ghidra.program.model.data.DWordDataType;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeConflictHandler;
import ghidra.program.model.data.DataTypeManager;
import ghidra.program.model.data.EnumDataType;
import ghidra.program.model.data.Float4DataType;
import ghidra.program.model.data.Float8DataType;
import ghidra.program.model.data.PointerDataType;
import ghidra.program.model.data.QWordDataType;
import ghidra.program.model.data.SignedByteDataType;
import ghidra.program.model.data.SignedDWordDataType;
import ghidra.program.model.data.SignedQWordDataType;
import ghidra.program.model.data.SignedWordDataType;
import ghidra.program.model.data.Structure;
import ghidra.program.model.data.StructureDataType;
import ghidra.program.model.data.TypeDef;
import ghidra.program.model.data.TypedefDataType;
import ghidra.program.model.data.VoidDataType;
import ghidra.program.model.data.WideChar16DataType;
import ghidra.program.model.data.WordDataType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Function.FunctionUpdateType;
import ghidra.program.model.listing.Parameter;
import ghidra.program.model.listing.ParameterImpl;
import ghidra.program.model.listing.ReturnParameterImpl;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.SymbolType;

public class apply_metadata extends export_metadata {
	static final String PLAN_SCHEMA = "re-metadata-plan/1";
	static final List<String> ORDER = List.of("set_type", "create_function", "set_function_body",
		"set_function_name", "set_function_signature", "set_comment_segment");
	static final Map<String, String> TIER_FILE = Map.of("export", "reverse/exports.csv",
		"ilt", "reverse/functions.csv", "reloc", "reverse/reloc_names.csv");
	static final Map<String, String> TIER_RVA = Map.of("export", "rva", "ilt", "target_rva", "reloc", "target_rva");
	// tools/ghidra_refdb.py PLACEHOLDER, searched with Python's re.search semantics.
	static final Pattern PLACEHOLDER = Pattern.compile(
		"(?:^|[^A-Za-z])(?:fun|sub|thunk_fun|lab|dat|d|dup|uw|eh|tg|nullsub|loc|j)_[0-9a-f]{4,8}"
			+ "|rva[0-9a-f]{4,8}|gen_?[0-9a-f]{3,8}|(?:^|[^a-z])bfme|[0-9A-F]{6,8}",
		Pattern.CASE_INSENSITIVE);
	static final Pattern MANGLED = Pattern.compile("^\\?(\\?[0-9]|\\?_[A-Z0-9])?([^@?]*)@((?:[^@?]+@)*)@");
	static final Pattern SEGMENT_ID = Pattern.compile("[A-Za-z0-9_.-]{1,64}");

	static class Refused extends Exception {
		Refused(String message) {
			super(message);
		}
	}

	private String evidenceRoot;

	// ------------------------------------------------------------ evidence rules

	static boolean placeholder(String name) {
		return PLACEHOLDER.matcher(name).find();
	}

	/** ghidra_refdb.qualified(): [namespace..., name] for a mangled name, else [name]. */
	static List<String> qualified(String name) {
		List<String> out = new ArrayList<>();
		Matcher m = MANGLED.matcher(name);
		if (!m.find()) {
			out.add(name);
			return out;
		}
		String special = m.group(1), base = m.group(2);
		List<String> scopes = new ArrayList<>();
		for (String s : m.group(3).split("@")) {
			if (!s.isEmpty()) {
				scopes.add(0, s);
			}
		}
		if ("?0".equals(special)) {
			if (base.isEmpty()) {
				base = scopes.isEmpty() ? "" : scopes.get(scopes.size() - 1);
			}
			scopes.add(base);
		}
		else if ("?1".equals(special)) {
			scopes.add(base);
			base = "~" + base;
		}
		else if (special != null) {
			out.add(name);
			return out;
		}
		out.addAll(scopes);
		out.add(base);
		return out;
	}

	/** RFC 4180 rows of a CSV file, header first. */
	static List<List<String>> csv(String text) {
		List<List<String>> rows = new ArrayList<>();
		List<String> row = new ArrayList<>();
		StringBuilder field = new StringBuilder();
		boolean quoted = false, any = false;
		for (int i = 0; i < text.length(); i++) {
			char c = text.charAt(i);
			if (quoted) {
				if (c == '"') {
					if (i + 1 < text.length() && text.charAt(i + 1) == '"') {
						field.append('"');
						i++;
					}
					else {
						quoted = false;
					}
				}
				else {
					field.append(c);
				}
				continue;
			}
			if (c == '"') {
				quoted = true;
				any = true;
			}
			else if (c == ',') {
				row.add(field.toString());
				field.setLength(0);
				any = true;
			}
			else if (c == '\r' || c == '\n') {
				if (c == '\r' && i + 1 < text.length() && text.charAt(i + 1) == '\n') {
					i++;
				}
				if (any || field.length() > 0) {
					row.add(field.toString());
					rows.add(row);
				}
				row = new ArrayList<>();
				field.setLength(0);
				any = false;
			}
			else {
				field.append(c);
				any = true;
			}
		}
		if (any || field.length() > 0) {
			row.add(field.toString());
			rows.add(row);
		}
		return rows;
	}

	/** csv.DictReader rows of one evidence file. */
	List<Map<String, String>> evidenceRows(String relative) throws Exception {
		File f = new File(evidenceRoot, relative);
		List<List<String>> rows = csv(Files.readString(f.toPath(), StandardCharsets.UTF_8));
		List<Map<String, String>> out = new ArrayList<>();
		if (rows.isEmpty()) {
			return out;
		}
		List<String> header = rows.get(0);
		for (List<String> r : rows.subList(1, rows.size())) {
			Map<String, String> d = new LinkedHashMap<>();
			for (int i = 0; i < header.size(); i++) {
				d.put(header.get(i), i < r.size() ? r.get(i) : null);
			}
			out.add(d);
		}
		return out;
	}

	static String rowDigest(Map<String, String> row) throws Exception {
		JsonObject o = new JsonObject();
		for (Map.Entry<String, String> m : row.entrySet()) {
			o.add(m.getKey(), m.getValue() == null ? JsonNull.INSTANCE : new JsonPrimitive(m.getValue()));
		}
		return digest(o);
	}

	static String field(Map<String, String> row, String key) {
		String v = row.get(key);
		return v == null ? "" : v;
	}

	/** ghidra_refdb evidence predicates: does this row admit its name under `tier`? */
	static boolean admits(String tier, Map<String, String> row) {
		String name = field(row, "name");
		if (name.isEmpty() || placeholder(name) || field(row, TIER_RVA.get(tier)).isEmpty()) {
			return false;
		}
		switch (tier) {
			case "export":
				String kind = field(row, "kind");
				// Python's row.get("section", ".text"): the default only when the column is absent.
				boolean text = row.containsKey("section") ? ".text".equals(row.get("section")) : true;
				return (kind.equals("code") || kind.equals("function") || kind.equals("func")) && text;
			case "ilt":
				return field(row, "status").equals("matched") && field(row, "notes").contains("ilt-verified=");
			case "reloc":
				return field(row, "notes").contains("identity=real");
			default:
				return false;
		}
	}

	static long rvaValue(String text) {
		return Long.parseLong(text.startsWith("0x") || text.startsWith("0X") ? text.substring(2) : text, 16);
	}

	/** Refuses unless the op's evidence admits exactly its desired name at its entry. */
	void checkNameEvidence(JsonObject op, Function f) throws Exception {
		JsonObject prov = op.getAsJsonObject("provenance");
		String tier = prov.has("identity_tier") ? prov.get("identity_tier").getAsString() : "";
		if (!TIER_FILE.containsKey(tier)) {
			throw new Refused("name operation without an admissible identity tier: " + tier);
		}
		String raw = op.getAsJsonObject("desired").get("raw").getAsString();
		long entry = rvaValue(op.getAsJsonObject("target").get("entry_rva").getAsString());
		JsonArray refs = prov.getAsJsonArray("evidence_refs");
		if (refs == null || refs.size() == 0) {
			throw new Refused("name operation without evidence_refs");
		}
		boolean admitted = false;
		for (JsonElement e : refs) {
			JsonObject ref = e.getAsJsonObject();
			String path = ref.get("path").getAsString();
			if (!path.equals(TIER_FILE.get(tier))) {
				throw new Refused("evidence " + path + " cannot establish tier " + tier);
			}
			String key = ref.get("record_key").getAsString();
			Map<String, String> found = null;
			int hits = 0;
			for (Map<String, String> row : evidenceRows(path)) {
				String k = TIER_RVA.get(tier) + "=" + field(row, TIER_RVA.get(tier)) + ";name=" + field(row, "name");
				if (k.equals(key)) {
					found = row;
					hits++;
				}
			}
			if (hits != 1) {
				throw new Refused("evidence record " + path + " [" + key + "] matched " + hits + " rows");
			}
			if (!rowDigest(found).equals(ref.get("sha256").getAsString())) {
				throw new Refused("evidence record " + path + " [" + key + "] changed since planning");
			}
			if (!admits(tier, found)) {
				throw new Refused("evidence record " + path + " [" + key + "] does not admit tier " + tier);
			}
			if (rvaValue(field(found, TIER_RVA.get(tier))) != entry || !field(found, "name").equals(raw)) {
				throw new Refused("evidence record " + path + " [" + key + "] names another function or symbol");
			}
			admitted = true;
		}
		// Aliases: another admissible name for the same entry in any tier file is a conflict.
		for (Map.Entry<String, String> t : TIER_FILE.entrySet()) {
			File file = new File(evidenceRoot, t.getValue());
			if (!file.exists()) {
				continue;
			}
			for (Map<String, String> row : evidenceRows(t.getValue())) {
				String r = field(row, TIER_RVA.get(t.getKey()));
				if (!r.isEmpty() && rvaValue(r) == entry && admits(t.getKey(), row)
						&& !field(row, "name").equals(raw)) {
					throw new Refused("alias conflict: " + t.getValue() + " admits " + field(row, "name"));
				}
			}
		}
		List<String> q = qualified(raw);
		JsonObject desired = op.getAsJsonObject("desired").getAsJsonObject("name");
		JsonArray ns = new JsonArray();
		for (String s : q.subList(0, q.size() - 1)) {
			ns.add(s);
		}
		if (!desired.get("name").getAsString().equals(q.get(q.size() - 1)) || !desired.get("namespace").equals(ns)) {
			throw new Refused("desired name is not the evidence spelling's demangled form");
		}
		// The existing overwrite rule: only the ILT oracle replaces a name that is not a placeholder.
		// A function this plan creates carries a default name.
		String have = f == null ? "" : f.getName(true);
		if (f != null && !tier.equals("ilt") && !(f.getSymbol().getSource() == SourceType.DEFAULT || placeholder(have))) {
			throw new Refused("tier " + tier + " may not overwrite the non-placeholder name " + have);
		}
		if (!admitted) {
			throw new Refused("no admitted evidence");
		}
	}

	// ------------------------------------------------------------ data types

	static CategoryPath category(String path) {
		int slash = path.lastIndexOf('/');
		return slash <= 0 ? CategoryPath.ROOT : new CategoryPath(path.substring(0, slash));
	}

	static String leaf(String path) {
		return path.substring(path.lastIndexOf('/') + 1);
	}

	DataType resolveRef(JsonObject ref) throws Refused {
		DataTypeManager dtm = currentProgram.getDataTypeManager();
		if (ref.has("prim")) {
			switch (ref.get("prim").getAsString()) {
				case "void": return VoidDataType.dataType;
				case "bool8": return BooleanDataType.dataType;
				case "char8": return CharDataType.dataType;
				case "wchar16": return WideChar16DataType.dataType;
				case "i8": return SignedByteDataType.dataType;
				case "u8": return ByteDataType.dataType;
				case "i16": return SignedWordDataType.dataType;
				case "u16": return WordDataType.dataType;
				case "i32": return SignedDWordDataType.dataType;
				case "u32": return DWordDataType.dataType;
				case "i64": return SignedQWordDataType.dataType;
				case "u64": return QWordDataType.dataType;
				case "f32": return Float4DataType.dataType;
				case "f64": return Float8DataType.dataType;
				default: throw new Refused("unsupported primitive " + ref);
			}
		}
		if (ref.has("ptr")) {
			if (ref.has("size")) {
				throw new Refused("unsupported pointer width " + ref);
			}
			return new PointerDataType(resolveRef(ref.getAsJsonObject("ptr")), currentProgram.getDefaultPointerSize(), dtm);
		}
		if (ref.has("array")) {
			DataType e = resolveRef(ref.getAsJsonObject("array"));
			return new ArrayDataType(e, ref.get("count").getAsInt(), e.getLength(), dtm);
		}
		if (ref.has("named")) {
			DataType dt = dtm.getDataType(ref.get("named").getAsString());
			if (dt == null) {
				throw new Refused("unresolved type " + ref.get("named").getAsString());
			}
			return dt;
		}
		throw new Refused("unsupported type reference " + ref);
	}

	StructureDataType structure(String path, JsonObject p) throws Refused {
		DataTypeManager dtm = currentProgram.getDataTypeManager();
		StructureDataType s = new StructureDataType(category(path), leaf(path), p.get("size").getAsInt(), dtm);
		s.setPackingEnabled(false);
		s.setDescription(p.get("description").getAsString());
		for (JsonElement e : p.getAsJsonArray("fields")) {
			JsonObject f = e.getAsJsonObject();
			DataType dt = resolveRef(f.getAsJsonObject("type"));
			int size = f.get("size").getAsInt();
			if (dt.getLength() != size) {
				throw new Refused(path + ": field " + f.get("name") + " resolves to " + dt.getLength()
					+ " bytes, layout says " + size);
			}
			String comment = f.get("comment").getAsString();
			s.replaceAtOffset(f.get("offset").getAsInt(), dt, size,
				f.get("name").isJsonNull() ? null : f.get("name").getAsString(), comment.isEmpty() ? null : comment);
		}
		return s;
	}

	void applyTypes(List<JsonObject> ops) throws Exception {
		DataTypeManager dtm = currentProgram.getDataTypeManager();
		// Shells first, so pointer cycles resolve; by-value order is the plan's.
		for (JsonObject op : ops) {
			String path = op.getAsJsonObject("target").get("type_path").getAsString();
			JsonObject p = op.getAsJsonObject("desired").getAsJsonObject("projection");
			if (dtm.getDataType(path) == null && p.get("kind").getAsString().equals("struct")) {
				StructureDataType shell = new StructureDataType(category(path), leaf(path), p.get("size").getAsInt(), dtm);
				shell.setPackingEnabled(false);
				DataType added = dtm.addDataType(shell, DataTypeConflictHandler.DEFAULT_HANDLER);
				if (!typePath(added).equals(path)) {
					throw new Refused("type " + path + " was added as " + typePath(added));
				}
			}
		}
		for (JsonObject op : ops) {
			String path = op.getAsJsonObject("target").get("type_path").getAsString();
			JsonObject p = op.getAsJsonObject("desired").getAsJsonObject("projection");
			DataType existing = dtm.getDataType(path);
			String kind = p.get("kind").getAsString();
			DataType made;
			if (kind.equals("struct")) {
				made = structure(path, p);
			}
			else if (kind.equals("enum")) {
				EnumDataType e = new EnumDataType(category(path), leaf(path), p.get("size").getAsInt(), dtm);
				e.setDescription(p.get("description").getAsString());
				for (JsonElement v : p.getAsJsonArray("values")) {
					e.add(v.getAsJsonArray().get(0).getAsString(), v.getAsJsonArray().get(1).getAsLong());
				}
				made = e;
			}
			else if (kind.equals("typedef")) {
				if (!p.get("description").getAsString().isEmpty()) {
					throw new Refused("a typedef cannot carry a description in Ghidra");
				}
				made = new TypedefDataType(category(path), leaf(path), resolveRef(p.getAsJsonObject("target")), dtm);
			}
			else {
				throw new Refused("unsupported type kind " + kind);
			}
			if (existing == null) {
				existing = dtm.addDataType(made, DataTypeConflictHandler.DEFAULT_HANDLER);
				if (!typePath(existing).equals(path)) {
					throw new Refused("type " + path + " was added as " + typePath(existing));
				}
			}
			else if (existing instanceof TypeDef && kind.equals("typedef")) {
				// A typedef's base cannot be replaced in place: replace the whole type.
				existing = dtm.replaceDataType(existing, made, false);
			}
			else {
				existing.replaceWith(made);
			}
			if (!kind.equals("typedef")) {
				existing.setDescription(p.get("description").getAsString());
			}
		}
	}

	// ------------------------------------------------------------ functions

	Namespace namespace(JsonArray path, boolean create) throws Exception {
		SymbolTable st = currentProgram.getSymbolTable();
		Namespace ns = currentProgram.getGlobalNamespace();
		for (JsonElement e : path) {
			String part = e.getAsString();
			for (Symbol s : st.getSymbols(part, ns)) {
				if (s.getSymbolType() != SymbolType.NAMESPACE && s.getSymbolType() != SymbolType.CLASS) {
					throw new Refused("namespace collision: " + part + " is a " + s.getSymbolType());
				}
			}
			Namespace next = st.getNamespace(part, ns);
			if (next == null) {
				if (!create) {
					return null;
				}
				next = st.createNameSpace(ns, part, SourceType.IMPORTED);
			}
			ns = next;
		}
		return ns;
	}

	void applyName(JsonObject op, Function f) throws Exception {
		JsonObject d = op.getAsJsonObject("desired").getAsJsonObject("name");
		JsonArray holders = nameHolders(d.getAsJsonArray("namespace"), d.get("name").getAsString());
		for (JsonElement h : holders) {
			if (!h.getAsString().equals(rva(f.getEntryPoint()))) {
				throw new Refused("name collision: " + d + " is held by the function at " + h.getAsString());
			}
		}
		Namespace ns = namespace(d.getAsJsonArray("namespace"), true);
		f.getSymbol().setNameAndNamespace(d.get("name").getAsString(), ns, SourceType.IMPORTED);
	}

	void applyBody(JsonObject op, Function f, Address entry) throws Exception {
		AddressSet set = addressSet(op.getAsJsonObject("desired").getAsJsonArray("body"));
		if (!set.contains(entry)) {
			throw new Refused("entry " + rva(entry) + " is outside its desired body");
		}
		String defect = mappedDefect(set);
		if (defect != null) {
			throw new Refused(defect);
		}
		if (overlapping(set, entry).size() != 0) {
			throw new Refused("desired body overlaps " + overlapping(set, entry));
		}
		if (currentProgram.getListing().getDefinedData(set, true).hasNext()) {
			throw new Refused("desired body contains defined data");
		}
		for (AddressRange r : set.getAddressRanges()) {
			if (currentProgram.getListing().getInstructionAt(r.getMinAddress()) == null) {
				DisassembleCommand cmd = new DisassembleCommand(r.getMinAddress(), set, true);
				if (!cmd.applyTo(currentProgram, monitor)) {
					throw new Refused("disassembly failed at " + rva(r.getMinAddress()) + ": " + cmd.getStatusMsg());
				}
			}
		}
		if (f == null) {
			currentProgram.getFunctionManager().createFunction(null, entry, set, SourceType.DEFAULT);
		}
		else {
			f.setBody(set);
		}
	}

	void applySignature(JsonObject op, Function f) throws Exception {
		JsonObject sig = op.getAsJsonObject("desired").getAsJsonObject("signature");
		if (!sig.get("storage_mode").getAsString().equals("dynamic") || sig.get("variadic").getAsBoolean()) {
			throw new Refused("unsupported signature mode");
		}
		String cc = sig.get("convention").getAsString();
		if (!List.of("__cdecl", "__stdcall", "__thiscall").contains(cc)) {
			throw new Refused("unsupported calling convention " + cc);
		}
		List<Parameter> params = new ArrayList<>();
		for (JsonElement e : sig.getAsJsonArray("params")) {
			JsonObject p = e.getAsJsonObject();
			params.add(new ParameterImpl(p.get("name").getAsString(), resolveRef(p.getAsJsonObject("type")), currentProgram));
		}
		ReturnParameterImpl ret = new ReturnParameterImpl(resolveRef(sig.getAsJsonObject("return").getAsJsonObject("type")),
			currentProgram);
		f.setCustomVariableStorage(false);
		f.updateFunction(cc, ret, params, FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS, true, SourceType.IMPORTED);
		f.setVarArgs(false);
	}

	// ------------------------------------------------------------ managed comment segments

	/** [start, end) of the delimited block (with its leading separator newline), or null. */
	static int[] segmentBounds(String text, String id) throws Refused {
		if (text == null) {
			return null;
		}
		String open = "[re-metadata:" + id + "]\n", close = "\n[/re-metadata:" + id + "]";
		int count = 0, at = -1;
		for (int i = text.indexOf(open); i >= 0; i = text.indexOf(open, i + 1)) {
			if (i == 0 || text.charAt(i - 1) == '\n') {
				count++;
				at = i;
			}
		}
		if (count == 0) {
			if (text.contains("[re-metadata:" + id + "]") || text.contains("[/re-metadata:" + id + "]")) {
				throw new Refused("malformed managed segment " + id);
			}
			return null;
		}
		int end = text.indexOf(close, at + open.length());
		if (count > 1 || end < 0) {
			throw new Refused("malformed managed segment " + id);
		}
		end += close.length();
		if (end < text.length() && text.charAt(end) != '\n') {
			throw new Refused("malformed managed segment " + id);
		}
		return new int[] { at, end };
	}

	static String segmentText(String text, String id) throws Refused {
		int[] b = segmentBounds(text, id);
		if (b == null) {
			return null;
		}
		String open = "[re-metadata:" + id + "]\n", close = "\n[/re-metadata:" + id + "]";
		return text.substring(b[0] + open.length(), b[1] - close.length());
	}

	/** The comment with segment `id` set to `value` (null removes it); other text is kept as is. */
	static String withSegment(String text, String id, String value) throws Refused {
		int[] b = segmentBounds(text, id);
		String block = value == null ? null : "[re-metadata:" + id + "]\n" + value + "\n[/re-metadata:" + id + "]";
		String out;
		if (b == null) {
			if (block == null) {
				return text;
			}
			out = text == null || text.isEmpty() ? block : text + "\n" + block;
		}
		else if (block != null) {
			out = text.substring(0, b[0]) + block + text.substring(b[1]);
		}
		else if (b[0] > 0) {
			out = text.substring(0, b[0] - 1) + text.substring(b[1]);
		}
		else {
			out = text.substring(b[1] < text.length() ? b[1] + 1 : b[1]);
		}
		return out.isEmpty() ? null : out;
	}

	// ------------------------------------------------------------ plan checks

	JsonElement currentValue(JsonObject op) throws Exception {
		String kind = op.get("kind").getAsString();
		JsonObject t = op.getAsJsonObject("target");
		JsonObject o = new JsonObject();
		switch (kind) {
			case "set_type":
				JsonObject proj = typeProjection(managedType(t.get("type_path").getAsString()));
				o.add("projection", proj == null ? JsonNull.INSTANCE : proj);
				return o;
			case "set_comment_segment":
				String text = comment(t.get("address_rva").getAsString(), t.get("kind").getAsString());
				String seg = segmentText(text, t.get("segment_id").getAsString());
				o.add("segment", seg == null ? JsonNull.INSTANCE : new JsonPrimitive(seg));
				return o;
			default:
				Function f = currentProgram.getFunctionManager().getFunctionAt(addr(t.get("entry_rva").getAsString()));
				if (kind.equals("create_function")) {
					o.addProperty("exists", f != null);
					return o;
				}
				if (f == null) {
					return JsonNull.INSTANCE;
				}
				if (kind.equals("set_function_body")) {
					o.add("body", ranges(f.getBody()));
				}
				else if (kind.equals("set_function_name")) {
					o.add("name", nameProjection(f));
					o.addProperty("source", f.getSymbol().getSource().toString());
				}
				else if (kind.equals("set_function_signature")) {
					o.add("signature", signatureProjection(f));
					o.addProperty("source", f.getSignatureSource().toString());
				}
				return o;
		}
	}

	/** The desired value as currentValue() would report it after a successful write. */
	static JsonElement achieved(JsonObject op, JsonElement current) {
		JsonObject d = op.getAsJsonObject("desired");
		JsonObject o = new JsonObject();
		switch (op.get("kind").getAsString()) {
			case "set_type": o.add("projection", d.get("projection")); break;
			case "set_comment_segment": o.add("segment", d.get("segment")); break;
			case "create_function": o.addProperty("exists", true); break;
			case "set_function_body": o.add("body", d.get("body")); break;
			case "set_function_name":
				o.add("name", d.get("name"));
				o.addProperty("source", "IMPORTED");
				break;
			case "set_function_signature":
				o.add("signature", d.get("signature"));
				o.addProperty("source", "IMPORTED");
				break;
		}
		return o;
	}

	static String stateKey(JsonObject op) {
		JsonObject t = op.getAsJsonObject("target");
		switch (op.get("kind").getAsString()) {
			case "set_type": return "type:" + t.get("type_path").getAsString();
			case "set_comment_segment":
				return "comment:" + t.get("address_rva").getAsString() + ":" + t.get("kind").getAsString() + ":"
					+ t.get("segment_id").getAsString();
			case "create_function":
			case "set_function_body": return "function:" + t.get("entry_rva").getAsString() + ":body";
			case "set_function_name": return "function:" + t.get("entry_rva").getAsString() + ":name";
			default: return "function:" + t.get("entry_rva").getAsString() + ":signature";
		}
	}

	void checkPlan(JsonObject plan) throws Exception {
		if (!PLAN_SCHEMA.equals(plan.has("schema") ? plan.get("schema").getAsString() : null)) {
			throw new Refused("unknown plan schema");
		}
		JsonObject unsigned = plan.deepCopy();
		unsigned.remove("plan_sha256");
		if (!plan.has("plan_sha256") || !digest(unsigned).equals(plan.get("plan_sha256").getAsString())) {
			throw new Refused("plan digest does not match its content");
		}
		if (!plan.get("status").getAsString().equals("ready") && !plan.get("status").getAsString().equals("noop")) {
			throw new Refused("plan status is " + plan.get("status").getAsString() + ", not ready");
		}
		JsonObject want = plan.getAsJsonObject("target"), have = programIdentity();
		for (String k : List.of("executable_sha256", "image_base", "address_space", "pointer_size", "language_id",
			"compiler_spec_id")) {
			if (!want.has(k) || !want.get(k).getAsString().equals(have.get(k).getAsString())) {
				throw new Refused("wrong target: " + k + " is " + have.get(k) + ", the plan is for " + want.get(k));
			}
		}
		JsonObject baseline = optionJson(BASELINE), state = optionJson(STATE);
		String b = baseline == null ? null : digest(baseline), s = state == null ? null : digest(state);
		if (!String.valueOf(b).equals(plan.get("baseline_sha256").isJsonNull() ? "null" : plan.get("baseline_sha256").getAsString())) {
			throw new Refused("stale plan: the program's baseline record changed since planning");
		}
		if (!String.valueOf(s).equals(plan.get("state_sha256").isJsonNull() ? "null" : plan.get("state_sha256").getAsString())) {
			throw new Refused("stale plan: the program's managed-state record changed since planning");
		}
		if (plan.getAsJsonArray("conflicts").size() != 0 || plan.getAsJsonArray("unsupported").size() != 0) {
			throw new Refused("plan carries conflicts or unsupported results");
		}
		int last = -1;
		for (JsonElement e : plan.getAsJsonArray("operations")) {
			JsonObject op = e.getAsJsonObject();
			int rank = ORDER.indexOf(op.get("kind").getAsString());
			if (rank < 0) {
				throw new Refused("unknown operation kind " + op.get("kind"));
			}
			if (rank < last) {
				throw new Refused("operations are not in dependency order");
			}
			last = rank;
			JsonObject id = new JsonObject();
			for (String k : List.of("kind", "target", "expected", "desired", "provenance")) {
				id.add(k, op.get(k));
			}
			if (!digest(id).equals(op.get("operation_id").getAsString())) {
				throw new Refused("operation id does not match its content: " + op.get("operation_id"));
			}
			JsonObject prov = op.getAsJsonObject("provenance");
			if (!prov.get("review").getAsString().equals("accepted")
				|| prov.get("status").getAsString().equals("hypothesis")) {
				throw new Refused("operation " + op.get("operation_id").getAsString() + " is not an accepted fact");
			}
			JsonObject t = op.getAsJsonObject("target");
			if (!t.get("executable_sha256").getAsString().equals(currentProgram.getExecutableSHA256())) {
				throw new Refused("operation bound to another executable");
			}
			if (op.get("kind").getAsString().equals("set_comment_segment")
				&& !SEGMENT_ID.matcher(t.get("segment_id").getAsString()).matches()) {
				throw new Refused("malformed segment id");
			}
		}
	}

	JsonObject curatedState(JsonObject scope) throws Exception {
		JsonObject o = new JsonObject();
		JsonObject fns = new JsonObject();
		for (JsonElement e : scope.getAsJsonArray("functions")) {
			Function f = currentProgram.getFunctionManager().getFunctionAt(addr(e.getAsString()));
			if (f == null) {
				fns.add(e.getAsString(), JsonNull.INSTANCE);
				continue;
			}
			JsonObject x = new JsonObject();
			x.add("name", nameProjection(f));
			x.add("body", ranges(f.getBody()));
			x.add("signature", signatureProjection(f));
			fns.add(e.getAsString(), x);
		}
		o.add("functions", fns);
		JsonObject types = new JsonObject();
		for (JsonElement e : scope.getAsJsonArray("types")) {
			JsonObject p = typeProjection(managedType(e.getAsString()));
			types.add(e.getAsString(), p == null ? JsonNull.INSTANCE : p);
		}
		o.add("types", types);
		JsonObject comments = new JsonObject();
		for (JsonElement e : scope.getAsJsonArray("comments")) {
			JsonObject c = e.getAsJsonObject();
			String text = comment(c.get("address_rva").getAsString(), c.get("kind").getAsString());
			comments.add(c.get("address_rva").getAsString() + ":" + c.get("kind").getAsString(),
				text == null ? JsonNull.INSTANCE : new JsonPrimitive(text));
		}
		o.add("comments", comments);
		JsonObject state = optionJson(STATE);
		o.add("state", state == null ? JsonNull.INSTANCE : state);
		return o;
	}

	JsonObject apply(JsonObject plan, int failAfter) throws Exception {
		JsonObject result = new JsonObject();
		result.addProperty("schema", "re-metadata-apply-result/1");
		result.add("plan_sha256", plan.get("plan_sha256"));
		JsonArray opResults = new JsonArray();
		result.add("operations", opResults);
		JsonObject before = curatedState(plan.getAsJsonObject("scope"));
		result.addProperty("before_sha256", digest(before));
		List<JsonObject> ops = new ArrayList<>();
		for (JsonElement e : plan.getAsJsonArray("operations")) {
			ops.add(e.getAsJsonObject());
		}
		// Every precondition, before any write.
		for (JsonObject op : ops) {
			JsonElement current = currentValue(op);
			if (!canon(current).equals(canon(op.get("expected")))) {
				throw new Refused("stale plan: " + op.get("kind").getAsString() + " " + op.get("target")
					+ " is now " + canon(current));
			}
			if (op.get("kind").getAsString().equals("set_function_name")) {
				checkNameEvidence(op, currentProgram.getFunctionManager()
					.getFunctionAt(addr(op.getAsJsonObject("target").get("entry_rva").getAsString())));
			}
		}
		JsonObject state = optionJson(STATE);
		if (state == null) {
			state = new JsonObject();
			state.addProperty("schema", "re-metadata-state/1");
			state.add("fields", new JsonObject());
		}
		int tx = currentProgram.startTransaction("re_metadata apply " + plan.get("plan_sha256").getAsString());
		boolean commit = false;
		int done = 0;
		try {
			List<JsonObject> types = new ArrayList<>();
			for (JsonObject op : ops) {
				if (op.get("kind").getAsString().equals("set_type")) {
					types.add(op);
				}
			}
			if (!types.isEmpty()) {
				applyTypes(types);
			}
			for (JsonObject op : ops) {
				String kind = op.get("kind").getAsString();
				JsonObject t = op.getAsJsonObject("target");
				if (!kind.equals("set_type")) {
					Address entry = t.has("entry_rva") ? addr(t.get("entry_rva").getAsString()) : null;
					Function f = entry == null ? null : currentProgram.getFunctionManager().getFunctionAt(entry);
					if (f == null && !kind.equals("create_function") && !kind.equals("set_comment_segment")) {
						throw new Refused("no function at " + t.get("entry_rva").getAsString());
					}
					switch (kind) {
						case "create_function":
						case "set_function_body": applyBody(op, f, entry); break;
						case "set_function_name": applyName(op, f); break;
						case "set_function_signature": applySignature(op, f); break;
						case "set_comment_segment":
							String rvaText = t.get("address_rva").getAsString(), ck = t.get("kind").getAsString();
							JsonElement v = op.getAsJsonObject("desired").get("segment");
							String text = withSegment(comment(rvaText, ck), t.get("segment_id").getAsString(),
								v.isJsonNull() ? null : v.getAsString());
							currentProgram.getListing().setComment(addr(rvaText), commentType(ck), text);
							break;
					}
				}
				done++;
				if (failAfter >= 0 && done >= failAfter) {
					throw new IllegalStateException("injected failure after " + done + " operation(s)");
				}
			}
			// Verify every write, then record what is now managed.
			JsonObject fields = state.getAsJsonObject("fields");
			for (JsonObject op : ops) {
				JsonElement now = currentValue(op), want = achieved(op, now);
				JsonObject r = new JsonObject();
				r.add("operation_id", op.get("operation_id"));
				r.addProperty("kind", op.get("kind").getAsString());
				JsonElement managedValue = want;
				if (op.get("kind").getAsString().equals("create_function")) {
					Function made = currentProgram.getFunctionManager()
						.getFunctionAt(addr(op.getAsJsonObject("target").get("entry_rva").getAsString()));
					JsonObject body = new JsonObject();
					body.add("body", op.getAsJsonObject("desired").get("body"));
					JsonObject have = new JsonObject();
					have.add("body", made == null ? JsonNull.INSTANCE : ranges(made.getBody()));
					if (!canon(have).equals(canon(body))) {
						throw new Refused("verification failed for create_function: got " + canon(have));
					}
					managedValue = body;
				}
				if (!canon(now).equals(canon(want))) {
					throw new Refused("verification failed for " + op.get("kind").getAsString() + " " + op.get("target")
						+ ": wanted " + canon(want) + ", got " + canon(now));
				}
				r.addProperty("result", "changed");
				opResults.add(r);
				String key = stateKey(op);
				JsonObject prior = fields.has(key) ? fields.getAsJsonObject(key) : null;
				JsonObject rec = new JsonObject();
				rec.addProperty("digest", digest(managedValue));
				rec.add("plan_sha256", plan.get("plan_sha256"));
				rec.addProperty("provenance_sha256", digest(op.get("provenance")));
				rec.add("provenance", op.get("provenance"));
				rec.add("original", prior != null && prior.has("original") ? prior.get("original") : op.get("expected"));
				fields.add(key, rec);
			}
			if (!ops.isEmpty()) {
				state.add("metadata_sha256", plan.get("metadata_sha256"));
				state.add("recipe_sha256", plan.get("recipe_sha256"));
				state.add("last_plan_sha256", plan.get("plan_sha256"));
				currentProgram.getOptions(OPTIONS).setString(STATE, canon(state));
			}
			commit = true;
		}
		catch (Exception ex) {
			result.addProperty("status", "rolled_back");
			result.addProperty("error", ex.getClass().getSimpleName() + ": " + ex.getMessage());
			result.addProperty("applied_before_failure", done);
		}
		finally {
			// An aborted nested transaction rolls back the whole script transaction.
			currentProgram.endTransaction(tx, commit);
		}
		result.addProperty("changed", commit ? ops.size() : 0);
		result.addProperty("noop", plan.getAsJsonArray("noops").size());
		if (commit) {
			result.addProperty("status", ops.isEmpty() ? "noop" : "committed");
			result.addProperty("after_sha256", digest(curatedState(plan.getAsJsonObject("scope"))));
		}
		else {
			// In-memory state is restored when the script transaction ends; report the precondition digest.
			result.addProperty("after_sha256", result.get("before_sha256").getAsString());
		}
		return result;
	}

	JsonObject selftest(JsonObject vectors) throws Exception {
		JsonObject out = new JsonObject();
		JsonObject names = new JsonObject();
		for (JsonElement e : vectors.getAsJsonArray("names")) {
			JsonObject r = new JsonObject();
			r.addProperty("placeholder", placeholder(e.getAsString()));
			JsonArray q = new JsonArray();
			for (String s : qualified(e.getAsString())) {
				q.add(s);
			}
			r.add("qualified", q);
			names.add(e.getAsString(), r);
		}
		out.add("names", names);
		JsonArray canons = new JsonArray();
		for (JsonElement e : vectors.getAsJsonArray("canonical")) {
			canons.add(canon(e) + " " + digest(e));
		}
		out.add("canonical", canons);
		JsonArray segs = new JsonArray();
		for (JsonElement e : vectors.getAsJsonArray("segments")) {
			JsonObject v = e.getAsJsonObject();
			String text = v.get("text").isJsonNull() ? null : v.get("text").getAsString();
			String value = v.get("value").isJsonNull() ? null : v.get("value").getAsString();
			JsonObject r = new JsonObject();
			try {
				String seg = segmentText(text, v.get("id").getAsString());
				String now = withSegment(text, v.get("id").getAsString(), value);
				r.add("segment", seg == null ? JsonNull.INSTANCE : new JsonPrimitive(seg));
				r.add("result", now == null ? JsonNull.INSTANCE : new JsonPrimitive(now));
			}
			catch (Refused ex) {
				r.addProperty("error", "malformed");
			}
			segs.add(r);
		}
		out.add("segments", segs);
		JsonArray rows = new JsonArray();
		for (JsonElement e : vectors.getAsJsonArray("csv")) {
			JsonArray r = new JsonArray();
			for (List<String> row : csv(e.getAsString())) {
				JsonArray cells = new JsonArray();
				for (String c : row) {
					cells.add(c);
				}
				r.add(cells);
			}
			rows.add(r);
		}
		out.add("csv", rows);
		return out;
	}

	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		base = currentProgram.getImageBase().getOffset();
		if (args.length == 3 && args[0].equals("selftest")) {
			writeJson(args[2], selftest(readJson(args[1]).getAsJsonObject()));
			return;
		}
		if (args.length < 4 || args.length > 5 || !args[0].equals("apply")) {
			throw new IllegalArgumentException(
				"usage: apply <plan.json> <evidence_root> <result.json> [fail-after=N] | selftest <in> <out>");
		}
		evidenceRoot = args[2];
		int failAfter = -1;
		if (args.length == 5) {
			if (!args[4].startsWith("fail-after=")) {
				throw new IllegalArgumentException("unknown option " + args[4]);
			}
			failAfter = Integer.parseInt(args[4].substring("fail-after=".length()));
		}
		JsonObject result;
		try {
			JsonElement parsed = readJson(args[1]);
			if (!parsed.isJsonObject()) {
				throw new Refused("plan is not a JSON object");
			}
			JsonObject plan = parsed.getAsJsonObject();
			checkPlan(plan);
			result = apply(plan, failAfter);
		}
		catch (Refused | RuntimeException ex) {
			result = new JsonObject();
			result.addProperty("schema", "re-metadata-apply-result/1");
			result.addProperty("status", "refused");
			result.addProperty("error", ex.getClass().getSimpleName() + ": " + ex.getMessage());
			result.addProperty("changed", 0);
		}
		writeJson(args[3], result);
		println("apply_metadata: " + result.get("status").getAsString());
	}
}
