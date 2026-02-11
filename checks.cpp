#include "checks.h"
#include "probability.h"
#include <algorithm>
#include <numeric>

bool snb_condition(int nsnb_s, int v_s, int m_s) {
    if (m_s == 0) return true;
    if (v_s == 0) return false;
    int min_m = 2 * ((nsnb_s - 1) / v_s) + 1;
    return m_s >= min_m;
}

int compute_sigma(const std::vector<int>& nsnb, int up_to_step) {
    int sum = 0;
    for (int i = 0; i < up_to_step; ++i) sum += nsnb[i];
    return sum;
}

double P_s(int n, double p, const std::vector<int>& nsnb, int step, std::vector<double> prev_Ps) {
    if (step < 1) return 1.0;
    int sigma_prev = compute_sigma(nsnb, step - 1);
    double prod = 1.0;
    for (int i = 0; i < (int)prev_Ps.size(); ++i) prod *= prev_Ps[i];
    int capacity = nsnb[step - 1];
    return blocking_probability(n - sigma_prev, p * prod, capacity);
}
bool is_feasible(int n, int k, const std::vector<int>& m, const std::vector<int>& v, 
    const std::vector<int>& nsnb, double p, double epsilon, int N, int a, int S) {
int total_vm = 0;
int total_m = 0;

for (int s = 0; s < S; ++s) {
total_vm += v[s] * m[s];
total_m += m[s];
// Port constraint (Eq 12): v_s * k <= N
if (v[s] * k > N) return false;
// SNB condition (Eq 3)
if (!snb_condition(nsnb[s], v[s], m[s])) return false;
}

// Hardware limits (Eq 11 & 13)
if (n + total_vm > N) return false;
if (k + total_m > a) return false;

// Admissible Blocking Probability (Eq 7 & 8)
std::vector<double> eps_list;
for (int s = 1; s <= S; ++s) {
double current_P = P_s(n, p, nsnb, s, eps_list);
if (s == S && current_P > epsilon) return false;
eps_list.push_back(current_P);
}

return true;
}