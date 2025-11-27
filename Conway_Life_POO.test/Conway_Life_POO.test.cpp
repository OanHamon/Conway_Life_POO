#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../Grid.h"
#include "../Grid.cpp"
#include "../Rule.h"
#include "../Rule.cpp"
#include "../Cell.h"
#include "../Cell.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace GridGameCalculationTest
{
    TEST_CLASS(GridGameCalculationTest)
    {
    public:
        TEST_METHOD(TestGrilleAttendue)
        {
            // paramètres
            vector<vector<int>> inGridInt = {
                {0, 0},
                {0, 0}
            };

            vector<vector<int>> attendueGridInt = {
                {0, 0},
                {0, 0}
            };

            int nIter = 5;
            ConwayRule rule;



            // test
            Grid grid(inGridInt.size(), inGridInt[0].size(), &rule, inGridInt);

            for (int i = 0; i < nIter; i++)
            {
                grid.computeNextGen();
            }

            vector<vector<int>> outGridInt = grid.getGridInt();
            Assert::IsTrue(outGridInt == attendueGridInt, L"La grille finale ne correspond pas à la grille attendue.");
        }
    };
}