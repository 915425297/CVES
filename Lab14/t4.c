#include "declarations.h"

void
t4(float M1[LEN4][LEN4], float M2[LEN4][LEN4], float M3[LEN4][LEN4]) {
    for (int nl = 0; nl < ntimes / (10 * LEN4); nl ++) {
        for (int i = 0; i < LEN4; i ++) {
            for (int j = 0; j < LEN4; j += 4) {
                for (int k = 0; k < LEN4; k ++) {
                	M3[i][j] += M1[i][k] * M2[k][j];
                    M3[i][j + 1] += M1[i][k] * M2[k][j + 1];
                    M3[i][j + 2] += M1[i][k] * M2[k][j + 2];
                    M3[i][j + 3] += M1[i][k] * M2[k][j + 3];
                }
            }
        }
        M3[0][0] ++;
    }
}
