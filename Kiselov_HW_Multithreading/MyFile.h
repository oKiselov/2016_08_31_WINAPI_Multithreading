#pragma once
#include <iostream>
#include <exception>
#include <Windows.h>
#include <string>
#include <fstream>

// Class MyFile for operations with files 
class MyFile
{
public:
	// static variable for saving the path to file 
	static std::wstring wstrPath;
	// static variable for saving the content of file 
	static std::wstring wstrBuf; 
	
	MyFile(){}
	virtual ~MyFile(){}

	// Member-function of reading from file 
	DWORD ReadFromFile(void)
	{
		try
		{
			std::wifstream wifs(MyFile::wstrPath);
			if (!wifs.is_open())
			{
				std::wcout << L"Error = " << GetLastError() << std::endl;
			}

			wifs.seekg(0, std::ios::end);
			size_t sSizeOfFile = wifs.tellg();

			wifs.seekg(0, std::ios::beg);
			std::wstring wStrBuf(sSizeOfFile, '\0');
			wifs.read(&wStrBuf[0], wStrBuf.size());

			MyFile::wstrBuf = wStrBuf;

			wifs.close();
		}
		catch (...)
		{
			std::wcout << L"Error = " << GetLastError() << std::endl;
		}
		return 0;
	}
};
