#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

static const int kOuputPrecision = 10, kPrebackNum = 3;

class Point {
public:
  int x, y;

  Point() = default;
  Point(int xx, int yy) : x(xx), y(yy) {}
  Point(int lx, int ly, int rx, int ry) {
    x = rx - lx;
    y = ry - ly;
  }
  int len() const {
    return sqrt(x * x + y * y);
  }
  int vecProd(Point a) const {
    return x * a.y - y * a.x;
  }
  int dotProd(Point a) const {
    return x * a.x + y * a.y;
  }
};

Point base;

bool cmpAng(Point a, Point b) {
  Point an(a.x - base.x, a.y - base.y);
  Point bn(b.x - base.x, b.y - base.y);
  int vp = an.vecProd(bn);
  return vp > 0 ||
         (vp == 0 && an.x * an.x + an.y * an.y < bn.x * bn.x + bn.y * bn.y);
}

std::vector<Point> buildHull(int n, const std::vector<Point>& nice_polygon) {
  std::vector<Point> hull;
  hull.push_back(base);

  for (int i = 0; i < n - 1; ++i) {
    hull.push_back(nice_polygon[i]);

    int vp = 1;
    while (vp >= 0 && int(hull.size()) >= kPrebackNum) {
      Point vertex = hull[hull.size() - 1];
      Point back = hull[hull.size() - 2];
      Point preback = hull[hull.size() - kPrebackNum];

      Point first_segm(back.x, back.y, preback.x, preback.y);
      Point second_segm(back.x, back.y, vertex.x, vertex.y);

      vp = first_segm.vecProd(second_segm);

      if (vp >= 0) {
        hull.pop_back();
        hull.pop_back();
        hull.push_back(vertex);
      }
    }
  }

  return hull;
}

std::vector<Point> normalizePolygon(int n, std::vector<Point> polygon) {
  base = polygon[0];
  int index = 0;
  for (int i = 0; i < n; ++i) {
    if (base.y > polygon[i].y ||
        (polygon[i].y == base.y && polygon[i].x < base.x)) {
      base = polygon[i];
      index = i;
    }
  }

  std::vector<Point> nice_polygon(n - 1);
  for (int i = 0, j = 0; j < n; ++i, ++j) {
    if (i == index) {
      if (j + 1 < n) {
        ++j;
      } else {
        break;
      }
    }
    nice_polygon[i] = polygon[j];
  }

  std::sort(nice_polygon.begin(), nice_polygon.end(), &cmpAng);

  return nice_polygon;
}

int main() {
  std::cout << std::setprecision(kOuputPrecision);

  int n;
  std::cin >> n;

  std::vector<Point> polygon(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> polygon[i].x >> polygon[i].y;
  }

  polygon = normalizePolygon(n, polygon);

  std::vector<Point> hull = buildHull(n, polygon);
  std::cout << hull.size() << '\n';
  for (auto point : hull) {
    std::cout << point.x << ' ' << point.y << '\n';
  }
}
