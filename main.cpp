#include <utility>

#include "types.h"
#include "utils.h"

extern template class variable<int>;
extern template class variable<float>;
extern template class variable<std::string>;

void read_data(std::string path, std::list<std::string> &data);
void build(std::list<std::string> &data, std::list<instrument> &instruments);


std::list<std::string> data;
std::list<instrument> instruments;
int main(int argc, char *argv[]) {
	if(argc < 2) {
		log("usage: " + std::string(argv[0]) + " <path> <optional: view_end>");
		exit(std::to_underlying(ERROR::invalid_usage));
	}
	read_data(argv[1], data);
	build(data, instruments);
	return 0;
}


void read_data(std::string path, std::list<std::string> &data) {
	std::list<std::string> dummy;
	std::list<std::string> dummy_2;
	read_file(path, dummy, true);
	for(auto it = dummy.begin(); it != dummy.end(); it++) split(*it, dummy_2);
	for(auto it = dummy_2.begin(); it != dummy_2.end(); it++) split(*it, data, ' ');
}

void build(std::list<std::string> &data, std::list<instrument> &instruments) {
	bool declaration = false;
	bool ignoring = false;
	bool ruling = false;

	std::string acc_s;
	int acc_i[10];

	int operating_instrument = 0;
	int operating_rule = 0;
	int piece_of_rule = 0;
	for(auto it = data.begin(); it != data.end(); it++) {
		std::string token = (*it);
		if(token == "/") ignoring = !ignoring;
		if(ignoring) continue;

		if(token == "!") {
			if(declaration) instruments.push_back(instrument(acc_s));
			else declaration = true;
		}
		else if(token == "end") ++operating_instrument;
		else if(token == "=") {
			auto x = --it;
			++it;
			auto i = (*(++it));
			
			switch(t_type(i)) {
			case T_TYPE::T_INT:
				ilget(instruments, operating_instrument).variable_types.push_back(0);
				ilget(instruments, operating_instrument).variable_types.push_back(ilget(instruments, operating_instrument).var_ints.size() - 1);
				ilget(instruments, operating_instrument).var_ints.push_back(variable(*x, stoi(i)));
				break;
			case T_TYPE::T_FLOAT:
				ilget(instruments, operating_instrument).variable_types.push_back(1);
				ilget(instruments, operating_instrument).variable_types.push_back(ilget(instruments, operating_instrument).var_floats.size() - 1);
				ilget(instruments, operating_instrument).var_floats.push_back(variable(*x, (float)strtod(i.c_str(), NULL)));
				break;
			case T_TYPE::T_STRING:
				ilget(instruments, operating_instrument).variable_types.push_back(2);
				ilget(instruments, operating_instrument).variable_types.push_back(ilget(instruments, operating_instrument).var_strings.size() - 1);
				ilget(instruments, operating_instrument).var_strings.push_back(variable(*x, i));
				break;
			}
		}
		else if(token == ":") {
			if(!ruling) ilget(instruments, operating_instrument).rule();
			else piece_of_rule = 0;
			ruling = !ruling;
		}
		else if(token == ">") {
			if(ruling) {
				ilget(instruments, operating_instrument).logic_gates.append(logic::greater);
				.. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..//START HERE		
			}
			else {
				log("Invalid token '>'. Logic must be placed in rules.");
				exit(ERROR::invalid_token);
			}
		}
		else if(token == ",") {
			++piece_of_rule;
		}
	}
}