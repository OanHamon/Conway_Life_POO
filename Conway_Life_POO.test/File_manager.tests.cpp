
#include "pch.h"
#include "CppUnitTest.h"
#include "../FileManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileManagerTests
{
    TEST_CLASS(FileManagerTests)
    {
    public:
        TEST_METHOD(TestSaveAndGetGrid)
        {/*
            std::string testPath = "grid.txt";
            File_manager fm(testPath);

            std::vector<std::vector<int>> grid = { {1, 2}, {3, 4} };
            Assert::IsTrue(fm.saveGrid(grid), L"saveGrid échoué");

            auto loadedGrid = fm.getGrid();
            Assert::AreEqual((size_t)2, loadedGrid.size(), L"Nombre de lignes incorrect");
            Assert::AreEqual((size_t)2, loadedGrid[0].size(), L"Nombre de colonnes incorrect");
            Assert::AreEqual(3, loadedGrid[1][0], L"Valeur incorrecte");*/
        }
    };
}