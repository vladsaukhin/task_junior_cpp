//created by SaVage on 17.08.2018
//read more in the file README.txt

#include"used_functions.h"

//shared container for every calculated prime number 
//global variable because you can not pass a vector to function for each a stream without copying
std::vector<int64_t> result;

//testing::Test


int main(int argc, char* argv[]) {

	//testing::InitGoogleTest(&argc, argv);

	int64_t leftRange{ 0 }, rightRange{ 0 };
	//to determine the line where the error occurred
	short count = 0;												
	std::string exceptionMess1("the left range is greater/equal than the right range on the interval:  ");
	std::string exceptionMess2("out of range[1; 999'999'999'999] on the interval:  ");
	std::vector<std::thread> mult—alculation;

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

		mult—alculation.push_back(std::thread(primes_alg, leftRange, rightRange));									//init all threads 

		el = el->NextSiblingElement();
	}

	join_thread(mult—alculation);

	output();
	system("pause");
	return 0;
		//RUN_ALL_TESTS();
}
