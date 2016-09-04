#pragma once
//#include "Exception.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

// Parent class of THREAD FOR MULTIFUNCTION
class MyThreadBase
{
	HANDLE hndlThread;		// pointer to void - handler 
	friend DWORD WINAPI ThreadProc(LPVOID lpParametr);
public:
	
	MyThreadBase();

	virtual ~MyThreadBase();

	virtual DWORD WINAPI ThreadFunction() = 0;

	void Run(void); 

	void Wait(void)const;

	void Close(void)const; 
}; 



// EXTERN GLOBAL FUNCTION FOR THREAD 
extern inline DWORD WINAPI ThreadProc(LPVOID lpParametr)
{
	MyThreadBase *currTread = reinterpret_cast<MyThreadBase*>(lpParametr); 
	return currTread->ThreadFunction(); 
}




// INHERITOR CLASS THREAD FOR CURRENT WORK WITH FILES 
class MyThreadFile : public MyThreadBase
{
public:
	// static variable for saving the path to file 
	static std::wstring wstrPath;
	// static variable for saving the content of file 
	static std::wstring wstrBuf;

	MyThreadFile(){}; 
	virtual ~MyThreadFile(){}; 

	// Override of member-function FOR CURRENT CLASS 
	DWORD WINAPI ThreadFunction()override; 
};
