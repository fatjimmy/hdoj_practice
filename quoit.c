#include <stdio.h>
#include <string.h>

#define MAX 100001
#define PRECISION 0.0001
typedef struct node {
	double x,y;
} Node;
Node pointx[MAX];
Node pointy[MAX];
Node tmp[MAX];
int compx(const void * p1, const void *p2);
int compy(const void * p1, const void *p2);
double get_closet(int l, int r);
double get_distance(Node p1, Node p2);
double min(double a, double b);
double sqrt(double x);

int main() {
	int n;
	double ans;
	int i;

	scanf("%d", &n);
	while (n != 0) {
		memset(pointx, 0, MAX*sizeof(Node));
		for (i = 0; i < n; i++) {
			scanf("%lf %lf", &pointx[i].x, &pointx[i].y);
			pointy[i].x = pointx[i].x;
			pointy[i].y = pointx[i].y;
		}
		qsort(&pointx, n-1, sizeof(Node), compx);	
		qsort(&pointy, n-1, sizeof(Node), compy);	
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

double get_closet(int l, int r){
	int mid;
	double dis, dis_tmp;
	int len;
	int i,j;

	if (l == r){
		return 10000000;
	}
	if (r == l+1) {
		return get_distance(pointx[l], pointx[r]);
	}
	if (r == l+2){
		return min(get_distance(pointx[l], pointx[l+1]),min(get_distance(pointx[l+1], pointx[l+2]), 
		get_distance(pointx[l], pointx[l+2])));
	}
	
	mid = (l+r) >> 1;
	dis = min(get_closet(l, mid), get_closet(mid+1, r));
	
	len = 0;
	for (i = l; i <= r; i++) {
		if ((pointy[i].x >= (pointy[mid].x-dis))	&& (pointy[i].x <= (pointy[mid].x+dis))) {
			tmp[len++] = pointy[i];	
		}
	}

	for (i = 0; i < len-1; i++) {
		for (j = i+1; j < len; j++) 
			if (tmp[j].y <= tmp[i].y + dis){
				dis_tmp = get_distance(tmp[i], tmp[j]);
				if (dis_tmp < dis) {
					dis = dis_tmp;
				}
			}
	}
	return dis;
}

double get_distance(Node p1, Node p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y))/2;
}

double min(double a, double b) {
	if (a < b) {
		return a;	
	} else {
		return b;
	}
}
double sqrt(double x) {
	double lo, hi, mid;
	if (x == 0.0f){
		return 0;	
	}

	lo = 1.0;
  	hi = x;
	while (hi - lo > PRECISION) {
		mid = lo + (hi - lo)/2;
		if (mid*mid - x > PRECISION) {
			hi = mid;	
		} else {
			lo = mid;
		}
	}
	return lo;
}
