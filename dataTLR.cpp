// Author:	Jerry Strickland
// Assignment:	Homework2
// File Name:	datatl.c
// Course:	COSC 2325 Fall 2017 TTH (section 32569)
// Instructor:	Roie Black
//
// Exploring data types, create each type
// and display the range of values

#include <limits>
#include <iostream>

int main() {

	bool boolVar = true;
	char charVar = 'a';
	signed char signCharVar = -1;
	unsigned char unsignCharVar = 1;
	wchar_t wchar_tVar = L'B';
	char16_t char16_tVar = u'C';
	char32_t char32_tVar = U'D';
	short shortVar = -2;
	signed short signShortVar = -2;
	unsigned short unsignShortVar = 2;
	int intVar = -1;
	signed int signIntVar = -1;
	unsigned int unsignIntVar = 1;
	long longVar = -3;
	signed long signLongVar = -3;
	unsigned long unsignLongVar = 3;
	long long longLongVar = -3;
	signed long long signLongLongVar = -3;
	unsigned long long unsignLongLongVar = 3;
	float floatVar = 1.1;
	double doubleVar = 2.2;
	long double longDoubleVar = 3.3;
//	void
	float *pointerVar = nullptr;

	std::cout << "type\t\t\tsize\tlowest\thighest\n";
	std::cout << "bool\t\t\t"
		  << sizeof(boolVar) << "\t"
		  << std::numeric_limits<bool>::min() << "\t"
		  << std::numeric_limits<bool>::max() << "\n";

	std::cout << "char\t\t\t"
		  << sizeof(charVar) << "\t"
		  << std::numeric_limits<char>::min() << "\t"
		  << std::numeric_limits<char>::max() << "\n";
	std::cout << "signed char\t\t"
		  << sizeof(signCharVar) << "\t"
		  << std::numeric_limits<signed char>::min() << "\t"
		  << std::numeric_limits<signed char>::max() << "\n";
	std::cout << "unsigned char\t\t"
		  << sizeof(unsignCharVar) << "\t"
		  << std::numeric_limits<unsigned char>::min() << "\t"
		  << std::numeric_limits<unsigned char>::max() << "\n";

	std::cout << "wchar_t\t\t\t"
		  << sizeof(wchar_tVar) << "\t"
		  << std::numeric_limits<wchar_t>::min() << "\t"
		  << std::numeric_limits<wchar_t>::max() << "\n";
	std::cout << "char16_t\t\t"
		  << sizeof(char16_tVar) << "\t"
		  << std::numeric_limits<char16_t>::min() << "\t"
		  << std::numeric_limits<char16_t>::max() << "\n";
	std::cout << "char32_t\t\t"
		  << sizeof(char32_tVar) << "\t"
		  << std::numeric_limits<char32_t>::min() << "\t"
		  << std::numeric_limits<char32_t>::max() << "\n";

	std::cout << "short\t\t\t"
		  << sizeof(shortVar) << "\t"
		  << std::numeric_limits<short>::min() << "\t"
		  << std::numeric_limits<short>::max() << "\n";
	std::cout << "signed short\t\t"
		  << sizeof(signShortVar) << "\t"
		  << std::numeric_limits<signed short>::min() << "\t"
		  << std::numeric_limits<signed short>::max() << "\n";
	std::cout << "unsigned short\t\t"
		  << sizeof(unsignShortVar) << "\t"
		  << std::numeric_limits<unsigned short>::min() << "\t"
		  << std::numeric_limits<unsigned short>::max() << "\n";

	std::cout << "int\t\t\t"
		  << sizeof(intVar) << "\t"
		  << std::numeric_limits<int>::min() << "\t"
		  << std::numeric_limits<int>::max() << "\n";
	std::cout << "signed int\t\t"
		  << sizeof(signIntVar) << "\t"
		  << std::numeric_limits<signed int>::min() << "\t"
		  << std::numeric_limits<signed int>::max() << "\n";
	std::cout << "unsigned int\t\t"
		  << sizeof(unsignIntVar) << "\t"
		  << std::numeric_limits<unsigned int>::min() << "\t"
		  << std::numeric_limits<unsigned int>::max() << "\n";

	std::cout << "long\t\t\t"
		  << sizeof(longVar) << "\t"
		  << std::numeric_limits<long>::min() << "\t"
		  << std::numeric_limits<long>::max() << "\n";
	std::cout << "signed long\t\t"
		  << sizeof(signLongVar) << "\t"
		  << std::numeric_limits<signed long>::min() << "\t"
		  << std::numeric_limits<signed long>::max() << "\n";
	std::cout << "unsigned long\t\t"
		  << sizeof(unsignLongVar) << "\t"
		  << std::numeric_limits<unsigned long>::min() << "\t"
		  << std::numeric_limits<unsigned long>::max() << "\n";

	std::cout << "long long\t\t"
		  << sizeof(longLongVar) << "\t"
		  << std::numeric_limits<long long>::min() << "\t"
		  << std::numeric_limits<long long>::max() << "\n";
	std::cout << "signed long long\t"
		  << sizeof(signLongLongVar) << "\t"
		  << std::numeric_limits<signed long long>::min() << "\t"
		  << std::numeric_limits<signed long long>::max() << "\n";
	std::cout << "unsigned long long\t"
		  << sizeof(unsignLongLongVar) << "\t"
		  << std::numeric_limits<unsigned long long>::min() << "\t"
		  << std::numeric_limits<unsigned long long>::max() << "\n";

	std::cout << "float\t\t\t"
		  << sizeof(floatVar) << "\t"
		  << std::numeric_limits<float>::min() << "\t"
		  << std::numeric_limits<float>::max() << "\n";

	std::cout << "double\t\t\t"
		  << sizeof(doubleVar) << "\t"
		  << std::numeric_limits<double>::min() << "\t"
		  << std::numeric_limits<double>::max() << "\n";

	std::cout << "long double\t\t"
		  << sizeof(longDoubleVar) << "\t"
		  << std::numeric_limits<long double>::min() << "\t"
		  << std::numeric_limits<long double>::max() << "\n";

	std::cout << "pointer\t\t\t"
		  << sizeof(pointerVar) << "\n";

	return 0;
}
