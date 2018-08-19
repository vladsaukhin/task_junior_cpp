#include"used_functions.h"

//avoiding errors
//the vector will not be threaded into two streams simultaneously if the calculations take a long time
std::mutex mtx;

//function for searching primes num within a given range
//l - left range; r - right range
void primes_alg(ul l, ul r) {

	bool flag = false;
	if (l == 2) {
		std::lock_guard<std::mutex> lcg(mtx);								//critical section
		result.push_back(l);
	}

	if (!(l & 1)) l++;														// paired numbers are not primes
	if (!(r & 1)) r--;

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

}

//detach for asynchronous execution for each thread
void join_thread(std::vector<std::thread>& other) {

	for (ul i = 0; i < other.size(); i++) {
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

	for (ul i = 0; i < result.size(); i++) {
		out += std::to_string(result.at(i));
		out += " ";
	}

	el->SetText(out.c_str());

	doc.SaveFile("output.xml");
}

//
void Quick_Sort(int l, int r) {

	int i, j;
	i = l;
	j = r;
	ul middle = result.at((i + j) / 2);

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

	for (ul i = 0; i < result.size() - 1; i++) {
		for (ul j = i + 1; j < result.size(); j++) {
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