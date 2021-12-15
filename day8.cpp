
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <cstdlib>

#include "day8.h"

using namespace std;

namespace day8
{

constexpr char fileName[] = "../input/i8.txt";

vector<pair<vector<string>, vector<string>>> read_data()
{
    vector< pair< vector<string>, vector<string> > > result;
    ifstream dataFile{fileName};
    string signalsString;
    while (getline(dataFile, signalsString)) {
        stringstream signalsStringStream(signalsString);
        vector<string> vs1;
        vector<string> vs2;
        string token;
        for (unsigned int i=0; i<10; ++i) {
            signalsStringStream >> token;
            vs1.push_back(token);
        }
        signalsStringStream >> token;
        for (unsigned int i=0; i<4; ++i) {
            signalsStringStream >> token;
            vs2.push_back(token);
        }
        result.push_back(make_pair(vs1, vs2));
    }
    
    return result;
}

void task0()
{
    auto data = read_data();
    unsigned int counter{0};
    for (const auto &l : data) {
        for (const auto &s : l.second) {
            if ((s.length() <= 4) || (s.length() == 7)) ++counter;
        }
    }
    
    cout << counter << endl;
}

size_t getIntersectionLen(const string &s1, const string &s2)
{
    string res;
    return set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), res.begin()) - res.begin();
}

void task1()
{
    int sum{0};
    auto data = read_data();
    for (auto &l : data) {
        array<string, 10> code;
        vector<string> s6;
        vector<string> s5;
        for (auto &s : l.first) {
            sort(s.begin(), s.end());
            if (s.length() == 2) {
                code[1] = s;
            }
            else if (s.length() == 3) {
                code[7] = s;
            }
            else if (s.length() == 4) {
                code[4] = s;
            }
            else if (s.length() == 5) {
                s5.push_back(s);
            }
            else if (s.length() == 6) {
                s6.push_back(s);
            }
            else if (s.length() == 7) {
                code[8] = s;
            }
        }
        
        for (const auto &s : s6) {
            size_t inters = getIntersectionLen(s, code[4]);
            if (inters == 2) {
                code[9] = s;
            }
            else if (inters == 3) {
                size_t inters = getIntersectionLen(s, code[7]);
                if (inters == 3) {
                    code[0] = s;
                }
                else if (inters == 4) {
                    code[6] = s;
                }
            }
        }

        for (const auto &s : s5) {
            size_t inters = getIntersectionLen(s, code[7]);
            if (inters == 2) {
                code[3] = s;
            }
            else if (inters == 3) {
                size_t inters = getIntersectionLen(s, code[4]);
                if (inters == 3) {
                    code[2] = s;
                }
                else if (inters == 2) {
                    code[5] = s;
                }
            }
        }
        
        int res{0};
        for (auto &s : l.second) {
            sort(s.begin(), s.end());
            for (unsigned int i=0; i<10; ++i) {
                if (s == code[i]) {
                    res *= 10;
                    res += i;
                    break;
                }
            }
        }
        sum += res;
    }
    cout << sum<< endl;
}

}; /* namespace day8 */
