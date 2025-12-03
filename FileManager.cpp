#pragma once
#include "FileManager.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

#pragma region Constructeurs
FileManager::FileManager(const std::string _path) : path(_path) {

    fs::path p(path);
    if (!p.parent_path().empty() && !fs::exists(p.parent_path())) {
        fs::create_directories(p.parent_path());
    }

    if (!fs::exists(p)) {
        write("");
    }

}
#pragma endregion

#pragma region Setters/Getters

std::string FileManager::getPath() {
    return path;
}

std::vector<std::vector<int>> FileManager::getGrid() {
    std::string data;
    if (!read(&data)) return {};

    std::stringstream ss(data);
    int rows, cols;
    if (!(ss >> rows >> cols) || rows <= 0 || cols <= 0) {
        std::cerr << "Erreur: dimensions invalides." << std::endl;
        return {};
    }

    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(ss >> grid[i][j])) {
                std::cerr << "Erreur: données insuffisantes ou invalides à (" << i << "," << j << ")." << std::endl;
                return {};
            }
        }
    }
    return grid;
}

#pragma endregion

#pragma region MethodeJeu


bool FileManager::write(const std::string _msg) {
    std::ofstream f(path, std::ios::out | std::ios::trunc);
    if (!f.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return false;
    }
    f << _msg;
    return true;
}

bool FileManager::read(std::string* _output) {
    std::ifstream f(path, std::ios::in);
    if (!f.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier !" << std::endl;
        return false;
    }
    *_output = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    return true;
}

bool FileManager::clearFile() {
    return write("");
}



bool FileManager::saveGrid(const std::vector<std::vector<int>>& _grid) {
    if (_grid.empty() || _grid[0].empty()) {
        std::cerr << "Erreur: la grille est vide ou invalide." << std::endl;
        return false;
    }

    int rows = static_cast<int>(_grid.size());
    int cols = static_cast<int>(_grid[0].size());
    for (const auto& r : _grid) {
        if ((int)r.size() != cols) {
            std::cerr << "Erreur: lignes de tailles différentes." << std::endl;
            return false;
        }
    }

    std::ostringstream oss;
    oss << rows << " " << cols << "\n";
    for (const auto& row : _grid) {
        for (int val : row) {
            oss << val << " ";
        }
        oss << "\n";
    }

    return write(oss.str());
}


#pragma endregion