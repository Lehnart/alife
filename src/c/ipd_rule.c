#include <stdlib.h>
#include "ipd_rule.h"

float score(const IPDRule *pRule, int s, int os) {
    if (s == 0 && os == 0) {
        return pRule->P;
    }
    if (s == 1 && os == 1) {
        return pRule->R;
    }
    if (s == 1 && os == 0) {
        return pRule->S;
    }
    return pRule->T;
}

float evaluate(const IPDRule *pRule, const CellNeighborhood *pN) {
    float sum = 0.f;
    for (int i = 0; i < pRule->try_count; i++) {
        sum += score(pRule, pN->m, pN->t);
        sum += score(pRule, pN->m, pN->l);
        sum += score(pRule, pN->m, pN->r);
        sum += score(pRule, pN->m, pN->b);
    }
    sum /= 4.f;
    sum /= (float) pRule->try_count;
    return sum;
}

void evolve(CellArray *pCA, const IPDRule *pRule) {
    float *intermediate_array = malloc(pCA->w * pCA->h * sizeof(float));
    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            CellNeighborhood cn = get_neighborhood(pCA, x, y);
            intermediate_array[x + (pCA->w * y)] = evaluate(pRule, &cn);
        }
    }

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            int t = get(pCA, x, y - 1);
            float ts = intermediate_array[get_index(pCA, x, y - 1)];

            int b = get(pCA, x, y + 1);
            float bs = intermediate_array[get_index(pCA, x, y +1)];

            int l = get(pCA, x - 1, y);
            float ls = intermediate_array[get_index(pCA, x-1, y)];

            int r = get(pCA, x + 1, y);
            float rs = intermediate_array[get_index(pCA, x+1, y)];

            int m = get(pCA, x, y);
            float ms = intermediate_array[get_index(pCA, x, y)];

            float max = -1.f;
            int max_state = -1;
            if (ts > max) {
                max_state = t;
                max = ts;
            }
            if (bs > max) {
                max_state = b;
                max = bs;
            }
            if (rs > max) {
                max_state = r;
                max = rs;
            }
            if (ls > max) {
                max_state = l;
                max = ls;
            }
            if (ms > max) {
                max_state = m;
            }
            set(pCA, x, y, max_state);
        }
    }
   free(intermediate_array);
}
