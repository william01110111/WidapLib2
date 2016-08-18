
#pragma once

///this file contains the prototype for various useful string functions

#include <string>

using std::string;

namespace widap
{

//returns the file extension of a filename, or an empty string if there isn't one
string getFileExtension(const string& in);

}

