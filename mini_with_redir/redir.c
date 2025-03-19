/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:25:07 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/19 18:25:10 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

void read_heredoc(const char *delimiter, int pipe_fd)
{
    char buffer[MAX_INPUT];
    while (1)
    {
        printf("heredoc> ");
        fflush(stdout);
        if (!fgets(buffer, MAX_INPUT, stdin))
            break;
        
        if (strncmp(buffer, delimiter, strlen(delimiter)) == 0 && buffer[strlen(delimiter)] == '\n')
            break;
        
        write(pipe_fd, buffer, strlen(buffer));
    }
    close(pipe_fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s comando delimitador\n", argv[0]);
        return 1;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0) // Proceso hijo
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    }
    else // Proceso padre
    {
        close(pipe_fd[0]);
        read_heredoc(argv[2], pipe_fd[1]);
        close(pipe_fd[1]);
        waitpid(pid, NULL, 0);
    }
    return 0;
}

