#include <limits.h>
#include <malloc.h>
#include "ipd_rule.h"
#include "../../tools/tools.h"


void add_to_memory(int *memory, int my_move, int p2_move) {
//    int temp;
//    for (int i = 0; i < memory_size; i++) {
//        temp = memory[i];
//
//        if(i==0) {
//            memory[i] = p2_move;
//        }
//
//        else {
//            memory[i] = my_move;
//            my_move = temp;
//        }
//    }

    memory[0] = my_move;
    memory[1] = p2_move;
}

int get_move(const IPDGame * pGame, const int *memory, int memory_size, int state) {

    int move_index = (memory[0]<<1) + memory[1];
    int move = pGame->pCodes->state_to_code[state].mem_to_move[move_index];

    if (rand_double() < pGame->pRule->error_proba){
        move++;
        move %= 2;
    }

    return move;
}

float score(const IPDRule *pRule, int p1_move, int p2_move) {
    if (p1_move == 0 && p2_move == 0) {
        return pRule->P;
    }
    if (p1_move == 1 && p2_move == 1) {
        return pRule->R;
    }
    if (p1_move == 1 && p2_move == 0) {
        return pRule->S;
    }
    return pRule->T;
}

float play(const IPDGame *pGame, int p1_state, int p2_state) {
    int memory_size = pGame->pRule->memory_size;

    for (int i = 0; i < pGame->pRule->memory_size; i++) {
        pGame->p1_memory[i] = (int) (rand_long() % 2);
        pGame->p2_memory[i] = (int) (rand_long() % 2);
    }

    float score_sum = 0.f;
    for (int i = 0; i < pGame->pRule->try_count; i++) {
        int p1_move = get_move(pGame, pGame->p1_memory, memory_size, p1_state);
        int p2_move = get_move(pGame, pGame->p2_memory, memory_size, p2_state);
        add_to_memory(pGame->p1_memory, p1_move, p2_move);
        add_to_memory(pGame->p2_memory, p2_move, p1_move);
        score_sum += score(pGame->pRule, p1_move, p2_move);
    }

    score_sum /= (float) pGame->pRule->try_count;
    return score_sum;
}

float evaluate(const IPDGame *pGame, const CellNeighborhood *pN) {
    float sum = 0.f;
    sum += play(pGame, pN->m, pN->t);
    sum += play(pGame, pN->m, pN->l);
    sum += play(pGame, pN->m, pN->r);
    sum += play(pGame, pN->m, pN->b);
    sum /= 4.f;
    return sum;
}

void evolve(CellArray *pCA, const IPDRule *pRule) {

    float *intermediate_array = malloc(pCA->w * pCA->h * sizeof(float));
    IPDGame game = {
            pRule,
            create(pRule->memory_size, pRule->state_count),
            malloc(pRule->memory_size*sizeof(int)),
            malloc(pRule->memory_size*sizeof(int))
    };

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            CellNeighborhood cn = get_neighborhood(pCA, x, y);
            intermediate_array[get_index(pCA, x, y)] = evaluate(&game, &cn);
        }
    }

    int *next_array = malloc(pCA->w * pCA->h * sizeof(int));
    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            int t = get(pCA, x, y - 1);
            float ts = intermediate_array[get_index(pCA, x, y - 1)];

            int b = get(pCA, x, y + 1);
            float bs = intermediate_array[get_index(pCA, x, y + 1)];

            int l = get(pCA, x - 1, y);
            float ls = intermediate_array[get_index(pCA, x - 1, y)];

            int r = get(pCA, x + 1, y);
            float rs = intermediate_array[get_index(pCA, x + 1, y)];

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
            next_array[get_index(pCA, x, y)] = max_state;
        }
    }
    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {

            if (rand_double() < pRule->mut_proba) {
                set(pCA, x, y, (int) (rand_long() % pRule->state_count));
            } else {
                set(pCA, x, y, next_array[get_index(pCA, x, y)]);
            }
        }
    }

    free(next_array);
    free(intermediate_array);
}
