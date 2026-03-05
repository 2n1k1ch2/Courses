#include <complex.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int main() {
    struct dirent *entry;
    DIR *dp = opendir("/proc");

    if (!dp) {
        perror("opendir");
        return 1;
    }
    int counter =0;
    while ((entry = readdir(dp))) {
        if (isdigit(*entry->d_name)) {
            char path[256];
            char line[256];
            
            snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);

            FILE *f = fopen(path, "r");
            if (f) {
                if (fgets(line, sizeof(line), f)) {
		    if (strstr(line, "genenv")!=NULL) counter++;
                }
                fclose(f);
            }
        }
    }
    printf("%d\n",counter);
    closedir(dp);
    return 0;
}
