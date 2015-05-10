#include <iostream>
#include "..\core\string.h"
#include <assert.h>

using namespace std;
using CORE_LIB::String;

bool testString()
{
	String a = String(_T("This is a string "));
	String b = String(_T("and its continuation!"));
	String c = String();
	
	String doubleString1 = _T("12456.04242");
	String doubleString2 = _T("-5535123456.04242");
	String doubleString3 = _T("0.0353532");
	String doubleString4 = _T("-0.0353532");

	bool testStringToDouble = (static_cast<double>(doubleString1) == 12456.04242) && (static_cast<double>(doubleString2) == -5535123456.04242) &&
		(static_cast<double>(doubleString3) == 0.0353532) && static_cast<double>(doubleString4) == -0.0353532;

	bool testStringToInt = (static_cast<int>(doubleString1) == 12456) && (static_cast<int>(doubleString2) == -5535123456) &&
		(static_cast<int>(doubleString3) == 0) && static_cast<int>(doubleString4) == 0;

	bool testConcat = a + b == String(_T("This is a string and its continuation!"));
	bool testConcatAndAssign = ((c += a) == String(_T("This is a string ")) && c == String((_T("This is a string "))));
	bool testErase = (c.erase(5, 2) == String(_T("This  a string ")) && c == String(_T("This  a string ")));

	bool testResult = testConcat && testConcatAndAssign && testErase && testStringToDouble;

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