#ifndef ALIFE_G_CELL_ARRAY_H
#define ALIFE_G_CELL_ARRAY_H

/**
 * The 8 cell states around a middle one.
 */
typedef struct{
    union {
        struct {
            void* m;
            void* t;
            void* r;
            void* b;
            void* l;
            void* tl;
            void* tr;
            void* br;
            void* bl;
        };
        void* states[9];
    };

} CellNeighborhood;


/**
 * A 2D grid of cells with generic state (void*)
 */
typedef struct {
    int     w;
    int     h;
    void**    array;
} CellArray;

CellArray *         ca_create          (int w, int h, void* (*create_state)());

int                 ca_get_index           (const CellArray* ca, int x, int y);
void*               ca_get                 (const CellArray* ca, int x, int y);
CellNeighborhood    ca_get_neighborhood    (const CellArray* ca, int x, int y);
void                ca_set                 (CellArray* ca, int x, int y, void* s);

#endif //ALIFE_G_CELL_ARRAY_H
