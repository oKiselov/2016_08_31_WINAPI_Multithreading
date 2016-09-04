//Написать класс - обертку для хранения дескриптора потока.

#pragma once

#include <Windows.h>

class WrapperHandle
{
	// Private member - thread descriptor - pointer to void  
	void* formerHandle; 
public:
	// Default constructor 
	WrapperHandle() :formerHandle(nullptr){}

	// Copy constructor 
	WrapperHandle(HANDLE h) :formerHandle(h){}

	// Virtual distructor, which closes existing handle 
	virtual ~WrapperHandle()
	{
		this->CloseFormerHandle(); 
	}	

	// Casting 
	operator HANDLE()const throw()
	{
		return this->formerHandle; 
	}

	// Casting 
	operator HANDLE*() throw()
	{
		return &this->formerHandle; 
	}

	// Member-function of handle closing
	void CloseFormerHandle()throw()
	{
		if (this->formerHandle)
		{
			CloseHandle(this->formerHandle); 
			this->formerHandle = nullptr; 
		}
	}

};

