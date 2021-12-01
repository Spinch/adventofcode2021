
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>

#include "day1.h"

using namespace std;

constexpr char fileName[] = "../input/i1.txt";

vector<int> read_data()
{
    ifstream dataFile{fileName};
    const vector data(istream_iterator<int>{dataFile}, {});
    return data;
}

void day1_0()
{
    auto data = read_data();
    adjacent_difference(data.begin(), data.end(), data.begin());
    const int counter = count_if(data.begin()+1, data.end(), [](int i){return i>0;});
    cout << counter << endl;
}

void day1_1()
{
    auto data = read_data();
    transform(data.begin()+3, data.end(), data.begin(), data.begin(), [](int x, int y){return x-y;});
    const int counter = count_if(data.begin(), data.end()-3, [](int i){return i>0;});
    cout << counter << endl;
}
