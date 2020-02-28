#include <stdio.h>

int R, BF[1005], N, f, j;
int jjacksline[1005], head, tail, res;

struct jjack {
    int l;
    int r;

    jjack() {};
    jjack(int l, int r) : l(l), r(r) {};
} cycles[1005];

struct Route {
    Route *next;
    int e;

    Route() {};
    Route(int e, Route *next) : e(e), next(next) {};

} con[1005];

struct Info {
    int start;
    int now;
    int length;
    
    Info() {};
    Info(int start, int now, int length) : start(start), now(now), length(length) {};
} queue[100005];

Route *mem[1005];

bool visited[1005];
void init() {
    for (int i = 0; i < 1005; i++) {
        mem[i] = nullptr;
        visited[i] = false;
        cycles[i] = jjack();
        BF[i] = 0;
        jjacksline[i] = 0;
    }
    j = 0;
    res = 0;
}

Info pop() {
    if (head > tail) return Info();
    return queue[head++];
}

void push(int start, int now, int length) {
    queue[++tail] = Info(start, now, length);
}

int main() {

    scanf("%d", &R);

    for (int ro = 1; ro <= R; ro++) {
        scanf("%d", &N);
        init();
        for (int i = 1; i <= N; i++) {
            scanf("%d", &f);
            BF[i] = f;
            con[i] = Route(i, mem[f]);
            mem[f] = &con[i];
            if (BF[f] == i) {
                cycles[j++] = jjack(i, f);
            }
        }
        

        for (int i = 0; i < j; i++) {
            int start = cycles[i].l;
            int end = cycles[i].r;
            visited[start] = true;
            visited[end] = true;
            tail = -1;
            head = 0;
            int max_length_l = 0;
            int max_length_r = 0;
            push(start, start, 1);
            while (tail >= head) {
                Info info = pop();
                if (max_length_l < info.length) max_length_l = info.length;

                for (Route *edge = mem[info.now]; edge != nullptr; edge = edge -> next) {
                    if (visited[edge -> e]) continue;
                    visited[edge -> e] = true;
                    push(start, edge -> e, info.length + 1);
                }
            }

            tail = -1;
            head = 0;
            push(end, end, 1);
            while (tail >= head) {
                Info info = pop();
                if (max_length_r < info.length) max_length_r = info.length;

                for (Route *edge = mem[info.now]; edge != nullptr; edge = edge -> next) {
                    if (visited[edge -> e]) continue;
                    visited[edge -> e] = true;
                    push(start, edge -> e, info.length + 1);
                }

            }
            jjacksline[i] = max_length_l + max_length_r;
        }
        for (int i = 0; i < j; i++) {
            res += jjacksline[i];
        }
        int max_length = 0;
        for (int t_start = 1; t_start <= N; t_start ++) {
            if (visited[t_start]) continue;
            tail = -1;
            head = 0;
            visited[t_start] = true;
            push(t_start, t_start, 1);

            while (tail >= head) {
                Info info = pop();

                for (Route *edge = mem[info.now]; edge != nullptr; edge = edge -> next) {

                    if (edge -> e == t_start) {
                        if (max_length < info.length) max_length = info.length;
                        continue;
                    };
                    visited[edge -> e] = true;
                    push(t_start, edge -> e, info.length + 1);
                }
            }
        }
        
        int result = max_length > res ? max_length : res;
        printf("#%d %d \n", ro, result);
    }


    return 0;
}