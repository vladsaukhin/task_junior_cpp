#pragma once

#include<stdexcept>
#include<fstream>
#include <chrono> 
#include<string>

#pragma warning(disable : 4996)
#include <ctime>

#include"tinyxml2.h"

constexpr auto MAX_RVAL = 999'999'999'999;


//outputting time and error text with location information in log file
void log_to_file(std::string&);

