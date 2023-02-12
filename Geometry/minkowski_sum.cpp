#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll inf = numeric_limits<ll>::max();
static const ld eps = 1e-12;

class v {
public:
    ll x, y;

    v() = default;
    v(ll xx, ll yy): x(xx), y(yy) {}
    ll len() { return sqrt(x * x + y * y); }
    ll vec_prod(v b) { return x * b.y - y * b.x; }
    ll dot_prod(v b) { return x * b.x + y * b.y; }
};

bool cmp(v a, v b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

vector<v> mink_sum(const vector<v>& p1, const vector<v>& p2) {
    ll n1 = p1.size(), n2 = p2.size();

    v min_vertex1 = p1[0];
    ll min_v_index1 = 0;
    for (ll i = 0; i < n1; ++i) {
        if (cmp(p1[i], min_vertex1)) {
            min_vertex1 = p1[i];
            min_v_index1 = i;
        }
    }

    v min_vertex2 = p2[0];
    ll min_v_index2 = 0;
    for (ll i = 0; i < n2; ++i) {
        if (cmp(p2[i], min_vertex2)) {
            min_vertex2 = p2[i];
            min_v_index2 = i;
        }
    }

    vector<v> sum;
    sum.push_back(v(min_vertex1.x + min_vertex2.x, min_vertex1.y + min_vertex2.y));
    ll i1 = 1, i2 = 1;

    while (i1 <= n1 || i2 <= n2) {
        v vect1(p1[(min_v_index1 + i1) % n1].x - p1[(min_v_index1 + i1 - 1) % n1].x,
                p1[(min_v_index1 + i1) % n1].y - p1[(min_v_index1 + i1 - 1) % n1].y);
        v vect2(p2[(min_v_index2 + i2) % n2].x - p2[(min_v_index2 + i2 - 1) % n2].x,
                p2[(min_v_index2 + i2) % n2].y - p2[(min_v_index2 + i2 - 1) % n2].y);
        if (vect1.vec_prod(vect2) > 0) {
            sum.push_back(v(sum.back().x + vect1.x, sum.back().y + vect1.y));
            ++i1;
        } else if (vect1.vec_prod(vect2) < 0) {
            sum.push_back(v(sum.back().x + vect2.x, sum.back().y + vect2.y));
            ++i2;
        } else {
            sum.push_back(v(sum.back().x + vect1.x + vect2.x, sum.back().y + vect1.y + vect2.y));
            ++i1, ++i2;
        }
    }

    while ((sum.back().x - sum[0].x) * (sum[1].y - sum.back().y) == (sum[1].x - sum.back().x) * (sum.back().y - sum[0].y))
        sum.pop_back();

    return sum;
}

bool valid(v point, const vector<v>& p, ll vertex_num) {
    if (vertex_num >= p.size()) return true;
    if (vertex_num == 0) return false;
    v to_point(point.x - p[0].x, point.y - p[0].y);
    v to_vertex(p[vertex_num].x - p[0].x, p[vertex_num].y - p[0].y);
    return to_point.vec_prod(to_vertex) >= 0;
}

bool inside(v point, const vector<v>& p) {
    ll n = p.size();

    v first_segm(p[1].x - p[0].x, p[1].y - p[0].y);
    v to_point(point.x - p[0].x, point.y - p[0].y);
    v last_segm(p[n - 1].x - p[0].x, p[n - 1].y - p[0].y);

    if (to_point.vec_prod(first_segm) > 0 || last_segm.vec_prod(to_point) > 0) return false;
    if (to_point.vec_prod(first_segm) == 0 && v(point.x - p[1].x, point.y - p[1].y).vec_prod(v(p[2].x - p[1].x, p[2].y - p[1].y)) > 0) return false;

    ll first_tr = -1;
    for (ll delta = n + 1; delta >= 1; delta /= 2)
        while (!valid(point, p, first_tr + delta))
            first_tr += delta;

    v last_side(p[first_tr + 1].x - p[first_tr].x, p[first_tr + 1].y - p[first_tr].y);
    v to_v_from1(point.x - p[first_tr].x, point.y - p[first_tr].y);
    v to_v_from2(point.x - p[first_tr + 1].x, point.y - p[first_tr + 1].y);

    return last_side.vec_prod(to_v_from1) >= 0;
}

int main() {
    cout << setprecision(10);

    ll n1, n2, n3;
    cin >> n1;
    vector<v> p1(n1);

    v elem;
    for (ll i = 0; i < n1; ++i) {
        cin >> elem.x >> elem.y;
        p1[i] = elem;
    }

    cin >> n2;
    vector<v> p2(n2);

    for (ll i = 0; i < n2; ++i) {
        cin >> elem.x >> elem.y;
        p2[i] = elem;
    }

    cin >> n3;
    vector<v> p3(n3);

    for (ll i = 0; i < n3; ++i) {
        cin >> elem.x >> elem.y;
        p3[i] = elem;
    }

    vector<v> p1p2 = mink_sum(p1, p2);
    vector<v> p1p2p3 = mink_sum(p1p2, p3);

    ll q;
    cin >> q;

    while (q--) {
        v center;
        cin >> center.x >> center.y;
        center.x *= 3;
        center.y *= 3;

        if (inside(center, p1p2p3)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}
