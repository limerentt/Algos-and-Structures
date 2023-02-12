#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
static const ld eps = 1e-12;


class v {
public:
    ll x, y;

    v() = default;
    v(ll xx, ll yy): x(xx), y(yy) {}
    v(ll lx, ll ly, ll rx, ll ry) {
        x = rx - lx;
        y = ry - ly;
    }
    ll len() { return sqrt(x * x + y * y); }
    ll vec_prod(v a) { return x * a.y - y * a.x; }
    ll dot_prod(v a) { return x * a.x + y * a.y; }
};

v base;

bool cmp_ang(v a, v b) {
    v an(a.x - base.x, a.y - base.y);
    v bn(b.x - base.x, b.y - base.y);
    ll vp = an.vec_prod(bn);
    return vp > 0 || vp == 0 && an.x * an.x + an.y * an.y < bn.x * bn.x + bn.y * bn.y;
}

int main() {
    cout << setprecision(10);

    ll n;
    cin >> n;
    vector<v> p(n);

    for (ll i = 0; i < n; ++i) {
        pair<ll, ll> elem;
        cin >> elem.first >> elem.second;
        v to_make(elem.first, elem.second);
        p[i] = to_make;
    }

    base = p[0];
    ll index = 0;
    for (ll i = 0; i < n; ++i) {
        if (base.y > p[i].y || p[i].y == base.y && p[i].x < base.x) {
            base = p[i];
            index = i;
        }
    }


    vector<v> pp(n - 1);
    for (ll i = 0, j = 0; j < n; ++i, ++j) {
        if (i == index) {
            if (j + 1 < n) ++j;
            else break;
        }
        pp[i] = p[j];
    }

    sort(pp.begin(), pp.end(), &cmp_ang);

    vector<v> hull;
    hull.push_back(base);

    for (ll i = 0; i < n - 1; ++i) {
        hull.push_back(pp[i]);

        ll vp = 1;
        while (vp >= 0 && hull.size() >= 3) {
            v vertex = hull[hull.size() - 1];
            v back = hull[hull.size() - 2];
            v preback = hull[hull.size() - 3];

            v first_segm(back.x, back.y, preback.x, preback.y);
            v second_segm(back.x, back.y, vertex.x, vertex.y);

            vp = first_segm.vec_prod(second_segm);

            if (vp >= 0) {
                hull.pop_back();
                hull.pop_back();
                hull.push_back(vertex);
            }
        }
    }

    cout << hull.size() << '\n';

    for (auto point: hull) cout << point.x << ' ' << point.y << '\n';
}
