#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("before fork: pid=%ld\n", (long)getpid());
    fflush(stdout);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* TODO:
         * 1. 打印当前进程 PID
         * 2. 打印父进程 PID
         * 3. 使用 _exit(EXIT_SUCCESS) 结束子进程
         */
	printf("child: pid=%ld, parent=%ld\n",(long)getpid, (long)getppid);
	_exit(EXIT_SUCCESS);

    }

    /*
     * TODO:
     * 当前只能是父进程。
     *
     * 1. 打印父进程 PID
     * 2. 打印 fork 返回的子进程 PID
     * 3. 使用 waitpid 等待该子进程
     * 4. 正确处理 waitpid 被信号中断、errno == EINTR 的情况
     * 5. 子进程结束后打印确认信息
     */
    printf("child:pid=%ld, parent=%ld\n",(long)pid, (long)getpid);
    while (waitpid(pid, NULL, 0) < 0) {
	    if (errno == EINTR) {
		    continue;
	    }

	    perror("waitpid");
	    return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
