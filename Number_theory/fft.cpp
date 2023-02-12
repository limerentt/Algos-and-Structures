#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void FFT(vector<complex<double>>& p, bool inv) {
    ll deg = p.size();
    if (deg == 1) return;
    vector<complex<double>> p0(deg / 2), p1(deg / 2);
    for (ll i = 0; i < deg / 2; ++i)
        p0[i] = p[2 * i], p1[i] = p[2 * i + 1];

    FFT(p0, inv), FFT(p1, inv);

    double angle = (2.0 * numbers::pi) / double(deg);
    if (inv) angle *= -1;
    complex<double> prim_w = polar(double(1), angle);
    complex<double> w_n = 1;

    for (ll i = 0; i < deg / 2; ++i, w_n *= prim_w) {
        p[i] = p0[i] + w_n * p1[i];
        p[i + deg / 2] = p0[i] - w_n * p1[i];
    }
}

signed main() {
    ll n, m;
    cin >> n;
    vector<complex<double>> a(n + 1);
    for (ll i = n; i >= 0; --i) cin >> a[i];
    cin >> m;
    vector<complex<double>> b(m + 1);
    for (ll i = m; i >= 0; --i) cin >> b[i];

    ll k = n + m;
    while (k & (k + 1)) ++k; //k + 1 is a pow of 2

    a.resize(k + 1, 0);
    b.resize(k + 1, 0);

    FFT(a, false), FFT(b, false);

    vector<complex<double>> c(k + 1, 0);
    for (ll i = 0; i <= k; ++i) c[i] = a[i] * b[i];

    FFT(c, true);
    cout << n + m << ' ';
    for (ll i = n + m; i >= 0; --i) cout << lround((c[i] / complex<double>(k + 1)).real()) << ' ';
}
