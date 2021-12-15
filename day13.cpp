
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

#include "day13.h"

using namespace std;

namespace day13
{

constexpr char fileName[] = "../input/i13.txt";
using coordinate = pair<unsigned int, unsigned int>;
using foldOver = pair<char, unsigned int>;

tuple<vector<coordinate>, vector<foldOver>> read_data()
{
    ifstream dataFile{fileName};
    string dataString;
    
    vector<coordinate> coordinates;
    while (getline(dataFile, dataString)) {
        if (dataString.empty()) break;
        stringstream dataStringStream(dataString);
        unsigned int x, y;
        char c;
        dataStringStream >> x >> c >> y;
        coordinates.emplace_back(x, y);
    }

    vector<foldOver> foldOvers;
    while (getline(dataFile, dataString)) {
        stringstream dataStringStream(dataString);
        string token;
        dataStringStream >> token >> token >> token;
        stringstream tokenStringStream(token);
        char c, ct;
        unsigned int v;
        tokenStringStream >> c >> ct >> v;

        foldOvers.emplace_back(c, v);
    }

    return make_tuple(coordinates, foldOvers);
}

void foldFunction(vector<coordinate> &coordinates, char foldDirection, unsigned int foldLine)
{
    auto foldOnes = [](vector<coordinate> &coordinates, unsigned int foldLine, function<unsigned int &(coordinate &)> getOne)
    {
        unsigned int maxV{0};
        for_each(coordinates.begin(), coordinates.end(), [&maxV, &getOne](coordinate c){
            maxV = max(maxV, getOne(c));
        });
        
        int addV = max(static_cast<int>(maxV) - 2*static_cast<int>(foldLine), 0);
        for (auto &c : coordinates) {
            if (getOne(c) < foldLine) {
                getOne(c) += addV;
            }
            else {
                getOne(c) = static_cast<int>(addV) + 2*static_cast<int>(foldLine) - static_cast<int>(getOne(c));
            }
        }    
    };

    if (foldDirection == 'x') {
        foldOnes(coordinates, foldLine, [](coordinate &c)->unsigned int & {return c.first;});
    }
    else if (foldDirection == 'y') {
        foldOnes(coordinates, foldLine, [](coordinate &c)->unsigned int & {return c.second;});
    }

    return;
}

struct coordinate_hash {
    inline std::size_t operator()(const coordinate & v) const {
        return v.first*31+v.second;
    }
};

void task0()
{
    vector<coordinate> coordinates;
    vector<foldOver> foldOvers;
    tie(coordinates, foldOvers) = read_data();
    
    foldFunction(coordinates, foldOvers[0].first, foldOvers[0].second);
    unordered_set<coordinate, coordinate_hash> coordinatesSet(coordinates.begin(), coordinates.end());
    cout << coordinatesSet.size() << endl;
}

void task1()
{
    vector<coordinate> coordinates;
    vector<foldOver> foldOvers;
    tie(coordinates, foldOvers) = read_data();
    
    for (const auto &f : foldOvers) {
        foldFunction(coordinates, f.first, f.second);
    }
    unordered_set<coordinate, coordinate_hash> coordinatesSet(coordinates.begin(), coordinates.end());
    
    unsigned int maxX{0}, maxY{0};
    for_each(coordinatesSet.begin(), coordinatesSet.end(), [&maxX, &maxY](coordinate c){
        maxX = max(maxX, c.first);
        maxY = max(maxY, c.second);
    });
    for (unsigned int y=0; y<=maxY; ++y) {
        for (unsigned int x=0; x<=maxX; ++x) {
            if (coordinatesSet.find(make_pair(x, y)) == coordinatesSet.end()) {
                cout << ".";
            }
            else {
                cout << "#";
            }
        }
        cout << endl;
    }
}

}; /* namespace day13 */
