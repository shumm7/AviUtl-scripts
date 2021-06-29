#include <lua.hpp>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <time.h>

#define module_name "textmodule"
#define version "0.0.3"
#define version_num 3

using namespace std::chrono;


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

	if(space)
		string = _jreplace(string, L"Å@", L" ", invert);

	return string;
}

int getinfo(lua_State* L) {
	int i;
	std::wstring t;

	if (lua_type(L, 1) == LUA_TSTRING) {
		t = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}

	if (lua_type(L, 2) == LUA_TNUMBER) {
		i = lua_tonumber(L, 2);
	}
	else {
		i = 1;
	}

	if (t == L"version") {
		if (i == 1) {
			lua_pushstring(L, version);
			return 1;
		}
		else if (i == 2) {
			lua_pushinteger(L, version_num);
			return 1;
		}
	}
	else if(t == L"name") {
		lua_pushstring(L, module_name);
		return 1;
	}

	return 0;
}

int find(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	if (lua_type(L, 2) != LUA_TSTRING) {
		return 0;
	}
	std::wstring text = StrToWstr(lua_tostring(L, 1));
	std::wstring pattern = StrToWstr(lua_tostring(L, 2));

	std::wsmatch results;
	bool l = std::regex_search(text, results, std::wregex(pattern));
	if (l) {
		lua_pushinteger(L, results.position()+1 );
		lua_pushinteger(L, results.position()+results.length() );
		return 2;
	}
	else {
		return 0;
	}
}

int sub(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	if (lua_type(L, 2) != LUA_TNUMBER) {
		return 0;
	}

	std::wstring text = StrToWstr(lua_tostring(L, 1));
	int start = lua_tointeger(L, 2) - 1;
	int end;
	bool mode_last = false;

	if (lua_type(L, 3) == LUA_TNUMBER) {
		end = lua_tointeger(L, 3) - 1;
	}
	else if (lua_type(L, 3) != LUA_TNIL) {
		end = text.length() - 1;
	}
	else {
		return 0;
	}

	lua_pushstring(L, WstrToStr(text.substr(start, end - start + 1)).c_str());
	return 1;
}

int gsub(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	if (lua_type(L, 2) != LUA_TSTRING) {
		return 0;
	}
	if (lua_type(L, 3) != LUA_TSTRING) {
		return 0;
	}

	std::wstring text = StrToWstr(lua_tostring(L, 1));
	std::wstring pattern = StrToWstr(lua_tostring(L, 2));
	std::wstring repl = StrToWstr(lua_tostring(L, 3));
	int num;

	if (lua_type(L, 4) == LUA_TNUMBER) {
		num = lua_tointeger(L, 4);
	}
	else if (lua_type(L, 4) == LUA_TNIL || lua_type(L, 4) == -1) {
		num = 1;
	}
	else {
		return 0;
	}

	for (int i = 0; i < num; i++)
	{
		std::wsmatch results;
		bool l = std::regex_search(text, results, std::wregex(pattern));
		if (l) {
			int s = results.position();
			int l = results.length();
			text = text.replace(s, l, repl);
		}
		else {
			break;
		}
		lua_pushstring(L, WstrToStr(text).c_str());
	}
	return 1;
}

int len(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	std::wstring text = StrToWstr(lua_tostring(L, 1));

	lua_pushinteger(L, text.length());
	return 1;
}

int reverse(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	std::wstring text = StrToWstr(lua_tostring(L, 1));
	std::wstring ret;
	for (int i = 0; i < text.length(); i++)
	{
		ret += text.substr(text.length() - i - 1 , 1);
	}
	
	lua_pushstring(L, WstrToStr(ret).c_str() );
	return 1;
}

int upper(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}

	std::wstring text = StrToWstr(lua_tostring(L, 1));
	std::wstring ret;
	for (int i = 0; i < text.length(); i++)
	{
		ret += toupper(text[i]);
	}

	lua_pushstring(L, WstrToStr(ret).c_str());
	return 1;
}

int lower(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}

	std::wstring text = StrToWstr(lua_tostring(L, 1));
	std::wstring ret;
	for (int i = 0; i < text.length(); i++)
	{
		ret += tolower(text[i]);
	}

	lua_pushstring(L, WstrToStr(ret).c_str());
	return 1;
}

int match(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	if (lua_type(L, 2) != LUA_TSTRING) {
		return 0;
	}
	std::wstring text = StrToWstr(lua_tostring(L, 1));
	std::wstring pattern = StrToWstr(lua_tostring(L, 2));

	int start;
	if (lua_type(L, 3) == LUA_TNUMBER) {
		start = lua_tointeger(L, 3) - 1;
	}
	else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == -1) {
		start = 0;
	}
	else {
		return 0;
	}

	text = text.substr(start);
	std::wsmatch results;
	bool l = std::regex_search(text, results, std::wregex(pattern));
	if (l) {
		lua_pushstring(L, WstrToStr(results.str()).c_str());
		return 1;
	}
	else {
		return 0;
	}
}

int wbyte(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	std::wstring text = StrToWstr(lua_tostring(L, 1));
	int i;
	int j;
	int length = text.length();

	if (lua_type(L, 2) == LUA_TNUMBER) {
		i = lua_tointeger(L, 2) - 1;
	}
	else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == -1) {
		i = 0;
	}
	else {
		return 0;
	}

	if (lua_type(L, 3) == LUA_TNUMBER) {
		j = lua_tointeger(L, 3) - 1;
	}
	else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == -1) {
		j = i;
	}
	else {
		return 0;
	}

	if (length < 1) {
		return 0;
	}
	if (j < i) {
		return 0;
	}
	if (i >= length) {
		return 0;
	}
	if (j >= length) {
		j = length - 1;
	}

	for (int k = i; k <= j; k++)
	{
		int c = text[k];
		lua_pushinteger(L, c);
	}
	return j - i + 1;
}

int wchar(lua_State * L) {
		int cnt = 1;
		std::vector<int> list;

		while (true) {
			int tp = lua_type(L, cnt);

			if (tp == LUA_TNUMBER) {
				list.push_back(lua_tointeger(L, cnt));
			}
			else if (tp == LUA_TNIL || tp == -1) {
				break;
			}
			else {
				return 0;
			}

			cnt++;
		}

		if (list.size() < 1) {
			return 0;
		}

		wchar_t temp;
		std::wstring ret;
		for (int i = 0; i < list.size(); i++)
		{
			temp = list[i];
			ret += temp;
		}

		lua_pushstring(L, WstrToStr(ret).c_str());
		return 1;
	}

int gmatch(lua_State* L) {
	std::wstring s;
	std::wsmatch m;
	std::wstring pattern;
	if (lua_type(L, 1) == LUA_TSTRING) {
		s = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}
	if (lua_type(L, 2) == LUA_TSTRING) {
		pattern = StrToWstr(lua_tostring(L, 2));
	}
	else {
		return 0;
	}

	luaL_dostring(L, "function my_factory(x) local pos,length=0,#x  return function()  pos = pos + 1  if pos>length then  return nil  else  return x[pos] end end end");
	lua_getglobal(L, "my_factory");
	lua_newtable(L);

	if ( std::regex_match(s, m, std::wregex(pattern)) ) {
		int size = m.size();

		for (int i = 0; i < size; i++)
		{
			lua_pushinteger(L, i+1);
			lua_pushstring(L, WstrToStr( m[i].str() ).c_str() );
			lua_settable(L, -3);
		}
	}

	lua_pcall(L, 1, 1, 0);
	return 1;
}

int hiragana(lua_State* L) {
	std::wstring katakana;
	if (lua_type(L, 1) == LUA_TSTRING) {
		katakana = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}

	lua_pushstring(L, WstrToStr(toKatakana(katakana, true)).c_str());
	return 1;
}

int katakana(lua_State* L) {
	std::wstring hiragana;
	if (lua_type(L, 1) == LUA_TSTRING) {
		hiragana = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}

	lua_pushstring(L, WstrToStr(toKatakana(hiragana, false)).c_str() );
	return 1;
}

int halfwidth(lua_State* L) {
	std::wstring fullwidth;
	bool mode;

	if (lua_type(L, 1) == LUA_TSTRING) {
		fullwidth = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}
	if (lua_type(L, 2) == LUA_TBOOLEAN) {
		mode = lua_toboolean(L, 2);
	}
	else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2)==-1) {
		mode = true;
	}
	else {
		return 0;
	}

	lua_pushstring(L, WstrToStr(toHalfwidth(fullwidth, false, mode)).c_str());
	return 1;
}

int fullwidth(lua_State* L) {
	std::wstring halfwidth;
	bool mode;

	if (lua_type(L, 1) == LUA_TSTRING) {
		halfwidth = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}
	if (lua_type(L, 2) == LUA_TBOOLEAN) {
		mode = lua_toboolean(L, 2);
	}
	else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == -1) {
		mode = true;
	}
	else {
		return 0;
	}

	lua_pushstring(L, WstrToStr(toHalfwidth(halfwidth, true, mode)).c_str());
	return 1;
}


int time(lua_State* L) {
	if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == -1) {
		auto now = std::chrono::system_clock::now();
		__time64_t now_c = std::chrono::system_clock::to_time_t(now);
		
		lua_pushnumber(L, now_c);
		return 1;
	}
	else if (lua_type(L, 1) == LUA_TTABLE) {
		lua_getfield(L, 1, "year");
		lua_getfield(L, 1, "month");
		lua_getfield(L, 1, "day");
		lua_getfield(L, 1, "hour");
		lua_getfield(L, 1, "min");
		lua_getfield(L, 1, "sec");

		struct tm Time = {0, 0, 0, 1, 0, 0};
		__time64_t res;
		
		if (lua_type(L, -6) == LUA_TNUMBER) //year
			Time.tm_year = lua_tonumber(L, -6) - 1900;
		else
			return 0;
		if (lua_type(L, -5) == LUA_TNUMBER) //month
			Time.tm_mon = lua_tonumber(L, -5) - 1;
		else
			return 0;
		if (lua_type(L, -4) == LUA_TNUMBER) //day
			Time.tm_mday = lua_tonumber(L, -4);
		else
			return 0;

		if (lua_type(L, -3) == LUA_TNUMBER) //hour
			Time.tm_hour = lua_tonumber(L, -3);
		if (lua_type(L, -2) == LUA_TNUMBER) //min
			Time.tm_min = lua_tonumber(L, -2);
		if (lua_type(L, -1) == LUA_TNUMBER) //sec
			Time.tm_sec = lua_tonumber(L, -1);

		res = _mktime64(&Time);
		lua_pushnumber(L, res);
		return 1;
	}

	return 0;
}

int date(lua_State* L) {
	std::wstring format;
	__time64_t time;
	struct tm time_st;
	bool utc = false;

	if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == -1) {
		format = L"%c";
	}
	else if (lua_type(L, 1) == LUA_TSTRING) {
		format = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}

	//UTC
	if (WstrToStr(format)[0] == '!') {
		utc = true;
		format = format.substr(1);
	}

	if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == -1) {
		auto now = std::chrono::system_clock::now();
		time = std::chrono::system_clock::to_time_t(now);
	}
	else if (lua_type(L, 2) == LUA_TNUMBER) {
		time = lua_tonumber(L, 2);
	}
	else {
		return 0;
	}

	if (utc) {
		_gmtime64_s(&time_st, &time);
	}
	else {
		_localtime64_s(&time_st, &time);
	}

	if (format == L"*t") {
		lua_newtable(L);

		lua_pushnumber(L, (long long)time_st.tm_year + (long long)1900);
		lua_setfield(L, -2, "year");
		lua_pushnumber(L, (long long)time_st.tm_mon+ (long long)1);
		lua_setfield(L, -2, "month");
		lua_pushnumber(L, time_st.tm_mday);
		lua_setfield(L, -2, "day");
		lua_pushnumber(L, time_st.tm_hour);
		lua_setfield(L, -2, "hour");
		lua_pushnumber(L, time_st.tm_min);
		lua_setfield(L, -2, "min");
		lua_pushnumber(L, time_st.tm_sec);
		lua_setfield(L, -2, "sec");
		lua_pushnumber(L, (long long)time_st.tm_wday + (long long)1);
		lua_setfield(L, -2, "wday");
		lua_pushnumber(L, (long long)time_st.tm_yday + (long long)1);
		lua_setfield(L, -2, "yday");
		lua_pushnumber(L, time_st.tm_isdst);
		lua_setfield(L, -2, "isdst");

		return 1;
	}
	else {
		wchar_t buffer[128];
		wcsftime(buffer, 128, format.c_str(), &time_st);
		lua_pushstring(L, WstrToStr(buffer).c_str());
		return 1;
	}

}


static luaL_Reg functions[] = {
	{"getinfo", getinfo},

	{"find", find},
	{"sub", sub},
	{"gsub", gsub},
	{"len", len},
	{"reverse", reverse},
	{"upper", upper},
	{"lower", lower},
	{"match", match},
	{"byte", wbyte},
	{"char", wchar},
	{"gmatch", gmatch},

	{"hiragana", hiragana},
	{"katakana", katakana},
	{"halfwidth", halfwidth},
	{"fullwidth", fullwidth},

	{"time", time},
	{"date", date},
	{ nullptr, nullptr }
};

extern "C" {
	__declspec(dllexport) int luaopen_textmodule(lua_State* L) {
		luaL_register(L, "textmodule", functions);
		return 1;
	}
}