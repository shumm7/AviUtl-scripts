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
	string = _jreplace(string, L"��", L"�@", invert);
	string = _jreplace(string, L"��", L"�A", invert);
	string = _jreplace(string, L"��", L"�B", invert);
	string = _jreplace(string, L"��", L"�C", invert);
	string = _jreplace(string, L"��", L"�D", invert);
	string = _jreplace(string, L"��", L"�E", invert);
	string = _jreplace(string, L"��", L"�F", invert);
	string = _jreplace(string, L"��", L"�G", invert);
	string = _jreplace(string, L"��", L"�H", invert);
	string = _jreplace(string, L"��", L"�I", invert);
	string = _jreplace(string, L"��", L"�J", invert);
	string = _jreplace(string, L"��", L"�K", invert);
	string = _jreplace(string, L"��", L"�L", invert);
	string = _jreplace(string, L"��", L"�M", invert);
	string = _jreplace(string, L"��", L"�N", invert);
	string = _jreplace(string, L"��", L"�O", invert);
	string = _jreplace(string, L"��", L"�P", invert);
	string = _jreplace(string, L"��", L"�Q", invert);
	string = _jreplace(string, L"��", L"�R", invert);
	string = _jreplace(string, L"��", L"�S", invert);
	string = _jreplace(string, L"��", L"�T", invert);
	string = _jreplace(string, L"��", L"�U", invert);
	string = _jreplace(string, L"��", L"�V", invert);
	string = _jreplace(string, L"��", L"�W", invert);
	string = _jreplace(string, L"��", L"�X", invert);
	string = _jreplace(string, L"��", L"�Y", invert);
	string = _jreplace(string, L"��", L"�Z", invert);
	string = _jreplace(string, L"��", L"�[", invert);
	string = _jreplace(string, L"��", L"�\", invert);
	string = _jreplace(string, L"��", L"�]", invert);
	string = _jreplace(string, L"��", L"�^", invert);
	string = _jreplace(string, L"��", L"�_", invert);
	string = _jreplace(string, L"��", L"�`", invert);
	string = _jreplace(string, L"��", L"�a", invert);
	string = _jreplace(string, L"��", L"�b", invert);
	string = _jreplace(string, L"��", L"�c", invert);
	string = _jreplace(string, L"��", L"�d", invert);
	string = _jreplace(string, L"��", L"�e", invert);
	string = _jreplace(string, L"��", L"�f", invert);
	string = _jreplace(string, L"��", L"�g", invert);
	string = _jreplace(string, L"��", L"�h", invert);
	string = _jreplace(string, L"��", L"�i", invert);
	string = _jreplace(string, L"��", L"�j", invert);
	string = _jreplace(string, L"��", L"�k", invert);
	string = _jreplace(string, L"��", L"�l", invert);
	string = _jreplace(string, L"��", L"�m", invert);
	string = _jreplace(string, L"��", L"�n", invert);
	string = _jreplace(string, L"��", L"�o", invert);
	string = _jreplace(string, L"��", L"�p", invert);
	string = _jreplace(string, L"��", L"�q", invert);
	string = _jreplace(string, L"��", L"�r", invert);
	string = _jreplace(string, L"��", L"�s", invert);
	string = _jreplace(string, L"��", L"�t", invert);
	string = _jreplace(string, L"��", L"�u", invert);
	string = _jreplace(string, L"��", L"�v", invert);
	string = _jreplace(string, L"��", L"�w", invert);
	string = _jreplace(string, L"��", L"�x", invert);
	string = _jreplace(string, L"��", L"�y", invert);
	string = _jreplace(string, L"��", L"�z", invert);
	string = _jreplace(string, L"��", L"�{", invert);
	string = _jreplace(string, L"��", L"�|", invert);
	string = _jreplace(string, L"��", L"�}", invert);
	string = _jreplace(string, L"��", L"�~", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"��", L"��", invert);

	return string;
}

std::wstring toHalfwidth(std::wstring string, bool invert, bool space) {
	string = _jreplace(string, L"�O", L"0", invert);
	string = _jreplace(string, L"�P", L"1", invert);
	string = _jreplace(string, L"�Q", L"2", invert);
	string = _jreplace(string, L"�R", L"3", invert);
	string = _jreplace(string, L"�S", L"4", invert);
	string = _jreplace(string, L"�T", L"5", invert);
	string = _jreplace(string, L"�U", L"6", invert);
	string = _jreplace(string, L"�V", L"7", invert);
	string = _jreplace(string, L"�W", L"8", invert);
	string = _jreplace(string, L"�X", L"9", invert);

	string = _jreplace(string, L"�`", L"A", invert);
	string = _jreplace(string, L"�a", L"B", invert);
	string = _jreplace(string, L"�b", L"C", invert);
	string = _jreplace(string, L"�c", L"D", invert);
	string = _jreplace(string, L"�d", L"E", invert);
	string = _jreplace(string, L"�e", L"F", invert);
	string = _jreplace(string, L"�f", L"G", invert);
	string = _jreplace(string, L"�g", L"H", invert);
	string = _jreplace(string, L"�h", L"I", invert);
	string = _jreplace(string, L"�i", L"J", invert);
	string = _jreplace(string, L"�j", L"K", invert);
	string = _jreplace(string, L"�k", L"L", invert);
	string = _jreplace(string, L"�l", L"M", invert);
	string = _jreplace(string, L"�m", L"N", invert);
	string = _jreplace(string, L"�n", L"O", invert);
	string = _jreplace(string, L"�o", L"P", invert);
	string = _jreplace(string, L"�p", L"Q", invert);
	string = _jreplace(string, L"�q", L"R", invert);
	string = _jreplace(string, L"�r", L"S", invert);
	string = _jreplace(string, L"�s", L"T", invert);
	string = _jreplace(string, L"�t", L"U", invert);
	string = _jreplace(string, L"�u", L"V", invert);
	string = _jreplace(string, L"�v", L"W", invert);
	string = _jreplace(string, L"�w", L"X", invert);
	string = _jreplace(string, L"�x", L"Y", invert);
	string = _jreplace(string, L"�y", L"Z", invert);

	string = _jreplace(string, L"��", L"a", invert);
	string = _jreplace(string, L"��", L"b", invert);
	string = _jreplace(string, L"��", L"c", invert);
	string = _jreplace(string, L"��", L"d", invert);
	string = _jreplace(string, L"��", L"e", invert);
	string = _jreplace(string, L"��", L"f", invert);
	string = _jreplace(string, L"��", L"g", invert);
	string = _jreplace(string, L"��", L"h", invert);
	string = _jreplace(string, L"��", L"i", invert);
	string = _jreplace(string, L"��", L"j", invert);
	string = _jreplace(string, L"��", L"k", invert);
	string = _jreplace(string, L"��", L"l", invert);
	string = _jreplace(string, L"��", L"m", invert);
	string = _jreplace(string, L"��", L"n", invert);
	string = _jreplace(string, L"��", L"o", invert);
	string = _jreplace(string, L"��", L"p", invert);
	string = _jreplace(string, L"��", L"q", invert);
	string = _jreplace(string, L"��", L"r", invert);
	string = _jreplace(string, L"��", L"s", invert);
	string = _jreplace(string, L"��", L"t", invert);
	string = _jreplace(string, L"��", L"u", invert);
	string = _jreplace(string, L"��", L"v", invert);
	string = _jreplace(string, L"��", L"w", invert);
	string = _jreplace(string, L"��", L"x", invert);
	string = _jreplace(string, L"��", L"y", invert);
	string = _jreplace(string, L"��", L"z", invert);

	string = _jreplace(string, L"�A", L"�", invert);
	string = _jreplace(string, L"�C", L"�", invert);
	string = _jreplace(string, L"�E", L"�", invert);
	string = _jreplace(string, L"�G", L"�", invert);
	string = _jreplace(string, L"�I", L"�", invert);
	string = _jreplace(string, L"�J", L"�", invert);
	string = _jreplace(string, L"�L", L"�", invert);
	string = _jreplace(string, L"�N", L"�", invert);
	string = _jreplace(string, L"�P", L"�", invert);
	string = _jreplace(string, L"�R", L"�", invert);
	string = _jreplace(string, L"�T", L"�", invert);
	string = _jreplace(string, L"�V", L"�", invert);
	string = _jreplace(string, L"�X", L"�", invert);
	string = _jreplace(string, L"�Z", L"�", invert);
	string = _jreplace(string, L"�\", L"�", invert);
	string = _jreplace(string, L"�^", L"�", invert);
	string = _jreplace(string, L"�`", L"�", invert);
	string = _jreplace(string, L"�c", L"�", invert);
	string = _jreplace(string, L"�e", L"�", invert);
	string = _jreplace(string, L"�g", L"�", invert);
	string = _jreplace(string, L"�i", L"�", invert);
	string = _jreplace(string, L"�j", L"�", invert);
	string = _jreplace(string, L"�k", L"�", invert);
	string = _jreplace(string, L"�l", L"�", invert);
	string = _jreplace(string, L"�m", L"�", invert);
	string = _jreplace(string, L"�n", L"�", invert);
	string = _jreplace(string, L"�q", L"�", invert);
	string = _jreplace(string, L"�t", L"�", invert);
	string = _jreplace(string, L"�w", L"�", invert);
	string = _jreplace(string, L"�z", L"�", invert);
	string = _jreplace(string, L"�}", L"�", invert);
	string = _jreplace(string, L"�~", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"��", invert);
	string = _jreplace(string, L"�K", L"��", invert);
	string = _jreplace(string, L"�M", L"��", invert);
	string = _jreplace(string, L"�O", L"��", invert);
	string = _jreplace(string, L"�Q", L"��", invert);
	string = _jreplace(string, L"�S", L"��", invert);
	string = _jreplace(string, L"�U", L"��", invert);
	string = _jreplace(string, L"�W", L"��", invert);
	string = _jreplace(string, L"�Y", L"��", invert);
	string = _jreplace(string, L"�[", L"��", invert);
	string = _jreplace(string, L"�]", L"��", invert);
	string = _jreplace(string, L"�_", L"��", invert);
	string = _jreplace(string, L"�a", L"��", invert);
	string = _jreplace(string, L"�d", L"��", invert);
	string = _jreplace(string, L"�f", L"��", invert);
	string = _jreplace(string, L"�h", L"��", invert);
	string = _jreplace(string, L"�o", L"��", invert);
	string = _jreplace(string, L"�r", L"��", invert);
	string = _jreplace(string, L"�u", L"��", invert);
	string = _jreplace(string, L"�x", L"��", invert);
	string = _jreplace(string, L"�{", L"��", invert);
	string = _jreplace(string, L"�p", L"��", invert);
	string = _jreplace(string, L"�s", L"��", invert);
	string = _jreplace(string, L"�v", L"��", invert);
	string = _jreplace(string, L"�y", L"��", invert);
	string = _jreplace(string, L"�|", L"��", invert);
	string = _jreplace(string, L"�@", L"�", invert);
	string = _jreplace(string, L"�B", L"�", invert);
	string = _jreplace(string, L"�D", L"�", invert);
	string = _jreplace(string, L"�F", L"�", invert);
	string = _jreplace(string, L"�H", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"��", L"�", invert);
	string = _jreplace(string, L"�[", L"�", invert);
	string = _jreplace(string, L"�J", L"�", invert);
	string = _jreplace(string, L"�K", L"�", invert);
	string = _jreplace(string, L"�E", L"�", invert);
	string = _jreplace(string, L"�u", L"�", invert);
	string = _jreplace(string, L"�v", L"�", invert);
	string = _jreplace(string, L"�B", L"�", invert);
	string = _jreplace(string, L"�A", L"�", invert);

	string = _jreplace(string, L"�I", L"!", invert);
	string = _jreplace(string, L"�W", L"\"", invert);
	string = _jreplace(string, L"��", L"#", invert);
	string = _jreplace(string, L"��", L"$", invert);
	string = _jreplace(string, L"��", L"%", invert);
	string = _jreplace(string, L"��", L"&", invert);
	string = _jreplace(string, L"�V", L"\'", invert);
	string = _jreplace(string, L"�i", L"(", invert);
	string = _jreplace(string, L"�j", L")", invert);
	string = _jreplace(string, L"��", L"*", invert);
	string = _jreplace(string, L"�{", L"+", invert);
	string = _jreplace(string, L"�C", L",", invert);
	string = _jreplace(string, L"�|", L"-", invert);
	string = _jreplace(string, L"�D", L".", invert);
	string = _jreplace(string, L"�^", L"/", invert);
	string = _jreplace(string, L"�F", L":", invert);
	string = _jreplace(string, L"�G", L";", invert);
	string = _jreplace(string, L"��", L"<", invert);
	string = _jreplace(string, L"��", L"=", invert);
	string = _jreplace(string, L"��", L">", invert);
	string = _jreplace(string, L"�H", L"\?", invert);
	string = _jreplace(string, L"��", L"@", invert);
	string = _jreplace(string, L"�m", L"[", invert);
	string = _jreplace(string, L"�_", L"\\", invert);
	string = _jreplace(string, L"�n", L"]", invert);
	string = _jreplace(string, L"�O", L"^", invert);
	string = _jreplace(string, L"�Q", L"_", invert);
	string = _jreplace(string, L"�M", L"`", invert);
	string = _jreplace(string, L"�o", L"{", invert);
	string = _jreplace(string, L"�b", L"|", invert);
	string = _jreplace(string, L"�p", L"}", invert);
	string = _jreplace(string, L"�`", L"~", invert);
	string = _jreplace(string, L"��", L"\\", invert);

	if(space)
		string = _jreplace(string, L"�@", L" ", invert);

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