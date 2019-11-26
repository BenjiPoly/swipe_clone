#include "binary.h"
using namespace std;

Binary::Binary()
{
	binary_letter = -1;
}


void Binary::setBinary(char letter)
{
	
	/*
	cout << letter << endl;
	int i;
	for (i = 0; i<400; i++){
		//cout << i << endl;
		if ( letter == i)
			cout << i << endl;
	}
	*/
	
	if (letter == 42)
		binary_letter = 25;
	else if ( letter == 45)
		binary_letter = 0;
	else if (letter > 64 && letter < 74  )
		binary_letter = (letter - 64);
	else if (letter == 74)
		binary_letter = 27;
	else if (letter > 74 && letter < 79)
		binary_letter = (letter - 65);
	else if (letter == 79)
		binary_letter = 26;
	else if (letter > 79 && letter < 85)
		binary_letter = (letter - 66);
	else if (letter == 85)
		binary_letter = 24;
	else if (letter > 85 && letter < 91)
		binary_letter = (letter - 67);
}

int8_t Binary::getBinary_letter() const
{
	return binary_letter;
}

