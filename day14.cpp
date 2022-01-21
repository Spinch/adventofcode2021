
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#include "day14.h"

using namespace std;

namespace day14
{

constexpr char fileName[] = "../input/i14.txt";
using insertCode = unordered_map<string, char>;

tuple<string, insertCode> read_data()
{
    ifstream dataFile{fileName};
    string polymerTemplate;
    getline(dataFile, polymerTemplate);

    string dataString;
    insertCode pairInsertion;
    while (getline(dataFile, dataString)) {
        stringstream dataStringStream(dataString);
        string token;
        string i1;
        char i2;
        dataStringStream >> i1 >> token >> i2;
        pairInsertion[i1] = i2;
    }

    return make_tuple(polymerTemplate, pairInsertion);
}


void task0()
{
    string polymerTemplate;
    insertCode pairInsertion;
    tie(polymerTemplate, pairInsertion) = read_data();
    
    for (unsigned int n=0; n<10; ++n) {
        string newPloymerTemplate;
        for (size_t i=0; i<polymerTemplate.size()-1; ++i) {
            newPloymerTemplate.push_back(polymerTemplate[i]);
            string code;
            code.push_back(polymerTemplate[i]);
            code.push_back(polymerTemplate[i+1]);
            newPloymerTemplate.push_back(pairInsertion[code]);
        }
        newPloymerTemplate.push_back(polymerTemplate.back());
        polymerTemplate = move(newPloymerTemplate);
    }
    
    unordered_map<char, unsigned int> counter;
    for (auto c : polymerTemplate) {
        counter.try_emplace(c, 0);
        ++counter[c];
    }
    auto polymerMinMax = minmax_element(counter.begin(), counter.end(), [](const pair<char, unsigned int> &k1, const pair<char, unsigned int> &k2){return k1.second < k2.second;});
    cout << polymerMinMax.second->second - polymerMinMax.first->second << endl;
}

void task1()
{
    string polymerTemplate;
    insertCode pairInsertion;
    tie(polymerTemplate, pairInsertion) = read_data();
    
    unordered_map<string, long unsigned int> counterPairs;
    for (size_t i=0; i<polymerTemplate.size()-1; ++i) {
        string code;
        code.push_back(polymerTemplate[i]);
        code.push_back(polymerTemplate[i+1]);
        counterPairs.try_emplace(code, 0);
        ++counterPairs[code];
    }
    string firstPair;
    firstPair.push_back(polymerTemplate[0]);
    firstPair.push_back(polymerTemplate[1]);
    string lastPair;
    lastPair.push_back(polymerTemplate.back()+1);
    lastPair.push_back(polymerTemplate.back());

    for (unsigned int n=0; n<40; ++n) {
        unordered_map<string, long unsigned int> newCounterPairs;
        for (const auto &cp : counterPairs) {
            string code1, code2;
            code1.push_back(cp.first[0]);
            code1.push_back(pairInsertion[cp.first]);
            code2.push_back(pairInsertion[cp.first]);
            code2.push_back(cp.first[1]);
            newCounterPairs.try_emplace(code1, 0);
            newCounterPairs.try_emplace(code2, 0);
            newCounterPairs[code1] += cp.second;
            newCounterPairs[code2] += cp.second;
        }
        counterPairs = move(newCounterPairs);
        
        firstPair[1] = pairInsertion[firstPair];
        lastPair[0] = pairInsertion[lastPair];
    }
    
    unordered_map<char, long long unsigned int> counter;
    for (auto c : counterPairs) {
        counter.try_emplace(c.first[0], 0);
        counter.try_emplace(c.first[1], 0);
        counter[c.first[0]] += c.second;
        counter[c.first[1]] += c.second;
    }
    ++counter[firstPair[0]];
    ++counter[lastPair[1]];
    auto polymerMinMax = minmax_element(counter.begin(), counter.end(), [](const pair<char, long long unsigned int> &k1, const pair<char, long long unsigned int> &k2){return k1.second < k2.second;});
    cout << (polymerMinMax.second->second - polymerMinMax.first->second)/2 << endl;
}

}; /* namespace day14 */
