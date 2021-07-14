#pragma once

std::string WstrToStr(std::wstring str);
std::wstring StrToWstr(std::string str);

std::wstring _jreplace(std::wstring String1, std::wstring String2, std::wstring String3, bool invert);
unsigned long long UnicodeToUTF8(unsigned long long code);
unsigned long long UTF8ToUnicode(unsigned long long code);
std::wstring toKatakana(std::wstring string, bool invert);
std::wstring toHalfwidth(std::wstring string, bool invert, bool space);

void debug_string(std::wstring message);