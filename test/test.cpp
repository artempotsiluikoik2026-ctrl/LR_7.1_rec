#include "pch.h"
#include "CppUnitTest.h"
#include "../ЛР 7.1 рек/ЛР 7.1 рек.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test71rec
{
	TEST_CLASS(test71rec)
	{
	public:

		int** MakeMatrix(const int rows, const int cols, const int* data)
		{
			int** Q = new int* [rows];
			for (int i = 0; i < rows; i++)
			{
				Q[i] = new int[cols];
				for (int j = 0; j < cols; j++)
					Q[i][j] = data[i * cols + j];
			}
			return Q;
		}

		void DeleteMatrix(int** Q, const int rows)
		{
			for (int i = 0; i < rows; i++)
				delete[] Q[i];
			delete[] Q;
		}

		TEST_METHOD(TestChange)
		{
			int data[6] = { 1, 2, 3, 4, 5, 6 };
			int expected[6] = { 3, 2, 1, 6, 5, 4 };
			int** Q = MakeMatrix(2, 3, data);
			Change(Q, 0, 2, 2, 0);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					Assert::AreEqual(expected[i * 3 + j], Q[i][j]);
			DeleteMatrix(Q, 2);
		}

		TEST_METHOD(TestSort)
		{
			int data[12] = { 5, 9, 5, 9,   1, 2, 3, 4,   7, 8, 9, 6 };
			int expected[12] = { 9, 9, 5, 5,   2, 4, 1, 3,   8, 6, 7, 9 };
			int** Q = MakeMatrix(3, 4, data);
			Sort(Q, 3, 4, 0);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 4; j++)
					Assert::AreEqual(expected[i * 4 + j], Q[i][j]);
			DeleteMatrix(Q, 3);
		}

		TEST_METHOD(TestCalc)
		{
			int data[12] = { 10, 9, 5, 5,   2, 4, 1, 3,   8, 6, 7, 9 };
			int expected[12] = { 10, 9, 5, 5,   0, 0, 1, 3,   0, 0, 7, 9 };
			int** Q = MakeMatrix(3, 4, data);
			int S = 0;
			int k = 0;
			CalcRows(Q, 3, 4, 0, S, k);
			Assert::AreEqual(20, S);
			Assert::AreEqual(4, k);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 4; j++)
					Assert::AreEqual(expected[i * 4 + j], Q[i][j]);
			DeleteMatrix(Q, 3);
		}

		TEST_METHOD(TestCreate_Range)
		{
			int data[12] = { 0 };
			int** Q = MakeMatrix(3, 4, data);
			CreateRows(Q, 3, 4, 7, 62, 0);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 4; j++)
				{
					Assert::IsTrue(Q[i][j] >= 7);
					Assert::IsTrue(Q[i][j] <= 62);
				}
			DeleteMatrix(Q, 3);
		}
	};
}