#include <iostream>
#include <string>
using std::string;

class Binary
{
private:
	int8_t binary_letter;
public:
	Binary();
	void setBinary(char letter);
	int8_t getBinary_letter() const;
};
