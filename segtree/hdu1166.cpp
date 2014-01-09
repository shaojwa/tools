
#include <stdio.h>

typedef struct {
	int left;
	int right;
	int mid;
	int weight;
}NODE;

#define N (50000)
NODE buf[3*N];
char cmd[6];

void build(int left, int right, int index)
{
	buf[index].left = left;
	buf[index].right = right;
	buf[index].mid = ((right + left) >> 1);
	buf[index].weight = 0;
	if (left + 1 == right) {
		return;
	}
	else  {
		build(left, buf[index].mid, (index << 1) + 1);
		build(buf[index].mid, right, (index + 1) << 1);
	}
}

void update(int num, int delta, int index)
{
	buf[index].weight += delta;
	if (buf[index].left + 1 == buf[index].right) {
		return;		
	}else if(num < buf[index].mid) {
		update(num, delta, (index << 1) + 1);
	}else  {
		update(num, delta, (index + 1) << 1);
	}
}

int query(int from, int to, int index)
{
	if ((from == buf[index].left) && (to == buf[index].right)) {
		return buf[index].weight;
	}
	else if (to <= buf[index].mid) {
		return query(from, to, (index << 1) + 1);
	}
	else if (from >= buf[index].mid) {
		return query(from, to, (index + 1) << 1);
	}
	else {
		return (query(from, buf[index].mid, (index << 1) + 1) +
			query(buf[index].mid, to, (index + 1) << 1));
	}
}

int main(void)
{
	int i = 0, j = 0;
	int cases = 0, n = 0, num = 0;
	int pa = 0, pb = 0, ret = 0;
	scanf("%d", &cases);
	for(i = 0; i < cases; i++) {
		scanf("%d", &n);
		build(0, n, 0);
		for (j = 0; j < n; j++) {
			scanf("%d", &num);
			update(j, num, 0);
		}
		printf("Case %d:\n", i + 1);
		while(scanf("%s", cmd))  
		{
			if ('A' == cmd[0]) {
				scanf("%d %d", &pa, &pb);
				update(pa - 1, pb, 0);
			}
			else if ('S' == cmd[0]) {
				scanf("%d %d", &pa, &pb);
				update(pa - 1, -pb, 0);
			}
			else if ('Q' == cmd[0]) {
				scanf("%d %d", &pa, &pb);
				ret = query(pa - 1, pb, 0);
				printf("%d\n", ret);
			}
			else {
				break;
			}
		}
	}
	return 0;
}


