
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <numeric>
#include <cstdlib>

#include "day9.h"

#define TRACE cout << "Line: " << __LINE__ << endl;

using namespace std;

namespace day9
{

constexpr char fileName[] = "../input/i9.txt";

vector<vector<int>> read_data()
{
    vector<vector<int>> result;
    ifstream dataFile{fileName};
    string dataString;
    while (getline(dataFile, dataString)) {
        char c;
        stringstream dataStringStream(dataString);
        vector<int> numbersLine;
        while (dataStringStream >> c) {
            numbersLine.push_back(stoi(to_string(c-'0')));
        }
        result.push_back(move(numbersLine));
    }
    
    return result;
}

void task0()
{
    unsigned int counter{0};
    auto data = read_data();
    for (size_t y=0; y<data.size(); ++y) {
        for (size_t x=0; x<data[0].size(); ++x) {
            bool minimum{true};
            if ((y>0) && (data[y-1][x] <= data[y][x])) minimum = false;
            if ((y+1<data.size()) && (data[y+1][x] <= data[y][x])) minimum = false;
            if ((x>0) && (data[y][x-1] <= data[y][x])) minimum = false;
            if ((x+1<data[0].size()) && (data[y][x+1] <= data[y][x])) minimum = false;
            if (minimum) {
                counter += data[y][x] + 1;
            }
        }
    }
    
    cout << counter << endl;
    return;
}

unsigned int checkBasin(size_t x, size_t y, vector<vector<int>> &data)
{
    vector<vector<bool>> checked(data.size(), vector<bool>(data[0].size(), false));
    unsigned int counter{0};
    deque<pair<size_t, size_t>> dq;
    dq.emplace_back(x, y);
    while (!dq.empty()) {
        size_t x;
        size_t y;
        tie(x, y) = dq.front();
        dq.pop_front();
        ++counter;
        auto checkOneNeighbor = [&data, &checked, &dq](bool condBorder, size_t y, size_t x, int dy, int dx){
            if (condBorder && (data[y+dy][x+dx] != 9) && ((data[y+dy][x+dx] - data[y][x]) >= 0) && (checked[y+dy][x+dx] == false)) {
                dq.emplace_back(x+dx, y+dy);
                checked[y+dy][x+dx] = true;
            };
        };
        checkOneNeighbor(y>0, y, x, -1, 0);
        checkOneNeighbor(y+1<data.size(), y, x, 1, 0);
        checkOneNeighbor(x>0, y, x, 0, -1);
        checkOneNeighbor(x+1<data[0].size(), y, x, 0, 1);
    }
    return counter;
}

void task1()
{
    auto data = read_data();
    vector<unsigned int> basinSizes;
    for (size_t y=0; y<data.size(); ++y) {
        for (size_t x=0; x<data[0].size(); ++x) {
            bool minimum{true};
            if ((y>0) && (data[y-1][x] <= data[y][x])) minimum = false;
            if ((y+1<data.size()) && (data[y+1][x] <= data[y][x])) minimum = false;
            if ((x>0) && (data[y][x-1] <= data[y][x])) minimum = false;
            if ((x+1<data[0].size()) && (data[y][x+1] <= data[y][x])) minimum = false;
            if (minimum) {
                basinSizes.push_back(checkBasin(x, y, data));
            }
        }
    }
    
    sort(basinSizes.begin(), basinSizes.end(), std::greater<int>());
    unsigned int max3 = basinSizes[0]*basinSizes[1]*basinSizes[2];
    cout << max3 << endl;
    return;
}

}; /* namespace day9 */
