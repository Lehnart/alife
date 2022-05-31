#include <malloc.h>
#include "ipd_state.h"
#include "../../tools/tools.h"

IPDStateCodes* create(int memory_size, int state_count){
    int move_size = get_pow(2, memory_size);
    int *moves;
    IPDStateCode * code_array = malloc(state_count*sizeof(IPDStateCode));

    for(int state=0; state<state_count; state++){
        moves = malloc(move_size*sizeof(int));

        int state_reminder = state;
        for(int i = move_size; i>1; i--){
            if (state_reminder >= get_pow(2,i-1)) {
                moves[i-1] = 1;
                state_reminder -= get_pow(2,i-1);
            }
            else moves[i-1]=0;
        }
        if (state_reminder>0) moves[0]=1;
        else moves[0]=0;

        code_array[state].mem_to_move = moves;
    }

    IPDStateCodes *codes = malloc(sizeof(IPDStateCodes));
    codes->state_to_code = code_array;
    return codes;
}