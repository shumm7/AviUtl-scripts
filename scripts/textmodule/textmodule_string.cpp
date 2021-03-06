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
	string = _jreplace(string, L"", L"@", invert);
	string = _jreplace(string, L" ", L"A", invert);
	string = _jreplace(string, L"”", L"B", invert);
	string = _jreplace(string, L"¢", L"C", invert);
	string = _jreplace(string, L"£", L"D", invert);
	string = _jreplace(string, L"¤", L"E", invert);
	string = _jreplace(string, L"„", L"F", invert);
	string = _jreplace(string, L"¦", L"G", invert);
	string = _jreplace(string, L"§", L"H", invert);
	string = _jreplace(string, L"Ø", L"I", invert);
	string = _jreplace(string, L"©", L"J", invert);
	string = _jreplace(string, L"Ŗ", L"K", invert);
	string = _jreplace(string, L"«", L"L", invert);
	string = _jreplace(string, L"¬", L"M", invert);
	string = _jreplace(string, L"­", L"N", invert);
	string = _jreplace(string, L"®", L"O", invert);
	string = _jreplace(string, L"Æ", L"P", invert);
	string = _jreplace(string, L"°", L"Q", invert);
	string = _jreplace(string, L"±", L"R", invert);
	string = _jreplace(string, L"²", L"S", invert);
	string = _jreplace(string, L"³", L"T", invert);
	string = _jreplace(string, L"“", L"U", invert);
	string = _jreplace(string, L"µ", L"V", invert);
	string = _jreplace(string, L"¶", L"W", invert);
	string = _jreplace(string, L"·", L"X", invert);
	string = _jreplace(string, L"ø", L"Y", invert);
	string = _jreplace(string, L"¹", L"Z", invert);
	string = _jreplace(string, L"ŗ", L"[", invert);
	string = _jreplace(string, L"»", L"\", invert);
	string = _jreplace(string, L"¼", L"]", invert);
	string = _jreplace(string, L"½", L"^", invert);
	string = _jreplace(string, L"¾", L"_", invert);
	string = _jreplace(string, L"æ", L"`", invert);
	string = _jreplace(string, L"Ą", L"a", invert);
	string = _jreplace(string, L"Į", L"b", invert);
	string = _jreplace(string, L"Ā", L"c", invert);
	string = _jreplace(string, L"Ć", L"d", invert);
	string = _jreplace(string, L"Ä", L"e", invert);
	string = _jreplace(string, L"Å", L"f", invert);
	string = _jreplace(string, L"Ę", L"g", invert);
	string = _jreplace(string, L"Ē", L"h", invert);
	string = _jreplace(string, L"Č", L"i", invert);
	string = _jreplace(string, L"É", L"j", invert);
	string = _jreplace(string, L"Ź", L"k", invert);
	string = _jreplace(string, L"Ė", L"l", invert);
	string = _jreplace(string, L"Ģ", L"m", invert);
	string = _jreplace(string, L"Ķ", L"n", invert);
	string = _jreplace(string, L"Ī", L"o", invert);
	string = _jreplace(string, L"Ļ", L"p", invert);
	string = _jreplace(string, L"Š", L"q", invert);
	string = _jreplace(string, L"Ń", L"r", invert);
	string = _jreplace(string, L"Ņ", L"s", invert);
	string = _jreplace(string, L"Ó", L"t", invert);
	string = _jreplace(string, L"Ō", L"u", invert);
	string = _jreplace(string, L"Õ", L"v", invert);
	string = _jreplace(string, L"Ö", L"w", invert);
	string = _jreplace(string, L"×", L"x", invert);
	string = _jreplace(string, L"Ų", L"y", invert);
	string = _jreplace(string, L"Ł", L"z", invert);
	string = _jreplace(string, L"Ś", L"{", invert);
	string = _jreplace(string, L"Ū", L"|", invert);
	string = _jreplace(string, L"Ü", L"}", invert);
	string = _jreplace(string, L"Ż", L"~", invert);
	string = _jreplace(string, L"Ž", L"", invert);
	string = _jreplace(string, L"ß", L"", invert);
	string = _jreplace(string, L"ą", L"", invert);
	string = _jreplace(string, L"į", L"", invert);
	string = _jreplace(string, L"ā", L"", invert);
	string = _jreplace(string, L"ć", L"", invert);
	string = _jreplace(string, L"ä", L"", invert);
	string = _jreplace(string, L"å", L"", invert);
	string = _jreplace(string, L"ę", L"", invert);
	string = _jreplace(string, L"ē", L"", invert);
	string = _jreplace(string, L"č", L"", invert);
	string = _jreplace(string, L"é", L"", invert);
	string = _jreplace(string, L"ź", L"", invert);
	string = _jreplace(string, L"ė", L"", invert);
	string = _jreplace(string, L"ģ", L"", invert);
	string = _jreplace(string, L"ķ", L"", invert);
	string = _jreplace(string, L"š", L"", invert);
	string = _jreplace(string, L"ń", L"", invert);
	string = _jreplace(string, L"ī", L"", invert);
	string = _jreplace(string, L"ļ", L"", invert);

	return string;
}

std::wstring toHalfwidth(std::wstring string, bool invert, bool space) {
	string = _jreplace(string, L"O", L"0", invert);
	string = _jreplace(string, L"P", L"1", invert);
	string = _jreplace(string, L"Q", L"2", invert);
	string = _jreplace(string, L"R", L"3", invert);
	string = _jreplace(string, L"S", L"4", invert);
	string = _jreplace(string, L"T", L"5", invert);
	string = _jreplace(string, L"U", L"6", invert);
	string = _jreplace(string, L"V", L"7", invert);
	string = _jreplace(string, L"W", L"8", invert);
	string = _jreplace(string, L"X", L"9", invert);

	string = _jreplace(string, L"`", L"A", invert);
	string = _jreplace(string, L"a", L"B", invert);
	string = _jreplace(string, L"b", L"C", invert);
	string = _jreplace(string, L"c", L"D", invert);
	string = _jreplace(string, L"d", L"E", invert);
	string = _jreplace(string, L"e", L"F", invert);
	string = _jreplace(string, L"f", L"G", invert);
	string = _jreplace(string, L"g", L"H", invert);
	string = _jreplace(string, L"h", L"I", invert);
	string = _jreplace(string, L"i", L"J", invert);
	string = _jreplace(string, L"j", L"K", invert);
	string = _jreplace(string, L"k", L"L", invert);
	string = _jreplace(string, L"l", L"M", invert);
	string = _jreplace(string, L"m", L"N", invert);
	string = _jreplace(string, L"n", L"O", invert);
	string = _jreplace(string, L"o", L"P", invert);
	string = _jreplace(string, L"p", L"Q", invert);
	string = _jreplace(string, L"q", L"R", invert);
	string = _jreplace(string, L"r", L"S", invert);
	string = _jreplace(string, L"s", L"T", invert);
	string = _jreplace(string, L"t", L"U", invert);
	string = _jreplace(string, L"u", L"V", invert);
	string = _jreplace(string, L"v", L"W", invert);
	string = _jreplace(string, L"w", L"X", invert);
	string = _jreplace(string, L"x", L"Y", invert);
	string = _jreplace(string, L"y", L"Z", invert);

	string = _jreplace(string, L"", L"a", invert);
	string = _jreplace(string, L"", L"b", invert);
	string = _jreplace(string, L"", L"c", invert);
	string = _jreplace(string, L"", L"d", invert);
	string = _jreplace(string, L"", L"e", invert);
	string = _jreplace(string, L"", L"f", invert);
	string = _jreplace(string, L"", L"g", invert);
	string = _jreplace(string, L"", L"h", invert);
	string = _jreplace(string, L"", L"i", invert);
	string = _jreplace(string, L"", L"j", invert);
	string = _jreplace(string, L"", L"k", invert);
	string = _jreplace(string, L"", L"l", invert);
	string = _jreplace(string, L"", L"m", invert);
	string = _jreplace(string, L"", L"n", invert);
	string = _jreplace(string, L"", L"o", invert);
	string = _jreplace(string, L"", L"p", invert);
	string = _jreplace(string, L"", L"q", invert);
	string = _jreplace(string, L"", L"r", invert);
	string = _jreplace(string, L"", L"s", invert);
	string = _jreplace(string, L"", L"t", invert);
	string = _jreplace(string, L"", L"u", invert);
	string = _jreplace(string, L"", L"v", invert);
	string = _jreplace(string, L"", L"w", invert);
	string = _jreplace(string, L"", L"x", invert);
	string = _jreplace(string, L"", L"y", invert);
	string = _jreplace(string, L"", L"z", invert);

	string = _jreplace(string, L"A", L"±", invert);
	string = _jreplace(string, L"C", L"²", invert);
	string = _jreplace(string, L"E", L"³", invert);
	string = _jreplace(string, L"G", L"“", invert);
	string = _jreplace(string, L"I", L"µ", invert);
	string = _jreplace(string, L"J", L"¶", invert);
	string = _jreplace(string, L"L", L"·", invert);
	string = _jreplace(string, L"N", L"ø", invert);
	string = _jreplace(string, L"P", L"¹", invert);
	string = _jreplace(string, L"R", L"ŗ", invert);
	string = _jreplace(string, L"T", L"»", invert);
	string = _jreplace(string, L"V", L"¼", invert);
	string = _jreplace(string, L"X", L"½", invert);
	string = _jreplace(string, L"Z", L"¾", invert);
	string = _jreplace(string, L"\", L"æ", invert);
	string = _jreplace(string, L"^", L"Ą", invert);
	string = _jreplace(string, L"`", L"Į", invert);
	string = _jreplace(string, L"c", L"Ā", invert);
	string = _jreplace(string, L"e", L"Ć", invert);
	string = _jreplace(string, L"g", L"Ä", invert);
	string = _jreplace(string, L"i", L"Å", invert);
	string = _jreplace(string, L"j", L"Ę", invert);
	string = _jreplace(string, L"k", L"Ē", invert);
	string = _jreplace(string, L"l", L"Č", invert);
	string = _jreplace(string, L"m", L"É", invert);
	string = _jreplace(string, L"n", L"Ź", invert);
	string = _jreplace(string, L"q", L"Ė", invert);
	string = _jreplace(string, L"t", L"Ģ", invert);
	string = _jreplace(string, L"w", L"Ķ", invert);
	string = _jreplace(string, L"z", L"Ī", invert);
	string = _jreplace(string, L"}", L"Ļ", invert);
	string = _jreplace(string, L"~", L"Š", invert);
	string = _jreplace(string, L"", L"Ń", invert);
	string = _jreplace(string, L"", L"Ņ", invert);
	string = _jreplace(string, L"", L"Ó", invert);
	string = _jreplace(string, L"", L"Ō", invert);
	string = _jreplace(string, L"", L"Õ", invert);
	string = _jreplace(string, L"", L"Ö", invert);
	string = _jreplace(string, L"", L"×", invert);
	string = _jreplace(string, L"", L"Ų", invert);
	string = _jreplace(string, L"", L"Ł", invert);
	string = _jreplace(string, L"", L"Ś", invert);
	string = _jreplace(string, L"", L"Ū", invert);
	string = _jreplace(string, L"", L"Ü", invert);
	string = _jreplace(string, L"", L"¦", invert);
	string = _jreplace(string, L"", L"Ż", invert);
	string = _jreplace(string, L"", L"³Ž", invert);
	string = _jreplace(string, L"K", L"¶Ž", invert);
	string = _jreplace(string, L"M", L"·Ž", invert);
	string = _jreplace(string, L"O", L"øŽ", invert);
	string = _jreplace(string, L"Q", L"¹Ž", invert);
	string = _jreplace(string, L"S", L"ŗŽ", invert);
	string = _jreplace(string, L"U", L"»Ž", invert);
	string = _jreplace(string, L"W", L"¼Ž", invert);
	string = _jreplace(string, L"Y", L"½Ž", invert);
	string = _jreplace(string, L"[", L"¾Ž", invert);
	string = _jreplace(string, L"]", L"æŽ", invert);
	string = _jreplace(string, L"_", L"ĄŽ", invert);
	string = _jreplace(string, L"a", L"ĮŽ", invert);
	string = _jreplace(string, L"d", L"ĀŽ", invert);
	string = _jreplace(string, L"f", L"ĆŽ", invert);
	string = _jreplace(string, L"h", L"ÄŽ", invert);
	string = _jreplace(string, L"o", L"ŹŽ", invert);
	string = _jreplace(string, L"r", L"ĖŽ", invert);
	string = _jreplace(string, L"u", L"ĢŽ", invert);
	string = _jreplace(string, L"x", L"ĶŽ", invert);
	string = _jreplace(string, L"{", L"ĪŽ", invert);
	string = _jreplace(string, L"p", L"Źß", invert);
	string = _jreplace(string, L"s", L"Ėß", invert);
	string = _jreplace(string, L"v", L"Ģß", invert);
	string = _jreplace(string, L"y", L"Ķß", invert);
	string = _jreplace(string, L"|", L"Īß", invert);
	string = _jreplace(string, L"@", L"§", invert);
	string = _jreplace(string, L"B", L"Ø", invert);
	string = _jreplace(string, L"D", L"©", invert);
	string = _jreplace(string, L"F", L"Ŗ", invert);
	string = _jreplace(string, L"H", L"«", invert);
	string = _jreplace(string, L"", L"¬", invert);
	string = _jreplace(string, L"", L"­", invert);
	string = _jreplace(string, L"", L"®", invert);
	string = _jreplace(string, L"[", L"°", invert);
	string = _jreplace(string, L"J", L"Ž", invert);
	string = _jreplace(string, L"K", L"ß", invert);
	string = _jreplace(string, L"E", L"„", invert);
	string = _jreplace(string, L"u", L"¢", invert);
	string = _jreplace(string, L"v", L"£", invert);
	string = _jreplace(string, L"B", L"”", invert);
	string = _jreplace(string, L"A", L"¤", invert);

	string = _jreplace(string, L"I", L"!", invert);
	string = _jreplace(string, L"śW", L"\"", invert);
	string = _jreplace(string, L"", L"#", invert);
	string = _jreplace(string, L"", L"$", invert);
	string = _jreplace(string, L"", L"%", invert);
	string = _jreplace(string, L"", L"&", invert);
	string = _jreplace(string, L"śV", L"\'", invert);
	string = _jreplace(string, L"i", L"(", invert);
	string = _jreplace(string, L"j", L")", invert);
	string = _jreplace(string, L"", L"*", invert);
	string = _jreplace(string, L"{", L"+", invert);
	string = _jreplace(string, L"C", L",", invert);
	string = _jreplace(string, L"|", L"-", invert);
	string = _jreplace(string, L"D", L".", invert);
	string = _jreplace(string, L"^", L"/", invert);
	string = _jreplace(string, L"F", L":", invert);
	string = _jreplace(string, L"G", L";", invert);
	string = _jreplace(string, L"", L"<", invert);
	string = _jreplace(string, L"", L"=", invert);
	string = _jreplace(string, L"", L">", invert);
	string = _jreplace(string, L"H", L"\?", invert);
	string = _jreplace(string, L"", L"@", invert);
	string = _jreplace(string, L"m", L"[", invert);
	string = _jreplace(string, L"_", L"\\", invert);
	string = _jreplace(string, L"n", L"]", invert);
	string = _jreplace(string, L"O", L"^", invert);
	string = _jreplace(string, L"Q", L"_", invert);
	string = _jreplace(string, L"M", L"`", invert);
	string = _jreplace(string, L"o", L"{", invert);
	string = _jreplace(string, L"b", L"|", invert);
	string = _jreplace(string, L"p", L"}", invert);
	string = _jreplace(string, L"`", L"~", invert);
	string = _jreplace(string, L"", L"\\", invert);

	if (space)
		string = _jreplace(string, L"@", L" ", invert);

	return string;
}

void debug_string(std::wstring message) {
	OutputDebugString(WstrToStr(message).c_str());
}