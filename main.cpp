#include <stdio.h>
#include <string.h>

#include "board.h"
#include "ai.h"

int main()
{
    Board t;
    AI ai[3];
    ai[BLACK] = AI(BLACK);
    ai[WHITE] = AI(WHITE);
    chess c = BLACK;
    while (true) {
        t.print();
        if (!t.haveMove(c)) {
            if (!t.haveMove(opposite(c))) {
                printf("BOTH NO AVAILABLE MOVE\n");
                break;
            }
            printf("NO AVAILABLE MOVE\n");
        } else {
            int x, y;
            if (c == WHITE)
                ai[c].judge(x, y, t, 7);
            else do {
                scanf("%d%d", &x, &y);
            } while (!t.canPut(x, y, c));
            printf("CHOICE: (%d, %d)\n", x, y);
            t = t.put(x, y, c);
        }
        c = opposite(c);
        printf("\n");
    }
    return 0;
}
