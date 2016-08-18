#include "../../h/Mscl/Error.h"

#include <iostream>

namespace widap
{

Error err("global error: ");

void (*Error::defaultPost)(std::string)=defaultDefaultPost;

Error::Error()
{
	setPrefix("error: ");
	setPost(0);
}

Error::Error(std::string prefixIn)
{
	Error();
	setPrefix(prefixIn);
}

void Error::setPrefix(std::string in)
{
	prefix=in;
}

void Error::setPost(void (*in)(std::string))
{
	post=in;
}

void Error::setDefaultPost(void (*in)(std::string))
{
	defaultPost=in;
}

void Error::defaultDefaultPost(std::string in)
{
	std::cout << in << std::endl;
}

}

