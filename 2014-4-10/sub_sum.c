#include <stdio.h>

int main() {
	int n, t;
	int i, j;
	int sum, max;
	int x;
	int p, s, e;

	scanf("%d", &t);
	for (i = 0; i < t; i ++) {
		scanf("%d", &n);
		
		max = -1 << 31;
		sum = -1 << 31;p = 0;s = 0;e = 1;
		
		for (j = 0; j < n; j++) {
			scanf("%d", &x);
			
			if (sum >= 0) {
				sum += x;
			} else {
				sum = x;
				p = j + 1;
			}
			
			if (sum > max) {
				max = sum;
				s = p;
				e = j + 1;
			}
		}
		
		printf("Case %d:\n", i+1);
		printf("%d %d %d\n", max, s, e);
		if (i < t-1) printf("\n");
	} 
	return 0;
}
