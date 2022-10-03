/*	Number theory template :
  Deals with various aspects of integer, division, modulo, etc.
*/

#include <bits/stdc++.h>

namespace number {

  const double PI = acos(-1);

  /*	Basic constants & functions :
      long long inverse (const long long &x, const long long &mod) :
        returns the inverse of x modulo mod.
        i.e. x * inv (x) % mod = 1.
      int fpm (int x, int n, int mod) :
        returns x^n % mod. i.e. Fast Power with Modulo.
      void euclid (const long long &a, const long long &b,
                   long long &x, long long &y) :
        solves for ax + by = gcd (a, b).
      long long gcd (const long long &a, const long long &b) :
        solves for the greatest common divisor of a and b.
      long long mul_mod (const long long &a, const long long &b, const long long &mod)
     : returns a * b % mod. long long llfpm (const long long &x, const long long &n,
     const long long &mod) : returns x^n % mod.
  */

  long long abs(const long long &x) { return x > 0 ? x : -x; }

  long long inverse(const long long &x, const long long &mod) {
    if (x == 1) return 1;
    return (mod - mod / x) * inverse(mod % x, mod) % mod;
  }

  int fpm(int x, int n, int mod) {
    register int ans = 1, mul = x;
    while (n) {
      if (n & 1) ans = int(1ll * ans * mul % mod);
      mul = int(1ll * mul * mul % mod);
      n >>= 1;
    }
    return ans;
  }

  void euclid(const long long &a, const long long &b, long long &x, long long &y) {
    if (b == 0) x = 1, y = 0;
    else euclid(b, a % b, y, x), y -= a / b * x;
  }

  long long gcd(const long long &a, const long long &b) {
    if (!b) return a;
    long long x = a, y = b;
    while (x > y ? (x = x % y) : (y = y % x))
      ;
    return x + y;
  }

  long long mul_mod(const long long &a, const long long &b, const long long &mod) {
    long long ans = 0, add = a, k = b;
    while (k) {
      if (k & 1) ans = (ans + add) % mod;
      add = (add + add) % mod;
      k >>= 1;
    }
    return ans;
  }

  long long llfpm(const long long &x, const long long &n, const long long &mod) {
    long long ans = 1, mul = x, k = n;
    while (k) {
      if (k & 1) ans = mul_mod(ans, mul, mod);
      mul = mul_mod(mul, mul, mod);
      k >>= 1;
    }
    return ans;
  }

  /*	Discrete Fourier transform :
      int dft::init (int n) : initializes the transformation with dimension n.
      void dft::solve (complex *a, int n, int f) :
        transforms array a with dimension n to its image representation.
        Transforms back when f = 1.
  */

  template <int MAXN = 1000000> struct dft {

    typedef std::complex<double> complex;

    static complex e[2][MAXN];

    int init(int n) {
      int len = 1;
      for (; len <= 2 * n; len <<= 1)
        ;
      for (int i = 0; i < len; i++) {
        e[0][i] = complex(cos(2 * PI * i / len), sin(2 * PI * i / len));
        e[1][i] = complex(cos(2 * PI * i / len), -sin(2 * PI * i / len));
      }
      return len;
    }

    void solve(complex *a, int n, int f) {
      for (int i = 0, j = 0; i < n; i++) {
        if (i > j) std::swap(a[i], a[j]);
        for (int t = n >> 1; (j ^= t) < t; t >>= 1)
          ;
      }
      for (int i = 2; i <= n; i <<= 1)
        for (int j = 0; j < n; j += i)
          for (int k = 0; k < (i >> 1); k++) {
            complex A = a[j + k];
            complex B = e[f][n / i * k] * a[j + k + (i >> 1)];
            a[j + k] = A + B;
            a[j + k + (i >> 1)] = A - B;
          }
      if (f == 1) {
        for (int i = 0; i < n; i++) a[i] = complex(a[i].real() / n, a[i].imag());
      }
    }
  };

  /* Number-theoretic transform :
    void ntt::solve (int *a, int n, int f, int mod, int prt) :
      transfers a[n] to its image representation.
      Converts back if f = 1.
      Requries specific mod and corresponding prt to work. (given in MOD and PRT)
    int ntt::crt (int *a, int mod) :
      fixes the results a from module 3 primes to a certain module mod.
  */

  template <int MAXN = 1000000> struct ntt {

    void solve(int *a, int n, int f, int mod, int prt) {
      for (register int i = 0, j = 0; i < n; i++) {
        if (i > j) std::swap(a[i], a[j]);
        for (register int t = n >> 1; (j ^= t) < t; t >>= 1)
          ;
      }
      for (register int i = 2; i <= n; i <<= 1) {
        static int exp[MAXN];
        exp[0] = 1;
        exp[1] = fpm(prt, (mod - 1) / i, mod);
        if (f == 1) exp[1] = fpm(exp[1], mod - 2, mod);
        for (register int k = 2; k < (i >> 1); k++) {
          exp[k] = int(1ll * exp[k - 1] * exp[1] % mod);
        }
        for (register int j = 0; j < n; j += i) {
          for (register int k = 0; k < (i >> 1); k++) {
            register int &pA = a[j + k], &pB = a[j + k + (i >> 1)];
            register int A = pA, B = int(1ll * pB * exp[k] % mod);
            pA = (A + B) % mod;
            pB = (A - B + mod) % mod;
          }
        }
      }
      if (f == 1) {
        register int rev = fpm(n, mod - 2, mod);
        for (register int i = 0; i < n; i++) { a[i] = int(1ll * a[i] * rev % mod); }
      }
    }

    int MOD[3] = {1045430273, 1051721729, 1053818881}, PRT[3] = {3, 6, 7};

    int crt(int *a, int mod) {
      static int inv[3][3];
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) inv[i][j] = (int)inverse(MOD[i], MOD[j]);
      static int x[3];
      for (int i = 0; i < 3; i++) {
        x[i] = a[i];
        for (int j = 0; j < i; j++) {
          int t = (x[i] - x[j] + MOD[i]) % MOD[i];
          if (t < 0) t += MOD[i];
          x[i] = int(1LL * t * inv[j][i] % MOD[i]);
        }
      }
      int sum = 1, ret = x[0] % mod;
      for (int i = 1; i < 3; i++) {
        sum = int(1LL * sum * MOD[i - 1] % mod);
        ret += int(1LL * x[i] * sum % mod);
        if (ret >= mod) ret -= mod;
      }
      return ret;
    }
  };

  /*	Chinese remainder theroem :
      bool crt::solve (const std::vector <std::pair<long long, long long> > &input,
                      std::pair<long long, long long> &output) :
        solves for an integer set x = output.first + k * output.second
          that satisfies x % input[i].second = input[i].first.
        Returns whether a solution exists.
  */

  struct crt {

    long long fix(const long long &a, const long long &b) { return (a % b + b) % b; }

    bool solve(const std::vector<std::pair<long long, long long>> &input,
        std::pair<long long, long long> &output) {
      output = std::make_pair(1, 1);
      for (int i = 0; i < (int)input.size(); ++i) {
        long long number, useless;
        euclid(output.second, input[i].second, number, useless);
        long long divisor = gcd(output.second, input[i].second);
        if ((input[i].first - output.first) % divisor) { return false; }
        number *= (input[i].first - output.first) / divisor;
        number = fix(number, input[i].second);
        output.first += output.second * number;
        output.second *= input[i].second / divisor;
        output.first = fix(output.first, output.second);
      }
      return true;
    }
  };

  /*	Miller Rabin :
      bool miller_rabin::solve (const long long &) :
        tests whether a certain integer is prime.
  */

  struct miller_rabin {

    int BASE[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    bool check(const long long &prime, const long long &base) {
      long long number = prime - 1;
      for (; ~number & 1; number >>= 1)
        ;
      long long result = llfpm(base, number, prime);
      for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1)
        result = mul_mod(result, result, prime);
      return result == prime - 1 || (number & 1) == 1;
    }

    bool solve(const long long &number) {
      if (number < 2) return false;
      if (number < 4) return true;
      if (~number & 1) return false;
      for (int i = 0; i < 12 && BASE[i] < number; ++i)
        if (!check(number, BASE[i])) return false;
      return true;
    }
  };

  /*	Pollard Rho :
      std::vector <long long> pollard_rho::solve (const long long &) :
        factorizes an integer.
  */

  struct pollard_rho {

    miller_rabin is_prime;
    const long long threshold = 13E9;

    long long factorize(const long long &number, const long long &seed) {
      long long x = rand() % (number - 1) + 1, y = x;
      for (int head = 1, tail = 2;;) {
        x = mul_mod(x, x, number);
        x = (x + seed) % number;
        if (x == y) return number;
        long long answer = gcd(abs(x - y), number);
        if (answer > 1 && answer < number) return answer;
        if (++head == tail) {
          y = x;
          tail <<= 1;
        }
      }
    }

    void search(const long long &number, std::vector<long long> &divisor) {
      if (number > 1) {
        if (is_prime.solve(number)) divisor.push_back(number);
        else {
          long long factor = number;
          for (; factor >= number;
               factor = factorize(number, rand() % (number - 1) + 1))
            ;
          search(number / factor, divisor);
          search(factor, divisor);
        }
      }
    }

    std::vector<long long> solve(const long long &number) {
      std::vector<long long> ans;
      if (number > threshold) search(number, ans);
      else {
        long long rem = number;
        for (long long i = 2; i * i <= rem; ++i)
          if (number % i) ++i;
          else {
            ans.push_back(i);
            rem %= i;
          }
      }
      return ans;
    }
  };

  /*	Adaptive Simpson's method :
      double simpson::solve (double (*f) (double), double l, double r, double eps) :
        integrates f over (l, r) with error eps.
  */

  struct simpson {

    double area(double (*f)(double), double l, double r) {
      double m = l + (r - l) / 2;
      return (f(l) + 4 * f(m) + f(r)) * (r - l) / 6;
    }

    double solve(double (*f)(double), double l, double r, double eps, double a) {
      double m = l + (r - l) / 2;
      double left = area(f, l, m), right = area(f, m, r);
      if (fabs(left + right - a) <= 15 * eps)
        return left + right + (left + right - a) / 15.0;
      return solve(f, l, m, eps / 2, left) + solve(f, m, r, eps / 2, right);
    }

    double solve(double (*f)(double), double l, double r, double eps) {
      return solve(f, l, r, eps, area(f, l, r));
    }
  };

} // namespace number

using namespace number;

typedef std::complex<double> complex;
template <int MAXN> std::complex<double> dft<MAXN>::e[2][MAXN];
const int MAXN = 1000000;

dft<> m_dft;
int N, M;
complex A[MAXN], B[MAXN], C[MAXN];

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N + 1; ++i) {
    int tmp;
    scanf("%d", &tmp);
    A[i] = complex(tmp, 0);
  }
  for (int i = 0; i < M + 1; ++i) {
    int tmp;
    scanf("%d", &tmp);
    B[i] = complex(tmp, 0);
  }
  int size = N + M + 1;
  int len = m_dft.init(size);
  m_dft.solve(A, len, 0);
  m_dft.solve(B, len, 0);
  for (int i = 0; i < len; ++i) C[i] = A[i] * B[i];
  m_dft.solve(C, len, 1);
  for (int i = 0; i < N + M + 1; ++i)
    printf("%d%c", int(C[i].real() + .5), " \n"[i == size - 1]);
  return 0;
}
