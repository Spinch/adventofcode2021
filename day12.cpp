
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#include "day12.h"

using namespace std;

namespace day12
{

constexpr char fileName[] = "../input/i12.txt";
constexpr char NAME_START[] = "start";
constexpr char NAME_END[] = "end";

struct caveInside
{
    bool big;
    vector<string> paths;
};

void addData(string name1, string name2, unordered_map<string, caveInside> &data) {
    auto f1 = data.find(name1);
    if (f1 == data.end()) {
        caveInside newCaveIns;
        newCaveIns.big = all_of(name1.begin(), name1.end(), [](const char &c){return isupper(c);});
        newCaveIns.paths.push_back(move(name2));
        data.insert({move(name1), move(newCaveIns)});
    }
    else {
        f1->second.paths.push_back(move(name2));
    }
    
    return;
}

unordered_map<string, caveInside> read_data()
{
    unordered_map<string, caveInside> result;
    ifstream dataFile{fileName};
    string dataString;
    while (getline(dataFile, dataString)) {
        stringstream dataStringStream(dataString);
        string name1, name2;
        getline(dataStringStream, name1, '-');
        getline(dataStringStream, name2, '-');
        addData(name1, name2, result);
        addData(name2, name1, result);
    }
    
    return result;
}

void recursiveSearch(const unordered_map<string, caveInside> &data, vector<string> currentPath, unsigned int &pathsCounter, bool additionalVisit)
{
    string lastNode = currentPath.back();
    if (lastNode == NAME_END) {
        ++pathsCounter;
        return;
    }
    for (const auto &p : data.at(lastNode).paths) {
        bool newAdditionalVisit{additionalVisit};
        bool mayGo{false};
        if (data.at(p).big) {
            mayGo = true;
        }
        else if (find(currentPath.begin(), currentPath.end(), p) == currentPath.end()) {
            mayGo = true;
        }
        else {
            if ((additionalVisit) && (p != NAME_START) && (p != NAME_END)) {
                mayGo = true;
                newAdditionalVisit = false;
            }
        }
        if (mayGo) {
            vector<string> newPath(currentPath.size());
            copy(currentPath.begin(), currentPath.end(), newPath.begin());
            newPath.push_back(p);
            recursiveSearch(data, newPath, pathsCounter, newAdditionalVisit);
        }
    }
}

void task0()
{
    auto data = read_data();
    vector<string> path;
    path.emplace_back(NAME_START);
    unsigned int pathsCounter{0};
    recursiveSearch(data, path, pathsCounter, false);
    cout << pathsCounter << endl;
}

void task1()
{
    auto data = read_data();
    vector<string> path;
    path.emplace_back(NAME_START);
    unsigned int pathsCounter{0};
    recursiveSearch(data, path, pathsCounter, true);
    cout << pathsCounter << endl;
}

}; /* namespace day12 */
