#include <complex>
#include <iostream>
#include <numbers>
#include <vector>

static const double kPi = 3.14159265358979323846;

void fft(std::vector<std::complex<double>>& p, bool inv) {
  int deg = int(p.size());
  if (deg == 1) {
    return;
  }

  std::vector<std::complex<double>> p0(deg / 2);
  std::vector<std::complex<double>> p1(deg / 2);
  for (int i = 0; i < deg / 2; ++i) {
    p0[i] = p[2 * i], p1[i] = p[2 * i + 1];
  }

  fft(p0, inv), fft(p1, inv);

  double angle = (2 * kPi) / double(deg);
  if (inv) {
    angle *= -1;
  }
  std::complex<double> prim_w = std::polar(double(1), angle);
  std::complex<double> w_n = 1;

  for (int i = 0; i < deg / 2; ++i, w_n *= prim_w) {
    p[i] = p0[i] + w_n * p1[i];
    p[i + deg / 2] = p0[i] - w_n * p1[i];
  }
}

int main() {
  int n;
  int m;
  std::cin >> n;
  std::vector<std::complex<double>> a(n + 1);
  for (int i = n; i >= 0; --i) {
    std::cin >> a[i];
  }
  std::cin >> m;
  std::vector<std::complex<double>> b(m + 1);
  for (int i = m; i >= 0; --i) {
    std::cin >> b[i];
  }

  int k = n + m;
  while ((k & (k + 1)) != 0) {
    ++k;
  }

  a.resize(k + 1, 0);
  b.resize(k + 1, 0);
  fft(a, false), fft(b, false);

  std::vector<std::complex<double>> c(k + 1, 0);
  for (int i = 0; i <= k; ++i) {
    c[i] = a[i] * b[i];
  }

  fft(c, true);
  std::cout << n + m << ' ';
  for (int i = n + m; i >= 0; --i) {
    std::cout << lround((c[i] / std::complex<double>(k + 1)).real()) << ' ';
  }
}
