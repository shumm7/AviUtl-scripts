#include <lua.hpp>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <codecvt>
#include <exception>

#include "textmodule_string.h"

#define module_name "textmodule"
#define version "0.1.2"
#define version_num 6

using namespace std::chrono;


////////////////////////////////////
//          LUA FUNCTION          //
///////////////////////////////////
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
	bool l;
	try {
		l = std::regex_search(text, results, std::wregex(pattern));
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}

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
		bool l;
		try {
			l = std::regex_search(text, results, std::wregex(pattern));
		}
		catch (std::exception& e) {
			luaL_error(L, e.what());
			return 1;
		}

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
	bool l;
	try {
		l = std::regex_search(text, results, std::wregex(pattern));
	}
	catch (std::exception &e) {
		luaL_error(L, e.what());
		return 1;
	}

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
		unsigned long long c = text[k];
		lua_pushinteger(L, c);
	}
	return j - i + 1;
}

int wchar(lua_State * L) {
		int cnt = 1;
		std::vector<unsigned long long> list;

		while (true) {
			int tp = lua_type(L, cnt);

			if (tp == LUA_TNUMBER) {
				list.push_back(lua_tonumber(L, cnt));
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

	luaL_dostring(L, "function _TEXTMODULE_GMATCH_IFUNC(x) local pos,length=0,#x  return function()  pos = pos + 1  if pos>length then  return nil  else  return x[pos] end end end");
	lua_getglobal(L, "_TEXTMODULE_GMATCH_IFUNC");
	
	lua_newtable(L);
	try {
		if (std::regex_match(s, m, std::wregex(pattern))) {
			int size = m.size();

			for (int i = 0; i < size; i++)
			{
				lua_pushinteger(L, i + 1);
				lua_pushstring(L, WstrToStr(m[i].str()).c_str());
				lua_settable(L, -3);
			}
		}

		lua_pcall(L, 1, 1, 0);
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
	}
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

int mojibake(lua_State* L) {
	std::wstring str = L"";
	std::string hex = "";
	std::string ret = "";

	if (lua_type(L, 1) == LUA_TSTRING) {
		str = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}

	for (int i = 0; i < str.length(); i++)
	{
		auto unicode_c = str[i];
		if (unicode_c == L'\n') {
			hex = hex + "0d0a";
		}
		else if (unicode_c == L'\t') {
			hex = hex + "09";
		}
		else if (unicode_c == L'\b') {
			hex = hex + "08";
		}
		else if (unicode_c == L'\a') {
			hex = hex + "07";
		}
		else {
			auto utf8_c = UnicodeToUTF8(unicode_c);
			hex += std::format("{:x}", utf8_c);
		}
		
	}

	for (int i = 0; i < hex.length() / 2; i++) {
		std::string c = hex.substr(i * 2, 2);
		ret += std::stoi(c, 0, 16);
	}

	lua_pushstring(L, ret.c_str());
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
	bool utc = false;

	__time64_t time_t;


	if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == -1) {
		format = L"%c";
	}
	else if (lua_type(L, 1) == LUA_TSTRING) {
		format = StrToWstr(lua_tostring(L, 1));
	}
	else {
		return 0;
	}

	if (WstrToStr(format)[0] == '!') {  //UTC
		utc = true;
		format = format.substr(1);
	}


	std::chrono::time_point now = std::chrono::system_clock::now();

	if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == -1) {
		time_t = std::chrono::system_clock::to_time_t(now);
	}
	else if (lua_type(L, 2) == LUA_TNUMBER) {
		time_t = lua_tonumber(L, 2);
	}
	else {
		return 0;
	}


	if (format == L"*t") {
		struct tm tm;
		if (utc) { //tm struct
			_gmtime64_s(&tm, &time_t);
		}
		else {
			_localtime64_s(&tm, &time_t);
		}

		lua_newtable(L);
		lua_pushnumber(L, (long long)tm.tm_year + (long long)1900);
		lua_setfield(L, -2, "year");
		lua_pushnumber(L, (long long)tm.tm_mon+ (long long)1);
		lua_setfield(L, -2, "month");
		lua_pushnumber(L, tm.tm_mday);
		lua_setfield(L, -2, "day");
		lua_pushnumber(L, tm.tm_hour);
		lua_setfield(L, -2, "hour");
		lua_pushnumber(L, tm.tm_min);
		lua_setfield(L, -2, "min");
		lua_pushnumber(L, tm.tm_sec);
		lua_setfield(L, -2, "sec");
		lua_pushnumber(L, (long long)tm.tm_wday + (long long)1);
		lua_setfield(L, -2, "wday");
		lua_pushnumber(L, (long long)tm.tm_yday + (long long)1);
		lua_setfield(L, -2, "yday");
		lua_pushnumber(L, tm.tm_isdst);
		lua_setfield(L, -2, "isdst");

		return 1;
	}
	else {
		std::wstring f = L"{:" + format + L"}";

		std::chrono::sys_seconds now_sec = std::chrono::floor<std::chrono::seconds>(now); // •b’PˆÊ
		std::chrono::zoned_seconds zone_time;
		if (utc) {
			zone_time = { "UTC" , now_sec };
		}
		else {
			zone_time = { std::chrono::current_zone() , now_sec };
		}
		std::chrono::local_seconds local_time = zone_time.get_local_time();

		try {
			f = std::format(f, local_time);
		}
		catch (std::exception e) {
			luaL_error(L, e.what());
			return 1;
		}

		lua_pushstring(L, WstrToStr(f).c_str());
		return 1;
	}

}


int utf8_byte(lua_State* L) {
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
		auto r = UnicodeToUTF8(c);
		if (r != -1) {
			lua_pushinteger(L, r);
		}
		else {
			return 0;
		}

	}
	return j - i + 1;
}

int utf8_char(lua_State* L) {
	int cnt = 1;
	std::vector<unsigned long long> list;

	while (true) {
		int tp = lua_type(L, cnt);

		if (tp == LUA_TNUMBER) {
			unsigned long long r = UTF8ToUnicode(lua_tonumber(L, cnt));

			if(r!=-1){
				list.push_back(r);
			}
			else {
				return 0;
			}
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


/////////////////////////////////////////////////
//          FUNCTION REGISTRATION          //
////////////////////////////////////////////////

static luaL_Reg _TEXTMODULE_FUNCTION_REG[] = {
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
			{"mojibake", mojibake},

			{"time", time},
			{"date", date},

			{"utf8_char", utf8_char},
			{"utf8_byte", utf8_byte},

			{ nullptr, nullptr }
};

extern "C" {
	__declspec(dllexport) int luaopen_textmodule(lua_State* L) {

		luaL_register(L, "textmodule", _TEXTMODULE_FUNCTION_REG);
		return 1;
	}
}