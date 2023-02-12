// Find reverse polynomial modulo x^m.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll p = 7340033;
static const ll pow2 = ll(1) << 20;

ll bin_pow(ll num, ll pow) {
    if (pow == 0) return 1;
    if (pow == 1) return num % p;
    if (pow % 2 == 0) {
        ll lpow = bin_pow(num, pow / 2);
        return (lpow * lpow) % p;
    } else {
        return (num * bin_pow(num, pow - 1)) % p;
    }
}

void FFT(vector<ll>& f, bool inv) {
    ll deg = f.size();
    if (deg == 1) return;
    vector<ll> f0(deg / 2), f1(deg / 2);
    for (ll i = 0; i < deg / 2; ++i)
        f0[i] = f[2 * i], f1[i] = f[2 * i + 1];

    FFT(f0, inv), FFT(f1, inv);

    ll prim_power = pow2 / deg;
    ll prim_w = bin_pow(5, prim_power); // primitive root
    if (inv) prim_w = bin_pow(prim_w, p - 2);

    ll w_n = 1;
    ll half_w = bin_pow(prim_w, deg / 2);

    for (ll i = 0; i < deg / 2; ++i) {
        f[i] = (((f0[i] + ((w_n * f1[i]) % p)) % p) + p) % p;
        f[i + deg / 2] = (((f0[i] + half_w * ((w_n * f1[i]) % p)) % p) + p) % p;
        if (inv) {
            f[i] *= (p + 1) / 2;
            f[i] %= p;
            f[i + deg / 2] *= (p + 1) / 2;
            f[i + deg / 2] %= p;
        }
        w_n *= prim_w;
        w_n %= p;
    }
}

void mul(vector<ll> a, vector<ll> b, vector<ll>& c) {
    FFT(a, false), FFT(b, false);
    for (ll i = 0; i < c.size(); ++i) c[i] = ((a[i] * b[i] % p) + p) % p;
    FFT(c, true);
}

vector<ll> get_q(vector<ll>& f, ll x_deg) {
    if (x_deg == 1) return vector<ll>(1, bin_pow(f[0], p - 2));
    vector<ll>  q(get_q(f, x_deg / 2)),
                f0 = vector<ll>(f.begin(), f.begin() + x_deg / 2),
                f1 = vector<ll>(f.begin() + x_deg / 2, f.begin() + x_deg),
                r(x_deg, 0),
                f1_q(x_deg, 0),
                t(x_deg, 0);

    q.resize(x_deg, 0), f0.resize(x_deg, 0), f1.resize(x_deg, 0);
    mul(f0, q, r);

    r = vector<ll>(r.begin() + x_deg / 2, r.end());
    r.resize(x_deg, 0);

    mul(f1, q, f1_q);

    for (ll i = 0; i < x_deg; ++i)
        f1_q[i] = (((-r[i] - f1_q[i]) % p) + p) % p;

    for (ll i = x_deg / 2; i < x_deg; ++i) f1_q[i] = 0;

    mul(f1_q, q, t);

    vector<ll> t_end(x_deg, 0);
    for (ll i = x_deg / 2; i < x_deg; ++i)
        t_end[i] = t[i - x_deg / 2];

    for (ll i = 0; i < x_deg; ++i)
        t_end[i] = (t_end[i] + q[i]) % p;

    q = t_end;

    return q;
}

signed main() {
    ll m, n;
    cin >> m >> n;

    ll x_deg = max(n + 1, m + 1);
    while (x_deg & (x_deg - 1)) ++x_deg;

    vector<ll> f(x_deg, 0);
    for (ll i = 0; i <= n; ++i) cin >> f[i];

    if (f[0] == 0) {
        cout << "The ears of a dead donkey\n";
        return 0;
    }

    vector<ll> q = get_q(f, x_deg);

    for (ll i = 0; i < m; ++i) cout << ((q[i] % p) + p) % p << ' ';
}
