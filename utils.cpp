#include "utils.h"


void log(std::string text, bool endl, bool flush) {
	std::cout << text;
	if(endl) std::cout << std::endl;
	else if(flush) std::cout << std::flush;
}

void read_file(std::string path, std::list<std::string> &dump, bool logging) {
	std::string text;
	std::ifstream file(path);
	while(std::getline(file, text)) {
		if(logging) log(text);
		dump.push_back(text);
	}
	file.close();
}

void split(std::string source, std::list<std::string> &dump, char delimiter) {
	std::stringstream text_stream(source);
	std::string text;
	while(std::getline(text_stream, text, delimiter)) {
		dump.push_back(text);
	}
}

instrument ilget(std::list<instrument> list, int index) {
	auto it = list.begin();
	for(int i = 0; i != index; i++) ++it;
	return *it;
}

T_TYPE t_type(std::string &in) {
	int i = 0; int acc = 0;
	for(auto it = in.begin(); it != in.end(); it++) {
		if(std::isdigit(static_cast<unsigned char>(*it))) acc++;
		i++;
	}
	if(i == acc) return T_TYPE::T_INT;
	if(strtod(in.c_str(), NULL) != 0) return T_TYPE::T_FLOAT;
	return T_TYPE::T_STRING;
}