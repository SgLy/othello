#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <stdio.h>
#include <string.h>

typedef unsigned short chess;
const chess EMPTY = 0, BLACK = 1, WHITE = 2;
const int size = 8;
const int go[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

bool valid(int x, int y);

chess opposite(chess c);

class Board {
    private:
        chess map[size][size];
        unsigned int cnt[3];

        void reset();
        void flip(int x, int y);
        void _put(int x, int y, chess c);
        bool willFlip(int x, int y, chess c) const;

    public:
        Board();
        Board(const Board &b);

        bool canPut(int x, int y, chess c) const;
        bool haveMove(chess c) const;
        void print() const;
        Board put(int x, int y, chess c) const;
        int getCnt(chess c) const;
        chess getChess(int x, int y) const;
};

#endif
