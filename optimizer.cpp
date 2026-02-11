#include "optimizer.h"
#include "checks.h"
#include <iostream>

TFResult optimize_tf_clos(int N, int a, double p, double epsilon, int S) {
    TFResult best;
    best.n = 0;
    best.k = 0;
    best.capacity = 0;

    // For old compiler + speed: limit to S=1 and reasonable loops
    if (S != 1) {
        std::cout << "Warning: only S=1 supported on this compiler\n";
        return best;
    }

    for (int m0 = 1; m0 <= a; ++m0) {
        for (int v0 = 1; v0 <= N; ++v0) {
            int max_nsnb0 = N / v0;
            for (int nsnb0 = 1; nsnb0 <= max_nsnb0; ++nsnb0) {
                std::vector<int> m(1, m0);
                std::vector<int> v(1, v0);
                std::vector<int> nsnb(1, nsnb0);

                int sum_vm = v0 * m0;
                int denom = N - sum_vm;
                if (denom <= 0) continue;

                int max_k = a - m0;
                for (int k = 1; k <= max_k; ++k) {
                    for (int n_try = 1; n_try <= denom; ++n_try) {
                        if (is_feasible(n_try, k, m, v, nsnb, p, epsilon, N, a, S)) {
                            long long new_cap = (long long)n_try * k;
                            if (new_cap > best.capacity) {
                                best.n = n_try;
                                best.k = k;
                                best.m = m;
                                best.v = v;
                                best.nsnb = nsnb;
                                best.capacity = new_cap;
                                std::cout << "Better: nk=" << new_cap << "\n";
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
}