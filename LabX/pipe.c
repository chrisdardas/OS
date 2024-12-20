#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int fd[2];
    char* message = malloc(100 * sizeof(char));
    int size_msg ;


    if(pipe(fd) == -1)
    {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();


    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    else if(pid == 0)
    {
        close(fd[1]);
        read(fd[0], &size_msg, sizeof(size_msg));
        read(fd[0], message, size_msg);
        printf("Message from parent: %s\n", message);
        close(fd[1]);
    }

    else
    {
        close(fd[0]);
        strcpy(message, "Hello from parent");
        size_msg = strlen(message) + 1;
        write(fd[1], &size_msg, sizeof(size_msg));
        write(fd[1], message, size_msg);
        close(fd[1]);
        waitpid(-1, NULL, 0);
        free(message);
    }

    return 0;
}