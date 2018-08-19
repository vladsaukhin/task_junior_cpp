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

//global var
extern std::vector<ul> result;


void primes_alg(ul l, ul r);
void join_thread(std::vector<std::thread> & other);
void output();
void Quick_Sort(int l, int r);
void uniqueness();
void log_to_file(std::string&);
