
#pragma once

#include <sstream>

///Ok, listen up because without this explanation (and perhaps with it) this class makes no fucking sense
//I mean, its not that complicated, the way it works is a member operator template function gets a const
//reference which it adds to a stringstream unless it is sent a 'this' pointer in which case it overrides
//the template and uses a function which calls a function pointer, unless that is null (as is default) in
//which case it calls a static member function pointer with the data from the stringstream added to a preset
//prefix string. simple, right?

//luckily I think it works, so all you need to know is how to use it.
//to throw an error message:
//err << "there was an error with " << filename << " on section " << num << err;
//note that the global err variable is used like cout but it is at both the start and the end
//also note that there are no line breaks. they will work, but they are generally not needed as they are
//automatically inserted after each error

//err is a global instance of Error. most classes (such as Image) will make there own instance.
//each instance can have its own prefix (set with .setPrefix), this way error messages printed with err
//	start with "error: " but this can be removed or changed in each instance of the class

//also, where the error strings go can be changed. by default they are printed using cout, but that can be changed in 2 ways

//first, if you call the static function Error::setDefaultPost([function pointer]) with a function that accepts a string, then
//most instances of Error will start using the function you provided to post their error messages.

//second, if you call err.setPost([function pointer]) on an instance of Error, only that instance will use
//	the function you provide.

namespace widap
{

class Error
{
public:
	Error();
	Error(std::string prefixIn);
	
	//allows writing to the error message just like cout
	//since its a template, it must be in this header
	template<typename T>
	Error& operator << (const T &data)
	{
		ss << data;
		
		return *this;
	}
	
	Error& operator << (const Error &data)
	{
		if (post)
			post(prefix+ss.str());
		else
			defaultPost(prefix+ss.str());
		
		ss.str(std::string());
		
		return *this;
	}
	
	void setPrefix(std::string in);
	
	void setPost(void (*in)(std::string));
	static void setDefaultPost(void (*in)(std::string));
	
private:
	std::string prefix;
	void (*post)(std::string);
	static void (*defaultPost)(std::string);
	std::stringstream ss;
	
	//the default post function, just prints it to cout
	static void defaultDefaultPost(std::string in);
};

extern Error err;

}

