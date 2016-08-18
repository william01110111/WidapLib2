
#include "../../h/Mscl/StringFuncs.h"

namespace widap
{

//returns the file extension of a filename, or an empty string if there isn't one
string getFileExtension(const string& in)
{
	unsigned int i=in.find_last_of('.');
	
	if (i>=in.length()-1)
		return string();
	else
		return in.substr(i+1);
}

}

