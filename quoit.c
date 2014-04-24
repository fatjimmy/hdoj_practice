#include <stdio.h>
#include <string.h>

#define SQRT_MAGIC_F 0x5f3759df
#define MAX 100001

typedef struct node {
	float x,y;
	int index;
} Node;

int compx(const void *, const void *);
int compy(const void *, const void *);
float get_closet(Node[], Node[], Node[],int , int );
float get_distance(Node , Node );
float min(float , float);
float _sqrt(float);
void merge(Node[], Node[], int, int);

Node a[MAX],b[MAX],c[MAX];

int main() {
	int n;
	float ans;
	int i;

	while (scanf("%d", &n) != EOF && n != 0) {
		memset(a, 0, MAX*sizeof(Node));
		for (i = 0; i < n; i++)
			scanf("%f %f", &a[i].x, &a[i].y);
		qsort(&a, n-1, sizeof(Node), compx);	
			
		for (i = 0; i < n; i++)
			a[i].index = i;
		memcpy(&b, &a, MAX*sizeof(Node));
		qsort(&b, n-1, sizeof(Node), compy);	
		ans = get_closet(a, b, c, 0, n-1);
		printf("%.2f\n", ans);
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

void merge(Node data[], Node tmp[], int l, int r) {
	int mid;
	int i, j, k;

	mid = (l+r) >> 1;
	i = l;
	j = mid + 1;
	k = l;
	while (i <= mid && j <= r) {
		if (tmp[i].y < tmp[j].y)
			data[k++] = tmp[i++];
		else data[k++] = tmp[j++];
	}
	while (i <= mid) 
		data[k++] = tmp[i++];
	while (j <= r)
		data[k++] = tmp[j++];
}

float get_closet(Node a[], Node b[], Node c[],int l, int r) {
	int mid;
	float dis, tmp;
	int i,j,k;
	int len;

	if (l == r) return 1000000;
	if (r == l + 1) return get_distance(a[l], a[r]);
	if (r == l + 2) return min( get_distance(a[l], a[l+1]), 
		min( get_distance(a[l+1],a[l+2]), get_distance(a[l],a[l+2])));	
	
	mid = (l+r) >> 1;
	for (k = l, i = l, j = mid+1; k < r; k++) 
		if (b[k].index <= mid) {
			c[i++] = b[k];
		} else {
			c[j++] = b[k];	
		}
	dis = min(get_closet(a, c, b, l, mid), get_closet(a, c, b, mid+1, r));
	merge(b, c, l, r);
	
	len = l;
	for (i = l; i <= r; i++)
		if ((b[i].x >= a[mid].x-dis) && (b[i].x <= a[mid].x+dis)) 
		c[len++] = b[i];

	for (i = l; i < len-1; i++)
		for (j = i+1; j < len && c[j].y <= c[i].y+dis; j++){
			tmp = get_distance(c[i], c[j]);
			if (tmp < dis) dis = tmp;
		}
	return dis;
}
