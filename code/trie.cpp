#include <bits/stdc++.h>
#define SIZE 1000
struct trie {
  int tr[SIZE][26];
  int e[SIZE], cnt = 0;
  void insert(char *s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
      int now = s[i] - 'a';
      if (!tr[p][now]) tr[p][now] = ++cnt;
      p = tr[p][now];
    }
    e[p]++;
  }
  bool find(char *s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
      int now = s[i] - 'a';
      if (!tr[p][now]) return false;
      p = tr[p][now];
    }
    return e[p];
  }
};
