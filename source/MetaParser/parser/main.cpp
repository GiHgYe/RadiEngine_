#include <chrono>
#include <iostream>
#include "parser/parser.h"

int main(int argc, char* argv[]) {
	auto start_time = std::chrono::system_clock::now();

	int result = 0;

	if (argc == 6){
		bool is_show_error = "0" != std::string(argv[4]);
		MetaParser parser(argv[1], argv[2], argv[3], argv[4], is_show_error);
		result = parser.Parse();
		if (result != 0) {
			return result;
		}
		parser.GenerateFiles();
	}
	else{
		std::cout << "error: invalid arguments. arg count:" << argc << std::endl;
		return -1;
	}

	auto duration_time = std::chrono::system_clock::now() - start_time;

	std::cout << "Completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(duration_time).count() << "ms" << std::endl;

	return 0;
}