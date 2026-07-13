#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void usage(const char *program)
{
    fprintf(stderr, "Usage: %s exit|abort\n", program);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    pid_t result;
    int status;

    if (argc != 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "exit") != 0 &&
        strcmp(argv[1], "abort") != 0) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /*
         * TODO:
         * 参数为 exit 时，调用 _exit(42)。
         * 参数为 abort 时，调用 abort()。
         */
	if (strcmp(argv[1], "exit") == 0) {
	    _exit(42);
	} else {
	    abort();
	}
    }

    /*
     * TODO:
     * 1. 使用 waitpid 等待指定子进程
     * 2. 如果 waitpid 因 EINTR 失败，则重新调用
     * 3. 使用 WIFEXITED 判断是否正常退出
     * 4. 使用 WEXITSTATUS 取得退出码
     * 5. 使用 WIFSIGNALED 判断是否被信号终止
     * 6. 使用 WTERMSIG 取得信号编号
     */
    for (;;) {
        result = waitpid(pid, &status, 0);

        if (result >= 0) {
            break;
        }

        if (errno == EINTR) {
            continue;
        }

        perror("waitpid");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
        printf("child exited normally, status=%d\n",
               WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("child terminated by signal %d\n",
               WTERMSIG(status));
    } else {
        printf("child changed state in another way\n");
    }

    return EXIT_SUCCESS;
}
