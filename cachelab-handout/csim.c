// 骆炳君 软件71 2017013573

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cachelab.h"

// block
typedef struct
{
    unsigned int valid;
    unsigned int LRU;
    unsigned int tag;
} Block;

unsigned int s = 0;
unsigned int E = 0;
unsigned int b = 0;
unsigned int v = 0;
char *t = NULL;
FILE *fp = NULL;     // FILE pointer of .trace file
Block *cache = NULL; // pointer of the begin of cache memories

int time = 0; // caculate LRU
int hits = 0;
int misses = 0;
int evictions = 0;

Block *initCache()
{
    Block *ret = malloc(sizeof(Block) * (1 << s) * E);
    memset(ret, 0, sizeof(Block) * (1 << s) * E);
    return ret;
}

void showHelp()
{
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("    -h          Print this help message.\n");
    printf("    -v          Optional verbose flag.\n");
    printf("    -s <num>    Number of set index bits.\n");
    printf("    -E <num>    Number of lines per set.\n");
    printf("    -b <num>    Number of block offset bits.\n");
    printf("    -t <file>   Trace file.\n");
    printf("\n");
    printf("Examples:\n");
    printf("    linux> ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("    linux> ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

// search cache memories for certain addr, and load it if missed
void searchCache(unsigned long long addr)
{
    // printf("%llx\n", addr);
    unsigned int set_index = (addr >> b) & ((1 << s) - 1);
    unsigned int tag = addr >> (s + b);

    int farthest = set_index * E;
    for (int i = set_index * E; i < (set_index + 1) * E; i++)
    {
        if (cache[i].valid == 0)
        {
            if (v)
                printf("miss ");
            misses++;
            cache[i].valid = 1;
            cache[i].LRU = time;
            cache[i].tag = tag;
            return;
        }

        if (cache[i].tag == tag)
        {
            if (v)
                printf("hit ");
            hits++;
            cache[i].LRU = time;
            return;
        }

        if (cache[i].LRU < cache[farthest].LRU)
        {
            farthest = i;
        }
    }

    if (v)
        printf("miss eviction ");
    evictions++;
    misses++;
    cache[farthest].valid = 1;
    cache[farthest].LRU = time;
    cache[farthest].tag = tag;
}

// read .trace file and simulate cache operations
void sim()
{
    char op;
    unsigned long long addr;
    unsigned int size;
    while (fscanf(fp, "%c %llx,%u\n", &op, &addr, &size) != EOF)
    {
        time++;
        switch (op)
        {
        case 'I':
            break;

        case 'L':
        case 'S':
            if (v)
            {
                printf("%c %llx,%d ", op, addr, size);
                searchCache(addr);
                printf("\n");
            }
            else
            {
                searchCache(addr);
            }

            break;
        case 'M':
            if (v)
            {
                printf("%c %llx,%d ", op, addr, size);
                searchCache(addr);
                printf("hit\n");
            }
            else
            {
                searchCache(addr);
            }
            hits++;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 's':
                s = atoi(argv[++i]);
                break;

            case 'E':
                E = atoi(argv[++i]);
                break;

            case 'b':
                b = atoi(argv[++i]);
                break;

            case 't':
                t = argv[++i];
                break;

            case 'v':
                v = 1;
                break;

            case 'h':
            default:
                showHelp();
                return 0;
            }
        }
    }
    if (s != 0 && E != 0 && b != 0)
    {
        cache = initCache();
        fp = fopen(t, "r");
        sim();
        printSummary(hits, misses, evictions);
    }
    else
    {
        showHelp();
    }
    return 0;
}