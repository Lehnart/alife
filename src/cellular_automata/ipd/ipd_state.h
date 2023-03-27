#ifndef ALIFE_IPD_STATE_H
#define ALIFE_IPD_STATE_H

typedef struct {
    int *mem_to_move;
} IPDStateCode;

typedef struct {
    IPDStateCode *state_to_code;
} IPDStateCodes;

IPDStateCodes *create(int memory_size, int state_count);

void destruct(IPDStateCodes *pIPDStateCodes);

#endif //ALIFE_IPD_STATE_H
