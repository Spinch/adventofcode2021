
#include <fstream>
#include <iostream>
#include <regex>

#include "day5.h"

using namespace std;

namespace day5
{

constexpr char fileName[] = "../input/i5.txt";

struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
    
    Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

vector<Line> read_data()
{
    ifstream dataFile{fileName};
    vector<Line> res;
    int x1, y1, x2, y2;
    char c;
    while (dataFile >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2) {
        res.emplace_back(x1, y1, x2, y2);
    }
    
    return res;
}

void task0()
{
    auto data = read_data();
    int maxX{0}, maxY{0};
    for (const auto &line : data) {
        maxX = max(maxX, max(line.x1, line.x2));
        maxY = max(maxY, max(line.y1, line.y2));
    }
    vector<vector<unsigned int>> field(maxY+1, vector<unsigned int>(maxX+1, 0));
    for (const auto &line : data) {
        if (line.x1 == line.x2) {
            for (int i=min(line.y1,line.y2); i<=max(line.y1,line.y2); ++i) {
                field[i][line.x1] += 1;
            }
        }
        else if(line.y1 == line.y2) {
            for (int i=min(line.x1,line.x2); i<=max(line.x1,line.x2); ++i) {
                field[line.y1][i] += 1;
            }
        }
    }

    unsigned int counter{0};
    for (const auto &y : field) {
        for (const auto &x : y) {
            if (x>=2) ++counter;
        }
    }
    
    cout << counter << endl;
}


void task1()
{
    auto data = read_data();
    int maxX{0}, maxY{0};
    for (const auto &line : data) {
        maxX = max(maxX, max(line.x1, line.x2));
        maxY = max(maxY, max(line.y1, line.y2));
    }

    vector<vector<unsigned int>> field(maxY+1, vector<unsigned int>(maxX+1, 0));
    for (const auto &line : data) {
        if (line.x1 == line.x2) {
            for (int i=min(line.y1,line.y2); i<=max(line.y1,line.y2); ++i) {
                field[i][line.x1] += 1;
            }
        }
        else if(line.y1 == line.y2) {
            for (int i=min(line.x1,line.x2); i<=max(line.x1,line.x2); ++i) {
                field[line.y1][i] += 1;
            }
        }
        else {
            int sx = (line.x2-line.x1)/abs(line.x1-line.x2);
            int sy = (line.y2-line.y1)/abs(line.y1-line.y2);
            int x = line.x1;
            int y = line.y1;
            while (x != line.x2) {
                field[y][x] += 1;
                y += sy;
                x += sx;
            } 
            field[y][x] += 1;

        }
    }

    unsigned int counter{0};
    for (const auto &y : field) {
        for (const auto &x : y) {
            if (x>=2) ++counter;
        }
    }
    
    cout << counter << endl;
    
}

}; /* namespace day5 */
