
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "day4.h"

using namespace std;

namespace day4
{

constexpr char fileName[] = "../input/i4.txt";
constexpr size_t N = 5;

using Board = vector<vector<int>>;

tuple<vector<int>, vector<Board>> read_data()
{
    ifstream dataFile{fileName};
    string numbersString;
    dataFile >> numbersString;
//     auto numbers = parse(numbersString, ',');
    vector<int> numbers;
    string token;
    stringstream sNumbersString(numbersString);
    while (getline(sNumbersString, token, ',')) {
        numbers.push_back(stoi(token));
    }

    vector<Board> boards;
    size_t i{0},j{0};
    while (dataFile >> token) {
        if (j==0) {
            if (i==0) {
                boards.push_back(Board());
            }
            boards.back().push_back(vector<int>());
            i = (i+1)%N;
        }
        boards.back().back().push_back(stoi(token));
        j = (j+1)%N;
    }
    return make_tuple(numbers, boards);
}

bool searchBoard(Board &board, int n)
{
    for (size_t y=0; y<N; ++y) {
        for (size_t x=0; x<N; ++x) {
            if (board[y][x] == n) {
                board[y][x] = -1;
                
                bool allXNeg = true;
                bool allYNeg = true;
                for (size_t i=0; i<N; ++i) {
                    if (board[y][i] >= 0) allXNeg = false;
                    if (board[i][x] >= 0) allYNeg = false;
                }
                if (allXNeg || allYNeg) {
                    return true;
                }
            }
        }
    }
    return false;
}

void task0()
{
    vector<int> numbers;
    vector<Board> boards;
    tie(numbers, boards) = read_data();
    for (auto n : numbers) {
        for (auto &board : boards) {
            if (searchBoard(board, n)) {
                int sum{0};
                for (size_t y=0; y<N; ++y) {
                    for (size_t x=0; x<N; ++x) {
                        if (board[y][x] > 0) sum+=board[y][x];
                    }
                }
                cout << sum << " " << n << endl;
                cout << sum*n << endl;
                return;
            }
        }
    }
}

void task1()
{
    vector<int> numbers;
    vector<Board> boards;
    tie(numbers, boards) = read_data();
    vector found(boards.size(), false);
    unsigned int winCounter{0};
    for (auto n : numbers) {
        for (size_t b=0; b<boards.size(); ++b) {
            if (found[b])
                continue;
            auto &board = boards[b];

            if (searchBoard(board, n)) {
                int sum{0};
                for (size_t y=0; y<N; ++y) {
                    for (size_t x=0; x<N; ++x) {
                        if (board[y][x] > 0) sum+=board[y][x];
                    }
                }
                found[b] = true;
                ++winCounter;
                if (winCounter == boards.size()) {
                    cout << "Board " << b << " win: " << sum << " " << n << endl;
                    cout << sum*n << endl;
                    return;
                }
            }
        }
    }
}

}; /* namespace day4 */
