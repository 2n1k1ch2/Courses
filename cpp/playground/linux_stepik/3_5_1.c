#include <stdio.h>
#include <string.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <syslog.h>
const unsigned long BUFFER_SIZE =16;
int main(){

    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "%d",getpid());
    const char* pid =  buffer;

    char full_path[50] = "/proc/";
    strcat(full_path, pid);
    strcat(full_path, "/stat");
    FILE *fp = fopen(full_path, "r");
    if (fp ==NULL){
	openlog("ppid_finder", LOG_PID | LOG_CONS, LOG_USER);
	syslog(LOG_ERR,"Can't find %s",full_path);
	closelog();
	printf("Can't open procfs...");
	return 0;
    }
    int PID, ppid;
    char comm[256];
    char state;

    if(fscanf(fp,"%d %s %c %d" , &PID,comm,&state,&ppid)==4) {
	printf("%d\n",ppid);
    } else {
	printf("Can't parse file...");
    }
    return 0;
}
