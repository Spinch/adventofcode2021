
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

#include "day6.h"

using namespace std;

namespace day6
{

constexpr char fileName[] = "../input/i6.txt";

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

template<typename T>
void solveTask(size_t N)
{
    auto data = read_data();
    vector<T> days(N+9, 0);
    for (auto i : data) {
        days[i] += 1;
    }
    for (size_t n=0; n<N; ++n) {
        days[n+7] += days[n];
        days[n+9] += days[n];
    }
    T total = accumulate(days.begin()+N, days.begin()+N+9, T{0});
    cout << total << endl;
}

void task0()
{
    solveTask<int>(80);
}

void task1()
{
    solveTask<long long unsigned int>(256);
}

}; /* namespace day5 */
