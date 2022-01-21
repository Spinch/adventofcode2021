
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <variant>
#include <optional>
#include <memory>
#include <functional>
#include <utility>
#include <math.h>

#include "day18.h"

using namespace std;

namespace day18
{

constexpr char fileName[] = "../input/i18.txt";
constexpr unsigned int EXPLODE_LEVEL = 4;

struct SnailfishNumber
{
    unique_ptr<array<variant<unsigned int, SnailfishNumber>, 2>> p;

    template <class T1, class T2>
    friend SnailfishNumber operator+(T1 &&n1, T2 &&n2);
    
    friend ostream &operator<<( ostream &output, const SnailfishNumber &n );
    
    SnailfishNumber() {p=make_unique<array<variant<unsigned int, SnailfishNumber>, 2>>();}
    
    SnailfishNumber(const SnailfishNumber &n);
    
    template<class T>
    SnailfishNumber & operator=(T&& n)
    {
        for (unsigned int i=0; i<2; ++i) {
            visit([this, i](auto&& arg){this->p->at(i) = (arg);}, forward<T>(n).p->at(i));
        }
        return *this;
    }

    unsigned int magnitude();
    
    void reduce();

private:
    
    optional<array<unsigned int, 2>> explode(unsigned int level);
    
    bool split();
};

SnailfishNumber::SnailfishNumber(const SnailfishNumber &n)
{
    p=make_unique<array<variant<unsigned int, SnailfishNumber>, 2>>();
    for (unsigned int i=0; i<2; ++i) {
        visit([this, i](auto&& arg){this->p->at(i) = arg;}, n.p->at(i));
    }
}

unsigned int SnailfishNumber::magnitude()
{
    const array<unsigned int, 2> cost = {3, 2};
    unsigned int m{0};
    for (unsigned int i=0; i<2; ++i) {
        if (holds_alternative<unsigned int>(p->at(i))) {
            m += cost[i]*get<unsigned int>(p->at(i));
        }
        else {
            m += cost[i]*get<SnailfishNumber>(p->at(i)).magnitude();
        }
    }
    
    return m;
}

void SnailfishNumber::reduce()
{
    while (true) {
        if (explode(0).has_value()) continue;
        if (!split()) break;
    }
    
    return;
}

optional<array<unsigned int, 2>> SnailfishNumber::explode(unsigned int level)
{
    function<void(variant<unsigned int, SnailfishNumber> &, unsigned int, size_t)> explodeSeed = 
    [&explodeSeed](variant<unsigned int, SnailfishNumber> &intoSeed, unsigned int what, size_t where) {
        if (holds_alternative<unsigned int>(intoSeed)) {
            get<unsigned int>(intoSeed) += what;
            return;
        }
        else {
            explodeSeed(get<SnailfishNumber>(intoSeed).p->at(where), what, where);
        }
    };
    
    if (level < EXPLODE_LEVEL) {
        for (size_t i=0; i<2; ++i) {
            if (holds_alternative<SnailfishNumber>(p->at(i))) {
                auto res = get<SnailfishNumber>(p->at(i)).explode(level+1);
                if (res.has_value()) {
                    auto v = res.value();
                    if (level == EXPLODE_LEVEL-1) {
                        p->at(i) = 0;
                        explodeSeed(p->at(!i), v[!i], i);
                        v[!i] = 0;
                    }
                    else {
                        if (v[!i] != 0) {
                            explodeSeed(p->at(!i), v[!i], i);
                            
                            v[!i] = 0;
                        }
                    }
                    return v;
                }
            }
        }
    }
    else {
        return array<unsigned int, 2>({get<unsigned int>(p->at(0)), get<unsigned int>(p->at(1))});
    }
    
    return nullopt;
}

bool SnailfishNumber::split()
{
    bool changed{false};
    for (size_t i=0; i<2; ++i) {
        if (holds_alternative<unsigned int>(p->at(i))) {
            unsigned int n = get<unsigned int>(p->at(i));
            if (n > 9) {
                auto splitNumber = SnailfishNumber();
                splitNumber.p->at(0) = n/2;
                splitNumber.p->at(1) = ceil(n/2.);
                p->at(i) = move(splitNumber);
                return true;
            }
        }
        else {
            if (get<SnailfishNumber>(p->at(i)).split()) return true;
        }
    }
    return changed;
}

ostream &operator<<( ostream &output, const SnailfishNumber &n )
{
    output << "[";
    visit([](auto&& arg){cout << arg;}, n.p->at(0));
    cout << ",";
    visit([](auto&& arg){cout << arg;}, n.p->at(1));
    cout << "]";
    return output;
}

template <class T1, class T2>
SnailfishNumber operator+(T1&& n1, T2&& n2) {
    if (n1.p == nullptr) {
        return forward<T2>(n2);
    }
    auto newNumber = SnailfishNumber();
    newNumber.p->at(0) = forward<T1>(n1);
    newNumber.p->at(1) = forward<T2>(n2);
    newNumber.reduce();
    return newNumber;
}


SnailfishNumber parseSnailfishNumber(stringstream &numberStream)
{
    auto number = SnailfishNumber();
    for (size_t i=0; i<2; ++i) {
        if (numberStream.peek() == '[') {
            numberStream.get();
            number.p->at(i) = parseSnailfishNumber(numberStream);
            numberStream.get();
        }
        else {
            unsigned int x;
            numberStream >> x;
            number.p->at(i) = x;
        }
        
        if (i==0) numberStream.get();
    }
    
    return number;
}

vector<SnailfishNumber> read_data()
{
    vector<SnailfishNumber> data;
    ifstream dataFile{fileName};
    string dataString;
    while (dataFile >> dataString) {
        stringstream numberStream(dataString);
        numberStream.get();
        auto number = parseSnailfishNumber(numberStream);
        data.push_back(move(number));
    }
    return data;
}

void task0()
{
    auto data = read_data();
    auto r = move(data[0]);
    for (unsigned int i=1; i<data.size(); ++i) {
        r = move(r) + move(data[i]);
    }
    cout << r.magnitude() << endl;
    return;
}

void task1()
{
    auto data = read_data();
    unsigned int mm{0};
    for (unsigned int i=0; i<data.size(); ++i) {
        for (unsigned int j=i+1; j<data.size(); ++j) {
            mm = max(mm, (data[i]+data[j]).magnitude());
            mm = max(mm, (data[j]+data[i]).magnitude());
        }
    }
    cout << mm << endl;
    return;
}

}; /* namespace day18 */
