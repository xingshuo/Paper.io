#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define MAX_X 15
#define MAX_Y 10

typedef struct CPoint {
	int x;
	int y;
} CPoint;

int map[MAX_Y+2][MAX_X+2] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,0},
	{0,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0},
	{0,1,1,1,1,0,0,0,1,1,1,0,0,1,0,0},
	{0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0},
	{0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0},
	{0,0,1,1,1,0,1,1,0,0,1,1,0,1,0,0},
	{0,0,0,0,1,0,0,0,0,1,1,0,0,1,0,0},
	{0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

static int //围魏救赵策略
borderfill(int minx, int miny, int maxx, int maxy, int borderflag) {
	assert(minx <= maxx && miny <= maxy);
	assert(minx>=0 && maxx<=MAX_X+1);
	assert(miny>=0 && maxy<=MAX_Y+1);
	assert(borderflag > 0);
	int outflag = -1; //will fill outside grids with -1
	minx--;
	miny--;
	maxx++;
	maxy++;
	CPoint seed = {minx, miny};
	CPoint queue[(maxx-minx+1)*(maxy-miny+1)];
	int head = 0;
	int tail = 0;
	queue[tail++] = seed;
	int dir[2] = {-1,1};
	while (head < tail) { //BFS Search
		CPoint cur = queue[head++];
		int i;
		for (i=0; i<2; i++) { //up and down
			int checky = cur.y + dir[i];
			if (checky >= miny && checky <= maxy) {
				int val = map[checky][cur.x];
				if (val != borderflag && val != outflag) {
					CPoint tmp = {cur.x,checky};
					queue[tail++] = tmp;
					map[checky][cur.x] = outflag;
				}
			}
		}
		for (i=0; i<2; i++) { //left and right
			int checkx = cur.x + dir[i];
			if (checkx >= minx && checkx <= maxx) {
				int val = map[cur.y][checkx];
				if (val != borderflag && val != outflag) {
					CPoint tmp = {checkx, cur.y};
					queue[tail++] = tmp;
					map[cur.y][checkx] = outflag;
				}
			}
		}
	}
	int i,j;
	for (i=minx; i<=maxx; i++) { //反向填充
		for (j=miny; j<=maxy; j++) {
			if (map[j][i] == outflag) {
				map[j][i] = 0;
			}else {
				map[j][i] = borderflag;
			}
		}
	}
	return 0;
}

static int
PrintArray(int** a, int maxrow, int maxcol, char* sTitle) {
	printf("---%s--start--\n", sTitle);
	int i,j;
	for (i=0; i< maxrow; i ++) {
		for (j=0; j< maxcol; j++) {
			printf("%d ",*((int*)a + maxcol*i + j));
		}
		printf("\n");
	}
	printf("---%s--end--\n", sTitle);
}

int main() {
	PrintArray(map, MAX_Y+2, MAX_X+2, "raw ");
	borderfill(1, 1, MAX_X, MAX_Y, 1); //minx, miny, maxx, maxy为待填充区域的最小覆盖矩形
	PrintArray(map, MAX_Y+2, MAX_X+2, "afterfill ");
	return 0;
}