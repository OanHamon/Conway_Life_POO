#include "pch.h"
#include "CppUnitTest.h"
#include "../FileManager.h"
#include "../FileManager.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace FileManagerTests
{
    TEST_CLASS(FileManagerTests)
    {
    public:
        TEST_METHOD(TestSaveAndGetGrid)
        {
            FileManager fm("grid.txt");

            vector<vector<int>> grid = { {1, 0}, {-1, 1} };
            Assert::IsTrue(fm.saveGrid(grid), L"saveGrid échoué");

            auto loadedGrid = fm.getGrid();
            Assert::AreEqual((size_t)2, loadedGrid.size(), L"Nombre de lignes incorrect");
            Assert::AreEqual((size_t)2, loadedGrid[0].size(), L"Nombre de colonnes incorrect");
            Assert::AreEqual(-1, loadedGrid[1][0], L"Valeur incorrecte");
        }
    };
}