#include "common.h"

using namespace std;

struct cell {
    int n, s, w, e;
    int is_set;

    cell() : n(-1), s(-1), w(-1), e(-1), is_set(1) {}
};

int order_of_largest_plus_sign(int N, vector<vector<int>>& mines)
{
    vector<vector<struct cell>> grid;
    int global_max;
    
    grid.resize(N);
    for (int i = 0; i < N; i++) {
        grid.at(i).resize(N);
    }

    // fill mines
    for (int pairs = 0; pairs < mines.size(); pairs++) {
        grid.at(mines.at(pairs).at(0)).at(mines.at(pairs).at(1)).is_set = 0;
    }

#if 0
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            printf("%d ", grid.at(y).at(x).is_set);
        }
        printf("\n");
    }
#endif

    // refine west to east, north to south, update w & n
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (grid.at(y).at(x).is_set == 0) {
                continue;
            }

            // check boundary
            if (x == 0) {
                grid.at(y).at(x).w = 0;
            }
            else {
                grid.at(y).at(x).w = grid.at(y).at(x - 1).w + 1;
            }
            if (y == 0) {
                grid.at(y).at(x).n = 0;
            }
            else {
                grid.at(y).at(x).n = grid.at(y - 1).at(x).n + 1;
            }


        }
    }

    // refine east to west, south to north, update e & s
    // determin order of each cell
    global_max = -1;
    for (int y = N - 1; y > -1; y--) {
        for (int x = N - 1; x > -1; x--) {
            int cell_order;

            if (grid.at(y).at(x).is_set == 0) {
                continue;
            }

            // check boundary
            if (x == N - 1) {
                grid.at(y).at(x).e = 0;
            }
            else {
                grid.at(y).at(x).e = grid.at(y).at(x + 1).e + 1;
            }
            if (y == N - 1) {
                grid.at(y).at(x).s = 0;
            }
            else {
                grid.at(y).at(x).s = grid.at(y + 1).at(x).s + 1;
            }

            // local min
            cell_order = (grid.at(y).at(x).n < grid.at(y).at(x).s) ? grid.at(y).at(x).n : grid.at(y).at(x).s;
            if (grid.at(y).at(x).e < cell_order)
                cell_order = grid.at(y).at(x).e;
            if (grid.at(y).at(x).w < cell_order)
                cell_order = grid.at(y).at(x).w;

            if (cell_order >= global_max) {
                global_max = cell_order;
                //printf("update order: %d y_x : %d_%d\n", global_max + 1, y, x);
            }
        }
    }

    return global_max + 1; // + 1 for center cell
}
