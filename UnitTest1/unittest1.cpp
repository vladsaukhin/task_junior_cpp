#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\task_junior_cpp\used_functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestSortArg)
		{
			bool flag = Quick_Sort(5, 2);
			Assert::AreEqual<bool>(true, flag);
		}

		TEST_METHOD(TestPrimesAlgArg)
		{
			bool flag = primes_alg(10,100);
			Assert::AreEqual<bool>(true, flag);
		}

	};
}