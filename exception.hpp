#include <iostream>
#include <gerastr.hpp>
#pragma once
using namespace std;


class AnyException : exception 
{
	private:
		str name;
		str msg;
	
	public:
		AnyException();
		AnyException(str _name);
		virtual ~AnyException() {}
		
		void form_msg();
	
		str get_msg() const;
		void show() const;	
};


class IndexError : public AnyException
{
	public:
		IndexError();
};

class SizeError : public AnyException
{
	public:
		SizeError();
};

class TimeError : public AnyException
{
	public:
		TimeError();
};

class DateError : public AnyException
{
	public:
		DateError();
};

class NewTypeError : public AnyException
{
	public:
		NewTypeError();
};

