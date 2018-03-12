#include "common.h"

#include<algorithm>

using namespace std;


struct location {
    int x;
    int y;
};

#if 1
#define _HEAP_PARENT(_i)    ((_i - (2 - (_i&1))) >> 1)
#define _HEAP_CHILD_L(_i)   ((_i << 1) + 1)
#define _HEAP_CHILD_R(_i)   ((_i << 1) + 2)
vector<int>* swimGrid_createMinHeap(void)
{
    vector<int> *hdl = new vector<int>;

    hdl->clear();

    return hdl;
}

int swimGrid_destroyMinHeap(vector<int> *pHeap)
{
    delete pHeap;
    return 0;
}

int swimGrid_pushMinHeap(vector<int> *pHeap, int val)
{
    int idx = 0;
    
    pHeap->push_back(val);

    idx = pHeap->size() - 1;

    while (idx) {
        int _p = _HEAP_PARENT(idx), tmp;

        if ((pHeap->at(idx)) >= pHeap->at(_p)) {
            break;
        }

        tmp = pHeap->at(_p);
        pHeap->at(_p) = pHeap->at(idx);
        pHeap->at(idx) = tmp;

        idx = _p;
    }
    
    return 0;
}

int swimGrid_popMinHeap(vector<int> *pHeap)
{
    int idx = 0;
    int val;

    val = pHeap->at(pHeap->size() - 1);
    pHeap->at(0) = val;

    while (idx < (pHeap->size() - 1)) {
        int _l = _HEAP_CHILD_L(idx);
        int _r = _HEAP_CHILD_R(idx);
        int _next = idx;
        
        if (_l < (pHeap->size() - 1)) {
            if (pHeap->at(_l) < pHeap->at(_next)) {
                _next = _l;
            }
        }
        if (_r < (pHeap->size() - 1)) {
            if (pHeap->at(_r) < pHeap->at(_next)) {
                _next = _r;
            }
        }

        if (_next == idx) {
            break;
        }
        pHeap->at(idx) = pHeap->at(_next);
        pHeap->at(_next) = val;
        idx = _next;
    }

    pHeap->pop_back();

    return 0;
}

int swimGrid_getMin(vector<int> *pHeap)
{
    return pHeap->at(0);
}
#else
struct cmp_minHeap {
    bool operator() (int i, int j) { return i > j; }
};
vector<int>* swimGrid_createMinHeap(void)
{
    vector<int> *hdl = new vector<int>;

    hdl->clear();
    make_heap(hdl->begin(), hdl->end(), cmp_minHeap());

    return hdl;
}

int swimGrid_destroyMinHeap(vector<int> *pHeap)
{
    delete pHeap;
    return 0;
}

int swimGrid_pushMinHeap(vector<int> *pHeap, int val)
{
    pHeap->push_back(val);
    push_heap(pHeap->begin(), pHeap->end(), cmp_minHeap());

    return 0;
}

int swimGrid_popMinHeap(vector<int> *pHeap)
{
    pop_heap(pHeap->begin(), pHeap->end(), cmp_minHeap());
    pHeap->pop_back();

    return 0;
}

int swimGrid_getMin(vector<int> *pHeap)
{
    return pHeap->at(0);
}
#endif

int swimInWater(vector<vector<int>>& grid)
{
#define MAX_N       (100)
    int N = grid.size(), max_h;
    location loc;
    vector<location> lut;
    vector<vector<int>> reached;
    vector<int> *grid_heap = swimGrid_createMinHeap();

#if 1
    printf("grid ***\n");
    for (int j = 0; j < grid.size(); j++) {
        for (int i = 0; i < grid.at(j).size(); i++) {
            printf("%2d, ", grid.at(j).at(i));
        }
        printf("\n");
    }
#endif

    reached.resize(N);
    for (int j = 0; j < reached.size(); j++) {
        reached.at(j).assign(N, 0);
    }

    lut.resize(N*N);

    for (int j = 0; j < grid.size(); j++) {
        for (int i = 0; i < grid.at(j).size(); i++) {
            lut[grid.at(j).at(i)].x = i;
            lut[grid.at(j).at(i)].y = j;
        }
    }

    loc.x = 0;
    loc.y = 0;
    max_h = grid.at(0).at(0);
    while (1) {
        int n = MAX_N, s = MAX_N, w = MAX_N, e = MAX_N, min_neighbor = MAX_N;

        //printf("@(%d,%d)\n", loc.y, loc.x);

        reached[loc.y][loc.x] = 2;

        if (grid.at(loc.y).at(loc.x) > max_h) {
            max_h = grid.at(loc.y).at(loc.x);
        }

        if ((loc.y == (N - 1)) && (loc.x == (N - 1))) {
            break;
        }

        if (loc.y > 0) {
            if (reached[loc.y - 1][loc.x] == 0) {
                reached[loc.y - 1][loc.x] = 1;
                n = grid.at(loc.y - 1).at(loc.x);
                swimGrid_pushMinHeap(grid_heap, n);
            }
        }
        if (loc.y < (N - 1)) {
            if (reached[loc.y + 1][loc.x] == 0) {
                reached[loc.y + 1][loc.x] = 1;
                s = grid.at(loc.y + 1).at(loc.x);
                swimGrid_pushMinHeap(grid_heap, s);
            }
        }
        if (loc.x > 0) {
            if (reached[loc.y][loc.x - 1] == 0) {
                reached[loc.y][loc.x - 1] = 1;
                w = grid.at(loc.y).at(loc.x - 1);
                swimGrid_pushMinHeap(grid_heap, w);
            }
        }
        if (loc.x < (N - 1)) {
            if (reached[loc.y][loc.x + 1] == 0) {
                reached[loc.y][loc.x + 1] = 1;
                e = grid.at(loc.y).at(loc.x + 1);
                swimGrid_pushMinHeap(grid_heap, e);
            }
        }

        if (n < min_neighbor) {
            min_neighbor = n;
        }
        if (s < min_neighbor) {
            min_neighbor = s;
        }
        if (e < min_neighbor) {
            min_neighbor = e;
        }
        if (w < min_neighbor) {
            min_neighbor = w;
        }

        if (grid_heap->size()) {
            loc.y = lut[swimGrid_getMin(grid_heap)].y;
            loc.x = lut[swimGrid_getMin(grid_heap)].x;
            swimGrid_popMinHeap(grid_heap);
        }
        else {
            printf("heap size 0\n");
            break;
        }
    }

#if 1
    printf("route ***\n");
    for (int j = 0; j < reached.size(); j++) {
        for (int i = 0; i < reached.at(j).size(); i++) {
            printf("%2d, ", reached.at(j).at(i));
        }
        printf("\n");
    }
    //printf("max:%d @(%d,%d)\n", max_h, lut[max_h].y, lut[max_h].x);
#endif

    swimGrid_destroyMinHeap(grid_heap);

    return max_h;
}

void main_swim_rising1()
{
    int _grid[] = {
        2, 1, 4,
        /*0, 6, 3,*/
        8, 7, 5
    };
    vector<int> *hp = swimGrid_createMinHeap();

    for (int i = 0; i < sizeof(_grid) / sizeof(_grid[0]); i++) {
        printf("roundt: %d\n", i);
        swimGrid_pushMinHeap(hp, _grid[i]);
    }

    printf("orig ***\n");
    for (int j = 0; j < sizeof(_grid) / sizeof(_grid[0]); j++) {
        printf("%2d, ", _grid[j]);
    }
    printf("\n");

    printf("heap ***\n");
    for (int j = 0; j < hp->size(); j++) {
        printf("%2d, ", hp->at(j));
    }
    printf("\n");

    printf("pop front: %d\n", swimGrid_getMin(hp));
    swimGrid_popMinHeap(hp);

    printf("heap ***\n");
    for (int j = 0; j < hp->size(); j++) {
        printf("%2d, ", hp->at(j));
    }
    printf("\n");

    swimGrid_destroyMinHeap(hp);
}
void main_swim_rising()
{
#if 1
    int dim = 5;
    int _grid[] = {
        0,  1,  2,  3,  4,
        24, 23, 22, 21,  5,
        12, 13, 14, 15, 16,
        11, 17, 18, 19, 20,
        10,  9,  8,  7,  6
    };
#elif
    int dim = 4;
    int _grid[] = {
        2, 1, 4, 15,
        5, 10, 13, 12,
        8, 7, 14, 11,
        6, 3, 9, 0
    };
#elif
    int dim = 3;
    int _grid[] = {
        2, 1, 4,
        0, 6, 3,
        8, 7, 5
    };
#endif
    vector<vector<int>> vin;

    vin.resize(dim);
    for (int j = 0; j < dim; j++) {
        vin.at(j).resize(dim);
        for (int i = 0; i < dim; i++) {
            vin[j][i] = _grid[j*dim + i];
        }
    }

    printf("time: %d\n", swimInWater(vin));
}
