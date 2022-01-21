
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

#include "day17.h"

using namespace std;

namespace day17
{

constexpr char fileName[] = "../input/i17.txt";
struct Coordinate
{
    int x;
    int y;
};

pair<Coordinate, Coordinate> read_data()
{
    Coordinate c1, c2;
    ifstream dataFile{fileName};
    string dataString1, dataString2;
    dataFile >> dataString1 >> dataString1 >> dataString1 >> dataString2; 
    char a;
    stringstream dataStringStream1(dataString1);
    dataStringStream1 >> a >> a >> c1.x >> a >> a >> c2.x;
    stringstream dataStringStream2(dataString2);
    dataStringStream2 >> a >> a >> c1.y >> a >> a >> c2.y;
    
    return make_pair(c1, c2);
}

void task0()
{
    auto data = read_data();
    int VYMax = -data.first.y-1;
    cout << VYMax*(VYMax+1)/2 << endl;
    return;
}

void task1()
{
    auto data = read_data();
    
    int VYMin = data.first.y;
    int VYMax = -data.first.y-1;
    vector<pair<int, pair<int, int>>> possibleVY;
    for (int v=VYMin; v<=VYMax; ++v) {
        auto getTY = [v](int y){
            double b = (-1-2*v);
            return (-b + sqrt(b*b - 8*y))/2;
        };
        int t1 = ceil(getTY(data.second.y));
        int t2 = floor(getTY(data.first.y));
        if (t1 <= t2) {
            possibleVY.emplace_back(v, make_pair(t1, t2));
        }
    }
    
    int VXMin = ceil((-1. + sqrt(2+8*data.first.x))/2);
    int VXMax = data.second.x;
    vector<pair<int, pair<int, int>>> possibleVX;
    for (int v=VXMin; v<=VXMax; ++v) {
        auto getTX = [v](int x) -> double {
            double b = -(1+2*v);
            double D = b*b - 8*x;
            if (D<0) return numeric_limits<int>::max();
            double r = (-b - sqrt(D))/2.;
            return r;
        };
        int t1 = ceil(getTX(data.first.x));
        int t2 = floor(getTX(data.second.x));
        if (t1 <= t2) {
            possibleVX.emplace_back(v, make_pair(t1, t2));
        }
    }
    
    unsigned int counter{0};
    for (const auto &vy : possibleVY) {
        for (const auto &vx : possibleVX) {
            if ((vy.second.first <= vx.second.second) && (vx.second.first <= vy.second.second)) {
                ++counter;
            }
        }
    }

    cout << counter << endl;
    return;
}

}; /* namespace day17 */
