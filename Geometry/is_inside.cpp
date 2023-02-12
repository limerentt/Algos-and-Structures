#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
static const ld eps = 1e-4;


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

void where(v vertex, const vector<v>& p) {
    ld angle = 0;
    ll n = p.size();
    for (ll i = 0; i < n; ++i) {
        ll j = (i + 1) % n;

        v a(p[i].x - vertex.x, p[i].y - vertex.y);
        v b(p[j].x - vertex.x, p[j].y - vertex.y);

        ld vi_len = a.len();
        ld vj_len = b.len();
        ld vector_product = a.vec_prod(b);

        ld local_sin = vector_product / (vi_len * vj_len);

        ld local_angle = asin(local_sin);

        ld dot_product = a.dot_prod(b);

        if (vector_product == 0 && dot_product <= 0) {
            cout << "BOUNDARY" << '\n';
            return;
        }

        if (dot_product < 0)
            local_angle = (local_angle > 0 ? 1 : -1) * numbers::pi - local_angle;

        angle += local_angle;
    }

    if (abs(angle) <= eps) cout << "OUTSIDE" << '\n';
    else cout << "INSIDE" << '\n';
}

int main() {
    cout << setprecision(10);
    ll n, m;
    cin >> n >> m;
    vector<v> p(n);

    for (ll i = 0; i < n; ++i) {
        cin >> p[i].x;
        cin >> p[i].y;
    }

    v vertex;
    while (m--) {
        cin >> vertex.x >> vertex.y;
        where(vertex, p);
    }
}
