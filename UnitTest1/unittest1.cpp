#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\task_junior_cpp\Primes.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestSortArg)
		{
			
			bool flag = Primes::Quick_Sort(5, 2);
			Assert::AreEqual<bool>(true, flag);
		}

		TEST_METHOD(TestSortArg2)
		{
		
			bool flag = Primes::Quick_Sort(30, 10);
			Assert::AreEqual<bool>(false, flag);
		}

	};
}