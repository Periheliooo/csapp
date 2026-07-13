#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
    pid_t pid;
    int status, result;

    /*
     * execve 的 argv 必须以 NULL 结尾。
     * argv[0] 通常是程序名称。
     */
    char *child_argv[] = {
        "echo",
        "hello",
        "system",
        "programming",
        NULL
    };

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /*
         * TODO:
         * 1. 调用 execve("/bin/echo", child_argv, environ)
         * 2. 如果 execve 返回，说明执行失败
         * 3. 使用 perror 输出错误
         * 4. 使用 _exit(127) 结束子进程
         */
	execve("/bin/echo", child_argv, environ);
	perror("execve");
	_exit(127);
    }

    /*
     * TODO:
     * 1. 等待子进程
     * 2. 正确处理 EINTR
     * 3. 输出子进程正常退出状态
     * 4. 如果子进程被信号终止，也应输出信号编号
     */
    while ((result = waitpid(pid, &status, 0)) < 0) {
        if (errno == EINTR) {
	       continue;
	}
	perror("waitpid");
	return EXIT_FAILURE;
    }
    
    if (WIFEXITED(status)) {
        printf("child exited normally, status=%d\n", WTERMSIG(status));
    } else if (WIFSIGNALED(status)) {
	printf("child terminated by signal %d\n", WTERMSIG(status));
			}

    return EXIT_SUCCESS;
}
