#include "types.h"


template <typename T>
variable<T>::variable(std::string name, T input) {
	this->name = name;
	this->val = input;
}
template <typename T>
variable<T>::variable() {}

instrument::instrument() {}
instrument::instrument(std::string name) {
	this->name = name;
	this->rule_amount = 0;
}
void instrument::rule() {
	++rule_amount;
}

template class variable<int>;
template class variable<float>;
template class variable<std::string>;