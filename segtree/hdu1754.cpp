

#include <cstdio>

int tree[524288]; /* 524288 == 2^(ceil(log2(200000)) + 1) */

void init(int low, int high, int index)
{
    tree[index] = 0;
    if (low == high) return;
    int mid = (low + high) >> 1;
    init(low, mid, index << 1);
    init(mid + 1, high, (index << 1) | 1);
}

void update(int num, int value, int low, int high, int index)
{    
    if (value > tree[index]) tree[index] = value;
    if (low == high) return;

    int mid = ((low + high) >> 1);
    if (num > mid)update(num, value, mid + 1, high, (index << 1) | 1);
    else update (num, value, low, mid, index << 1 );
}

int query(int from, int to, int low, int high, int index)
{
    if (from == low && to == high) 
        return tree[index];
    int mid = (low + high) >> 1;
    if (from > mid)
        return query (from, to, mid + 1, high, (index << 1) | 1);
    else if (to <= mid)
        return query (from, to, low, mid, index << 1);
    else {
        int left = query(from, mid, low, mid, index << 1);
        int right = query(mid + 1, to, mid + 1, high, (index << 1) | 1);
        return left > right ? left : right;
    }
}
int main(void)
{
    int nstu = 0, noper = 0, score = 0, pa = 0, pb = 0;
    char cmd[2];
    while(EOF != scanf("%d %d", &nstu, &noper)) {
        init(1, nstu, 1);
        for(int i = 0; i < nstu; i++) {
            scanf("%d", &score);
            update(i + 1, score, 1, nstu, 1);
        }
        for (int i = 0; i < noper; i++) {
            scanf("%s", cmd);
            scanf("%d %d", &pa, &pb);
            if ('U' == cmd[0]) {
                update(pa, pb, 1, nstu, 1);
            }else {
                printf("%d\n", query(pa, pb, 1, nstu, 1));
            }
        }
    }
    return 0;
}
