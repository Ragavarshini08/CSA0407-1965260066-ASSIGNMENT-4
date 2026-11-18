
#include <stdio.h>
#include <stdlib.h>

#define N 8
#define MAXCYL 199

int req[N] = {98, 183, 37, 122, 14, 124, 65, 67};

int cmp(const void *a, const void *b)
{
    return (*(const int *)a - *(const int *)b);
}

void show(const char *name, int order[], int n, int head)
{
    int total = 0;
    int pos = head;

    printf("%-8s %d", name, head);

    for (int i = 0; i < n; i++)
    {
        printf(" -> %d", order[i]);
        total += abs(order[i] - pos);
        pos = order[i];
    }

    printf(" | Total movement = %d\n", total);
}

int main(void)
{
    int head = 53;
    int order[N + 2];
    int s[N];

    show("FCFS", req, N, head);

    /* SSTF */
    int done[N] = {0};
    int pos = head;

    for (int k = 0; k < N; k++)
    {
        int best = -1;
        int bestdist = MAXCYL + 1;

        for (int i = 0; i < N; i++)
        {
            if (!done[i])
            {
                int d = abs(req[i] - pos);

                if (d < bestdist)
                {
                    bestdist = d;
                    best = i;
                }
            }
        }

        done[best] = 1;
        order[k] = req[best];
        pos = req[best];
    }

    show("SSTF", order, N, head);

    /* Sort requests */
    for (int i = 0; i < N; i++)
        s[i] = req[i];

    qsort(s, N, sizeof(int), cmp);

    /* SCAN: towards cylinder 0 first */
    int n = 0;

    for (int i = N - 1; i >= 0; i--)
        if (s[i] < head)
            order[n++] = s[i];

    order[n++] = 0;

    for (int i = 0; i < N; i++)
        if (s[i] >= head)
            order[n++] = s[i];

    show("SCAN", order, n, head);

    /* C-SCAN */
    n = 0;

    for (int i = N - 1; i >= 0; i--)
        if (s[i] < head)
            order[n++] = s[i];

    order[n++] = 0;
    order[n++] = MAXCYL;

    for (int i = 0; i < N; i++)
        if (s[i] >= head)
            order[n++] = s[i];

    show("C-SCAN", order, n, head);

    /* LOOK */
    n = 0;

    for (int i = N - 1; i >= 0; i--)
        if (s[i] < head)
            order[n++] = s[i];

    for (int i = 0; i < N; i++)
        if (s[i] >= head)
            order[n++] = s[i];

    show("LOOK", order, n, head);

    /* C-LOOK */
    n = 0;

    for (int i = N - 1; i >= 0; i--)
        if (s[i] < head)
            order[n++] = s[i];

    for (int i = N - 1; i >= 0; i--)
        if (s[i] >= head)
            order[n++] = s[i];

    show("C-LOOK", order, n, head);

    return 0;
}
