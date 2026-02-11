#pragma once
#include <vector>

class TFSimulator {
public:
    TFSimulator(int S, const std::vector<int>& nsnb);
    void reset();
    bool admit_request();
private:
    int S_;
    std::vector<int> nsnb_;
    std::vector<int> connections_;
};

double estimate_blocking(int na, double p, int S, const std::vector<int>& nsnb, int trials);