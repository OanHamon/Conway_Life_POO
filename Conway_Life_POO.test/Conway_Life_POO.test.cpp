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
        TEST_METHOD(TestGrilleVide)
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
            size_t gridX = inGridInt.size();
            size_t gridY = inGridInt[0].size();
            Grid grid(static_cast<int>(gridX), static_cast<int>(gridY), &rule, inGridInt);

            for (int i = 0; i < nIter; i++)
            {
                grid.computeNextGen();
            }

            vector<vector<int>> outGridInt = grid.getGridInt();
            Assert::IsTrue(outGridInt == attendueGridInt, L"La grille finale ne correspond pas à la grille attendue.");
        }

        TEST_METHOD(TestGrilleCarre)
        {
            // paramètres
            vector<vector<int>> inGridInt = {
                {0, 0, 0, 0},
                {0 ,1, 1, 0},
                {0 ,1, 1, 0},
                {0, 0, 0, 0}
            };

            vector<vector<int>> attendueGridInt = {
                {0, 0, 0, 0},
                {0 ,1, 1, 0},
                {0 ,1, 1, 0},
                {0, 0, 0, 0}
            };

            int nIter = 5;
            ConwayRule rule;



            // test
            size_t gridX = inGridInt.size();
            size_t gridY = inGridInt[0].size();
            Grid grid(static_cast<int>(gridX), static_cast<int>(gridY), &rule, inGridInt);

            for (int i = 0; i < nIter; i++)
            {
                grid.computeNextGen();
            }

            vector<vector<int>> outGridInt = grid.getGridInt();
            Assert::IsTrue(outGridInt == attendueGridInt, L"La grille finale ne correspond pas à la grille attendue.");
        }

        TEST_METHOD(TestGrilleCarreObstacle)
        {
            // paramètres
            vector<vector<int>> inGridInt = {
                {0, 0, 0, 0},
                {0 ,1, 2, 0},
                {0 ,2, 1, 0},
                {-1,0, 0, 0}
            };

            vector<vector<int>> attendueGridInt = {
                {0, 0, 0, 0},
                {0 ,1, 2, 0},
                {0 ,2, 1, 0},
                {-1,0, 0, 0}
            };

            int nIter = 5;
            ConwayRule rule;



            // test
            size_t gridX = inGridInt.size();
            size_t gridY = inGridInt[0].size();
            Grid grid(static_cast<int>(gridX), static_cast<int>(gridY), &rule, inGridInt);

            for (int i = 0; i < nIter; i++)
            {
                grid.computeNextGen();
            }

            vector<vector<int>> outGridInt = grid.getGridInt();
            Assert::IsTrue(outGridInt == attendueGridInt, L"La grille finale ne correspond pas à la grille attendue.");
        }

        TEST_METHOD(TestGrilleBlinker)
        {
            // paramètres
            vector<vector<int>> inGridInt = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 1, 1, 1, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
            };

            vector<vector<int>> attendueGridInt = {
                {0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
            };

            int nIter = 5;
            ConwayRule rule;



            // test
            size_t gridX = inGridInt.size();
            size_t gridY = inGridInt[0].size();
            Grid grid(static_cast<int>(gridX), static_cast<int>(gridY), &rule, inGridInt);

            for (int i = 0; i < nIter; i++)
            {
                grid.computeNextGen();
            }

            vector<vector<int>> outGridInt = grid.getGridInt();
            Assert::IsTrue(outGridInt == attendueGridInt, L"La grille finale ne correspond pas à la grille attendue.");
        }

        TEST_METHOD(TestGrilleGlider)
        {
            // paramètres
            vector<vector<int>> inGridInt = {
                {0, 1, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {1, 1, 1, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
            };

            vector<vector<int>> attendueGridInt = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 1, 0, 1, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 1, 0, 0}
            };

            int nIter = 5;
            ConwayRule rule;



            // test
            size_t gridX = inGridInt.size();
            size_t gridY = inGridInt[0].size();
            Grid grid(static_cast<int>(gridX), static_cast<int>(gridY), &rule, inGridInt);

            for (int i = 0; i < nIter; i++)
            {
                grid.computeNextGen();
            }

            vector<vector<int>> outGridInt = grid.getGridInt();
            Assert::IsTrue(outGridInt == attendueGridInt, L"La grille finale ne correspond pas à la grille attendue.");
        }
    };
}