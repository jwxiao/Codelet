#include "common.h"

using namespace std;


bool isBipartite(vector<vector<int>>& graph)
{
    int nnode = graph.size();
    vector<int> color_map;

    color_map.assign(nnode, 0);

    for (int nc = 0; nc < nnode;) {
        int pen = 0;
        list<int> bfs;

        for (; pen < nnode; pen++) {
            if (color_map.at(pen) == 0) {
                break;
            }
        }
        if (pen == nnode) {
            break;
        }

        color_map.at(pen) = 1;
        bfs.push_back(pen);

        while (bfs.size()) {
            list<int>::iterator it = bfs.begin();
            int new_color = (color_map.at(*it) == 1) ? 2 : 1;

            for (int v = 0; v < graph.at(*it).size(); v++) {
                if (color_map.at(graph.at(*it).at(v)) == 0) {
                    color_map.at(graph.at(*it).at(v)) = new_color;
                    bfs.push_back(graph.at(*it).at(v));
                }
                else if (color_map.at(graph.at(*it).at(v)) != new_color) {
                    return false;
                }
            }
            bfs.pop_front();
        }
    }

    return true;
}

void main_isBipartite(void)
{
#define INIT_VEC(_ary, _idx)\
    for (int i = 0; i < sizeof(_ary)/sizeof(_ary[0]); i++) { \
        vin.at(_idx).push_back(_ary[i]); \
        } \

#if 1
    int e0[] = { 4, 1 };
    int e1[] = { 0, 2 };
    int e2[] = { 1, 3 };
    int e3[] = { 2, 4 };
    int e4[] = { 3, 0 };
#else
    int e0[] = { 1, 2, 3 };// {1, 3};
    int e1[] = {0, 2};
    int e2[] = { 0, 1, 3 };// {1, 3};
    int e3[] = { 0, 2 };
    int e4[] = { 0, 2 };
#endif

    vector<vector<int>> vin;

    vin.resize(5);

    INIT_VEC(e0, 0);
    INIT_VEC(e1, 1);
    INIT_VEC(e2, 2);
    INIT_VEC(e3, 3);
    INIT_VEC(e4, 4);

    printf("bipartite: %d\n", isBipartite(vin));
}
