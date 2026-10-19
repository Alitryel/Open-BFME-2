// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z
// partial score=0.95 date=2026-10-19
// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z = GameLogic::setSawCRCMismatch (WB twin 0xD0CA20), retail 0x2401DD 1424 B.
// Compact bank: compile as Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp (its // cl: line and
// contents) followed by the declarations and body below; RecorderClass needs 'friend class GameLogic;'.
// Stock shim: 1425 B; with a ZH-style str() TheNullChr fallback: 1423 B (see the log entry).
// --- extras.inc ---

class ScriptActions
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e();
	virtual void closeWindows(bool suppressNewWindows);                  // +0x3C
};
extern ScriptActions *TheScriptActions;

class Rva002036B4GlobalCopier
{
public:
	void apply(void);
};

void Rva00437E84(int type, const UnicodeString &title, const UnicodeString &text);
File *createMemoryReadFile(char *buffer, int size);
bool Rva0060DFB5(File *input, File *output);

extern "C" __declspec(dllimport) int __stdcall GetComputerNameA(char *buffer, unsigned long *size);

extern bool g_fakeDesync;
extern bool TheBinaryDeepCRC;

// --- body_r1.inc ---
void GameLogic::rva002401DD(BfmeThingEC *stream, unsigned int frame, int player)
{
	m_71 = true;
	if (ignoreCRCMismatches && g_value12A6F38 != m_40)
		return;
	if (!m_1bc)
	{
		m_1bc = true;
		TheRecorder->logCRCMismatch();
		TheScriptActions->closeWindows(true);
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			Rva00437E84(4, TheGameText->fetch("GUI:DesyncTitle"), TheGameText->fetch("GUI:DesyncText"));
		m_1b8 = 0;
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	}
	if (!stream)
		return;
	{
		const char *map = ((const StringBase<char> &)TheWritableGlobalData->m_mapName).reverseFind('\\');
		if (!map)
			map = "";
		else
			++map;

		AsciiString playerName = ThePlayerList->getLocalPlayer()->m_4c;
		if (playerName.isEmpty())
		{
			char computerName[256] = { 0 };
			unsigned long size = 256;
			GetComputerNameA(computerName, &size);
			playerName = computerName;
		}

		AsciiString frameName;
		if (stream->m_04.str())
			frameName.format("Frame%s", stream->m_04.str());
		else
			frameName.format("Frame%d", frame);

		AsciiString filename;
		if (frame > 0)
			filename.format("DESYNC-%s-%s-%s.txt", frameName.str(), map, playerName.str());
		else
			filename.format("DESYNC-%s-%s.txt", map, playerName.str());

		File *output = TheFileSystem->openFile(filename.str(), 0x2a, 0);
		if (!output)
			return;

		int size;
		char *buffer = (char *)stream->bfmeTakeEC(&size);
		File *input = createMemoryReadFile(buffer, size);
		if (!input)
			return;

		AsciiString text;
		if (frame > 0)
		{
			if (g_fakeDesync)
				text.format("*** Frame #%d -- THIS IS A FAKE DESYNC THAT WAS TRIGGERED INTENTIONALLY BY THIS PLAYER! IGNORE!\n\n", frame);
			else if (g_value12A6F38 == m_40)
				text.format("*** Frame #%d -- THIS IS A FORCED DESYNC TRIGGERED ON FRAME %d USING COMMANDLINE -forceDesyncOnFrame %d! IGNORE!!!!\n\n", frame, m_40);
			else
				text.format("Frame #%d\n\n", frame);
			output->write(text.str(), text.getLength());
		}
		text = m_54;
		output->write(text.str(), text.getLength());
		for (unsigned int i = 0; i < m_58.size(); ++i)
		{
			text = rva0023FB58(i);
			output->write(text.str(), text.getLength());
		}
		text = m_64;
		output->write(text.str(), text.getLength());
		text = m_68;
		output->write(text.str(), text.getLength());
		text.format("\n");
		output->write(text.str(), text.getLength());
		text.format("\n--------------------------------------------------------\nREPLAY FILE\n---------------------------------------------------------\n");
		output->write(text.str(), text.getLength());
		TheRecorder->dumpCommandHistory((CommandDumpFile0037BE15 *)output, frame);
		text.format("---------------------------------------------------------\n\n");
		output->write(text.str(), text.getLength());
		Rva0060DFB5(input, output);
		input->close();
		output->close();
		if (TheBinaryDeepCRC)
		{
			if (frame > 0)
				filename.format("BIN_DESYNC-%s-%s-%s.bin", frameName.str(), map, playerName.str());
			else
				filename.format("BIN_DESYNC-%s-%s.bin", map, playerName.str());
			File *binFile = TheFileSystem->openFile(filename.str(), 0x4a, 0);
			if (!binFile)
				return;
			binFile->write(buffer, size);
			binFile->close();
		}
		free(buffer);
	}
}
