#include <stdio.h>

int T, M, P;

struct Info {
    int depth;
    int left;

    Info() {};
    Info(int depth, int left) : depth(depth), left(left) {};
};

void init() {

};

Info cal(int num) {
    int d = 1;
    while (d * (d + 1) / 2 < num) {
        d += 1;
    }
    return Info(d, num - (d - 1) * d / 2);
}

int abs(int num) {
    if (num >= 0) {
        return num;
    } else {
        return -1 * num;
    }
}

int dys[6] = {0, 0, 1, 1, -1, -1};
int dxs[6] = {1, -1, 1, -1, 1, -1};
int head, tail;

struct Qu {
    int left;
    int depth;
    int cnt;

    Qu() {};
    Qu(int left, int depth, int cnt) : left(left), depth(depth), cnt(cnt) {};
} queue[10006];


int main() {
    scanf("%d", &T);

    for (int ro = 1; ro <= T; ro++) {
        int res = 0;
        scanf("%d %d", &M, &P);
        Info minji = cal(M);
        Info presure = cal(P);

        int gap = presure.depth - minji.depth;

        int v_gap = abs(gap);
        int h_gap;
        bool isbetween = (presure.left - (minji.left + gap)) * (presure.left - minji.left) <= 0;

        if (isbetween) {
            res = v_gap;
        } else {
            h_gap = abs((presure.left - (minji.left + gap))) >= abs((presure.left - minji.left)) ? abs((presure.left - minji.left)) : abs((presure.left - (minji.left + gap)));
            res = v_gap + h_gap;
        }
        // printf("%d %d ", presure.depth - minji.depth, h_gap);
        printf("#%d %d\n", ro, res);
    }
    return 0;
}