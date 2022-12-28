#include <iostream>

#include "PredefinedStaticMember.h"

class MyClass {
	CREATE_STATIC_VARIABLE(int, value, 0)
public:
	MyClass() {
		ACCESS_STATIC_VARIABLE(value)++;
	}
	~MyClass() {
		ACCESS_STATIC_VARIABLE(value)--;
	}
	void print(std::ostream& os) const {
		os << ACCESS_STATIC_VARIABLE(value);
	}
};

int main() {
	MyClass a;

	a.print(std::cout);
	std::cout << std::endl;

	MyClass b;

	a.print(std::cout);
	std::cout << std::endl;
}
