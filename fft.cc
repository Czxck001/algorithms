// Fast Fourier Transform (FFT)
// Author: Czxck001 (github.com/Czxck001)

#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

using namespace std::complex_literals;
const double PI = 3.1415926535897;

template<typename T>
using Cvec = std::vector<std::complex<T>>;

template<typename T>
inline std::complex<T> cru(const int k, const int N) {
  // kth complex root of unity e ^ (i2Pi * (k / N))
  auto Tk = static_cast<T>(k);
  auto TN = static_cast<T>(N);
  return std::exp((2 * PI * 1i * Tk) / TN);
}

template<typename T>
Cvec<T> fft(const Cvec<T> &x) {
  // X[k] = E[k] + g^k * O[k]

  auto N = x.size();
  auto M = N / 2;

  if (N == 1) {
    return x;
  }

  // subdivide the signal into even part and odd part
  auto e = Cvec<T>();
  auto o = Cvec<T>();
  for (auto i = 0; i < N; i++) {
    if (i % 2 == 0) {
      e.push_back(x[i]);
    } else {
      o.push_back(x[i]);
    }
  }

  // recursively calculate sub-spectrums
  auto E = fft(e);
  auto O = fft(o);

  // calculate the spectrum from the sub-spectrums
  auto X = Cvec<T>();
  for (auto k = 0; k < N; k++) {
    X.push_back(E[k % M] + cru<T>(k, N) * O[k % M]);
  }

  return X;
}

template<typename T>
Cvec<T> ifft(const Cvec<T> &X) {
  auto x0 = fft(X);
  auto x = x0;
  auto N = static_cast<T>(x.size());

  for (auto i = 1; i < N; i++) {
    x[i] = 1.0 / N * x0[N - i];
  }
  return x;
}



int main() {
  auto x = Cvec<double>{0, 0, 0, 0, 1, 1, 1, 1};
  for (auto xi: x) {
    std::cout << xi << std::endl;
  }
  std::cout << std::endl;

  auto X = fft(x);
  for (auto Xk: X) {
    std::cout << Xk << std::endl;
  }
  std::cout << std::endl;

  auto y = ifft(X);
  for (auto yi: y) {
    std::cout << yi << std::endl;
  }
}
