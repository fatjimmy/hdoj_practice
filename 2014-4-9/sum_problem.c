#include <stdio.h>
#define LEN 20

int main(){
	char str[LEN];
	int n;
	int sum;
	while (EOF != scanf("%s", str)) {
		n = atoi(str);
		if (n % 2 == 0) {
			sum = n/2*(n+1);
		} else {
			sum = (n+1)/2*n;
		}
		if (n < 0) sum = 0;
		printf("%d\n\n", sum);
	}
	return 0;
}
