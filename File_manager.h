#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class File_manager {
private:
    string path;
    bool write(string _msg);
    bool read(string* _output);
    bool clearFile();

public:
    File_manager(string _path);
    string getPath();
    void setPath(string _path);

    vector<vector<int>> getGrid();
    bool saveGrid(const vector<vector<int>>& _grid);
};
/*
USAGE :

File_manager f_out("out.txt");
File_manager f_in("in.txt");


vector<vector<int>> matrix = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

vector<vector<int>> in_grid = f_in.getGrid();

f_out.saveGrid(in_grid);
*/