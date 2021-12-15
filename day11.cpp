
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

#include "day11.h"

using namespace std;

namespace day11
{

constexpr char fileName[] = "../input/i11.txt";

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
    auto data = read_data();
    unsigned int counter{0};
    for (unsigned int i=0; i<100; ++i) {

        function<void(int, int)> flash = [&data, &flash](int y, int x){
            for (int dy=max(0,y-1); dy<=min(static_cast<int>(data.size())-1,y+1); ++dy) {
                for (int dx=max(0,x-1); dx<=min(static_cast<int>(data.size())-1,x+1); ++dx) {
                    if ((dx==x) && (dy==y)) continue;
                    ++data[dy][dx];
                    if (data[dy][dx] == 10) flash(dy, dx);
                }
            }
        };
        for (int y=0; y<data.size(); ++y) {
            for (int x=0; x<data[0].size(); ++x) {
                ++data[y][x];
                if (data[y][x] == 10) flash(y, x);
            }
        }
        for (int y=0; y<data.size(); ++y) {
            for (int x=0; x<data[0].size(); ++x) {
                if (data[y][x] > 9) {
                    data[y][x] = 0;
                    ++counter;
                }
            }
        }
    }
    
    cout << counter << endl;
}

void task1()
{
    auto data = read_data();
    for (unsigned int i=0; i<2000; ++i) {

        function<void(int, int)> flash = [&data, &flash](int y, int x){
            for (int dy=max(0,y-1); dy<=min(static_cast<int>(data.size())-1,y+1); ++dy) {
                for (int dx=max(0,x-1); dx<=min(static_cast<int>(data.size())-1,x+1); ++dx) {
                    if ((dx==x) && (dy==y)) continue;
                    ++data[dy][dx];
                    if (data[dy][dx] == 10) flash(dy, dx);
                }
            }
        };
        for (int y=0; y<data.size(); ++y) {
            for (int x=0; x<data[0].size(); ++x) {
                ++data[y][x];
                if (data[y][x] == 10) flash(y, x);
            }
        }
        unsigned int counter{0};
        for (int y=0; y<data.size(); ++y) {
            for (int x=0; x<data[0].size(); ++x) {
                if (data[y][x] > 9) {
                    data[y][x] = 0;
                    ++counter;
                }
            }
        }
        if (counter == data.size()*data[0].size()) {
            cout << i+1 << endl;
            break;
        }
    }
}

}; /* namespace day11 */
