#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "cell_array.h"
#include "spiral_rule.h"
#include "cell_neighborhood.h"

int get(const CellArray* ca, int x, int y){
    if (x<0) x = ca->w + x;
    if (x>=ca->w) x = x - ca->w;
    if (y<0) y = ca->h + y;
    if (y>=ca->h) y = y - ca->h;
    return ca->array[x+(ca->w*y)];
}

void set(CellArray* ca, int x, int y, int s){
    if (x<0) return ;
    if (x>=ca->w) return ;
    if (y<0) return ;
    if (y>=ca->h) return ;
    ca->array[x+(ca->w*y)] = s;
}

CellArray * random_cell_array(int w, int h, const int * states, const double * cumulative_prob){

    int* p_array = (int*)malloc(sizeof(int) * (w*h) );
    int* p_iarray = (int*)malloc(sizeof(int) * (w*h) );

    CellArray * p_cell_array = (CellArray*)malloc(sizeof(CellArray));
    p_cell_array->w=w;
    p_cell_array->h=h;
    p_cell_array->array=p_array;
    p_cell_array->iarray=p_iarray;

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            double r = ( (double) rand() ) / ( (double) RAND_MAX );

            int index = 0;
            while (r > cumulative_prob[index]){
                index++;
            }
            p_array[x+(w*y)] = states[index];
        }
    }

    return p_cell_array;
}

CellArray * cell_array(int w, int h){

    int* p_array = (int*)malloc(sizeof(int) * (w*h) );
    int* p_iarray = (int*)malloc(sizeof(int) * (w*h) );

    CellArray * p_cell_array = (CellArray*)malloc(sizeof(CellArray));
    p_cell_array->w=w;
    p_cell_array->h=h;
    p_cell_array->array=p_array;
    p_cell_array->iarray=p_iarray;

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            p_array[x+(w*y)] = 0;
        }
    }

    return p_cell_array;
}

CellNeighborhood get_neighborhood(CellArray* pCA, int x, int y){
    CellNeighborhood cn;
    cn.m = get(pCA, x, y);
    cn.t = get(pCA, x, y - 1);
    cn.b = get(pCA, x, y + 1);
    cn.r = get(pCA, x + 1, y);
    cn.l = get(pCA, x - 1, y);
    cn.tl = get(pCA, x - 1, y - 1);
    cn.tr = get(pCA, x + 1, y - 1);
    cn.bl = get(pCA, x - 1, y + 1);
    cn.br = get(pCA, x + 1, y + 1);

    return cn;
}

void evolve(CellArray* pCA, const SpiralRule* pRule) {

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {

            CellNeighborhood cn = get_neighborhood(pCA, x, y);
            pCA->iarray[x + (pCA->w * y)] = apply(pRule, &cn);
        }
    }

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            pCA->array[x + (pCA->w * y)] = pCA->iarray[x + (pCA->w * y)];
        }
    }

    for (int y = 0; y < pCA->h; y+=2) {
        for (int x = 0; x < pCA->w; x+=2) {
            int tl = get(pCA, x, y);
            int tr = get(pCA, x+1, y);
            int bl = get(pCA, x, y+1);
            int br = get(pCA, x+1, y+1);

            double r = ( (double) rand() ) / ( (double) RAND_MAX );

            if (r < 0.5){
                set(pCA, x, y, tr);
                set(pCA, x, y+1, tl);
                set(pCA, x+1, y+1, bl);
                set(pCA, x+1, y, br);
            }

            else{
                set(pCA, x, y, bl);
                set(pCA, x, y+1, br);
                set(pCA, x+1, y+1, tr);
                set(pCA, x+1, y, tl);
            }
        }
    }

    for (int y = 1; y < pCA->h; y+=2) {
        for (int x = 1; x < pCA->w; x+=2) {
            int tl = get(pCA, x, y);
            int tr = get(pCA, x+1, y);
            int bl = get(pCA, x, y+1);
            int br = get(pCA, x+1, y+1);

            double r = ( (double) rand() ) / ( (double) RAND_MAX );

            if (r < 0.5){
                set(pCA, x, y, tr);
                set(pCA, x, y+1, tl);
                set(pCA, x+1, y+1, bl);
                set(pCA, x+1, y, br);
            }

            else{
                set(pCA, x, y, bl);
                set(pCA, x, y+1, br);
                set(pCA, x+1, y+1, tr);
                set(pCA, x+1, y, tl);
            }
        }
    }

}