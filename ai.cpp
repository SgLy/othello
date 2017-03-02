#include "ai.h"

int AI::countVal(const Board &b)
{
    int res = 0;
    int tmp[3];
    tmp[EMPTY] = 0; tmp[self] = 1; tmp[opposite(self)] = -1;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            res += tmp[b.getChess(i, j)] * values[i][j];
    return res;
}

AI::AI (chess _self):
    self(_self)
{
    const int tmp[8][8] = {
        {9, 8, 7, 6, 6, 7, 8, 9},
        {8, 8, 3, 2, 2, 3, 8, 8},
        {7, 3, 7, 1, 1, 7, 3, 7},
        {6, 2, 1, 6, 6, 1, 2, 6},
        {6, 2, 1, 6, 6, 1, 2, 6},
        {7, 3, 7, 1, 1, 7, 3, 7},
        {8, 8, 3, 2, 2, 3, 8, 8},
        {9, 8, 7, 6, 6, 7, 8, 9}
    };
    memcpy(values, tmp, sizeof(values));
}

int AI::judge(int &x, int &y, const Board &b, int depth)
{
    if (depth == 0)
        return countVal(b);
    AI * enemy = new AI(opposite(self));
    x = y = -1;
    int max = 1 << 31;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            if (!b.canPut(i, j, self))
                continue;
            int _x, _y;
            int c = -enemy->judge(_x, _y, b.put(i, j, self), depth - 1);
            if (c > max) {
                x = i;
                y = j;
                max = c;
            }
        }
    delete enemy;
    if (x == -1 && y == -1)
        return countVal(b);
    else
        return max;
}
