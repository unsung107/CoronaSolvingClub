#include <stdio.h>

int R, C, head, tail;

struct Route{
    int y;
    int x;
    int d;

    Route() {};
    Route(int y, int x, char c) {
        y = y;
        x = x;

        switch (c)
        {
        case '|':
            d = 3;
            break;
        case '-':
            d = 12;
            break;
        case '+':
            d = 15;
            break;
        case '1':
            d = 5;
            break;
        case '2':
            d = 6;
            break;
        case '3':
            d = 10;
            break;
        case '4':
            d = 9;
            break;
        case 'M':
        case 'Z':
            d = 16;
            break;
        default:
            d = 0;
            break;
        }
    }
} board[26][26];

bool visited[26][26];

int dxs[4] = {0, 0, 1, -1};
int dys[4] = {1, -1, 0, 0};

void init() {
    head = 0;
    tail = -1;
    for (int y = 0; y < 26; y ++) {
        for (int x = 0; x < 26; x ++) {
            visited[y][x] = false;
        }
    }
}

struct Rocation{
    int y;
    int x;

    Rocation() {};
    Rocation(int y, int x) : y(y), x(x) {};
} queue[100005];

void push(int y, int x) {
    queue[++tail] = Rocation(y, x);
}

Rocation pop() {
    if (head > tail) return Rocation();
    return queue[head++];
}

Rocation Moscow, Zagrev;
int main() {
    init();
    int resY = 0, resX = 0, resD = 0;
    char tempValue;
    scanf("%d %d ", &R, &C);
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            scanf("%c", &tempValue);
            // printf("[%c]", tempValue);
            board[r][c] = Route(r, c, tempValue);
            if (tempValue == 'M') Moscow = Rocation(r, c);
            else if (tempValue == 'Z') Zagrev = Rocation(r, c);
            else if (tempValue != '.') push(r, c);
        }
        scanf("%c", &tempValue);
    }
    push(Moscow.y, Moscow.x);
    push(Zagrev.y, Zagrev.x);
    bool mos = false, zar = false;
    while (tail >= head) {
        Rocation now = pop();

        if (now.y == Moscow.y && now.x == Moscow.x){
            for (int d = 0; d < 4; d++ ) {
                int ry = now.y + dys[d];
                int rx = now.x + dxs[d];
                if (board[ry][rx].d != 0) mos = true;
            }
        }  
        if (now.y == Zagrev.y && now.x == Zagrev.x){
            for (int d = 0; d < 4; d++ ) {
                int ry = now.y + dys[d];
                int rx = now.x + dxs[d];
                if (board[ry][rx].d != 0) zar = true;
            }
        }  
        
        for (int d = 0; d < 4; d++) {
            if (board[now.y][now.x].d & (1 << d) || board[now.y][now.x].d == 16) {
                // printf("(%d, %d)", now.y, now.x);
                int ry = now.y + dys[d];
                int rx = now.x + dxs[d];
                if (ry > R || ry <= 0 || rx > C || rx <= 0) continue;
                if (board[ry][rx].d == 16) continue;
                else if (board[ry][rx].d == 0) 
                {   
                    if ((resX != 0 && resY != 0) && (resX != rx || resY != ry)) continue;
                    if (now.y == Moscow.y && now.x == Moscow.x && mos) continue;
                    if (now.y == Zagrev.y && now.x == Zagrev.x && zar) continue;

                    resX = rx;
                    resY = ry;
                    int temp_d;
                    switch (d)
                    {
                    case 0:
                        temp_d = 1;
                        break;
                    case 1:
                        temp_d = 0;
                        break;
                    case 2:
                        temp_d = 3;
                        break;
                    case 3:
                        temp_d = 2;
                        break;
                    default:
                        break;
                    }

                    resD = resD | (1 << temp_d);    
                    // printf("(%d, %d), %d //", now.y, now.x, d);

                } else {
                    if (visited[ry][rx]) continue;
                    visited[ry][rx] = true;
                    push(ry, rx);
                }
            }
        }
    }
    char res;
    switch (resD)
    {
    case 3:
        res = '|';
        break;
    case 12:
        res = '-';
        break;
    case 15:
        res = '+';
        break;
    case 5:
        res = '1';
        break;
    case 6:
        res = '2';
        break;
    case 10:
        res = '3';
        break;
    case 9:
        res = '4';
        break;
    
    
    default:
        break;
    }
    printf("%d %d %c", resY, resX, res);
    return 0;
}