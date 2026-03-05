#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_ppid(int pid) {
    char path[64], line[256];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    int ppid = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "PPid:", 5) == 0) {
            ppid = atoi(line + 5); 
	    break;
        }
    }
    fclose(f);
    return ppid;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    int curr_pid = atoi(argv[1]);

    while (curr_pid != 0) {
        printf("%d\n", curr_pid);
        if (curr_pid == 1) break; 
        curr_pid = get_ppid(curr_pid);
        if (curr_pid == 0) break; 
    }
    return 0;
}
