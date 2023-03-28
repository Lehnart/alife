#include "cell_array_rule.h"
#include "malloc.h"

void read_buffer_from_file_with_one_neighboor(int *rule_map, const char buffer[10]);
void read_buffer_from_file_with_five_neighboor(int *rule_map, const char buffer[10]);

CellArrayRule *ca_rule_create(NEIGHBORHOOD_SIZE size) {
    int array_size = 0;
    if (size == NB_ONE){
        array_size = 100;
    }
    else if(size == NB_FIVE){
        array_size = 100000;
    }
    int *rule_map = malloc(sizeof(int) * array_size);
    CellArrayRule *ca_rule = malloc(sizeof(CellArrayRule));
    ca_rule->rule_map = rule_map;
    ca_rule->size = size;
    return ca_rule;
}

void ca_rule_init_from_file(CellArrayRule *ca_rule, char *filename) {
    FILE *rule_file = fopen(filename, "r");

    int *rule_map = ca_rule->rule_map;

    char buffer[10] = {0};
    fgets(buffer, 10, rule_file);

    while (buffer[0] >= '0' && buffer[0] <= '9') {
        if(ca_rule->size == NB_ONE){
            read_buffer_from_file_with_one_neighboor(rule_map,buffer);
        }
        else if(ca_rule->size == NB_FIVE){
            read_buffer_from_file_with_five_neighboor(rule_map,buffer);
        }

        buffer[0] = '\0';
        fgets(buffer, 10, rule_file);
    }
    fclose(rule_file);
}

void read_buffer_from_file_with_one_neighboor(int *rule_map, const char buffer[10]){
    int s = 0;
    s += (buffer[0] - '0') * 10000;
    rule_map[s] = buffer[1] - '0';
}

void read_buffer_from_file_with_five_neighboor(int *rule_map, const char buffer[10]){
    int s = 0;
    s += (buffer[0] - '0') * 10000;
    s += (buffer[1] - '0') * 1000;
    s += (buffer[2] - '0') * 100;
    s += (buffer[3] - '0') * 10;
    s += (buffer[4] - '0') * 1;
    rule_map[s] = buffer[5] - '0';

//    s = 0;
//    s += (buffer[0] - '0') * 10000;
//    s += (buffer[4] - '0') * 1000;
//    s += (buffer[1] - '0') * 100;
//    s += (buffer[2] - '0') * 10;
//    s += (buffer[3] - '0') * 1;
//    rule_map[s] = buffer[5] - '0';
//
//    s = 0;
//    s += (buffer[0] - '0') * 10000;
//    s += (buffer[3] - '0') * 1000;
//    s += (buffer[4] - '0') * 100;
//    s += (buffer[1] - '0') * 10;
//    s += (buffer[2] - '0') * 1;
//    rule_map[s] = buffer[5] - '0';
//
//
//    s = 0;
//    s += (buffer[0] - '0') * 10000;
//    s += (buffer[2] - '0') * 1000;
//    s += (buffer[3] - '0') * 100;
//    s += (buffer[4] - '0') * 10;
//    s += (buffer[1] - '0') * 1;
//    rule_map[s] = buffer[5] - '0';
}