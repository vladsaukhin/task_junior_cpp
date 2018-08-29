#include"used_functions.h"

void log_to_file(std::string& mess) {

	std::ofstream fout("log.txt", std::ios_base::app);
	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	fout << "at " << std::ctime(&end_time) << "	->" << mess << std::endl;

}
