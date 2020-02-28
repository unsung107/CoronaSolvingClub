#include <stdio.h>

int T, N, average;
int values[10005];
int children[3][2005];
bool visited[10005], check;
void init() {
    for (int i = 0; i < 10005; i++) {
        values[i] = 0;
        visited[i] = false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2005; j++) {
            children[i][j] = -1;
        }
    }
    check = false;
}

void dfs(int c, int idx, int sum, int now) {
    if (check) return;
    children[c][now] = idx;

    if (c == 2 && sum == average) {
        check = true;
        return ;
    }
    if (sum > average) {
        children[c][now] = -1;
        return ;
    }
    if (sum == average) {
        for (int x = 0; x < N; x++) {
            if (visited[x]) continue;
            visited[x] = true;
            dfs(c + 1, x, values[x], 0);
            if (check) break;
            visited[x] = false;
        }
        return ;
    }

    for (int i = idx + 1; i < N; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        dfs(c, i, sum + values[i], now + 1);
        if (check) break;
        children[c][now + 1] = -1;
        visited[i] = false;
    }

};

int main() {

    scanf("%d", &T);
    for (int ro = 1; ro <= T; ro ++ ) {
        int totalValue = 0, eachValue;
        init();
        scanf("%d", &N);

        for (int n = 0; n < N; n++) {
            scanf("%d", &eachValue);
            totalValue += eachValue;
            values[n] = eachValue;
        }

        average = totalValue / 3;
        
        for (int rx = 0; rx < N; rx ++) {
            visited[rx] = true;
            dfs(0,rx,values[rx],0);
            visited[rx] = false;
            if (check) break;
        }

        printf("#%d\n", ro);
        for (int chi = 0; chi < 3; chi++) {
            int id = 0;
            while (children[chi][id] != -1) {
                printf("%d ", values[children[chi][id++]]);
            }
            printf("\n");
        }
    }

    return 0;
}