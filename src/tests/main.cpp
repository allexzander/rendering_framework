#include <iostream>
#include "..\core\containers\string.h"
#include "..\core\containers\vector.h"
#include "..\core\containers\list.h"
#include "..\core\containers\map.h"
#include "..\core\containers\stack.h"
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

	TVectorArray<String> fruits(0);
	fruits.push_back(_T("banana"));
	fruits.push_back(_T("apple"));
	fruits.push_back(_T("pineapple"));
	fruits.push_back(_T("pear"));
	fruits.push_back(_T("orange"));
	fruits.push_back(_T("lemon"));

	fruits.erase(0);

	String coconut = fruits.at(3);

	String fruitsString;

	for (TVectorArray_const_iterator<String> it = fruits.constIterator(); it; ++it)
	{
		fruitsString += *it;
		fruitsString += _T(";");
	}

	fruitsString.erase(fruitsString.legth() - 1, 1);

	TVectorArray<String> splittedString = fruitsString.split(_T(';'));

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

	TVectorArray<int> emptyVector;

	TVectorArray<int> nonEmptyVector;
	nonEmptyVector.push_back(1);
	nonEmptyVector.push_back(5);
	nonEmptyVector.push_back(11);

	TVectorArray<String> wordsVector(5);

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
bool testList()
{
	bool testResult = true;

	TList<int> intList;

	bool sizeAfterConstruction = intList.size() == 0;

	intList.push_back(5);
	intList.push_back(7);
	intList.push_back(9);
	intList.push_back(11);

	bool sizeAfter4ElementsPushed = intList.size() == 4;

	intList.clear();

	bool sizeAfterClear = intList.size() == 0;

	intList.push_back(7);
	intList.push_back(9);

	bool sizeAfter2ElementsPushed = intList.size() == 2;

	intList.pop_back();
	intList.pop_back();

	bool sizeAfter2ElementsPopped = intList.size() == 0;

	intList.push_back(25);

	bool sizeAfter1ElementPushed = intList.size() == 1;

	intList.push_back(41);

	TList_iterator<int> insertAfterHead = intList.begin();
	intList.insert(insertAfterHead, 99);
	TList_iterator<int> insertAfterTail = intList.end();
	intList.insert(insertAfterTail, 156);

	TList_iterator<int> itMiddle = intList.iterator();

	for (; itMiddle; ++itMiddle)
	{
		if (*itMiddle == 99)
		{
			break;
		}
	}
	//!!!ADD MOAAAAR TESTS!!!
	if (itMiddle)
	{
		intList.insert(itMiddle, 666);
	}

	TList<String> listStrings;
	listStrings.push_front(_T(" world!"));
	listStrings.push_front(_T(" my brave new"));
	listStrings.push_front(_T("Hello"));

	TList<String> copyListStrings(listStrings);
	TList<String> copyAssignedListStrings = copyListStrings;

	TList_iterator<String> foundIt = listStrings.findFirst(_T(" world!"));
	TList_iterator<String> copyIt = foundIt;
	listStrings.erase(foundIt);
	listStrings.erase(_T(" my brave new"));
	testResult = sizeAfterConstruction && sizeAfterClear 
		&& sizeAfter2ElementsPushed && sizeAfter2ElementsPopped && sizeAfter1ElementPushed;

	return testResult;
}
bool testMap()
{
	TMap<String,int> intMap;
	intMap.insert(String(_T("Fifty Three")), 53);
	intMap.insert(String(_T("Sixty One")), 61);
	intMap.insert(String(_T("Forty Nine")), 49);
	intMap.insert(String(_T("Elleven")), 11);
	intMap.insert(String(_T("Ninety Nine")), 99);
	intMap.insert(String(_T("Ninety Nine")), 99);
	intMap.insert(String(_T("One hundred")), 101);
	intMap.insert(String(_T("One hundred")), 101);
	intMap.insert(String(_T("One hundred")), 101);
	intMap.insert(String(_T("One hundred")), 101);
	intMap.insert(String(_T("One hundred")), 101);
	intMap.insert(String(_T("Eighty six")), 86);
	intMap.insert(String(_T("Thirty Three")), 33);
	intMap.insert(String(_T("Twenty One")), 21);

	const TMapNode<String, int>* pFoundNode = intMap.find(_T("Ninety Nine"));

	TMap<String, int> intMapCopy(intMap);

	int *pBuffer = new int[intMapCopy.size()];
	memset(pBuffer, 0, sizeof(int) * intMapCopy.size());

	intMapCopy.toArray(pBuffer);

	for (uint32 i = 0; i < intMapCopy.size(); ++i)
	{
		std::cout << "pBuffer[i]: " << pBuffer[i] << std::endl;
	}

	int *pBufferCopy = new int[intMap.size()];
	memset(pBufferCopy, 0, sizeof(int) * intMap.size());

	intMap.toArray(pBufferCopy);

	for (uint32 i = 0; i < intMap.size(); ++i)
	{
		std::cout << "pBufferCopy[i]: " << pBufferCopy[i] << std::endl;
	}
	delete pBufferCopy;
	return true;
}
bool testStack()
{
	bool result = true;
	int A = 5;
	int B = 11;
	int C = 21;

	int* pIntA = &A;
	int* pIntB = &B;
	int* pIntC = &C;

	TStack<int*> intStack;

	intStack.push(pIntA);
	intStack.push(pIntB);
	intStack.push(pIntC);

	TStack<int*> copyIntStack = intStack;


	int* pInt = intStack.pop();
	pInt = intStack.pop();
	pInt = intStack.pop();
	

	return result;
}

int main()
{
	if (testString() && testVector() && testList() && testMap() && testStack())
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