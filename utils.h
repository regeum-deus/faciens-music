#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "types.h"

extern template class variable<int>;
extern template class variable<float>;
extern template class variable<std::string>;

enum class ERROR {
	invalid_usage,
	invalid_token,
};
enum class T_TYPE {
	T_INT,
	T_FLOAT,
	T_STRING,
};

void log(std::string s, bool endl=true, bool flush=true);
void read_file(std::string path, std::list<std::string> &dump, bool logging=false);
void split(std::string source, std::list<std::string> &dump, char delimiter='\n');
T_TYPE t_type(std::string &in);

instrument ilget(std::list<instrument> list, int index);