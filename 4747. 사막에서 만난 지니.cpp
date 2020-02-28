#include <stdio.h>

int T, N;
int values[10005], numOfValue[10005];
int children[3][2005];

void init() {
    for (int i = 0; i < 10005; i++) {
        values[i] = 0;
        numOfValue[i] = 0;
    }
}

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
            numOfValue[eachValue] += 1;
        }

    }

    return 0;
}