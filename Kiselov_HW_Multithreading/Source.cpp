//Написать программу, которая должна попросить пользователя ввести путь к файлу, 
//принять его, открыть, считать содержимое и вывести на консоль.
//Ввод - вывод инфорамции на / с консоли должен быть реализован и помощью юникода.

//Чтение данных с файла реализовать с помощью отдельного потока.
//Дескриптор потока хранить в обертке для гарантированного закрытия.

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <memory>
#include "WrapperHandle.h"
#include "MyFile.h"
#include "MyThreadBase.h"

// Global function of 
DWORD WINAPI ThreadFunction(LPVOID p)
{
	MyFile *mFile = reinterpret_cast<MyFile*>(p);
	return mFile->ReadFromFile();
}


// Initialization of static fields for classes which work with files 
std::wstring MyFile::wstrPath = L"\0";
std::wstring MyFile::wstrBuf = L"\0"; 

// Initialization of static fields for classes which work with files 
std::wstring MyThreadFile::wstrPath = L"\0"; 
std::wstring MyThreadFile::wstrBuf = L"\0";

int main()
{
	try
	{
		_wsetlocale(LC_ALL, L".866");

		std::wcout << L"Enter the path to file: ";
		std::wstring wstrTempPath;
		std::getline(std::wcin, wstrTempPath);
		MyFile::wstrPath = wstrTempPath;

		MyThreadFile threadFile;
		MyThreadFile::wstrPath = wstrTempPath; 

		WrapperHandle former_handle;

		// Инициализация указателя новым объектом класса для выподнения функции считывания с файла 
		MyFile *p = new MyFile;

		// Создание потока 
		*former_handle = CreateThread
			(0,
			0,
			ThreadFunction,
			p,
			0,
			0);

		// Проверка на создание дескриптора в обертке 
		if (!former_handle)
		{
			std::wcout << L"Error: " << GetLastError() << std::endl;
		}
		// Ожтдание завершения функции потока 
		if (WaitForSingleObject(*former_handle, INFINITE) != WAIT_OBJECT_0)
		{
			std::wcout << L"Error = " << GetLastError() << std::endl;
		}

		// Вывод результата работы через класс-обуртку
		std::wcout << std::endl << std::endl << L"||||||||||||||||WORKING WITH WRAPPER|||||||||||||||" 
			<< std::endl << std::endl;
		std::wcout << MyFile::wstrBuf << std::endl;

		// Вывод результата работы через дополнительный пользовательский класс ПОТОК 
		std::wcout << std::endl << std::endl << L"||||||||||||||||WORKING WITH CLASS THREAD|||||||||||||||" 
			<< std::endl << std::endl;

		threadFile.Run(); 
		threadFile.Wait(); 
		threadFile.Close(); 

		std::wcout << threadFile.wstrBuf << std::endl; 
	}
	catch (...)
	{
		std::wcout << L"Error = " << GetLastError() << std::endl;
	}
	return 0;
}