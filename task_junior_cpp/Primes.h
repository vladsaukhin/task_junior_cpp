#pragma once

#include<iostream>
#include<future>
#include<vector>
#include"used_functions.h"


class Primes {

	int64_t leftRange;
	int64_t rightRange;
public:
	static std::vector<int64_t> result;

public:

	Primes();
	Primes(int64_t a, int64_t b);

	//copying
	Primes(const Primes& other) = default;
	Primes& operator=(const Primes& other) = default;

	//moving
	//Primes(Primes&& other) = default;
	//Primes& operator=(Primes&& other) = default;


	~Primes();

	int64_t getLeftRange() const {
		return leftRange;
	}
	int64_t getRightRange() const {
		return rightRange;
	}
	int64_t getItemResult(int64_t index) const {
		if (index >= 0 && index < result.size())
			return result.at(index);
		else throw std::out_of_range("the index went beyond the vector");
	}

	void setLeftRange(const int64_t l) {
		leftRange = l;
	}
	void setRightRange(const int64_t r) {
		rightRange = r;
	}
	int64_t setItemResult(int64_t index, int64_t value) {
		if (index >= 0 && index < result.size())
			result.at(index) = value;
		else throw std::out_of_range("the index went beyond the vector");
	}

	int64_t getLenthResultVector() const {
		return result.size();
	}

	static void popLastItem() {
		result.pop_back();
	}


public:
	//sort the resulting vector: Quick_Sort();
	//leave only the unique values in the vector, delete the extra :uniqueness()
	//create a .xml file and output the values to the tag <primes/>
	//only for output all data from vector<int64_t>
	//static method
	static void output();

	//function for searching primes num within a given range
	//l - left range; r - right range
	static void primes_alg(int64_t l, int64_t r);

	static void uniqueness();

	static bool Quick_Sort(int l, int r);


};


