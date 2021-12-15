
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#include "day10.h"

using namespace std;

namespace day10
{

constexpr char fileName[] = "../input/i10.txt";

vector<string> read_data()
{
    vector<string> result;
    ifstream dataFile{fileName};
    string dataString;
    while (getline(dataFile, dataString)) {
        result.push_back(dataString);
    }
    
    return result;
}

const unordered_map<char, char> brPairs = {{')','('}, {']','['}, {'}','{'}, {'>','<'}};

void task0()
{
    auto data = read_data();
    unsigned int counter{0};
    for (const auto &l : data) {
        string brString;
        for (auto c : l) {
            auto f = brPairs.find(c);
            if (f == brPairs.end()) {
                brString.push_back(c);
            }
            else {
                if (brString.back() != f->second) {
                    const unordered_map<char, unsigned int> brScores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
                    counter += brScores.at(f->first);
                    break;
                }
                brString.pop_back();
            }
        }
    }
    
    cout << counter << endl;
}


void task1()
{
    auto data = read_data();
    vector<long unsigned int> scores;
    for (const auto &l : data) {
        string brString;
        for (auto c : l) {
            auto f = brPairs.find(c);
            if (f == brPairs.end()) {
                brString.push_back(c);
            }
            else {
                if (brString.back() != f->second) {
                    brString.clear();
                    break;
                }
                brString.pop_back();
            }
        }
        if (brString.size() > 0) {
            long unsigned int score{0};
            const unordered_map<char, unsigned int> brScores2 = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
            for_each(brString.rbegin(), brString.rend(), [&score, &brScores2](char c){
                score *=5;
                score += brScores2.at(c);
            });
            scores.push_back(score);
        }
    }
    sort(scores.begin(), scores.end());
    cout << scores[scores.size()/2] << endl;
}

}; /* namespace day10 */
