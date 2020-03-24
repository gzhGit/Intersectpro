#include "pch.h"
#include "CppUnitTest.h"
#include "../Dll1/pch.h"
#include "../Dll1/framework.h"
#include "../Dll1/pch.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			double* d = solve_lc(-1, 4, 5, 2, 'L', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 2);
		}
		TEST_METHOD(TestMethod2)
		{
			double* d = solve_lc(0, 7, 1, 8, 'L', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod3)
		{
			double* d = solve_lc(0, 6, 1, 6, 'L', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 1);
		}
		TEST_METHOD(TestMethod4)
		{
			double* d = solve_lc(-1, 4, 5, 2, 'S', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 1);
		}
		TEST_METHOD(TestMethod5)
		{
			double* d = solve_lc(2, 3, 8, 1, 'S', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 1);
		}
		TEST_METHOD(TestMethod6)
		{
			double* d = solve_lc(2, 3, 5, 2, 'S', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 0);
		}

		TEST_METHOD(TestMethod7)
		{
			double* d = solve_cc(4, 4, 1, 'C', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod8)
		{
			double* d = solve_cc(4, 4, 3, 'C', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 2);
		}
		TEST_METHOD(TestMethod9)
		{
			double* d = solve_cc(4, 4, 4, 'C', 3, 3, 1, 'C');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod10)
		{
			double* d = solve_lc(5, 2, 2, 3, 'R', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 1);
		}
		TEST_METHOD(TestMethod11)
		{
			double* d = solve_lc(2, 3, 8, 1, 'S', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 1);
		}
		TEST_METHOD(TestMethod12)
		{
			double* d = solve_lc(8, 1, 2, 3, 'S', 3, 3, 3, 'C');
			Assert::AreEqual((int)d[0], 2);
		}
		TEST_METHOD(TestMethod13)
		{
			double* d = solve_ll(0, 0, 1, 1, 'L', 1, 0, 0, 1, 'L');
			Assert::AreEqual((int)d[0], 1);
		}
		TEST_METHOD(TestMethod14)
		{
			double* d = solve_ll(0, 0, 1, 1, 'L', 0, 1, 1, 2, 'L');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod15)
		{
			double* d = solve_ll(0, 0, 1, 1, 'S', 3, 0, 0, 3, 'L');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod16)
		{
			double* d = solve_ll(0, 0, 1, 1, 'S', -1, 0, 0, -1, 'L');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod17)
		{
			double* d = solve_ll(1, 1, 0, 0, 'R', 3, 0, 0, 3, 'L');
			Assert::AreEqual((int)d[0], 0);
		}
		TEST_METHOD(TestMethod18)
		{
			double* d = solve_ll(0, 0, 1, 1, 'R', -1, 0, 0, -1, 'L');
			Assert::AreEqual((int)d[0], 0);
		}
	};
}
