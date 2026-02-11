#include "probability.h"
#include <cmath>

// Implementation of Equation (1) from the paper
double nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    double res = 1.0;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

double blocking_probability(int n, double p, int z) {
    if (z >= n) return 0.0;
    if (n <= 0) return 0.0;
    
    double sum = 0.0;
    // Sum from w = z+1 to n
    for (int w = z + 1; w <= n; ++w) {
        sum += nCr(n, w) * std::pow(p, w) * std::pow(1 - p, n - w);
    }
    return sum;
}