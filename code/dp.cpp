#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
  system("g++ a.cpp -o .usr");
  system("g++ a2.cpp -o .std");
  system("g++ a_gen.cpp -o .gen");
  int t = 0;
  while (++t) {
    system("./.gen > .fin");
    system("./.usr < .fin > .fout");
    system("./.std < .fin > .fstd");
    if (system("diff .fout .fstd")) break;
    printf("AC#%d\n", t);
  }
  printf("WA#%d\n", t);
  return 0;
}
