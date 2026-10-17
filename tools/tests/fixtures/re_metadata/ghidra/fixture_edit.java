// Test-only: simulate analyst edits in a private fixture project for
// tools/tests/test_re_metadata.py (stale plans, collisions, unmanaged text).
//   -postScript fixture_edit.java <edits.json>
// edits.json is a list of {"op": "rename"|"label"|"comment"|"struct", ...}.
//@category Test
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.CategoryPath;
import ghidra.program.model.data.DataTypeConflictHandler;
import ghidra.program.model.data.IntegerDataType;
import ghidra.program.model.data.StructureDataType;
import ghidra.program.model.listing.CommentType;
import ghidra.program.model.symbol.SourceType;

public class fixture_edit extends GhidraScript {
	@Override
	public void run() throws Exception {
		long base = currentProgram.getImageBase().getOffset();
		String text = Files.readString(new File(getScriptArgs()[0]).toPath(), StandardCharsets.UTF_8);
		for (JsonElement e : JsonParser.parseString(text).getAsJsonArray()) {
			JsonObject o = e.getAsJsonObject();
			String op = o.get("op").getAsString();
			Address a = o.has("rva") ? toAddr(base + Long.decode(o.get("rva").getAsString())) : null;
			switch (op) {
				case "rename":
					getFunctionAt(a).setName(o.get("name").getAsString(), SourceType.USER_DEFINED);
					break;
				case "label":
					createLabel(a, o.get("name").getAsString(), true, SourceType.USER_DEFINED);
					break;
				case "comment":
					CommentType kind = CommentType.valueOf(o.get("kind").getAsString().toUpperCase());
					currentProgram.getListing().setComment(a, kind,
						o.get("text").isJsonNull() ? null : o.get("text").getAsString());
					break;
				case "struct":
					String path = o.get("path").getAsString();
					int slash = path.lastIndexOf('/');
					StructureDataType s = new StructureDataType(new CategoryPath(path.substring(0, slash)),
						path.substring(slash + 1), 0);
					s.add(IntegerDataType.dataType, "unmanaged", null);
					currentProgram.getDataTypeManager().addDataType(s, DataTypeConflictHandler.KEEP_HANDLER);
					break;
				default:
					throw new IllegalArgumentException("unknown edit " + op);
			}
		}
		println("fixture_edit: done");
	}
}
