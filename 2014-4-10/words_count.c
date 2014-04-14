#include <stdio.h>
#include <string.h>
#define LEN 16
#define MAX 997

typedef struct node {
	char color[LEN];
	int times;
} Node;

int hash(char color[]);
void insert(char color[]);

Node list[MAX];
int max_times;
char max_color[LEN];

int main() {
	int n;
	int i;
	char color[LEN];
	
	scanf("%d", &n);
	while( n != 0) {
		//init
		memset(list, 0, MAX*sizeof(Node));
		max_times = 0;
		max_color[0] = '\0';
		//insert
		for (i = 0; i < n; i ++) {
			scanf("%s", color);
			insert(color);
		}
		//print
		printf("%s\n", max_color);
		scanf("%d", &n);
	}
	return 0;
}
void insert(char color[]) {
	int key;
		
	if (max_times == 0) {
		max_times = 1;
		strcpy(max_color, color);
	}
	//get the hash value
	key = hash(color);
	while (list[key].times != 0) { // the position is not null
		if (strcmp(color, list[key].color) == 0) {
			list[key].times ++;
			if (list[key].times > max_times) {
				max_times = list[key].times;
				strcpy(max_color, color);
			}
			return;
		}
		key = (key+1) % MAX;
	}
	
	// find a null position
	list[key].times = 1;
	strcpy(list[key].color, color);
}

int hash(char color[]) {
	int h;
	char *p;
	int a = 31415, b = 27183;
	for (h = 0, p = color; *p != '\0'; p++, a = a*b % (MAX-1)) {
		h = (a*h + *p - '0') % MAX;
	}
	return h;
}
