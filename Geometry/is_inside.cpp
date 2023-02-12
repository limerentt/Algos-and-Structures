#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

static const int kOuputPrecision = 10;
static const double kEps = 1e-4;
static const double kPi = 3.14159265358979323846;

class V {
public:
  double x, y;

  V() = default;
  V(double xx, double yy) : x(xx), y(yy) {}
  V(double lx, double ly, double rx, double ry) {
    x = rx - lx;
    y = ry - ly;
  }
  double len() const {
    return std::sqrt(x * x + y * y);
  }
  double vecProd(V a) const {
    return x * a.y - y * a.x;
  }
  double dotProd(V a) const {
    return x * a.x + y * a.y;
  }
};

void where(V vertex, const std::vector<V>& p) {
  double angle = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;

    V a(p[i].x - vertex.x, p[i].y - vertex.y);
    V b(p[j].x - vertex.x, p[j].y - vertex.y);

    double vi_len = a.len();
    double vj_len = b.len();
    double vector_product = a.vecProd(b);

    double local_sin = vector_product / (vi_len * vj_len);
    double local_angle = asin(local_sin);
    double dot_product = a.dotProd(b);

    if (vector_product == 0 && dot_product <= 0) {
      std::cout << "BOUNDARY" << '\n';
      return;
    }

    if (dot_product < 0) {
      local_angle = (local_angle > 0 ? 1 : -1) * kPi - local_angle;
    }

    angle += local_angle;
  }

  if (std::abs(angle) <= kEps) {
    std::cout << "OUTSIDE" << '\n';
  } else {
    std::cout << "INSIDE" << '\n';
  }
}

int main() {
  std::cout << std::setprecision(kOuputPrecision);

  int n;
  int m;
  std::cin >> n >> m;
  std::vector<V> p(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> p[i].x;
    std::cin >> p[i].y;
  }

  V vertex;
  while ((m--) != 0) {
    std::cin >> vertex.x >> vertex.y;
    where(vertex, p);
  }
}
