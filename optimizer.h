#pragma once
#include <vector>

struct TFResult {
    int n;
    int k;
    std::vector<int> m;
    std::vector<int> v;
    std::vector<int> nsnb;
    long long capacity;
};

TFResult optimize_tf_clos(int N, int a, double p, double epsilon, int S);