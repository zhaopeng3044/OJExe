// task url https://atcoder.jp/contests/acl1/tasks/acl1_a
// problem statement: https://hackmd.io/@InL1-d3QTEuuv1yqrRRg3g/HyQr0x48gg

#include <sys/resource.h>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>

const int MAX_ELEMENT_NUM = 200000;

struct Node
{
    int x, y;
    int minimum_root, maxmum_root;
    int connected_counts;
};

Node nodes[MAX_ELEMENT_NUM];
int nodes_sorted_index[MAX_ELEMENT_NUM + 1];

bool compareNodes(const Node &a, const Node &b)
{
    if (a.x == b.x)
    {
        return a.y < b.y;
    }
    return a.x < b.x;
}

void sortNodes(Node nodes[], int n)
{
    std::sort(nodes, nodes + n, compareNodes);
}

void printOriginArrayInfo(Node nodes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d %d %d %d %d\n", nodes[i].x, nodes[i].y, nodes[i].minimum_root, nodes[i].maxmum_root, nodes[i].connected_counts);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    memset(nodes, 0, sizeof(nodes));

    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        nodes[i].x = x;
        nodes[i].y = y;
        nodes[i].minimum_root = y; // 初始化最小父节点为当前节点的 y 值
        nodes[i].maxmum_root = y;  // 初始化最大父节点为当前节点

        // 利用 N+1空间大小的 array 进行排序
        nodes_sorted_index[x] = i;
    }

    // 更新每个节点的最小父节点，其中对于 x=1 的节点，最小父节点只能是它本身，所以从 x=2 开始更新
    for (int i = 2; i <= n; i++)
    {
        if (nodes[nodes_sorted_index[i - 1]].minimum_root < nodes[nodes_sorted_index[i]].y)
        {
            nodes[nodes_sorted_index[i]].minimum_root = nodes[nodes_sorted_index[i - 1]].minimum_root;
        }
    }

    // 更新每个节点的最大父节点，其中对于 x=n 的节点，最大父节点只能是它本身，所以从 x=n-1 开始更新
    for (int i = n - 1; i > 0; i--)
    {
        if (nodes[nodes_sorted_index[i + 1]].maxmum_root > nodes[nodes_sorted_index[i]].y)
        {
            nodes[nodes_sorted_index[i]].maxmum_root = nodes[nodes_sorted_index[i + 1]].maxmum_root;
        }
    }

    // 更新最后结果
    int last_minimum_root = 1;
    for (int i = 2; i <= n; i++)
    {
        if (nodes[nodes_sorted_index[i]].maxmum_root < nodes[nodes_sorted_index[i - 1]].minimum_root)
        {
            int connected_counts = i - last_minimum_root;
            for (int j = last_minimum_root; j < i; j++)
            {
                nodes[nodes_sorted_index[j]].connected_counts = connected_counts;
            }
            last_minimum_root = i;
        }
    }

    // 处理最后一段连续的节点
    if (last_minimum_root < n)
    {
        int connected_counts = n - last_minimum_root + 1;
        for (int j = last_minimum_root; j <= n; j++)
        {
            nodes[nodes_sorted_index[j]].connected_counts = connected_counts;
        }
    }
    else if (last_minimum_root == n)
    {
        nodes[nodes_sorted_index[n]].connected_counts = 1;
    }

    // 打印结果
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", nodes[i].connected_counts);
    }
    return 0;
}