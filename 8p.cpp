#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = 1e9;

void optimalBST(const vector<int>& keys, const vector<float>& p) {
    int n = keys.size();
    vector<vector<float>> cost(n + 2, vector<float>(n + 1, 0));
    vector<vector<int>> root(n + 2, vector<int>(n + 1, 0));
    vector<float> sumP(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        sumP[i] = sumP[i - 1] + p[i - 1];
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            cost[i][j] = INF;
            float sum = sumP[j] - sumP[i - 1];

            for (int r = i; r <= j; ++r) {
                float c = 0;
                if (r > i) c += cost[i][r - 1];
                if (r < j) c += cost[r + 1][j];
                c += sum;

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }


    cout << "Minimum search cost: " << cost[1][n] << endl;
}

int main() {
    vector<int> keys = {10, 20, 30, 40};      
    vector<float> prob = {0.1, 0.2, 0.4, 0.3};  

    optimalBST(keys, prob);

    return 0;
}
