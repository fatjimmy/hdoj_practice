#include <stdio.h>
#include <string.h>
#define MAX_LEN 1010

int a[MAX_LEN], b[MAX_LEN], sum[MAX_LEN];
char s1[MAX_LEN], s2[MAX_LEN];

void print_result(int index);

int main(){
	char str_n[3];
	int n;
	int i;
	int len;

	scanf("%s", str_n);
	n = atoi(str_n);
	for (i = 0; i < n - 1; i++) {
		print_result(i);
		printf("\n");
	}
	print_result(n - 1);
	return 0;
}

void print_result(int index) {
	int i;
	int len, len1, len2;
	
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(sum, 0, sizeof(sum));

	scanf("%s %s", s1, s2);
	len1 = strlen(s1);
	len2 = strlen(s2);

	for (i = 0; i < len1; i++) a[len1 - i - 1] = s1[i] - '0';
	for (i = 0; i < len2; i++) b[len2 - i - 1] = s2[i] - '0';
	
	if (len1 > len2) {
		len = len1;	
	} else {
		len = len2;
	}
	
	for (i = 0; i < len; i++ ){
		sum[i] += a[i] + b[i];
		if (sum[i] >= 10) {
			sum[i] -= 10;
			sum[i+1]++;
		}
	} 
	if (sum[len] > 0) len += 1;
	
	printf("Case %d:\n", index+1);
	printf("%s + %s = ", s1, s2);
	for (i = len-1; i >= 0; i--){
		printf("%d", sum[i]);
	}
	printf("\n");
}
