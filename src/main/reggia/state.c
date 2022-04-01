#include <malloc.h>
#include "state.h"

State* state_create(){
    State *s = malloc(sizeof(State));
    return s;
}