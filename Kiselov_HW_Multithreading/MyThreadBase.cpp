#include "MyThreadBase.h"

MyThreadBase::MyThreadBase() :hndlThread(nullptr){}

MyThreadBase::~MyThreadBase()
{
	Close(); 
}

void MyThreadBase::Run()
{
	if (this->hndlThread)
		return;
	else
	{
		this->hndlThread = CreateThread
			(0,
			0,
			ThreadProc,
			this,
			0,
			0);
	}
	return;
}


void MyThreadBase::Wait()const
{
	if (WaitForSingleObject((this->hndlThread), INFINITE) != WAIT_OBJECT_0)
	{
		std::wcout << L"Error = " << GetLastError() << std::endl;
	}
	return; 
}


void MyThreadBase::Close()const 
{
	if (!this->hndlThread)
		return; 
	else
	{
		CloseHandle(this->hndlThread); 
	}
}

// Override of member-function FOR CURRENT CLASS 
DWORD MyThreadFile::ThreadFunction()
{
	try
	{
		std::wifstream wifs(MyThreadFile::wstrPath);
		if (!wifs.is_open())
		{
			std::wcout << L"Error = " << GetLastError() << std::endl;
		}

		wifs.seekg(0, std::ios::end);
		size_t sSizeOfFile = wifs.tellg();

		wifs.seekg(0, std::ios::beg);
		std::wstring wStrBuf(sSizeOfFile, '\0');
		wifs.read(&wStrBuf[0], wStrBuf.size());

		MyThreadFile::wstrBuf = wStrBuf;

		wifs.close();
	}
	catch (...)
	{
		std::wcout << L"Error = " << GetLastError() << std::endl;
	}
	return 0;
}
