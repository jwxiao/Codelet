#include "common.h"

using namespace std;

string reorganize_string(string S)
{
    string reorg_str;
    vector<int> count_table;
    int total = S.size(), max_ch;
    int first_ofst = 0, max_cnt = 0;

    count_table.assign(26, 0);

    for (int i = 0; i < total; i++) {
        count_table.at(S.at(i) - 'a')++;
    }

    for (int i = 0; i < total; i++) {
        int cnt = count_table.at(S.at(i) - 'a');

        if ((total - cnt) < (cnt - 1)) {
            return string("");
        }

        if (max_cnt < cnt) {
            max_ch = S.at(i);
            max_cnt = cnt;
        }
    }
    
    reorg_str.resize(total);
    for (int i = 0; i < reorg_str.size(); i++) {
        reorg_str[i] = 0;
    }

    if (max_cnt * 2 > total) {
        for (int i = 0; (i < max_cnt) && (i*2 < total); i++) {
            reorg_str[i*2] = max_ch;
        }
        first_ofst = 1;
        count_table.at(max_ch - 'a') = 0;
    }

    int ofst = first_ofst;
    for (int src = 0; src < count_table.size(); src++) {
        char ch;
        int ch_cnt, wr_cnt;

        if (count_table.at(src) == 0) {
            continue;
        }

        ch = 'a' + src;
        ch_cnt = count_table.at(src);

        wr_cnt = 0;
        while (wr_cnt < ch_cnt) {
            reorg_str[ofst] = ch;
            wr_cnt++;

            ofst += 2;

            if (ofst >= reorg_str.size()) {
                if (ofst & 1) {
                    break;
                }
                else {
                    ofst = 1;
                }
            }
        }

    }
    reorg_str += "\0";

    return reorg_str;
}

void main_reorganize_string(void)
{
    string s0 = "vcc";
    string s1 = "vvvlo";
    string s2 = "aaaf";
    string s3 = "aacdabcdfe";

    printf("%s => %s\n", s0.c_str(), reorganize_string(s0).c_str());
    printf("%s => %s\n", s1.c_str(), reorganize_string(s1).c_str());
    printf("%s => %s\n", s2.c_str(), reorganize_string(s2).c_str());
    printf("%s => %s\n", s3.c_str(), reorganize_string(s3).c_str());
}