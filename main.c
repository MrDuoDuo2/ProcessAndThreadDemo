#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void active() {
    int i = 0;
    for (;;) {
        i++;
        printf("%d",i);
        exit(0);
    }
}
void kill_proc(FILE *file, int childPid[10]) {
    file = fopen("childPID.txt", "r");
    while (!feof(file)) {
        fgets(childPid, 10, file);
    }
    fclose(file);
    kill(childPid, 15);
//    sprintf(killCommand, "kill %s", childPid);
//    system(killCommand);
    system("rm childPID.txt");
    printf("子进程%s删除完毕\n", childPid);
}
void childProcess(int childPid) {
    FILE *file;
    printf("子进程已启动，ID为%d\n", childPid);
    file = fopen("childPID.txt", "wb+");
    fprintf(file, "%d", childPid);
    fclose(file);
    printf("请输入对应的操作符以继续：\n1.kill kill子进程\n2.restart 重启进程\n");
    active();
}

__attribute__((unused)) void myThread() {
    printf("线程启动成功,退出进程\n");
    system("ls");
    exit(1);
}

int main() {
    START:
    printf("请输入对应的操作符以继续：\n1.fork fork子进程\n2.thread 创建线程\n3.exit 退出程序\n");
    char command[] = "";
    scanf("%s", command);
    __pid_t pid;
    //fork子进程
    if (strcmp(command, "fork") == 0) {
        FORK:
        pid = fork();
        if (pid < 0) {
            printf("Fork FAILD");
            goto START;
        }
        if (pid == 0) {
            int childPid = getpid();
            childProcess(childPid);

        }
        if (pid > 0) {
            printf("父进程ID为%d\n", getpid());
            CHILDPROCESS:;
            char args[10];
            scanf("%s", args);
            if (strcmp(args, "kill") == 0) {
                char childPid[10];
                FILE *fp = NULL;
//                char ps[40];
                kill_proc(fp, childPid);
                goto START;
            }
            if (strcmp(args, "restart") == 0) {
                char childPid[10];
                FILE *fp = NULL;
                char killCommand[40];
//                char ps[40];
                kill_proc(fp, childPid, killCommand);
                goto FORK;
            } else {
                printf("指令输入错误\n请输入对应的操作符以继续：\n1.kill kill子进程\n2.restart 重启进程\n");
                goto CHILDPROCESS;
            }
        }
    }
    //创建子线程
//    if (strcmp(command, "thread") == 0) {
//        printf("%s\n", command);
//        std::thread childthread(myThread);
//        printf("%d\n", childthread.get_id());
//        childthread.join();
//    }
    //退出
    if (strcmp(command, "exit") == 0) {
        exit(1);
    } else {
        goto START;
    }
}

