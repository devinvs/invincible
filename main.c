#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>

const char ALLOWED[] = "abcdefghijklmnopqrstuvwxyz1234567890";
char name[10];

// Generate a new random name
void new_name() {
    srand(time(NULL));

    int asize = sizeof(ALLOWED)-1;

    for (int i=0; i<9; i++) {
        int c = rand() % asize;
        name[i] = ALLOWED[c];
    }

    name[9] = 0;
}

int main(int argc, char **argv) {
    if (strcmp(argv[0], "invincible") == 0) {
        // Setup memfd to hold our binary
        new_name();
        int mem = memfd_create(name, 0); // fd will always be 3

        // Find path to our binary
        pid_t pid = getpid();
        char path[128];
        sprintf(path, "/proc/%d/exe", pid);

        // Open and copy to memfd
        int exe = open(path, O_RDONLY);

        char buf[1024];
        for (;;) {
            size_t n = read(exe, buf, 1024);
            if (n == 0)
                break;

            char * loc = buf;
            while (n > 0) {
                size_t w = write(mem, loc, n);
                loc += w;
                n -= w;
            }
        }
    }
    
    // Set our name in the other ways that the system can see it
    prctl(PR_SET_NAME, (unsigned long) argv[0], 0, 0, 0);
    pthread_setname_np(pthread_self(), argv[0]);

    new_name();

    // Fork and let the parent die so we are an orphan
    if (fork() != 0)
        return 0;

    // detach from tty and pgroup
    // setsid();

    // Do something nefarious (optional)
    usleep(1000 * 300);

    // Execve into memfd
    //
    // File descriptors are preserved, so we can do this forever :)
    const char * const av[] = {name, NULL};
    const char * const ep[] = {NULL};
    int i = fexecve(3, (char * const *) av, (char * const *) ep);
    
    printf("fexec returned %d, errno=%d\n", i, errno);
}
