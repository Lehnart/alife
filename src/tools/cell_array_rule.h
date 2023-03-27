#ifndef ALIFE_CELL_ARRAY_RULE_H
#define ALIFE_CELL_ARRAY_RULE_H

typedef struct {
    int *rule_map;
} CellArrayRule;

CellArrayRule *ca_rule_create(int size);

void ca_rule_init_from_file(CellArrayRule *ca_rule, char *filename);

#endif //ALIFE_CELL_ARRAY_RULE_H
