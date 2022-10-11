#include "head.h"
namespace IO {
  char nc() {
    static char bf[100000], *st = bf, *ed = bf;
    return st == ed && (ed = (st = bf) + fread(bf, 1, 100000, stdin), st == ed)
             ? EOF
             : *st++;
  }
  int rd() {
    int res = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
  }
  int tmp[20], lt;
  char OBF[100000], *OBP = OBF;
  void flush() { fwrite(OBF, 1, OBP - OBF, stdout), OBP = OBF; }
  void wrch(char x) {
    if (OBP == OBF + 99999) flush();
    *OBP = x, ++OBP;
  }
  void wr(int x) {
    lt = 0;
    while (x) tmp[++lt] = x % 10, x /= 10;
    while (lt > 0) wrch(tmp[lt] + '0'), --lt;
  }
  void wr(long long x) {
    lt = 0;
    while (x) tmp[++lt] = x % 10, x /= 10;
    while (lt > 0) wrch(tmp[lt] + '0'), --lt;
  }
  void wr(const char *s) {
    while (*s) wrch(*s), ++s;
  }
  void wr(char x) { wrch(x); }
} // namespace IO
/*
 * nc():读取下一个字符，如果缓冲区没了就刷一次缓冲区
 * rd():读入一个整数 (含义为 read %d
 * flush():输出时把缓冲区清空。记得在程序结尾的时侯flush一下
 * wrch():输出单个字符
 * wr():输出一个整数/LL/字符串/单个字符
 */
