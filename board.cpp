#include "board.h"

inline bool valid(int x, int y)
{
    return 0 <= x && x < size && 0 <= y && y < size;
}

inline chess opposite(chess c)
{
    return 3 - c;
}


// Board public
void Board::reset()
{
    memset(map, 0, sizeof(map));
    memset(cnt, 0, sizeof(cnt));
    cnt[0] = size * size;

    _put(size / 2, size / 2, WHITE);
    _put(size / 2 - 1, size / 2, BLACK);
    _put(size / 2, size / 2 - 1, BLACK);
    _put(size / 2 - 1, size / 2 - 1, WHITE);
}

void Board::flip(int x, int y)
{
    --cnt[map[x][y]];
    map[x][y] = opposite(map[x][y]);
    ++cnt[map[x][y]];
}

void Board::_put(int x, int y, chess c)
{
    map[x][y] = c;
    ++cnt[c];
    --cnt[0];
    for (int i = 0; i < 8; ++i) {
        int nx = x + go[i][0], ny = y + go[i][1], cnt = 0;
        for ( ; valid(nx, ny) && map[nx][ny] == opposite(c);
                nx += go[i][0], ny += go[i][1])
            ++cnt;
        if (!(valid(nx, ny) && map[nx][ny] == c && cnt > 0))
            continue;
        nx = x + go[i][0], ny = y + go[i][1];
        for ( ; valid(nx, ny) && map[nx][ny] == opposite(c);
                nx += go[i][0], ny += go[i][1])
            flip(nx, ny);
    }
}

bool Board::willFlip(int x, int y, chess c) const
{
    for (int i = 0; i < 8; ++i) {
        int nx = x + go[i][0], ny = y + go[i][1], cnt = 0;
        for ( ; valid(nx, ny) && map[nx][ny] == opposite(c);
                nx += go[i][0], ny += go[i][1])
            ++cnt;
        if (valid(nx, ny) && map[nx][ny] == c && cnt > 0)
            return true;
    }
    return false;
}

Board::Board()
{
    reset();
}

Board::Board(const Board &b)
{
    memcpy(map, b.map, sizeof(map));
    memcpy(cnt, b.cnt, sizeof(cnt));
}

bool Board::canPut(int x, int y, chess c) const
{
    return map[x][y] == EMPTY && willFlip(x, y, c);
}

bool Board::haveMove(chess c) const
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (canPut(i, j, c))
                return true;
    return false;
}

void Board::print() const
{
    printf("BLACK: %2d, WHITE: %2d\n", cnt[BLACK], cnt[WHITE]);
    char chess_char[3] = {'_', '@', 'O'};
    printf("  ");
    for (int i = 0; i < size; ++i)
        printf("%d ", i);
    puts("");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j)
            if (canPut(i, j, BLACK))
                printf(". ");
            else printf("%c ", chess_char[map[i][j]]);
        puts("");
    }
}

Board Board::put(int x, int y, chess c) const
{
    Board res(*this);
    res._put(x, y, c);
    return res;
}

int Board::getCnt(chess c) const
{
    return cnt[c];
}

chess Board::getChess(int x, int y) const
{
    return map[x][y];
}
