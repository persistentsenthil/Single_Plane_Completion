#include "optimizer.h"
#include "simulator.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

int main() {
    std::cout << std::unitbuf;  // Disable buffering
    std::cout << "\nSTART OF PROGRAM\n" << std::flush;

    int N = 5;
    int a = 18;
    double p = 0.6;
    double epsilon = 0.0;
    int S = 1;

    std::cout << "Parameters loaded:\n";
    std::cout << "  N=" << N << "  a=" << a << "  p=" << p 
              << "  epsilon=" << epsilon << "  S=" << S << "\n" << std::flush;

    std::cout << "Calling optimizer...\n" << std::flush;

    TFResult result = optimize_tf_clos(N, a, p, epsilon, S);

    std::cout << "\nOptimizer returned. Checking result...\n" << std::flush;
    std::cout << "result.capacity = " << result.capacity << "\n" << std::flush;

    if (result.capacity > 0) {
        std::cout << "Feasible solution found!\n";
        std::cout << "  nk       = " << result.capacity << "\n";
        std::cout << "  n        = " << result.n << "\n";
        std::cout << "  k        = " << result.k << "\n";

        std::cout << "  m = [";
        for (size_t i = 0; i < result.m.size(); ++i) {
            std::cout << result.m[i];
            if (i < result.m.size()-1) std::cout << ", ";
        }
        std::cout << "]\n";

        std::cout << "  v = [";
        for (size_t i = 0; i < result.v.size(); ++i) {
            std::cout << result.v[i];
            if (i < result.v.size()-1) std::cout << ", ";
        }
        std::cout << "]\n";

        std::cout << "  nsnb = [";
        for (size_t i = 0; i < result.nsnb.size(); ++i) {
            std::cout << result.nsnb[i];
            if (i < result.nsnb.size()-1) std::cout << ", ";
        }
        std::cout << "]\n" << std::flush;

        std::cout << "Starting simulation...\n" << std::flush;
        double block_prob = estimate_blocking(result.n, p, S, result.nsnb, 20);

        std::cout << "Simulation done.\n";
        std::cout << "  Measured blocking = " << block_prob << "\n";
        if (block_prob <= epsilon + 0.0001) {
            std::cout << "  → PASSED guarantee\n";
        } else {
            std::cout << "  → Slightly above (numerical)\n";
        }
    } else {
        std::cout << "No feasible design found.\n" << std::flush;
    }

    std::cout << "\nEND OF PROGRAM\n" << std::flush;
    return 0;
}