/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:13:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/12/18 18:55:44 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

// void	redirect_fd()
// {
// 	char *content_file = "Add content to the output file\n";
// 	char *content_stdout = "No more content to the output file\n";

// 	// If the file doesn't exist, it's created
// 	int	fd = open("output_file.txt", O_WRONLY | O_CREAT, 0644);
// 	int	original_stdout = dup(STDOUT_FILENO);

// 	// now fd (the file) is the stdout. Everything printed in the terminal is redirected to the file
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	write(STDOUT_FILENO, content_file, strlen(content_file));

// 	// reset to the original stdout
// 	dup2(original_stdout, STDOUT_FILENO);

// 	// It's important to use write() or a write()-based function due to how printf deals with buffers
// 	write(STDOUT_FILENO, content_stdout, strlen(content_stdout));
// }

int main(int ac, char **av)
{
    char *rl;
    char *pwd;
   // DIR *dirp;

   rl = readline("");
    //dirp = "/home/iksaiz-m/Desktop/42cursus/minishell/librerias_importantes.txt";
    printf("%s\n", rl);
    // if (rl = "pwd")
    // {
    //     pwd = getcwd(NULL, 0);
    //     printf("%s\n", pwd);
    // }
    pwd = getcwd(NULL, 0);
    printf("pwd before chdir: %s\n", pwd);
    chdir("/home/iksaiz-m");
    // pwd = getcwd(NULL, 0);
    // printf("pwd after chdir: %s\n", pwd);
    // int stat(const char *restrict pathname, struct stat *restrict statbuf);
    // int lstat(const char *restrict pathname, struct stat *restrict statbuf);
    // int fstat(int fd, struct stat *statbuf);
     
     /* Comprobamos los argumentos */

    // if (argc != 2){
    // printf("Uso: %s directorio\n", argv[0]);
    // exit(1);
    // }
 
    /* Abrimos el directorio */
    // dirp = opendir(argv[1]);
    // dirp = opendir(rl);

    // if (dirp == NULL){
    // // printf("Error: No se puede abrir el directorio\n");
    // perror("Error: No se puede abrir el directorio");
    // abort();
    //exit(2);
//    FILE *fh;
 
//    if ((fh = fopen("mylib/myfile","r")) == NULL)
//    {
//       perror("Could not open data file");
//       abort();
//    }
    // DIR *opendir("librerias_importantes.txt");
    //closedir(dirp);
    
    // redirect_fd();

    // char *content_file = av[1];
	// char *content_stdout = "No more content to the output file\n";

	// // If the file doesn't exist, it's created
	// int	fd = open("output_file.txt", O_WRONLY | O_CREAT, 0644);
	// int	original_stdout = dup(STDOUT_FILENO);

	// // now fd (the file) is the stdout. Everything printed in the terminal is redirected to the file
	// dup2(fd, STDOUT_FILENO);
	// close(fd);
	// write(STDOUT_FILENO, content_file, strlen(content_file));

	// // reset to the original stdout
	// dup2(original_stdout, STDOUT_FILENO);

	// // It's important to use write() or a write()-based function due to how printf deals with buffers
	// write(STDOUT_FILENO, content_stdout, strlen(content_stdout));
    return (0);
}
