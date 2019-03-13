# algorithms
Cool algorithms + implementations.

## FFT in a nutshell
### Crucial Feature of DFT
[Discrete Fourier Transform (DFT)](https://en.wikipedia.org/wiki/Discrete_Fourier_transform) is defined as the discrete Z-transform sampled at each root of unity.

<img alt="$ F(k) = \sum_{n=0}^N f(n) z^n =  \sum_{n=0}^N f(n) U_N^{nk}​$" src="./svgs/7c0edd3992c818e931956cde050483a6.svg" align="middle" width="280.57929239999993pt" height="32.256008400000006pt"/>

where <img alt="$U_N = \exp(\frac{2\pi i}{N})$" src="./svgs/5cef59be7c359fe7f3e49eb286445446.svg" align="middle" width="106.75764989999999pt" height="28.172905199999978pt"/> is the [N-th root of unity](https://en.wikipedia.org/wiki/Root_of_unity).

It has the following feature, which leads to [Fast Fourier Transform (FFT)](https://en.wikipedia.org/wiki/Fast_Fourier_transform) algorithm:

<img alt="$F(k) = F_e(k) + U_N^k F_o(k),​$" src="./svgs/9e8c74690794d2e9052a6d813bffe513.svg" align="middle" width="184.21405694999999pt" height="27.91243950000002pt"/>

where <img alt="$F_e(k) = \sum_{n=0}^{N/2} f(2n) U_{N/2}^{nk}$" src="./svgs/364f0ccb93e76298f2ed3836096a477d.svg" align="middle" width="182.87609009999997pt" height="33.790234500000004pt"/>, <img alt="$F_o(k) = \sum_{n=0}^{N/2} f(2n+1) U_{N/2}^{nk}$" src="./svgs/ad4796183c3cf6f91d52b1c313c1cfeb.svg" align="middle" width="211.43817254999996pt" height="33.790234500000004pt"/>.

The <img alt="$F_e(k)$" src="./svgs/f61c983ccfd139356bb00b4b362df077.svg" align="middle" width="39.490410299999986pt" height="24.65753399999998pt"/> and <img alt="$F_o(k)$" src="./svgs/6d81c79a80efbe585340fa8f39ddd1e2.svg" align="middle" width="39.742091399999985pt" height="24.65753399999998pt"/> are defined and can be calculated by recursively applying FFT to even and odd subsequences of original signal <img alt="$f(t)​$" src="./svgs/2298629273334067fc61c78964310329.svg" align="middle" width="28.53894449999999pt" height="24.65753399999998pt"/>.

### Proof
Replacing <img alt="$U_{N/2}​$" src="./svgs/a7038c5e2a97234c26be5829f73d65b2.svg" align="middle" width="35.09595869999999pt" height="22.465723500000017pt"/> in <img alt="$F_e(k)​$" src="./svgs/b3f9bad0061eac70d4d4738c4002f3c4.svg" align="middle" width="39.490410299999986pt" height="24.65753399999998pt"/> and <img alt="$F_o(k)​$" src="./svgs/4c81005e81d84aba9d5c25935767a215.svg" align="middle" width="39.742091399999985pt" height="24.65753399999998pt"/> by the following observation:

<img alt="$U_{N/2}^n = U_N^{2n}$" src="./svgs/b43dcb472b66f9592f77127db0c50dac.svg" align="middle" width="85.52998409999998pt" height="26.76175259999998pt"/>

we'll get

<img alt="$ F_e(k) =\sum_{n=0}^{N/2} f(2n) U_N^{2nk},$" src="./svgs/baadfa4bf68eb391f7fc340f64b5f308.svg" align="middle" width="188.12880074999998pt" height="33.790234500000004pt"/>

<img alt="$ F_o(k) = \sum_{n=0}^{N/2} f(2n+1) U_N^{2nk},$" src="./svgs/f3696a94c5cd1e91dbcc658cfa61131e.svg" align="middle" width="216.6908832pt" height="33.790234500000004pt"/>

<img alt="$U_N^n F_o(k) = \sum_{n=0}^{N/2} f(2n+1) U_N^{(2n+1)k},​$" src="./svgs/14ea93c55ed666e77adbc0702b1705da.svg" align="middle" width="267.30060884999995pt" height="34.337843099999986pt"/>

We now see that <img alt="$F_e(k)​$" src="./svgs/b3f9bad0061eac70d4d4738c4002f3c4.svg" align="middle" width="39.490410299999986pt" height="24.65753399999998pt"/> consists of even terms of <img alt="$F(k)​$" src="./svgs/32b1a6bb757963189e014e6ef9f905ef.svg" align="middle" width="34.714717949999994pt" height="24.65753399999998pt"/>, and <img alt="$U_N^kF_o(k)​$" src="./svgs/cdeb95984af785bbdb213e13e5e3e88a.svg" align="middle" width="63.43388369999998pt" height="27.91243950000002pt"/> consists of odd terms of <img alt="$F(k)​$" src="./svgs/32b1a6bb757963189e014e6ef9f905ef.svg" align="middle" width="34.714717949999994pt" height="24.65753399999998pt"/>. QED.

### A Detail of Implementation
Originally <img alt="$F_e(k)$" src="./svgs/f61c983ccfd139356bb00b4b362df077.svg" align="middle" width="39.490410299999986pt" height="24.65753399999998pt"/> and  <img alt="$ F(k)$" src="./svgs/3a2002f4d035c46ace578d7afcb66c24.svg" align="middle" width="34.71471795pt" height="24.65753399999998pt"/>are both arrays of length <img alt="$N/2$" src="./svgs/c55ee43adc1329ac50c7b66663c0fbea.svg" align="middle" width="30.06850769999999pt" height="24.65753399999998pt"/>. However, in the last step we need to add the corresponding element from both into <img alt="$F(k)$" src="./svgs/f9648d8a82a1a6fefe1152ab19eb75e2.svg" align="middle" width="34.714717949999994pt" height="24.65753399999998pt"/> of length <img alt="$N$" src="./svgs/f9c4988898e7f532b9f826a75014ed3c.svg" align="middle" width="14.99998994999999pt" height="22.465723500000017pt"/>.

The key is the fact that <img alt="$F_e(k)$" src="./svgs/f61c983ccfd139356bb00b4b362df077.svg" align="middle" width="39.490410299999986pt" height="24.65753399999998pt"/> and <img alt="$F_o(k)$" src="./svgs/6d81c79a80efbe585340fa8f39ddd1e2.svg" align="middle" width="39.742091399999985pt" height="24.65753399999998pt"/> are both <img alt="$N/2$" src="./svgs/c55ee43adc1329ac50c7b66663c0fbea.svg" align="middle" width="30.06850769999999pt" height="24.65753399999998pt"/> periodical. So, <img alt="$F_e(k) = F_e(k - N/2)$" src="./svgs/fbc7f9cb9ac2800a9a644bacbad4eb59.svg" align="middle" width="151.05814845pt" height="24.65753399999998pt"/>. This also holds for <img alt="$F_o(k)$" src="./svgs/6d81c79a80efbe585340fa8f39ddd1e2.svg" align="middle" width="39.742091399999985pt" height="24.65753399999998pt"/>.
We can calculate <img alt="$F(k)​$" src="./svgs/32b1a6bb757963189e014e6ef9f905ef.svg" align="middle" width="34.714717949999994pt" height="24.65753399999998pt"/> like this:

```cpp
int M = N / 2;
for (int k = 0; k < N; k++) {
  F[k] = Fe[k % M] + RU(k, N) * Fo[k % M];
}
```
