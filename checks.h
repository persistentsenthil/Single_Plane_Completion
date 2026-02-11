#pragma once
#include <vector>

bool snb_condition(int nsnb_s, int v_s, int m_s);
int compute_sigma(const std::vector<int>& nsnb, int up_to_step);
double P_s(int n, double p, const std::vector<int>& nsnb, int step, std::vector<double> prev_Ps);
bool is_feasible(int n, int k, const std::vector<int>& m, const std::vector<int>& v,
                 const std::vector<int>& nsnb, double p, double epsilon, int N, int a, int S);