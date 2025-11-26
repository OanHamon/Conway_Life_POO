#pragma once
#include <vector>
#include <string>

using namespace std;

struct Pattern {
    string name;
    vector<pair<int, int>> cells;  // Coordonnées relatives (dx, dy)
    int width;
    int height;

    Pattern(const string& n) : name(n), width(0), height(0) {}

    void addCell(int dx, int dy) {
        cells.push_back({ dx, dy });
        // Mettre à jour les dimensions
        if (dx + 1 > width) width = dx + 1;
        if (dy + 1 > height) height = dy + 1;
    }
};

class PatternLibrary {
public:
    static Pattern getPoint() {
        Pattern p("Glider");
        p.addCell(0, 0);
        return p;
    }
    static Pattern getGlider() {
        Pattern p("Glider");
        p.addCell(1, 0);
        p.addCell(2, 1);
        p.addCell(0, 2);
        p.addCell(1, 2);
        p.addCell(2, 2);
        return p;
    }

    static Pattern getBlinker() {
        Pattern p("Blinker");
        p.addCell(0, 1);
        p.addCell(1, 1);
        p.addCell(2, 1);
        return p;
    }

    static Pattern getToad() {
        Pattern p("Toad");
        p.addCell(1, 0);
        p.addCell(2, 0);
        p.addCell(3, 0);
        p.addCell(0, 1);
        p.addCell(1, 1);
        p.addCell(2, 1);
        return p;
    }

    static Pattern getBeacon() {
        Pattern p("Beacon");
        p.addCell(0, 0);
        p.addCell(1, 0);
        p.addCell(0, 1);
        p.addCell(3, 2);
        p.addCell(2, 3);
        p.addCell(3, 3);
        return p;
    }

    static Pattern getPulsar() {
        Pattern p("Pulsar");
        // Quart supérieur gauche
        for (int i = 2; i <= 4; i++) {
            p.addCell(i, 0);
            p.addCell(0, i);
        }
        for (int i = 2; i <= 4; i++) {
            p.addCell(i, 5);
            p.addCell(5, i);
        }
        // Symétrie pour créer le pulsar complet
        for (int i = 8; i <= 10; i++) {
            p.addCell(i, 0);
            p.addCell(0, i);
        }
        for (int i = 8; i <= 10; i++) {
            p.addCell(i, 5);
            p.addCell(5, i);
        }
        for (int i = 2; i <= 4; i++) {
            p.addCell(i, 7);
            p.addCell(7, i);
        }
        for (int i = 8; i <= 10; i++) {
            p.addCell(i, 7);
            p.addCell(7, i);
        }
        for (int i = 2; i <= 4; i++) {
            p.addCell(i, 12);
            p.addCell(12, i);
        }
        for (int i = 8; i <= 10; i++) {
            p.addCell(i, 12);
            p.addCell(12, i);
        }
        return p;
    }

    static Pattern getLWSS() {
        Pattern p("LWSS");
        p.addCell(1, 0);
        p.addCell(4, 0);
        p.addCell(0, 1);
        p.addCell(0, 2);
        p.addCell(4, 2);
        p.addCell(0, 3);
        p.addCell(1, 3);
        p.addCell(2, 3);
        p.addCell(3, 3);
        return p;
    }

    static vector<Pattern> getAllPatterns() {
        return {
            getGlider(),
            getBlinker(),
            getToad(),
            getBeacon(),
            getPulsar(),
            getLWSS()
        };
    }
};