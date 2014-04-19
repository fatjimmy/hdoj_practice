#include <stdio.h>
#include <string.h>

#define MAX 100001
#define SQRT_MAGIC_F 0x5f3759df
typedef struct node {
	float x,y;
} Node;
Node pointx[MAX];
Node pointy[MAX];
Node tmp[MAX];
int compx(const void * p1, const void *p2);
int compy(const void * p1, const void *p2);
float get_closet(int l, int r);
float get_distance(Node p1, Node p2);
float min(float a, float b);
float _sqrt(float x);

int main() {
	int n;
	float ans;
	int i;

	scanf("%d", &n);
	while (n != 0) {
		memset(pointx, 0, MAX*sizeof(Node));
		for (i = 0; i < n; i++) {
			scanf("%f %f", &pointx[i].x, &pointx[i].y);
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
	if ( ((Node*)p1)->x < ((Node*)p2)->x ) {
		return -1;
	} else {
		return 1;	
	}
}
int compy(const void * p1, const void *p2){
	if ( ((Node*)p1)->y < ((Node*)p2)->y ) {
		return -1;
	} else {
		return 1;	
	}
}

float get_closet(int l, int r){
	int mid;
	float dis, dis_tmp;
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

float get_distance(Node p1, Node p2){
	return _sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y))/2;
}

float min(float a, float b) {
	if (a < b) {
		return a;	
	} else {
		return b;
	}
}
float _sqrt(float x){
	const float xhalf = 0.5f*x;
	union{
		float x;
		int i;
	}u;
	u.x = x;
	u.i = SQRT_MAGIC_F - (u.i >> 1);
	u.x = u.x*(1.5f - xhalf*u.x*u.x);
	u.x = u.x*(1.5f - xhalf*u.x*u.x);
	u.x = u.x*(1.5f - xhalf*u.x*u.x);
	return x*u.x;
}
