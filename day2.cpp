
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "day2.h"

using namespace std;

namespace day2
{

constexpr char fileName[] = "../input/i2.txt";

enum class Movement
{
    Forward,
    Up,
    Down,
};

vector<pair<Movement, int>> read_data()
{
    ifstream dataFile{fileName};
    vector<pair<Movement, int>> data;
    string movementString;
    int movementValue;
    while (dataFile >> movementString >> movementValue) {
        if (movementString == "forward") {
            data.emplace_back(make_pair(Movement::Forward, movementValue));
        }
        else if (movementString == "down") {
            data.emplace_back(make_pair(Movement::Down, movementValue));
        }
        else if (movementString == "up") {
            data.emplace_back(make_pair(Movement::Up, movementValue));
        }
    }
    return data;
}

void task0()
{
    auto data = read_data();
    int x{0},y{0};
    for (const auto &m : data) {
        if (m.first == Movement::Forward)
            x+= m.second;
        else if (m.first == Movement::Up)
            y-= m.second;
        else if (m.first == Movement::Down)
            y+= m.second;

    }
    
    cout << x << " " << y << endl << x*y << endl;
}

void task1()
{
    auto data = read_data();
    int x{0},y{0},a{0};
    for (const auto &m : data) {
        if (m.first == Movement::Forward) {
            x+= m.second;
            y+=a*m.second;
        }
        else if (m.first == Movement::Up)
            a-= m.second;
        else if (m.first == Movement::Down)
            a+= m.second;

    }
    
    cout << x << " " << y << endl << x*y << endl;

}

}; /* namespace day2 */
