const int N = 1000;
int n, nex[N];
void getNext(char *s, int l) {
  nex[0] = -1;
  int i = 0, j = -1;
  while (i < l)
    if (j == -1 || s[i] == s[j]) i++, j++, nex[i] = j;
    else j = nex[j];
}
int kmp(char *s, char *t) {
  int ls = strlen(s), lt = strlen(t);
  getNext(s, ls);
  int i = 0, j = 0;
  while (i < ls && j < lt)
    if (i == -1 || s[i] == t[j]) i++, j++;
    else i = nex[i];
  if (i == ls) return j - i;
  else return -1;
}
