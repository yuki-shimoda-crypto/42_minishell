// #include <sys/wait.h> // #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// 
// int main() {
//     pid_t pid = fork();
// 
//     if (pid == -1) {
//         perror("fork failed");
//         return 1;
//     } else if (pid == 0) {
//         // child process
//         printf("child process\n");
//         usleep(100);
//         exit(2);
//         return 4;
//     } else {
//         // parent process
//         int status;
//         printf("parent process\n");
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status)) {
//             printf("child process exited with status %d\n", WEXITSTATUS(status) & 0xff);
//         }
//         return 0;
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int sig) {
    // 何もしないが、シグナルを処理するためのハンドラが必要
}

int main() {
    struct sigaction sa;

    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    int n_children = 4;
    pid_t child_pids[n_children];

    for (int i = 0; i < n_children; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // 子プロセス
            printf("Child process %d with PID %d\n", i, getpid());
            exit(i);
        } else {
            // 親プロセス
            child_pids[i] = pid;
        }
    }

    int status;
    for (int i = 0; i < n_children; ++i) {
        pid_t pid = waitpid(-1, &status, 0);

        if (pid == -1) {
            perror("waitpid");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child process with PID %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process with PID %d was killed by signal %d (%s)\n", pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
            if (WCOREDUMP(status)) {
                printf("Child process with PID %d produced a core dump\n", pid);
            }
        } else if (WIFSTOPPED(status)) {
            printf("Child process with PID %d was stopped by signal %d (%s)\n", pid, WSTOPSIG(status), strsignal(WSTOPSIG(status)));
        }
    }

    return 0;
}
