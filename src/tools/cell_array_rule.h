#ifndef ALIFE_CELL_ARRAY_RULE_H
#define ALIFE_CELL_ARRAY_RULE_H

typedef enum NEIGHBORHOOD_SIZE {
    NB_ONE, NB_FIVE
} NEIGHBORHOOD_SIZE;

typedef struct {
    int *rule_map;
    NEIGHBORHOOD_SIZE size;
} CellArrayRule;

CellArrayRule *ca_rule_create(enum NEIGHBORHOOD_SIZE);

void ca_rule_init_from_file(CellArrayRule *ca_rule, char *filename);

#endif //ALIFE_CELL_ARRAY_RULE_H
