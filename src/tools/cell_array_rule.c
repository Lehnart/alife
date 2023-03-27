#include "cell_array_rule.h"
#include "malloc.h"

CellArrayRule *ca_rule_create(int size) {
    int *rule_map = malloc(sizeof(int) * size);
    CellArrayRule *ca_rule = malloc(sizeof(CellArrayRule));
    ca_rule->rule_map = rule_map;
    return ca_rule;
}

void ca_rule_init_from_file(CellArrayRule *ca_rule, char *filename) {
    FILE *rule_file = fopen(filename, "r");

    int *rule_map = ca_rule->rule_map;

    char buffer[10] = {0};
    fgets(buffer, 10, rule_file);

    while (buffer[0] >= '0' && buffer[0] <= '9') {
        int s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[1] - '0') * 1000;
        s += (buffer[2] - '0') * 100;
        s += (buffer[3] - '0') * 10;
        s += (buffer[4] - '0') * 1;
        rule_map[s] = buffer[5] - '0';

        s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[4] - '0') * 1000;
        s += (buffer[1] - '0') * 100;
        s += (buffer[2] - '0') * 10;
        s += (buffer[3] - '0') * 1;
        rule_map[s] = buffer[5] - '0';

        s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[3] - '0') * 1000;
        s += (buffer[4] - '0') * 100;
        s += (buffer[1] - '0') * 10;
        s += (buffer[2] - '0') * 1;
        rule_map[s] = buffer[5] - '0';


        s = 0;
        s += (buffer[0] - '0') * 10000;
        s += (buffer[2] - '0') * 1000;
        s += (buffer[3] - '0') * 100;
        s += (buffer[4] - '0') * 10;
        s += (buffer[1] - '0') * 1;
        rule_map[s] = buffer[5] - '0';

        buffer[0] = '\0';
        fgets(buffer, 10, rule_file);
    }
    fclose(rule_file);
}

