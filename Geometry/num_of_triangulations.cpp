#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
static const ld eps = 1e-6;
static const ll mod = 1e9 + 7;

class v {
public:
    ld x, y;

    v() = default;
    v(ld xx, ld yy): x(xx), y(yy) {}
    v(ld lx, ld ly, ld rx, ld ry) {
        x = rx - lx;
        y = ry - ly;
    }
    ld len() { return sqrt(x * x + y * y); }
    ld vec_prod(v a) { return x * a.y - y * a.x; }
    ld dot_prod(v a) { return x * a.x + y * a.y; }
};

ld vect_prod(ld xa, ld ya, ld xb, ld yb) {
    return xa * yb - xb * ya;
}

bool intersect(ld xl1, ld yl1, ld xr1, ld yr1, ld xl2, ld yl2, ld xr2, ld yr2) {
    ld v1 = vect_prod(xl1 - xr2, yl1 - yr2, xl2 - xr2, yl2 - yr2);
    ld v2 = vect_prod(xl2 - xr2, yl2 - yr2, xr1 - xr2, yr1 - yr2);
    ld v3 = vect_prod(xl2 - xl1, yl2 - yl1, xr1 - xl1, yr1 - yl1);
    ld v4 = vect_prod(xr1 - xl1, yr1 - yl1, xr2 - xl1, yr2 - yl1);

    ld v5 = vect_prod(xl1 - xr2, yl1 - yr2, xr1 - xr2, yr1 - yr2);
    ld v6 = vect_prod(xl1 - xl2, yl1 - yl2, xr1 - xl2, yr1 - yl2);

    if (v5 == v6) {
        return (v5 == 0 &&
            min(xr1, xl1) <= max(xr2, xl2) &&
            min(xr2, xl2) <= max(xr1, xl1) &&
            min(yr1, yl1) <= max(yr2, yl2) &&
            min(yr2, yl2) <= max(yr1, yl1));
    }

    return v1 * v2 >= 0 && v3 * v4 >= 0;
}

bool inside(v vertex, const vector<v>& p) {
    ld angle = 0;
    ll n = p.size();
    for (ll i = 0; i < n; ++i) {
        ll j = (i + 1) % n;

        v a(p[i].x - vertex.x, p[i].y - vertex.y);
        v b(p[j].x - vertex.x, p[j].y - vertex.y);

        ld vector_product = a.vec_prod(b);
        ld dot_product = a.dot_prod(b);

        ld local_sin = vector_product / (a.len() * b.len());
        if (local_sin < -1) local_sin = -1;
        if (local_sin > 1) local_sin = 1;
        ld local_angle = asin(local_sin);

        if (vector_product == 0 && dot_product <= 0) return false;

        if (dot_product < 0) local_angle = (local_angle > 0 ? 1 : -1) * numbers::pi - local_angle;

        angle += local_angle;
    }

    return abs(angle) > numbers::pi;
}

bool is_nice(ll i, ll j, const vector<v>& p) {
    ll sum_intersections = 0;
    ll n = p.size();
    v mid((p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2);
    if (!inside(mid, p) && (abs(j - i) > 1 && abs(j - i) < n - 1)) return false;
    for (ll k = 0; k < n; ++k)
        if (intersect(p[i].x, p[i].y, p[j].x, p[j].y, p[k].x, p[k].y, p[(k + 1) % n].x, p[(k + 1) % n].y))
            ++sum_intersections;
    return sum_intersections <= 4;
}


int main() {
    cout << setprecision(10);

    ll n;
    cin >> n;
    vector<v> p(n);

    v elem(0, 0);
    for (ll i = 0; i < n; ++i) {
        cin >> elem.x >> elem.y;
        p[i] = elem;
    }

    vector<vector<bool>> nice_segm(n, vector<bool>(n, true));
    for (ll i = 0; i < n; ++i)
        for (ll j = i + 2; j < n; ++j)
            nice_segm[i][j] = nice_segm[j][i] = is_nice(i, j, p);

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (ll i = 0; i < n - 1; ++i) dp[i][i + 1] = 1;

    for (ll i = 0; i < n - 2; ++i)
        if (nice_segm[i][i + 2]) dp[i][i + 2] = 1;

    for (ll delta = 3; delta < n; ++delta) {
        for (ll i = 0; i < n - delta; ++i) {
            ll j = i + delta;
            if (j >= n) break;
            if (!nice_segm[i][j]) continue;
            for (ll k = i + 1; k < j; ++k) {
                dp[i][j] += (dp[i][k] * dp[k][j]) % mod;
                dp[i][j] %= mod;
            }
        }
    }

    cout << dp[0][n - 1];
}
