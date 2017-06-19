# algorithms
Algorithms

## Gist of FFT
### Crucial Feature
Discrete Fourier Transform (FFT) is defined as the discrete Z-transform sampled at each root of unity.

```
F(k) = sigma{i, N} f(i) * z^i
     = sigma{i, N} f(i) * expi(-2Pi/N*k)^i
     = sigma{i, N} f(i) * expi(-2Pi/N*(i * k))
     = sigma{i, N} f(i) * RU(N, i*k)
```
where `RU(N, i)` is Nth root of unity to i.

It has following feature, which is crutial to FFT algorithm.
```
F(k) = Fe(k) + RU(N, k) * Fo(k)
```
where
```
Fe(k) = sigma{i, N/2} f(2*i) * RU(N/2, i*k)
Fo(k) = sigma{i, N/2} f(2*i+1) * RU(N/2, i*k)
```
Note that `Fe(k)` and `Fo(k)` can be calculated by recursively applying `FFT` to even and odd elements of original signal `f(t)`.

### Proof
Replacing `RU(N/2)` in `Fe(k)` and `Fo(k)` using following rule:
```
RU(N/2, i) = RU(N, 2*i)
```
we'll get
```
Fe(k) = sigma{i, N/2} f(2*i) * RU(N, 2*i*k)
Fo(k) = sigma{i, N/2} f(2*i+1) * RU(N, 2*i*k)
RU(N, i) * Fo(k) = sigma{i, N/2} f(2*i+1) * RU(N, (2*i + 1)*k)
```

We now see that `Fe(k)` consists of even terms of `F(k)`, and `RU(N, k) * Fo(k)` consists of odd terms of `F(k)`. QED.

### A Detail
Originally `Fe(k)` and `Fo(k)` are both arrays of length `N/2`. In the last step we need to merge them into `F(k)`, whose length is `N`.

The solution is based on the fact that `Fe(k)` and `Fo(k)` are both `N/2` periodical. So, `Fe(k) = Fe(k - N/2)`. This also holds for `Fo(k)`.
We can calculate `F(k)` like this:
```cpp
int M = N / 2;
for (int k = 0; k < N; k++) {
  F[k] = Fe[k % M] + RU(k, N) * Fo[k % M];
}
```
