#pragma once
#include <vector>
#include <string>

using namespace std;

struct Patern {
    string name;
    vector<pair<int, int>> cells;  // Coordonnées relatives (dx, dy)
    int width;
    int height;
    bool isObstacle = false;

    Patern(const string& n) : name(n), width(0), height(0) {}

    void addCell(int dx, int dy) {
        cells.push_back({ dx, dy });

        // Mettre à jour les dimensions
        if (dx + 1 > width) width = dx + 1;
        if (dy + 1 > height) height = dy + 1;
    }
};

class PaternLibrary {
public:

    static Patern getPoint() {
        Patern p("Point");
        p.addCell(0, 0);
        return p;
    }

    static Patern getAliveObstacle() {
        Patern p("Obstacle");
        p.addCell(0, 0);
        p.isObstacle = true;
        return p;
    }

    static Patern getBlock() {
        Patern p("Block");
        p.addCell(0, 0);
        p.addCell(0, 1);
        p.addCell(1, 1);
        p.addCell(1, 0);
        //p.isObstacle = true;
        return p;
    }

    static Patern getGlider() {
        Patern p("Glider");
        p.addCell(1, 0);
        p.addCell(2, 1);
        p.addCell(0, 2);
        p.addCell(1, 2);
        p.addCell(2, 2);
        return p;
    }

    static Patern getBlinker() {
        Patern p("Blinker");
        p.addCell(0, 1);
        p.addCell(1, 1);
        p.addCell(2, 1);
        return p;
    }

    static Patern getToad() {
        Patern p("Toad");
        p.addCell(1, 0);
        p.addCell(2, 0);
        p.addCell(3, 0);
        p.addCell(0, 1);
        p.addCell(1, 1);
        p.addCell(2, 1);
        return p;
    }

    static Patern getBeacon() {
        Patern p("Beacon");
        p.addCell(0, 0);
        p.addCell(1, 0);
        p.addCell(0, 1);
        p.addCell(3, 2);
        p.addCell(2, 3);
        p.addCell(3, 3);
        return p;
    }

    static Patern getPulsar() {
        Patern p("Pulsar");
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

    static Patern getLWSS() {
        Patern p("LWSS");
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

    static Patern getGliderShooter() {
        Patern p("GliderShooter");

        // Le célèbre Gosper Glider Gun
        // Bloc de gauche
        p.addCell(0, 4); p.addCell(0, 5);
        p.addCell(1, 4); p.addCell(1, 5);

        // Partie centrale
        p.addCell(10, 4); p.addCell(10, 5); p.addCell(10, 6);
        p.addCell(11, 3); p.addCell(11, 7);
        p.addCell(12, 2); p.addCell(12, 8);
        p.addCell(13, 2); p.addCell(13, 8);
        p.addCell(14, 5);
        p.addCell(15, 3); p.addCell(15, 7);
        p.addCell(16, 4); p.addCell(16, 5); p.addCell(16, 6);
        p.addCell(17, 5);

        // Partie droite
        p.addCell(20, 2); p.addCell(20, 3); p.addCell(20, 4);
        p.addCell(21, 2); p.addCell(21, 3); p.addCell(21, 4);
        p.addCell(22, 1); p.addCell(22, 5);
        p.addCell(24, 0); p.addCell(24, 1); p.addCell(24, 5); p.addCell(24, 6);

        // Petit bloc à droite
        p.addCell(34, 2); p.addCell(34, 3);
        p.addCell(35, 2); p.addCell(35, 3);

        return p;
    }

    static Patern getPentaDecathlon() {
        Patern p("PentaDecathlon");


        p.addCell(4, 0);
        p.addCell(4, 1);
        p.addCell(4, 2);

        p.addCell(0, 1);
        p.addCell(8, 1);

        p.addCell(1, 1);
        p.addCell(2, 1);
        p.addCell(3, 1);
        p.addCell(5, 1);
        p.addCell(6, 1);
        p.addCell(7, 1);

        return p;
    }

    static Patern getHWSS() {
        Patern p("HWSS");

        p.addCell(1, 0); p.addCell(2, 0); p.addCell(3, 0); p.addCell(4, 0);

        p.addCell(0, 1); p.addCell(5, 1);

        p.addCell(0, 2);

        p.addCell(0, 3); p.addCell(5, 3);

        p.addCell(1, 4); p.addCell(2, 4); p.addCell(3, 4); p.addCell(4, 4); p.addCell(5, 4);

        return p;
    }

    static vector<Patern> getAllPatterns() {
        return {
            getPoint(),
            getAliveObstacle(),
            getBlock(),
            getGlider(),
            getBlinker(),
            getToad(),
            getBeacon(),
            getPulsar(),
            getLWSS(),
            getHWSS(),
            getGliderShooter(),
            getPentaDecathlon()
        };
    }
};