
#include <stdio.h>

#define VIDEOS 10
#define CACHE_SIZE 3

int main(void)
{
    int access[VIDEOS] = {
        1, 2, 3, 1, 4, 2, 5, 1, 3, 2
    };

    int cache[CACHE_SIZE] = {-1, -1, -1};
    int last_used[CACHE_SIZE] = {0, 0, 0};

    int hdd_reads = 0;
    int cache_hits = 0;
    int cache_misses = 0;
    int time = 0;

    printf("VIDEO STORAGE SIMULATION\n");
    printf("------------------------\n");

    printf("\nDESIGN A: HDD-BASED STORAGE\n");

    for (int i = 0; i < VIDEOS; i++)
    {
        hdd_reads++;
        printf("Video %d: HDD READ\n", access[i]);
    }

    printf("\nDESIGN B: HYBRID SSD + HDD WITH LRU CACHE\n");

    for (int i = 0; i < VIDEOS; i++)
    {
        int found = -1;

        time++;

        for (int j = 0; j < CACHE_SIZE; j++)
        {
            if (cache[j] == access[i])
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            cache_hits++;
            last_used[found] = time;

            printf("Video %d: CACHE HIT\n", access[i]);
        }
        else
        {
            int replace = -1;
            int oldest = time + 1;

            cache_misses++;

            for (int j = 0; j < CACHE_SIZE; j++)
            {
                if (cache[j] == -1)
                {
                    replace = j;
                    break;
                }

                if (last_used[j] < oldest)
                {
                    oldest = last_used[j];
                    replace = j;
                }
            }

            cache[replace] = access[i];
            last_used[replace] = time;

            printf("Video %d: CACHE MISS - DISK READ\n",
                   access[i]);
        }
    }

    printf("\nPERFORMANCE COMPARISON\n");
    printf("----------------------\n");

    printf("Total Requests: %d\n", VIDEOS);

    printf("\nDesign A - HDD Only\n");
    printf("Disk Reads: %d\n", hdd_reads);

    printf("\nDesign B - Hybrid Storage\n");
    printf("Cache Hits: %d\n", cache_hits);
    printf("Cache Misses: %d\n", cache_misses);
    printf("Disk Reads: %d\n", cache_misses);

    printf("Cache Hit Ratio: %.2f%%\n",
           (double)cache_hits / VIDEOS * 100);

    return 0;
}
