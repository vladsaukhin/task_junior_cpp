
#include"Primes.h"

std::vector<int64_t> Primes::result = { 0 };

int main() {

	Primes::popLastItem();

	int64_t leftRange{ 0 }, rightRange{ 0 };
	//to determine the line where the error occurred
	short count = 0;
	std::string exceptionMess1("the left range is greater/equal than the right range on the interval:  ");
	std::string exceptionMess2("out of range[1; 999'999'999'999] on the interval:  ");
	std::vector<Primes> multÑalculation;
	std::vector<std::thread> th;

	tinyxml2::XMLDocument doc;

	try {
		doc.LoadFile("input.xml");
		if (doc.ErrorID() != 0) throw doc.ErrorIDToName(doc.ErrorID());
	}
	catch (const char* mess) {
		std::cerr << mess;
		std::string smess(mess);
		log_to_file(smess);
		system("pause>nul");
		return 0;
	}
	catch (...) {
		std::cerr << "some error with open file";
		std::string smess("some error with open file");
		log_to_file(smess);
	}

	//there is a strict typing of incoming data, you may not do exceptions processing
	tinyxml2::XMLElement* el = doc.FirstChildElement("root")->FirstChildElement("intervals")->FirstChildElement("interval");

	while (el != NULL) {

		leftRange = el->FirstChildElement("low")->Int64Text();
		rightRange = el->FirstChildElement("high")->Int64Text();
		++count;

		//max right range not more than INT64_MAX

		if (leftRange < 1 || rightRange < 1 || rightRange > MAX_RVAL) {
			exceptionMess2 += std::to_string(count);
			log_to_file(exceptionMess2);
			exceptionMess2.erase(exceptionMess2.length() - 1);
			el = el->NextSiblingElement();
			continue;

		}
		if (leftRange >= rightRange) {
			exceptionMess1 += std::to_string(count);
			log_to_file(exceptionMess1);
			exceptionMess1.erase(exceptionMess1.length() - 1);
			el = el->NextSiblingElement();
			continue;
		}

		multÑalculation.push_back(Primes(leftRange, rightRange));

		el = el->NextSiblingElement();
	}

	for (int64_t i = 0; i < multÑalculation.size(); i++) {
		th.push_back(std::thread(Primes::primes_alg, multÑalculation.at(i).getLeftRange(), multÑalculation.at(i).getRightRange()));

	}



	for (size_t i = 0; i < th.size(); i++) {
		th.at(i).join();
	}

	Primes::output();

	_sleep(1000);
	return 0;
}