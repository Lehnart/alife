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

CellArray *         cell_array          (int w, int h);

int                 get_index           (const CellArray* ca, int x, int y);
void*               get                 (const CellArray* ca, int x, int y);
CellNeighborhood    get_neighborhood    (const CellArray* ca, int x, int y);
void                set                 (CellArray* ca, int x, int y, void* s);

#endif //ALIFE_G_CELL_ARRAY_H
