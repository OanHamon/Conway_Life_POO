#include "pch.h"
#include "CppUnitTest.h"
#include "../../Conway_Life_POO/File_manager.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileManagerTests
{
    TEST_CLASS(FileManagerTests)
    {
    public:

        const string TEST_FILE = "test_file.txt";

        TEST_METHOD(TestSaveAndGetGrid)
        {
            File_manager fm(TEST_FILE);
            vector<vector<int>> grid = { {1, 2}, {3, 4} };
            Assert::IsTrue(fm.saveGrid(grid), L"saveGrid échoué");

            auto loadedGrid = fm.getGrid();
            Assert::AreEqual((size_t)2, loadedGrid.size(), L"Nombre de lignes incorrect");
            Assert::AreEqual((size_t)2, loadedGrid[0].size(), L"Nombre de colonnes incorrect");
            Assert::AreEqual(1, loadedGrid[0][0], L"Valeur incorrecte");
            Assert::AreEqual(4, loadedGrid[1][1], L"Valeur incorrecte");
        }

        TEST_METHOD(TestSaveEmptyGridFails)
        {
            File_manager fm(TEST_FILE);
            vector<vector<int>> emptyGrid;
            Assert::IsFalse(fm.saveGrid(emptyGrid), L"saveGrid devrait échouer avec une grille vide");
        }

        TEST_METHOD(TestGetGridInvalidData)
        {
            File_manager fm(TEST_FILE);
            auto grid = fm.getGrid();
            Assert::IsTrue(grid.empty(), L"La grille devrait être vide pour des données invalides");
        }
    };
}
