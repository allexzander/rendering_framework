#include <iostream>
#include "..\core\string.h"
#include <assert.h>

using namespace std;
using CORE_LIB::String;

bool testString()
{
	String a = String(_T("This is a string "));
	String b = String(_T("and its continuation!"));

	bool testConcat = a + b == String(_T("This is a string and its continuation!"));

	String c = String();

	bool testConcatAndAssign = ((c += a) == String(_T("This is a string ")) && c == String((_T("This is a string "))));

	bool testErase = (c.erase(5, 2) == String(_T("This  a string ")) && c == String(_T("This  a string ")));

	bool testResult = testConcat && testConcatAndAssign && testErase;

	assert(testResult && "Error!!! testString has failed");

	return testResult;
}

int main()
{
	if (testString())
	{
		std::cout << "All tests successfully completed."<<std::endl;
	}
	else
	{
		std::cout << "!!!!ERROR!!! SOME TESTS HAVE FAILED!!!"<<std::endl;
	}

	system("pause");

	return 0;
}