#include "Primes.h"


Primes::Primes()
	:leftRange(0), rightRange(0)
{}

Primes::Primes(int64_t a, int64_t b)
	: leftRange(a), rightRange(b)
{}

/*Primes::Primes(const Primes & other){
	leftRange = other.getLeftRange();
	rightRange = other.getRightRange();
}

Primes & Primes::operator=(const Primes & other)
{
	if (this == &other) return *this;
	leftRange = other.getLeftRange();
	rightRange = other.getRightRange();
	return *this;
}

Primes::Primes(Primes && other)
{
	leftRange = other.getLeftRange();
	rightRange = other.getRightRange();
}

Primes & Primes::operator=(Primes && other)
{
	if (this == &other) return *this;
	leftRange = other.getLeftRange();
	rightRange = other.getRightRange();
	return *this;
}*/


Primes::~Primes() {}

void Primes::uniqueness() {
	std::cout << "Uniqueness...";

	for (int64_t i = 0; i < result.size() - 1; i++) {
		for (int64_t j = i + 1; j < result.size(); j++) {
			if (result.at(i) == result.at(j))
				result.erase(result.begin() + j);
		}
	}

	std::cout << "Done" << std::endl;
}

bool Primes::Quick_Sort(int l, int r) {

	if (l > r) return false;

	int i, j;
	i = l;
	j = r;
	int middle = result.at((i + j) / 2);

	do {
		while (middle > result.at(i)) i++;
		while (middle < result.at(j)) j--;
		if (i <= j) {
			std::swap(result.at(i), result.at(j));
			i++;
			j--;
		}
	} while (i < j);

	if (i < r) Quick_Sort(i, r);
	if (j > l) Quick_Sort(l, j);
}

void Primes::output() {

	std::cout << "Sorting...";
	Primes::Quick_Sort(0, result.size() - 1);
	std::cout << "Done" << std::endl;

	Primes::uniqueness();

	std::string out;
	const char* xml =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<root>"
		"<primes></primes>"
		"</root>";

	tinyxml2::XMLDocument doc;
	doc.Parse(xml);
	tinyxml2::XMLElement* el = doc.FirstChildElement("root")->FirstChildElement("primes");

	for (int64_t i = 0; i < result.size(); i++) {
		out += std::to_string(result.at(i));
		out += " ";
	}

	el->SetText(out.c_str());

	doc.SaveFile("output.xml");

}

void Primes::primes_alg(int64_t l, int64_t r) {

	//std::cout << "Searching primes num...";

	//avoiding errors
	//the vector will not be threaded into two streams simultaneously if the calculations take a long time
	std::mutex mtx;

	bool flag = false;

	if (l == 1) ++l;


	if (l == 2) {
		std::lock_guard<std::mutex> lcg(mtx);								//critical section
		Primes::result.push_back(l);
	}

	if (!(l & 1)) ++l;														// paired numbers are not primes
	if (!(r & 1)) --r;

	for (; l <= r; l += 2) {
		flag = true;

		if (l % 2 == 0) flag = false;

		for (int64_t i = 3; i <= round(sqrt(l)); i += 2)
			if (l%i == 0) {
				flag = false;
				break;
			}

		if (flag) {
			std::lock_guard<std::mutex> lcg(mtx);							//critical section
			Primes::result.push_back(l);
		}
	}

	//std::cout << "Done" << std::endl;

}

