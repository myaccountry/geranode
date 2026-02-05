#include "exception.hpp"
using namespace std;


AnyException::AnyException() : name("Undefined")
{
	form_msg();
}

AnyException::AnyException(str _name) : name(_name) 
{
	form_msg();
}

void AnyException::form_msg()
{
	msg = "Exception of type: " + name;
}

str AnyException::get_msg() const
{
	return msg;
}

void AnyException::show() const
{
	cout << msg << endl;
}


IndexError::IndexError() 
: AnyException("IndexError (Index out of the array range)") {}

SizeError::SizeError() 
: AnyException("SizeError (New size is lower than zero\n\
or trying to decrease with expand() method)") {}

NewTypeError::NewTypeError()
: AnyException("NewTypeError (Incorrect type to construct from)") {}


TimeError::TimeError() 
: AnyException("TimeError (Incorrect format of time)") {}

DateError::DateError()
: AnyException("DateError (Incorrect format of date)") {}









