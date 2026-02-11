#include "simulator.h"
#include <cstdlib>  // srand, rand, RAND_MAX
#include <ctime>    // time
#include <iostream>

TFSimulator::TFSimulator(int S, const std::vector<int>& nsnb)
    : S_(S), nsnb_(nsnb), connections_(S, 0) {}

void TFSimulator::reset() {
    for (int i = 0; i < S_; ++i) connections_[i] = 0;
}

bool TFSimulator::admit_request() {
    for (int step = 0; step < S_; ++step) {
        if (connections_[step] < nsnb_[step]) {
            connections_[step]++;
            return true;
        }
    }
    return false;
}

// Simulates the binomial distribution B(n, p) correctly
int simulate_active_requests(int n, double p) {
    int active_count = 0;
    // Iterate through 'n' terminals and check if each one is active with probability 'p'
    for (int i = 0; i < n; ++i) {
        if ((double)rand() / RAND_MAX < p) {
            active_count++;
        }
    }
    return active_count;
}

// Estimates blocking probability via simulation
double estimate_blocking(int n, double p, int S, const std::vector<int>& nsnb, int trials) {
    // Note: Seeding rand() once at the start of main is usually better practice, 
    // but we use a fixed seed here as before for reproducibility within this function scope.
    srand(42);
    TFSimulator sim(S, nsnb);
    long long total_req = 0, total_block = 0;
    
    for (int t = 0; t < trials; ++t) {
        sim.reset();
        // Use the corrected function to simulate the number of active requests 'W'
        int W = simulate_active_requests(n, p); 
        
        int blocked = 0;
        for (int i = 0; i < W; ++i) {
            if (!sim.admit_request()) {
                ++blocked;
            }
        }
        total_block += blocked;
        total_req += W;
    }
    
    // Avoid division by zero if total requests happen to be 0
    return total_req > 0 ? (double)total_block / total_req : 0.0;
}
