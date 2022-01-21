
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "day15.h"

using namespace std;

namespace day15
{

constexpr char fileName[] = "../input/i15.txt";

struct coordinate {
    unsigned int x;
    unsigned int y;
    coordinate(unsigned int x, unsigned int y) : x(x), y(y) {};
    bool operator==(const coordinate c1) const {return ((this->x==c1.x)&&(this->y==c1.y));};
};

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


struct aStarNode {
    enum class Status {
        Open,
        Queue,
        Close,
    };
    coordinate c;
    coordinate from;
    unsigned int g;
    unsigned int h;
    Status status;
    aStarNode() : c(0,0), from(0,0), g(0), h(0), status(Status::Open) {};
};

unsigned int heuristicM(coordinate x1, coordinate x2) {
    return abs(static_cast<int>(x1.x)-static_cast<int>(x2.x)) + abs(static_cast<int>(x1.y)-static_cast<int>(x2.y));
}

const vector<pair<int, int>> d_neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

auto cmp = [](aStarNode *n1, aStarNode *n2){return (n1->g+n1->h)>(n2->g+n2->h);};
class custom_priority_queue : public std::priority_queue<aStarNode *, std::vector<aStarNode *>, decltype(cmp)>
{
public:

    custom_priority_queue() : priority_queue<aStarNode *, std::vector<aStarNode *>, decltype(cmp)>(cmp) {};
    
    bool remove(aStarNode *value) {
        auto it = std::find_if(this->c.begin(), this->c.end(), [value](aStarNode *a){return a==value;});
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
        else {
            return false;
        }
    }
};

optional<vector<coordinate>> aStarSearch(const vector<vector<int>> &field, coordinate startCoordinate, coordinate endCoordinate)
{
    vector<vector<aStarNode>> aStarField(field.size(), vector<aStarNode>(field[0].size()));
    for (unsigned int y=0; y<field.size(); ++y) {
        for (unsigned int x=0; x<field[0].size(); ++x) {
            aStarField[y][x].c.x = x;
            aStarField[y][x].c.y = y;
            aStarField[y][x].h = heuristicM(aStarField[y][x].c, endCoordinate);
            aStarField[y][x].status = aStarNode::Status::Open;
        }
    }
    
    custom_priority_queue exploreCandidates;
    exploreCandidates.push(&aStarField[startCoordinate.y][startCoordinate.x]);
    aStarField[startCoordinate.y][startCoordinate.x].status = aStarNode::Status::Queue;
    
    while (!exploreCandidates.empty()) {
        auto currentNode = exploreCandidates.top();
        exploreCandidates.pop();
        aStarField[currentNode->c.y][currentNode->c.x].status = aStarNode::Status::Close;
        if (currentNode->c == endCoordinate) {
            vector<coordinate> path;
            coordinate c = currentNode->c;
            while (!(c == startCoordinate)) {
                path.push_back(c);
                c = aStarField[c.y][c.x].from;
            }
            return path;
        }
        for (const auto &d_n : d_neighbors) {
            int nx = static_cast<int>(currentNode->c.x) + d_n.first;
            int ny = static_cast<int>(currentNode->c.y) + d_n.second;
            if ((nx>=0) && (nx<field[0].size()) && (ny>=0) && (ny<field.size())) {
                if (aStarField[ny][nx].status == aStarNode::Status::Open) {
                    aStarField[ny][nx].from = currentNode->c;
                    aStarField[ny][nx].g = currentNode->g + field[ny][nx];
                    aStarField[ny][nx].status = aStarNode::Status::Queue;
                    exploreCandidates.push(&aStarField[ny][nx]);
                }
                else if (aStarField[ny][nx].status == aStarNode::Status::Queue) {
                    if (aStarField[ny][nx].g > (currentNode->g + field[ny][nx])) {
                        exploreCandidates.remove(&aStarField[ny][nx]);
                        aStarField[ny][nx].g = currentNode->g + field[ny][nx];
                        aStarField[ny][nx].from = currentNode->c;
                        exploreCandidates.push(&aStarField[ny][nx]);
                    }
                }
            }
        }
    }
    
    return nullopt;
}

void task0()
{
    auto data = read_data();
    auto res = aStarSearch(data, coordinate(0,0), coordinate(data.size()-1, data[0].size()-1));
    unsigned int sum{0};
    if (res.has_value()) {
        for (auto c : res.value()) {
            sum += data[c.y][c.x];
        }
    }
    cout << sum << endl;
}

void task1()
{
    auto data = read_data();
    vector<vector<int>> dataF(data.size()*5, vector<int>(data[0].size()*5, 0));
    for (unsigned i=0; i<5; ++i) {
        size_t dy =i*data.size();
        for (unsigned j=0; j<5; ++j) {
            size_t dx =j*data.size();
            for (unsigned int y=0; y<data.size(); ++y) {
                for (unsigned int x=0; x<data.size(); ++x) {
                    dataF[y+dy][x+dx] = (data[y][x] + i + j - 1) % 9 + 1;
                }
            }
        }
    }
    auto res = aStarSearch(dataF, coordinate(0,0), coordinate(dataF.size()-1, dataF[0].size()-1));
    unsigned int sum{0};
    if (res.has_value()) {
        for (auto c : res.value()) {
            sum += dataF[c.y][c.x];
        }
    }
    cout << sum << endl;

}

}; /* namespace day15 */
