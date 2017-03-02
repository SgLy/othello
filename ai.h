#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "board.h"

class AI {
    private:
        chess self;
        int values[8][8];

        int countVal(const Board &b);

    public:
        AI (chess _self = EMPTY);

        int judge(int &x, int &y, const Board &b, int depth);
};

#endif
