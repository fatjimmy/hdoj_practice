#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 100001
typedef struct node {
	float x,y;
} Node;
Node point[MAX];
int compx(const void * p1, const void *p2);
int compy(const void * p1, const void *p2);
float get_closet(int l, int r);
float get_distance(Node p1, Node p2);
float min(float a, float b);
int main() {
	int n;
	float ans;
	int i;

	scanf("%d", &n);
	while (n != 0) {
		memset(point, 0, MAX*sizeof(Node));
		for (i = 0; i < n; i++) {
			scanf("%f %f", &point[i].x, &point[i].y);
		}
		qsort(&point, n-1, sizeof(Node), compx);	
		ans = get_closet(0, n-1);
		printf("%.2f\n", ans);
		
		scanf("%d", &n);
	}
	return 0;
}

int compx(const void * p1, const void *p2){
	if ( (*(Node*)p1).x < (*(Node*)p2).x ) {
		return -1;
	} else if ( (*(Node*)p1).x == (*(Node*)p2).x ) {
		return 0;
	} else {
		return 1;	
	}
}
int compy(const void * p1, const void *p2){
	if ( (*(Node*)p1).y < (*(Node*)p2).y ) {
		return -1;
	} else if ( (*(Node*)p1).y == (*(Node*)p2).y ) {
		return 0;
	} else {
		return 1;	
	}
}

float get_closet(int l, int r){
	int mid;
	float dis;
	int len;
	Node tmp[MAX];
	int i,j;

	if (l == r){
		return 10000000;
	}
	if (r == l+1) {
		return get_distance(point[l], point[r]);
	}
	if (r == l+2){
		return min(get_distance(point[l], point[l+1]),min(get_distance(point[l+1], point[l+2]), get_distance(point[l], point[l+2])));
	}
	
	mid = (l+r) >> 1;
	dis = min(get_closet(l, mid), get_closet(mid+1, r));
	
	len = 0;
	for (i = l; i <= r; i++) {
		if ((point[i].x >= (point[mid].x-dis))	&& (point[i].x <= (point[mid].x+dis))) {
			tmp[len++] = point[i];	
		}
	}
	qsort(&tmp, len-1, sizeof(Node), compy);	
	for (i = 0; i < len-1; i++) {
		for (j = i+1; j < len; j++) 
			if (tmp[j].y <= tmp[i].y + dis){
				if (get_distance(tmp[i], tmp[j]) < dis) {
					dis = get_distance(tmp[i], tmp[j]);
				}
			}
	}
	return dis;
}

float get_distance(Node p1, Node p2){
	return sqrtf((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y))/2;
}

float min(float a, float b) {
	if (a < b) {
		return a;	
	} else {
		return b;
	}
}
