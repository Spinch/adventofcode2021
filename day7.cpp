
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include "day7.h"

using namespace std;

namespace day7
{

constexpr char fileName[] = "../input/i7.txt";

vector<int> read_data()
{
    ifstream dataFile{fileName};
    vector<int> result;
    string token;
    while (getline(dataFile, token, ',')) {
        result.push_back(stoi(token));
    }
    return result;
}

int sumTask0(size_t i, const vector<int> &data)
{
    return data[i]*(2*i-data.size()+1) - accumulate(data.begin(), data.begin()+i, int(0)) + accumulate(data.begin()+i+1, data.end(), int(0));
}

void task0()
{
    auto data = read_data();
    sort(data.begin(), data.end());
    if (data.size() % 2 == 0) {
        cout << min(sumTask0(data.size() / 2, data), sumTask0(data.size() / 2 + 1, data)) << endl;
    }
    else {
        cout << sumTask0(data.size() / 2, data) << endl;
    }
}

int sumTask1(int i, const vector<int> &data)
{
    int sum{0};
    for_each(data.begin(), data.end(), [&sum, i](int x){ sum += abs(x-i)*(abs(x-i)+1)/2;});
    return sum;
}

void task1()
{
    auto data = read_data();
    sort(data.begin(), data.end());
    int avg = accumulate(data.begin(), data.end(), int(0)) / data.size();
    cout << min(sumTask1(avg, data), sumTask1(avg+1, data)) << endl;
}

}; /* namespace day7 */
