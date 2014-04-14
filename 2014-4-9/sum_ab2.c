#include <stdio.h>
#define LEN 10
int main(){
	char str_n[LEN];
	char str_a[LEN], str_b[LEN];
	int a,b;
	int n, i;

	scanf("%s", str_n);
	n = atoi(str_n);
	for (i = 0; i < n; i++) {
		scanf("%s %s", str_a, str_b);
		a = atoi(str_a);
		b = atoi(str_b);
		printf("%d\n", a+b);
	}
	return 0;
}
