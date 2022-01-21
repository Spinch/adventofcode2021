
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <variant>

#include "day16.h"

using namespace std;

namespace day16
{

constexpr char fileName[] = "../input/i16.txt";

string read_data()
{
    ifstream dataFile{fileName};
    string dataString;
    getline(dataFile, dataString);
    
    return dataString;
}

class BitReader
{
public:
    
    BitReader(string input) : _data(input), _totalBitsRead{0} {reset();};
    
    uint16_t get(unsigned int n);
    
    void reset();
    
    size_t totalBitsRead() {return _totalBitsRead;}

    static constexpr unsigned int BITS_IN_CHAR = 4;

private:
    stringstream _data;
    unsigned int _bitsLeft;
    uint64_t _bitsPull;
    size_t _totalBitsRead;
    
};

uint16_t BitReader::get(unsigned int n)
{
    while (_bitsLeft < n) {
        char c;
        _data >> c;
        uint8_t a = stoi(string(1, c), nullptr, 16);
        _bitsPull <<= BITS_IN_CHAR;
        _bitsLeft += BITS_IN_CHAR;
        _bitsPull |= a;
    }
    _bitsLeft -= n;
    uint64_t result = _bitsPull;
    result >>= _bitsLeft;
    uint64_t mask{0};
    if (_bitsLeft > 0) {
        mask = 1;
        mask <<= _bitsLeft;
        mask -= 1;
    }
    _bitsPull &= mask;
    _totalBitsRead += n;
    
    return result;
}

void BitReader::reset()
{
    _bitsLeft = 0;
    _bitsPull = 0;
}

struct Packet
{
    uint8_t version;
    uint8_t id;
    variant<uint64_t, vector<Packet>> content;
};


Packet readPacket(BitReader &reader)
{
    Packet packet;
    packet.version = reader.get(3);
    packet.id = reader.get(3);
    if (packet.id == 4) {
        uint64_t n{0};
        bool notEnd{true};
        while (notEnd) {
            auto number = reader.get(5);
            notEnd = number & 0b10000;
            number &= 0b1111;
            n <<= reader.BITS_IN_CHAR;
            n |= number;
        }
        packet.content = n;
    }
    else {
        vector<Packet> packets;
        auto lid = reader.get(1);
        if (lid) {
            auto len = reader.get(11);
            for (unsigned int i=0; i<len; ++i) {
                auto p = readPacket(reader);
                packets.push_back(move(p));
            }
        }
        else {
            auto len = reader.get(15);
            auto t1 = reader.totalBitsRead();
            while (reader.totalBitsRead()-t1 < len) {
                auto p = readPacket(reader);
                packets.push_back(move(p));
            }
        }
        packet.content = move(packets);
    }
    
    return packet;
}

unsigned int sumVersions(const Packet &p)
{
    unsigned int sum{p.version};
    if (holds_alternative<vector<Packet>>(p.content)) {
        for (const auto &sp : get<vector<Packet>>(p.content)) {
            sum += sumVersions(sp);
        }
    }
    return sum;
}

void task0()
{
    auto data = read_data();
    BitReader reader(move(data));
    auto packet = readPacket(reader);
    cout << sumVersions(packet) << endl;
    return;
}

uint64_t calculatePacket(const Packet &p)
{
    if (p.id == 0) {
        vector<uint64_t> v(get<vector<Packet>>(p.content).size());
        transform(get<vector<Packet>>(p.content).begin(), get<vector<Packet>>(p.content).end(), v.begin(), [](const Packet &sp){return calculatePacket(sp);});
        auto r = accumulate(v.begin(), v.end(), uint64_t{0});
        return r;
    }
    else if (p.id == 1) {
        vector<uint64_t> v(get<vector<Packet>>(p.content).size());
        transform(get<vector<Packet>>(p.content).begin(), get<vector<Packet>>(p.content).end(), v.begin(), [](const Packet &sp){return calculatePacket(sp);});
        auto r = accumulate(v.begin(), v.end(), uint64_t{1}, [](uint64_t a, uint64_t b){return a*b;});
        return r;
    }
    else if (p.id == 2) {
        vector<uint64_t> v(get<vector<Packet>>(p.content).size());
        transform(get<vector<Packet>>(p.content).begin(), get<vector<Packet>>(p.content).end(), v.begin(), [](const Packet &sp){return calculatePacket(sp);});
        auto r = accumulate(v.begin(), v.end(), std::numeric_limits<uint64_t>::max(), [](uint64_t a, uint64_t b){return min(a,b);});
        return r;
    }
    else if (p.id == 3) {
        vector<uint64_t> v(get<vector<Packet>>(p.content).size());
        transform(get<vector<Packet>>(p.content).begin(), get<vector<Packet>>(p.content).end(), v.begin(), [](const Packet &sp){return calculatePacket(sp);});
        auto r = accumulate(v.begin(), v.end(), uint64_t{0}, [](uint64_t a, uint64_t b){return max(a,b);});
        return r;
    }
    else if (p.id == 4) {
        auto r = get<uint64_t>(p.content);
        return r;
    }
    else if (p.id == 5) {
        auto r = (calculatePacket(get<vector<Packet>>(p.content)[0]) > calculatePacket(get<vector<Packet>>(p.content)[1]));
        return r;
    }
    else if (p.id == 6) {
        auto r = (calculatePacket(get<vector<Packet>>(p.content)[0]) < calculatePacket(get<vector<Packet>>(p.content)[1]));
        return r;
    }
    else if (p.id == 7) {
        auto r = (calculatePacket(get<vector<Packet>>(p.content)[0]) == calculatePacket(get<vector<Packet>>(p.content)[1]));
        return r;
    }
    
    exit(1);
    return numeric_limits<uint64_t>::max();
}

void task1()
{
    auto data = read_data();
    BitReader reader(move(data));
    auto packet = readPacket(reader);
    cout << calculatePacket(packet) << endl;
    return;
}

}; /* namespace day16 */
