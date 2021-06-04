#include <lua.hpp>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <string>
#include <windows.h>


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
	else if (lua_type(L, 4) == LUA_TNIL) {
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
	else if (lua_type(L, 3) != LUA_TNIL) {
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

/*
int wbyte(lua_State* L) {
	if (lua_type(L, 1) != LUA_TSTRING) {
		return 0;
	}
	std::wstring text = StrToWstr(lua_tostring(L, 1));
	int i;
	int j;

	if (lua_type(L, 2) == LUA_TNUMBER) {
		i = lua_tointeger(L, 2);
	}
	else if (lua_type(L, 2) == LUA_TNIL) {
		i = 1;
	}
	else {
		return 0;
	}

	if (lua_type(L, 3) == LUA_TNUMBER) {
		j = lua_tointeger(L, 3);
	}
	else if (lua_type(L, 3) == LUA_TNIL) {
		j = i;
	}
	else {
		return 0;
	}

	if (j < i) {
		return 0;
	}

	for (int a = i; a <= j; a++)
	{
		
	}
}
*/

static luaL_Reg functions[] = {
	{"find", find},
	{"sub", sub},
	{"gsub", gsub},
	{"len", len},
	{"reverse", reverse},
	{"upper", upper},
	{"lower", lower},
	{"match", match},
	{ nullptr, nullptr }
};

extern "C" {
	__declspec(dllexport) int luaopen_textmodule(lua_State* L) {
		luaL_register(L, "textmodule", functions);
		return 1;
	}
}