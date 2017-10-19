#pragma once
#include <string>
#include "Shlwapi.h"
#include <Windows.h>


#pragma comment (lib, "Shlwapi.lib")

class Utility
{
public:
	static std::string Path()
	{
		std::string path = "";

		// Full path to program
		char p[MAX_PATH];
		GetModuleFileNameA(NULL, p, MAX_PATH + 1);
		std::string fullpath = p;

		// Only the .exe
		std::string f = PathFindFileNameA(fullpath.c_str());

		// Remove program.exe from full path
		fullpath.erase(fullpath.size() - f.size(), f.size());

		return fullpath;
	}

};