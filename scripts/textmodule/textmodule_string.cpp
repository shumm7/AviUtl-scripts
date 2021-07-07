#include <iostream>
#include <windows.h>
#include <string>

std::string WstrToStr(std::wstring str) {
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, str.c_str(), -1, (char*)NULL, 0, NULL, NULL);
	CHAR* cpMultiByte = new CHAR[iBufferSize];

	WideCharToMultiByte(CP_OEMCP, 0, str.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

	delete[] cpMultiByte;
	return(oRet);
}

std::wstring StrToWstr(std::string str) {
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, cpUCS2, iBufferSize);
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	delete[] cpUCS2;
	return(oRet);
}

std::wstring _jreplace(std::wstring String1, std::wstring String2, std::wstring String3, bool invert)
{
	if (invert) {
		auto temp = String3;
		String3 = String2;
		String2 = temp;
	}

	std::string::size_type  Pos(String1.find(String2));

	while (Pos != std::string::npos)
	{
		String1.replace(Pos, String2.length(), String3);
		Pos = String1.find(String2, Pos + String3.length());
	}

	return String1;
}

unsigned long long UnicodeToUTF8(unsigned long long code) {

	std::string bin;
	unsigned int mask = (int)1 << (sizeof(unsigned int) * CHAR_BIT - 1);
	do bin += (mask & code ? '1' : '0');
	while (mask >>= 1);
	int m = bin.size();

	std::string ret;

	if (0x0000 <= code && code <= 0x007F) {
		ret = "0" + bin.substr(m - 7, 7);
	}
	else if (0x0080 <= code && code <= 0x07FF) {
		ret = "110" + bin.substr(m - 11, 5) + "10" + bin.substr(m - 6, 6);
	}
	else if (0x0890 <= code && code <= 0xFFFF) {
		ret = "1110" + bin.substr(m - 16, 4) + "10" + bin.substr(m - 12, 6) + "10" + bin.substr(m - 6, 6);
	}
	else if (0x10000 <= code && code <= 0x10FFFF) {
		ret = "11110" + bin.substr(m - 21, 3) + "10" + bin.substr(m - 18, 6) + "10" + bin.substr(m - 12, 6) + "10" + bin.substr(m - 6, 6);
	}
	else {
		return -1;
	}

	return std::stoull(ret, 0, 2);
}

unsigned long long UTF8ToUnicode(unsigned long long code) {

	std::string bin;
	unsigned int mask = (int)1 << (sizeof(unsigned int) * CHAR_BIT - 1);
	do bin += (mask & code ? '1' : '0');
	while (mask >>= 1);
	int m = bin.size();

	std::string ret;

	if (0x0000 <= code && code <= 0x007F) { //U+0000 - U+007F
		ret = bin.substr(m - 7, 7);
	}
	else if (0x0080 <= code && code <= 0xDFBF) { //U+0080 - U+07FF
		ret = bin.substr(m - 13, 5) + bin.substr(m - 6, 6);
	}
	else if (0xE08080 <= code && code <= 0xEFBFBF) { //U+0800 - U+FFFF
		ret = bin.substr(m - 20, 4) + bin.substr(m - 14, 6) + bin.substr(m - 6, 6);
	}
	else if (0xF0808080 <= code && code <= 0xF7BFBFBF) { //U+10000 - U+10FFFF
		ret = bin.substr(m - 27, 3) + bin.substr(m - 22, 6) + bin.substr(m - 14, 6) + bin.substr(m - 6, 6);
	}
	else {
		return -1;
	}

	return std::stoull(ret, 0, 2);
}

std::wstring toKatakana(std::wstring string, bool invert)
{
	string = _jreplace(string, L"Çü", L"É@", invert);
	string = _jreplace(string, L"Ç†", L"ÉA", invert);
	string = _jreplace(string, L"Ç°", L"ÉB", invert);
	string = _jreplace(string, L"Ç¢", L"ÉC", invert);
	string = _jreplace(string, L"Ç£", L"ÉD", invert);
	string = _jreplace(string, L"Ç§", L"ÉE", invert);
	string = _jreplace(string, L"Ç•", L"ÉF", invert);
	string = _jreplace(string, L"Ç¶", L"ÉG", invert);
	string = _jreplace(string, L"Çß", L"ÉH", invert);
	string = _jreplace(string, L"Ç®", L"ÉI", invert);
	string = _jreplace(string, L"Ç©", L"ÉJ", invert);
	string = _jreplace(string, L"Ç™", L"ÉK", invert);
	string = _jreplace(string, L"Ç´", L"ÉL", invert);
	string = _jreplace(string, L"Ç¨", L"ÉM", invert);
	string = _jreplace(string, L"Ç≠", L"ÉN", invert);
	string = _jreplace(string, L"ÇÆ", L"ÉO", invert);
	string = _jreplace(string, L"ÇØ", L"ÉP", invert);
	string = _jreplace(string, L"Ç∞", L"ÉQ", invert);
	string = _jreplace(string, L"Ç±", L"ÉR", invert);
	string = _jreplace(string, L"Ç≤", L"ÉS", invert);
	string = _jreplace(string, L"Ç≥", L"ÉT", invert);
	string = _jreplace(string, L"Ç¥", L"ÉU", invert);
	string = _jreplace(string, L"Çµ", L"ÉV", invert);
	string = _jreplace(string, L"Ç∂", L"ÉW", invert);
	string = _jreplace(string, L"Ç∑", L"ÉX", invert);
	string = _jreplace(string, L"Ç∏", L"ÉY", invert);
	string = _jreplace(string, L"Çπ", L"ÉZ", invert);
	string = _jreplace(string, L"Ç∫", L"É[", invert);
	string = _jreplace(string, L"Çª", L"É\", invert);
	string = _jreplace(string, L"Çº", L"É]", invert);
	string = _jreplace(string, L"ÇΩ", L"É^", invert);
	string = _jreplace(string, L"Çæ", L"É_", invert);
	string = _jreplace(string, L"Çø", L"É`", invert);
	string = _jreplace(string, L"Ç¿", L"Éa", invert);
	string = _jreplace(string, L"Ç¡", L"Éb", invert);
	string = _jreplace(string, L"Ç¬", L"Éc", invert);
	string = _jreplace(string, L"Ç√", L"Éd", invert);
	string = _jreplace(string, L"Çƒ", L"Ée", invert);
	string = _jreplace(string, L"Ç≈", L"Éf", invert);
	string = _jreplace(string, L"Ç∆", L"Ég", invert);
	string = _jreplace(string, L"Ç«", L"Éh", invert);
	string = _jreplace(string, L"Ç»", L"Éi", invert);
	string = _jreplace(string, L"Ç…", L"Éj", invert);
	string = _jreplace(string, L"Ç ", L"Ék", invert);
	string = _jreplace(string, L"ÇÀ", L"Él", invert);
	string = _jreplace(string, L"ÇÃ", L"Ém", invert);
	string = _jreplace(string, L"ÇÕ", L"Én", invert);
	string = _jreplace(string, L"ÇŒ", L"Éo", invert);
	string = _jreplace(string, L"Çœ", L"Ép", invert);
	string = _jreplace(string, L"Ç–", L"Éq", invert);
	string = _jreplace(string, L"Ç—", L"Ér", invert);
	string = _jreplace(string, L"Ç“", L"És", invert);
	string = _jreplace(string, L"Ç”", L"Ét", invert);
	string = _jreplace(string, L"Ç‘", L"Éu", invert);
	string = _jreplace(string, L"Ç’", L"Év", invert);
	string = _jreplace(string, L"Ç÷", L"Éw", invert);
	string = _jreplace(string, L"Ç◊", L"Éx", invert);
	string = _jreplace(string, L"Çÿ", L"Éy", invert);
	string = _jreplace(string, L"ÇŸ", L"Éz", invert);
	string = _jreplace(string, L"Ç⁄", L"É{", invert);
	string = _jreplace(string, L"Ç€", L"É|", invert);
	string = _jreplace(string, L"Ç‹", L"É}", invert);
	string = _jreplace(string, L"Ç›", L"É~", invert);
	string = _jreplace(string, L"Çﬁ", L"ÉÄ", invert);
	string = _jreplace(string, L"Çﬂ", L"ÉÅ", invert);
	string = _jreplace(string, L"Ç‡", L"ÉÇ", invert);
	string = _jreplace(string, L"Ç·", L"ÉÉ", invert);
	string = _jreplace(string, L"Ç‚", L"ÉÑ", invert);
	string = _jreplace(string, L"Ç„", L"ÉÖ", invert);
	string = _jreplace(string, L"Ç‰", L"ÉÜ", invert);
	string = _jreplace(string, L"ÇÂ", L"Éá", invert);
	string = _jreplace(string, L"ÇÊ", L"Éà", invert);
	string = _jreplace(string, L"ÇÁ", L"Éâ", invert);
	string = _jreplace(string, L"ÇË", L"Éä", invert);
	string = _jreplace(string, L"ÇÈ", L"Éã", invert);
	string = _jreplace(string, L"ÇÍ", L"Éå", invert);
	string = _jreplace(string, L"ÇÎ", L"Éç", invert);
	string = _jreplace(string, L"ÇÏ", L"Éé", invert);
	string = _jreplace(string, L"ÇÌ", L"Éè", invert);
	string = _jreplace(string, L"Ç", L"Éí", invert);
	string = _jreplace(string, L"ÇÒ", L"Éì", invert);
	string = _jreplace(string, L"ÇÓ", L"Éê", invert);
	string = _jreplace(string, L"ÇÔ", L"Éë", invert);

	return string;
}

std::wstring toHalfwidth(std::wstring string, bool invert, bool space) {
	string = _jreplace(string, L"ÇO", L"0", invert);
	string = _jreplace(string, L"ÇP", L"1", invert);
	string = _jreplace(string, L"ÇQ", L"2", invert);
	string = _jreplace(string, L"ÇR", L"3", invert);
	string = _jreplace(string, L"ÇS", L"4", invert);
	string = _jreplace(string, L"ÇT", L"5", invert);
	string = _jreplace(string, L"ÇU", L"6", invert);
	string = _jreplace(string, L"ÇV", L"7", invert);
	string = _jreplace(string, L"ÇW", L"8", invert);
	string = _jreplace(string, L"ÇX", L"9", invert);

	string = _jreplace(string, L"Ç`", L"A", invert);
	string = _jreplace(string, L"Ça", L"B", invert);
	string = _jreplace(string, L"Çb", L"C", invert);
	string = _jreplace(string, L"Çc", L"D", invert);
	string = _jreplace(string, L"Çd", L"E", invert);
	string = _jreplace(string, L"Çe", L"F", invert);
	string = _jreplace(string, L"Çf", L"G", invert);
	string = _jreplace(string, L"Çg", L"H", invert);
	string = _jreplace(string, L"Çh", L"I", invert);
	string = _jreplace(string, L"Çi", L"J", invert);
	string = _jreplace(string, L"Çj", L"K", invert);
	string = _jreplace(string, L"Çk", L"L", invert);
	string = _jreplace(string, L"Çl", L"M", invert);
	string = _jreplace(string, L"Çm", L"N", invert);
	string = _jreplace(string, L"Çn", L"O", invert);
	string = _jreplace(string, L"Ço", L"P", invert);
	string = _jreplace(string, L"Çp", L"Q", invert);
	string = _jreplace(string, L"Çq", L"R", invert);
	string = _jreplace(string, L"Çr", L"S", invert);
	string = _jreplace(string, L"Çs", L"T", invert);
	string = _jreplace(string, L"Çt", L"U", invert);
	string = _jreplace(string, L"Çu", L"V", invert);
	string = _jreplace(string, L"Çv", L"W", invert);
	string = _jreplace(string, L"Çw", L"X", invert);
	string = _jreplace(string, L"Çx", L"Y", invert);
	string = _jreplace(string, L"Çy", L"Z", invert);

	string = _jreplace(string, L"ÇÅ", L"a", invert);
	string = _jreplace(string, L"ÇÇ", L"b", invert);
	string = _jreplace(string, L"ÇÉ", L"c", invert);
	string = _jreplace(string, L"ÇÑ", L"d", invert);
	string = _jreplace(string, L"ÇÖ", L"e", invert);
	string = _jreplace(string, L"ÇÜ", L"f", invert);
	string = _jreplace(string, L"Çá", L"g", invert);
	string = _jreplace(string, L"Çà", L"h", invert);
	string = _jreplace(string, L"Çâ", L"i", invert);
	string = _jreplace(string, L"Çä", L"j", invert);
	string = _jreplace(string, L"Çã", L"k", invert);
	string = _jreplace(string, L"Çå", L"l", invert);
	string = _jreplace(string, L"Çç", L"m", invert);
	string = _jreplace(string, L"Çé", L"n", invert);
	string = _jreplace(string, L"Çè", L"o", invert);
	string = _jreplace(string, L"Çê", L"p", invert);
	string = _jreplace(string, L"Çë", L"q", invert);
	string = _jreplace(string, L"Çí", L"r", invert);
	string = _jreplace(string, L"Çì", L"s", invert);
	string = _jreplace(string, L"Çî", L"t", invert);
	string = _jreplace(string, L"Çï", L"u", invert);
	string = _jreplace(string, L"Çñ", L"v", invert);
	string = _jreplace(string, L"Çó", L"w", invert);
	string = _jreplace(string, L"Çò", L"x", invert);
	string = _jreplace(string, L"Çô", L"y", invert);
	string = _jreplace(string, L"Çö", L"z", invert);

	string = _jreplace(string, L"ÉA", L"±", invert);
	string = _jreplace(string, L"ÉC", L"≤", invert);
	string = _jreplace(string, L"ÉE", L"≥", invert);
	string = _jreplace(string, L"ÉG", L"¥", invert);
	string = _jreplace(string, L"ÉI", L"µ", invert);
	string = _jreplace(string, L"ÉJ", L"∂", invert);
	string = _jreplace(string, L"ÉL", L"∑", invert);
	string = _jreplace(string, L"ÉN", L"∏", invert);
	string = _jreplace(string, L"ÉP", L"π", invert);
	string = _jreplace(string, L"ÉR", L"∫", invert);
	string = _jreplace(string, L"ÉT", L"ª", invert);
	string = _jreplace(string, L"ÉV", L"º", invert);
	string = _jreplace(string, L"ÉX", L"Ω", invert);
	string = _jreplace(string, L"ÉZ", L"æ", invert);
	string = _jreplace(string, L"É\", L"ø", invert);
	string = _jreplace(string, L"É^", L"¿", invert);
	string = _jreplace(string, L"É`", L"¡", invert);
	string = _jreplace(string, L"Éc", L"¬", invert);
	string = _jreplace(string, L"Ée", L"√", invert);
	string = _jreplace(string, L"Ég", L"ƒ", invert);
	string = _jreplace(string, L"Éi", L"≈", invert);
	string = _jreplace(string, L"Éj", L"∆", invert);
	string = _jreplace(string, L"Ék", L"«", invert);
	string = _jreplace(string, L"Él", L"»", invert);
	string = _jreplace(string, L"Ém", L"…", invert);
	string = _jreplace(string, L"Én", L" ", invert);
	string = _jreplace(string, L"Éq", L"À", invert);
	string = _jreplace(string, L"Ét", L"Ã", invert);
	string = _jreplace(string, L"Éw", L"Õ", invert);
	string = _jreplace(string, L"Éz", L"Œ", invert);
	string = _jreplace(string, L"É}", L"œ", invert);
	string = _jreplace(string, L"É~", L"–", invert);
	string = _jreplace(string, L"ÉÄ", L"—", invert);
	string = _jreplace(string, L"ÉÅ", L"“", invert);
	string = _jreplace(string, L"ÉÇ", L"”", invert);
	string = _jreplace(string, L"ÉÑ", L"‘", invert);
	string = _jreplace(string, L"ÉÜ", L"’", invert);
	string = _jreplace(string, L"Éà", L"÷", invert);
	string = _jreplace(string, L"Éâ", L"◊", invert);
	string = _jreplace(string, L"Éä", L"ÿ", invert);
	string = _jreplace(string, L"Éã", L"Ÿ", invert);
	string = _jreplace(string, L"Éå", L"⁄", invert);
	string = _jreplace(string, L"Éç", L"€", invert);
	string = _jreplace(string, L"Éè", L"‹", invert);
	string = _jreplace(string, L"Éí", L"¶", invert);
	string = _jreplace(string, L"Éì", L"›", invert);
	string = _jreplace(string, L"Éî", L"≥ﬁ", invert);
	string = _jreplace(string, L"ÉK", L"∂ﬁ", invert);
	string = _jreplace(string, L"ÉM", L"∑ﬁ", invert);
	string = _jreplace(string, L"ÉO", L"∏ﬁ", invert);
	string = _jreplace(string, L"ÉQ", L"πﬁ", invert);
	string = _jreplace(string, L"ÉS", L"∫ﬁ", invert);
	string = _jreplace(string, L"ÉU", L"ªﬁ", invert);
	string = _jreplace(string, L"ÉW", L"ºﬁ", invert);
	string = _jreplace(string, L"ÉY", L"Ωﬁ", invert);
	string = _jreplace(string, L"É[", L"æﬁ", invert);
	string = _jreplace(string, L"É]", L"øﬁ", invert);
	string = _jreplace(string, L"É_", L"¿ﬁ", invert);
	string = _jreplace(string, L"Éa", L"¡ﬁ", invert);
	string = _jreplace(string, L"Éd", L"¬ﬁ", invert);
	string = _jreplace(string, L"Éf", L"√ﬁ", invert);
	string = _jreplace(string, L"Éh", L"ƒﬁ", invert);
	string = _jreplace(string, L"Éo", L" ﬁ", invert);
	string = _jreplace(string, L"Ér", L"Àﬁ", invert);
	string = _jreplace(string, L"Éu", L"Ãﬁ", invert);
	string = _jreplace(string, L"Éx", L"Õﬁ", invert);
	string = _jreplace(string, L"É{", L"Œﬁ", invert);
	string = _jreplace(string, L"Ép", L" ﬂ", invert);
	string = _jreplace(string, L"És", L"Àﬂ", invert);
	string = _jreplace(string, L"Év", L"Ãﬂ", invert);
	string = _jreplace(string, L"Éy", L"Õﬂ", invert);
	string = _jreplace(string, L"É|", L"Œﬂ", invert);
	string = _jreplace(string, L"É@", L"ß", invert);
	string = _jreplace(string, L"ÉB", L"®", invert);
	string = _jreplace(string, L"ÉD", L"©", invert);
	string = _jreplace(string, L"ÉF", L"™", invert);
	string = _jreplace(string, L"ÉH", L"´", invert);
	string = _jreplace(string, L"ÉÉ", L"¨", invert);
	string = _jreplace(string, L"ÉÖ", L"≠", invert);
	string = _jreplace(string, L"Éá", L"Æ", invert);
	string = _jreplace(string, L"Å[", L"∞", invert);
	string = _jreplace(string, L"ÅJ", L"ﬁ", invert);
	string = _jreplace(string, L"ÅK", L"ﬂ", invert);
	string = _jreplace(string, L"ÅE", L"•", invert);
	string = _jreplace(string, L"Åu", L"¢", invert);
	string = _jreplace(string, L"Åv", L"£", invert);
	string = _jreplace(string, L"ÅB", L"°", invert);
	string = _jreplace(string, L"ÅA", L"§", invert);

	string = _jreplace(string, L"ÅI", L"!", invert);
	string = _jreplace(string, L"˙W", L"\"", invert);
	string = _jreplace(string, L"Åî", L"#", invert);
	string = _jreplace(string, L"Åê", L"$", invert);
	string = _jreplace(string, L"Åì", L"%", invert);
	string = _jreplace(string, L"Åï", L"&", invert);
	string = _jreplace(string, L"˙V", L"\'", invert);
	string = _jreplace(string, L"Åi", L"(", invert);
	string = _jreplace(string, L"Åj", L")", invert);
	string = _jreplace(string, L"Åñ", L"*", invert);
	string = _jreplace(string, L"Å{", L"+", invert);
	string = _jreplace(string, L"ÅC", L",", invert);
	string = _jreplace(string, L"Å|", L"-", invert);
	string = _jreplace(string, L"ÅD", L".", invert);
	string = _jreplace(string, L"Å^", L"/", invert);
	string = _jreplace(string, L"ÅF", L":", invert);
	string = _jreplace(string, L"ÅG", L";", invert);
	string = _jreplace(string, L"ÅÉ", L"<", invert);
	string = _jreplace(string, L"ÅÅ", L"=", invert);
	string = _jreplace(string, L"ÅÑ", L">", invert);
	string = _jreplace(string, L"ÅH", L"\?", invert);
	string = _jreplace(string, L"Åó", L"@", invert);
	string = _jreplace(string, L"Åm", L"[", invert);
	string = _jreplace(string, L"Å_", L"\\", invert);
	string = _jreplace(string, L"Ån", L"]", invert);
	string = _jreplace(string, L"ÅO", L"^", invert);
	string = _jreplace(string, L"ÅQ", L"_", invert);
	string = _jreplace(string, L"ÅM", L"`", invert);
	string = _jreplace(string, L"Åo", L"{", invert);
	string = _jreplace(string, L"Åb", L"|", invert);
	string = _jreplace(string, L"Åp", L"}", invert);
	string = _jreplace(string, L"Å`", L"~", invert);
	string = _jreplace(string, L"Åè", L"\\", invert);

	if (space)
		string = _jreplace(string, L"Å@", L" ", invert);

	return string;
}