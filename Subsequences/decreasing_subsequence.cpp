#include <iostream>
#include <vector>
#include <climits>

using ll = long long;
const ll inf = LLONG_MAX;

std::vector<ll> find_longest_not_rising_subsequence(std::vector<ll>& input_array) {
    std::reverse(input_array.begin(), input_array.end());

    size_t size = input_array.size();
    //*dp[i] is the smallest number which is the end of not rising subsequence with length i*//
    std::vector<ll> dp(size, inf), subsequence(size, -1);
    ll index;
    for (ll i = 0; i < size; ++i) {
        index = std::upper_bound(dp.begin(), dp.end(), input_array[i]) - dp.begin();
        dp[index] = input_array[i];
        subsequence[index] = i;
        ++index;
        while (index < subsequence.size() && subsequence[index] != -1) {
            dp[index] = inf;
            subsequence[index] = -1;
            ++index;
        }
    }

    size_t slide = size - 1;
    while (subsequence[slide] == -1) {
        --slide;
    }
    std::vector<ll> needed_subsequence_indices;
    while (slide >= 0) {
        needed_subsequence_indices.push_back(size - subsequence[slide]);
        --slide;
    }
    return needed_subsequence_indices;
}

int main() {
    ll N;
    std::cin >> N;
    std::vector<ll> input_array(N);
    for (ll i = 0; i < N; ++i) {
        std::cin >> input_array[i];
    }

    std::vector<ll> subsequence_indices = find_longest_not_rising_subsequence(input_array);
    std::cout << subsequence_indices.size() << '\n';
    for (auto needed_index: subsequence_indices) {
        std::cout << needed_index << " ";
    }
}
