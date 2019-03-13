# algorithms
Cool algorithms + implementations.

## FFT in nutshell
### Crucial Feature of DFT
Discrete Fourier Transform (DFT) is defined as the discrete Z-transform sampled at each root of unity.

$ F(k) = \sum_{n=0}^N f(n) z^n =  \sum_{n=0}^N f(n) U_N^{nk}​$

where $U_N^m = \exp(\frac{2\pi mi}{N})$ is m-th unity root of order N.

It has the following feature, which leads to Fast Fourier Transform (FFT) algorithm:

$F(k) = F_e(k) + U_N^k F_o(k),$

where $F_e(k) = \sum_{n=0}^{N/2} f(2n) U_{N/2}^{nk}$, $F_o(k) = \sum_{n=0}^{N/2} f(2n+1) U_{N/2}^{nk}$.

Note that $F_e(k)​$ and $F_o(k)​$ can be calculated by recursively applying FFT to even and odd subsequences of original signal $f(t)​$.

### Proof
Replacing $U_{N/2}​$ in $F_e(k)​$ and $F_o(k)​$ by the following observation:

$U_{N/2}^n = U_N^{2n}$

we'll get

$ F_e(k) =\sum_{n=0}^{N/2} f(2n) U_N^{2nk},$

$ F_o(k) = \sum_{n=0}^{N/2} f(2n+1) U_N^{2nk},$

$U_N^n F_o(k) = \sum_{n=0}^{N/2} f(2n+1) U_N^{(2n+1)k},​$

We now see that $F_e(k)​$ consists of even terms of $F(k)​$, and $U_N^kF_o(k)​$ consists of odd terms of $F(k)​$. QED.

### A Detail of Implementation
Originally $F_e(k)$ and  $ F(k)$are both arrays of length $N/2$. However, in the last step we need to add the corresponding element from both into $F(k)$ of length $N$.

The key is the fact that $F_e(k)$ and $F_o(k)$ are both $N/2$ periodical. So, $F_e(k) = F_e(k - N/2)$. This also holds for $F_o(k)$.
We can calculate $F(k)​$ like this:

```cpp
int M = N / 2;
for (int k = 0; k < N; k++) {
  F[k] = Fe[k % M] + RU(k, N) * Fo[k % M];
}
```
