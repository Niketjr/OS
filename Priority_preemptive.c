#include <stdio.h>

#define MAX_PROC 10

struct Proc {
    int pid, at, bt, pri, ct, tat, wt, rt, exec, rem_bt;
};

void prio_preemptive(struct Proc proc[], int n) {
    int curr_time = 0, total_ct = 0, completed = 0;
    int is_first = 1;

    while (completed < n) {
        int high_prio = 9999, high_prio_idx = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].at <= curr_time && proc[i].exec == 0) {
                if (proc[i].pri < high_prio) {
                    high_prio = proc[i].pri;
                    high_prio_idx = i;
                }
                if (proc[i].pri == high_prio) {
                    if (proc[i].at < proc[high_prio_idx].at) {
                        high_prio_idx = i;
                    }
                }
            }
        }

        if (high_prio_idx != -1) {
            if (is_first) {
                proc[high_prio_idx].rt = curr_time - proc[high_prio_idx].at;
                if (proc[high_prio_idx].rt < 0) {
                    proc[high_prio_idx].rt = 0;
                }
                is_first = 0;
            }

            proc[high_prio_idx].rem_bt -= 1;
            curr_time += 1;

            if (proc[high_prio_idx].rem_bt == 0) {
                proc[high_prio_idx].ct = curr_time;
                proc[high_prio_idx].tat = proc[high_prio_idx].ct - proc[high_prio_idx].at;
                proc[high_prio_idx].wt = proc[high_prio_idx].tat - proc[high_prio_idx].bt;
                if (proc[high_prio_idx].wt < 0) {
                    proc[high_prio_idx].wt = 0;
                }
                proc[high_prio_idx].exec = 1;
                completed += 1;
                is_first = 1;
            }
        } else {
            curr_time++;
        }
    }
}

int main() {
    int n;
    struct Proc proc[MAX_PROC];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &proc[i].pri);
        proc[i].exec = 0;
        proc[i].rem_bt = proc[i].bt;
    }

    prio_preemptive(proc, n);

    printf("PID\tAT\tBT\tPri\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid, proc[i].at, proc[i].bt, proc[i].pri,
               proc[i].ct, proc[i].wt, proc[i].tat, proc[i].rt);
    }

    return 0;
}
