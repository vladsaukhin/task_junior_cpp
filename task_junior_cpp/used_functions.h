#pragma once

#include<iostream>
#include<vector>
#include<string>
//#include<algorithm>
//#include<iterator>
#include <future>
#include<stdexcept>

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
