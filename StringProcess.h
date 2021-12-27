#pragma once
#ifndef _STRINGPROCESS_H_
#define _STRINGPROCESS_H_
#include <string>
#include "pch.h"
#include <sstream>
#include <iostream>
class StringProcess
{
public:
	static bool Replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}
	static int ConstCharToInt(const char* value)
	{
		std::stringstream strValue;
		strValue << value;
		int intValue;
		strValue >> intValue;
		return intValue;
	}
	static CString int2cstring(int num)
	{
		CString str; 
		str.Format(_T("%d"), num); 
		return str; 
	}
	static double cs2double(const char* value)
	{
		return std::atof(value); 
	}
	static double cs2double(CString str)
	{
		return _wtof(str);
	}
	static CString double2cs(double num)
	{
		CString str;
		str.Format(_T("%g"), num);
		return str;
	}
private:
	StringProcess(); 
};
#endif // _STRINGPROCESS_H_
