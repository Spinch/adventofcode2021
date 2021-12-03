
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#include <bitset>

#include "day3.h"

using namespace std;

namespace day3
{

constexpr char fileName[] = "../input/i3.txt";

vector<string> read_data()
{
    ifstream dataFile{fileName};
    const vector data(istream_iterator<string>{dataFile}, {});
    return data;
}

void task0()
{
    auto data = read_data();
    size_t N = data[0].length();
    
    vector<unsigned int> counter(N, 0);
    for (const auto &s : data) {
        for (size_t i=0; i<N; ++i) {
            if (s[i]=='1') {
                ++counter[i];
            }
        }
    }
    
    unsigned long int gamma{0};
    unsigned long int epsilon{0};
    for (size_t i=0; i<N; ++i) {
        gamma <<= 1;
        epsilon <<= 1;

        if (2*counter[i]>data.size()) {
            ++gamma;
        }
        else {
            ++epsilon;
        }
    }
    
    cout << gamma << " " << epsilon << endl << gamma*epsilon << endl;
}


string search1(vector<string> data, char c1, char c2)
{
    size_t N = data[0].length();

    for (size_t i=0; i<N; ++i) {
        unsigned int counter{0};
        for (const auto &s : data) {
            if (s[i]=='1') {
                ++counter;
            }
        }
        char c;
        if (2*counter>=data.size()) {
            c = c1;
        }
        else {
            c = c2;
        }
        
        vector<string> newData;
        for (const auto &s : data) {
            if (s[i] == c) {
                newData.push_back(s);
            }
        }
        data = newData;
        
        if (data.size() == 1) return data[0];
    }
    return "";
}

void task1()
{
    auto data = read_data();
    int x = stoi(search1(data, '1', '0'), nullptr, 2);
    int y = stoi(search1(data, '0', '1'), nullptr, 2);
    cout << x << " " << y << endl << x*y << endl;
}

}; /* namespace day3 */
