#pragma once
#include<iostream>
#include<windows.h>

#define COLOR_BLUE blue
#define COLOR_RED red
#define COLOR_GREEN green
#define COLOR_YELLOW yellow
#define COLOR_WHIT white
#define COLOR_DEFAULT grey

inline std::ostream& blue(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& red(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_ERROR_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED | 
FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& green(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& yellow(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_ERROR_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN | FOREGROUND_RED |
		FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& white(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED | FOREGROUND_GREEN |
		FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& grey(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED | FOREGROUND_GREEN |
		FOREGROUND_BLUE);
	return s;
}