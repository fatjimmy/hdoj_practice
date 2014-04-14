#include <stdio.h>
#define LEN 10
int main(){
	char str_a[LEN], str_b[LEN];
	int a,b;

	while (EOF != scanf("%s %s", str_a, str_b)) {
		a = atoi(str_a);
		b = atoi(str_b);
		printf("%d\n", a+b);
	}
	return 0;
}
