#include <iostream>
#include <vector>

using ll = long long;

ll find_length_of_greatest_common_subsequence(const std::vector<ll>& first_sequence, const std::vector<ll>& second_sequence) {
    size_t N = first_sequence.size(), M = second_sequence.size();
    /*dp[i][j] равно наибольшей длине общей подпоследовательности считая первые i символов первой и
       первые j символов второй последовательностей*/
    std::vector<std::vector<ll>> dp(N + 1, std::vector<ll>(M + 1, 0));
    for (ll i = 0; i <= N; ++i) {
        dp[i][0] = 0;
    }
    for (ll i = 0; i <= M; ++i) {
        dp[0][i] = 0;
    }
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < M; ++j) {
            if (first_sequence[i] == second_sequence[j])
                dp[i + 1][j + 1] = dp[i][j] + 1;
            else
                dp[i + 1][j + 1] = std::max(dp[i + 1][j], dp[i][j + 1]);
        }
    }
    return dp[N][M];
}

int main() {
    ll N, M;
    std::cin >> N;
    std::vector<ll> first_sequence(N);
    for (ll i = 0; i < N; ++i) {
        std::cin >> first_sequence[i];
    }
    std::cin >> M;
    std::vector<ll> second_sequence(M);
    for (ll i = 0; i < M; ++i) {
        std::cin >> second_sequence[i];
    }

    std::cout << find_length_of_greatest_common_subsequence(first_sequence, second_sequence);
}
