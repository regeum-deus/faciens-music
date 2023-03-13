#pragma once
#include <string>
#include <list>

//logic types
enum class logic {
	greater,
	lesser,
	equal,
	not_equal,
};

//for variables
template <typename T>
class variable {
public:
	std::string name;
	T val;
	variable();
	variable(std::string name, T input);
};


class instrument {
public:
	std::string name;

	int rule_amount;
	std::list<bool> iterating;
	std::list<logic> logic_gates;

	//parameters
	std::list<int> parameter_which; // are we using a string parameter, an int parameter, or a variable
	std::list<int> parameter_rule; // which rule are we using
	std::list<int> parameter_index; // which parameter/variable are we using
	std::list<std::string> parameter_s; // string parameters
	std::list<int> parameter_i; //int parameters

	//variables
	std::list<int> variable_types; //which variable type are we using
	std::list<variable<int>> var_ints; //integer variables
	std::list<variable<float>> var_floats; //floating variables
	std::list<variable<std::string>> var_strings; //string variables
	instrument();
	instrument(std::string name);
	void rule();
};

instrument Instrument(std::string name); //instrument constructor
