#include"used_functions.h"

//avoiding errors
//the vector will not be threaded into two streams simultaneously if the calculations take a long time
std::mutex mtx;

bool primes_alg(int64_t l, int64_t r) {

	//added to demonstrate the work of the unit test
	//for values that do not satisfy this condition, checks are performed before creating the flow in main.cpp
	//return type void
	if (l < 1 || r < 1 || r > MAX_RVAL) return false;

	bool flag = false;

	if (l == 1) ++l;
	

	if (l == 2) {
		std::lock_guard<std::mutex> lcg(mtx);								//critical section
		result.push_back(l);
	}

	if (!(l & 1)) ++l;														// paired numbers are not primes
	if (!(r & 1)) --r;

	for (; l <= r; l += 2) {
		flag = true;

		if (l % 2 == 0) flag = false;

		for (ul i = 3; i <= round(sqrt(l)); i += 2)
			if (l%i == 0) {
				flag = false;
				break;
			}

		if (flag) {
			std::lock_guard<std::mutex> lcg(mtx);							//critical section
			result.push_back(l);
		}
	}

	return true;

}

void join_thread(std::vector<std::thread>& other) {

	for (int64_t i = 0; i < other.size(); i++) {
		other.at(i).join();
	}
}

void output()
{
	Quick_Sort(0, result.size() - 1);

	uniqueness();
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

bool Quick_Sort(int l, int r) {

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

void uniqueness() {

	for (int64_t i = 0; i < result.size() - 1; i++) {
		for (int64_t j = i + 1; j < result.size(); j++) {
			if (result.at(i) == result.at(j))
				result.erase(result.begin() + j);
		}
	}

	std::cout << "sec" << std::endl;

}

void log_to_file(std::string& mess) {

	std::ofstream fout("log.txt", std::ios_base::app);
	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	fout << "at " << std::ctime(&end_time) << "	->" << mess << std::endl;

}