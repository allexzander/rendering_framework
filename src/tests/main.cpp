#include <iostream>
#include "..\core\string.h"
#include "..\core\vector.h"
#include <assert.h>


using namespace std;
using namespace CORE_LIB;

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

	TVector<String> fruits(0);
	fruits.push_back(_T("banana"));
	fruits.push_back(_T("apple"));
	fruits.push_back(_T("pineapple"));
	fruits.push_back(_T("pear"));
	fruits.push_back(_T("orange"));
	fruits.push_back(_T("lemon"));

	String fruitsString;

	for (TVector_const_iterator<String> it = fruits.constIterator(); it; ++it)
	{
		fruitsString += *it;
		fruitsString += _T(";");
	}

	fruitsString.erase(fruitsString.legth() - 1, 1);

	TVector<String> splittedString = fruitsString.split(_T(';'));

	bool testStringSplit = splittedString == fruits;

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
	bool testConcatSingleChar = String(_T("temp_strin")) + _T('g') == _T("temp_string")
		&& _T('b') + String(_T("eginEnd")) == String(_T("beginEnd"));
	bool testStartsWith = wantBeTrimmed.startsWith(_T("Maybe")) && smallString.startsWith(String(_T("sm")));
	bool testEndsWith = wantBeTrimmed.endsWith(_T("time?")) && equal2.endsWith(_T("win!"));

	bool testResult = testStringSplit && testConcat && testConcatAndAssign && testErase && testStringToDouble
		&& testCopyConstructAndAssignment && testLengthIsValid && testAssignmentOperator && testLesserGreaterEqual
		&& testToConstChar && testClear && testTrim && testConcatSingleChar && testStartsWith && testEndsWith;
	assert(testResult && "Error!!! testString has failed");

	return testResult;
}
bool testVector() 
{
	bool testResult = false;

	TVector<int> emptyVector;

	TVector<int> nonEmptyVector;
	nonEmptyVector.push_back(1);
	nonEmptyVector.push_back(5);
	nonEmptyVector.push_back(11);

	TVector<String> wordsVector(5);

	wordsVector.push_back(_T("door"));
	wordsVector.push_back(_T("nose"));
	wordsVector.push_back(_T("horse"));
	wordsVector.push_back(_T("big"));
	wordsVector.push_back(_T("oranje juice"));
	wordsVector.push_back(_T("small"));

	bool testVectorsHaveCorrectSizeAndCapacity = emptyVector.size() == 0 && nonEmptyVector.size() > 0 
		&& nonEmptyVector.size() == 3 && wordsVector.size() == 6 && wordsVector.capacity() == 7;

	bool testVectorContainsCorrectElements = wordsVector[0] == _T("door") && wordsVector[1] == _T("nose") 
		&& wordsVector[2] == _T("horse") && wordsVector[3] == _T("big") && wordsVector[4] == _T("oranje juice");

	

	testResult = testVectorsHaveCorrectSizeAndCapacity && testVectorContainsCorrectElements;

	assert(testResult && "Error!!! testVector has failed");
	return testResult;
}
int main()
{
	if (testString() && testVector())
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