#include <stdio.h>
#include <string.h>

void allocateMemory(char method, int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (method == 'F') {
                    idx = j;
                    break; // For First-Fit, take the first suitable block
                } else if (method == 'B' && (idx == -1 || blockSize[j] < blockSize[idx])) {
                    idx = j;
                } else if (method == 'W' && (idx == -1 || blockSize[j] > blockSize[idx])) {
                    idx = j;
                }
            }
        }

        if (idx != -1) {
            allocation[i] = idx;
            blockSize[idx] -= processSize[i];
        }
    }

    const char* methodName = (method == 'F') ? "First-Fit" : (method == 'B') ? "Best-Fit" : "Worst-Fit";
    printf("\n%s Allocation:\n", methodName);
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m], blockSize1[m], blockSize2[m], blockSize3[m];
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        blockSize1[i] = blockSize2[i] = blockSize3[i] = blockSize[i];
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    allocateMemory('F', blockSize1, m, processSize, n);
    allocateMemory('B', blockSize2, m, processSize, n);
    allocateMemory('W', blockSize3, m, processSize, n);

    return 0;
}
