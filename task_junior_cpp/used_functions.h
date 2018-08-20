#pragma once

#include<iostream>
#include<vector>
#include<string>
#include <future>
#include<stdexcept>
#include<fstream>
#include <chrono> 

#pragma warning(disable : 4996)
#include <ctime>

#include"tinyxml2.h"

//short form to simplify the writing of the code
typedef unsigned long ul;

constexpr auto MAX_RVAL = 999'999'999'999;

//global var
extern std::vector<int64_t> result;

//function for searching primes num within a given range
//l - left range; r - right range
bool primes_alg(int64_t l, int64_t r);

//join for asynchronous execution for each thread
void join_thread(std::vector<std::thread> & other);

//sort the resulting vector: Quick_Sort();
//leave only the unique values in the vector, delete the extra :uniqueness()
//create a .xml file and output the values to the tag <primes/>
void output();

bool Quick_Sort(int l, int r);

void uniqueness();

//outputting time and error text with location information in log file
void log_to_file(std::string&);

