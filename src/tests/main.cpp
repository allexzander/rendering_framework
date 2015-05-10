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

	String original = _T("Original string");
	String copyConstructed(original);
	String copyAssigned = original;

	String equal1 = String(String(_T("Hello! I am your twin!")));
	String equal2 = _T("Hello! I am your twin!");

	String smallString = _T("small");

	String toBeCleared = String(_T("Still dirty"));
	String shouldBeTrimmed1 = String(_T("            I am here!"));
	String shouldBeTrimmed2 = String(_T("    And I am here!"));
	String wantBeTrimmed = _T("Maybe                 other time?");
	String iHaveNoSence = _T("                                                     ");


	bool testStringToDouble = (static_cast<double>(doubleString1) == 12456.04242) && (static_cast<double>(doubleString2) == -5535123456.04242) &&
		(static_cast<double>(doubleString3) == 0.0353532) && static_cast<double>(doubleString4) == -0.0353532;

	bool testStringToInt = (static_cast<int>(doubleString1) == 12456) && (static_cast<int>(doubleString2) == -5535123456) &&
		(static_cast<int>(doubleString3) == 0) && static_cast<int>(doubleString4) == 0;

	bool testConcat = a + b == String(_T("This is a string and its continuation!"));
	bool testConcatAndAssign = ((c += a) == _T("This is a string ") && c == String((_T("This is a string "))));
	bool testErase = (c.erase(5, 2) == String(_T("This  a string ")) && c == String(_T("This  a string ")) &&
		(static_cast<int>(doubleString1.erase(0, 2)) == 456));
	bool testCopyConstructAndAssignment = original == copyConstructed && original == copyAssigned;
	bool testLengthIsValid = original.legth() == 15 && b.legth() == 21;
	bool testAssignmentOperator = (original = _T("Not original! Any moaaaaaar!")) == _T("Not original! Any moaaaaaar!");
	bool testLesserGreaterEqual = (original > a && equal1 == equal2 && b > a && equal1 == _T("Hello! I am your twin!")
		&& a < _T("Whaaaaaaat a biiiiiiiig StRing!")) && _T("Big string!") > smallString && _T("tiny") < smallString;
	const TCHAR* toConstChar = a.toConstChar();
	const TCHAR* toConstCharOperator = a;
	bool testToConstChar = _tccmp(_T("This is a string "), toConstChar) == 0 && _tccmp(toConstCharOperator, _T("This is a string ")) == 0;
	toBeCleared.clear();
	bool testClear = toBeCleared.legth() == 0;
	bool testTrim = _T("Maybe                 other time?") == wantBeTrimmed.trim() && shouldBeTrimmed1.trim() == _T("I am here!")
		&& shouldBeTrimmed2.trim() == _T("And I am here!") && iHaveNoSence.trim().legth() == 0;

	bool testResult = testConcat && testConcatAndAssign && testErase && testStringToDouble
		&& testCopyConstructAndAssignment && testLengthIsValid && testAssignmentOperator && testLesserGreaterEqual
		&& testToConstChar && testClear && testTrim;
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