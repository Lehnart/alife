#include <stdlib.h>
#include "spiral_rule.h"

int apply(const SpiralRule * pRule, const CellNeighborhood *pN){

    int m = pN->m;
    if (m != 0){
        double r = (double)rand()/RAND_MAX;
        if (r < pRule->decay_proba){
            return 0;
        }
        return m;
    }

    float * ps = pRule->catalytic_probas;
    int   * cs = pRule->catalytic_states;

    for(int i=0; i<pRule->state_count; i++){
        ps[i]=0.f;
    }
    ps[0]=pRule->claim_empty;

    ps[pN->t] += pRule->claim_cell;
    if (cs[pN->t] == pN->tl) ps[pN->t] += pRule->claim_hyper;
    if (cs[pN->t] == pN->tr) ps[pN->t] += pRule->claim_hyper;
    if (cs[pN->t] == pN->l)  ps[pN->t] += pRule->claim_hyper;
    if (cs[pN->t] == pN->r)  ps[pN->t] += pRule->claim_hyper;

    ps[pN->l] += pRule->claim_cell;
    if (cs[pN->l] == pN->tl) ps[pN->l] += pRule->claim_hyper;
    if (cs[pN->l] == pN->bl) ps[pN->l] += pRule->claim_hyper;
    if (cs[pN->l] == pN->t)  ps[pN->l] += pRule->claim_hyper;
    if (cs[pN->l] == pN->b)  ps[pN->l] += pRule->claim_hyper;

    ps[pN->b] += pRule->claim_cell;
    if (cs[pN->b] == pN->l)   ps[pN->b] += pRule->claim_hyper;
    if (cs[pN->b] == pN->r)   ps[pN->b] += pRule->claim_hyper;
    if (cs[pN->b] == pN->bl)  ps[pN->b] += pRule->claim_hyper;
    if (cs[pN->b] == pN->br)  ps[pN->b] += pRule->claim_hyper;

    ps[pN->r] += pRule->claim_cell;
    if (cs[pN->r] == pN->br)   ps[pN->r] += pRule->claim_hyper;
    if (cs[pN->r] == pN->tr)   ps[pN->r] += pRule->claim_hyper;
    if (cs[pN->r] == pN->t)    ps[pN->r] += pRule->claim_hyper;
    if (cs[pN->r] == pN->b)    ps[pN->r] += pRule->claim_hyper;

    float sum = 0.f;
    for (int i = 0; i < pRule->state_count; i++) sum += ps[i];

    ps[0] = ps[0] / sum;
    for (int i = 1; i < pRule->state_count; i++) ps[i] = ps[i-1]+(ps[i]/sum);

    double r = ((double) rand())/ ((double) RAND_MAX);
    int index = 0;
    while (r > ps[index]){
        index++;
    }
    return index;
}

void evolve(CellArray* pCA, const SpiralRule* pRule) {

    int *intermediate_array = malloc( pCA->w*pCA->h*sizeof(int));

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {

            CellNeighborhood cn = get_neighborhood(pCA, x, y);
            intermediate_array[x + (pCA->w * y)] = apply(pRule, &cn);
        }
    }

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            pCA->array[x + (pCA->w * y)] = intermediate_array[x + (pCA->w * y)];
        }
    }
    free(intermediate_array);

    for (int y = 0; y < pCA->h; y+=2) {
        for (int x = 0; x < pCA->w; x+=2) {
            int tl = get(pCA, x, y);
            int tr = get(pCA, x+1, y);
            int bl = get(pCA, x, y+1);
            int br = get(pCA, x+1, y+1);

            double r = ( (double) rand() ) / ( (double) RAND_MAX );

            if (r < 0.5){
                set(pCA, x, y, tr);
                set(pCA, x, y+1, tl);
                set(pCA, x+1, y+1, bl);
                set(pCA, x+1, y, br);
            }

            else{
                set(pCA, x, y, bl);
                set(pCA, x, y+1, br);
                set(pCA, x+1, y+1, tr);
                set(pCA, x+1, y, tl);
            }
        }
    }

    for (int y = 1; y < pCA->h; y+=2) {
        for (int x = 1; x < pCA->w; x+=2) {
            int tl = get(pCA, x, y);
            int tr = get(pCA, x+1, y);
            int bl = get(pCA, x, y+1);
            int br = get(pCA, x+1, y+1);

            double r = ( (double) rand() ) / ( (double) RAND_MAX );

            if (r < 0.5){
                set(pCA, x, y, tr);
                set(pCA, x, y+1, tl);
                set(pCA, x+1, y+1, bl);
                set(pCA, x+1, y, br);
            }

            else{
                set(pCA, x, y, bl);
                set(pCA, x, y+1, br);
                set(pCA, x+1, y+1, tr);
                set(pCA, x+1, y, tl);
            }
        }
    }

}
