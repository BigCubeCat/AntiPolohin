#include <stdio.h>

int main() {
  int n, m; 
  scanf("%d %d", &n, &m);
  int result = n + 1; // Сначала лягушки, птом хомячки
  if (m == 0) {
    printf("%d", 1);
    return 0;
  }
  int count = n + m;
  int gap, dif;
  for (int i = 1; i <= n; ++i) {
    gap = i * (m - 1);
    if (gap == 0) {
      break;
    }
    if (gap + m <= count) {
      dif = count - m - gap;
      result += dif + 1;
    } else {
      break;
    }
  }
  printf("%d", result);
  return 0;
}
