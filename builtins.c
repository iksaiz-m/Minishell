/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:51:54 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/12/20 20:23:26 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"
#include "libft/libft.h"

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
}
// void	ls(char *path, char *av)
// {
// 	 //readdir(dirp);
// 	 execv(path, &av);
// }

void	cd(char *av)
{
	char	*path;
	char	*pwd;

	printf("av: %s\n", av);
	path = av;
	//pwd = getcwd(NULL, 0);
	//printf("%s\n", pwd);
	if(chdir(path) == -1)
{
    	perror("chdir");
		return ;
    /* return error of some sort, don't continue */
}
	else
		pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	//ls(path, av);
}

void	echo(char **av, int flag)
{	
	int i;

	i = 2;
	if (flag == 2)
		i = 3;
	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && ft_strlen(av[i]) == 2)
		i++;
	while (av[i])
	{
		printf("%s", av[i]);
		i++;
		if (av[i])
			printf(" ");
	}
	if (flag == 1)
		printf("\n");
}

int main(int ac, char **av)
{
	//pwd();
	// DIR *dirp;

	// if (av[1] && !av[2])
	// {
	// 	dirp = opendir(av[1]);
	
	// 	//ls(dirp);
	// }
	char	*path;

	// //cd(av[1]);
	if (ac != 1 && ft_strncmp(av[1], "ls", 2) == 0 && ft_strlen(av[1]) == 2)
	{
			path = "/usr/bin/ls";
			execv(path, &av[1]);
	}
	if (ac == 3 && ft_strncmp(av[1], "cd", 2) == 0 && ft_strlen(av[1]) == 2)
 		cd(av[2]);
	if (ac > 2 && ft_strncmp(av[1], "echo", 4) == 0 && ft_strlen(av[1]) == 4
		&& ft_strncmp(av[2], "-n", 2) == 0 && ft_strlen(av[2]) == 2)
		echo(av, 2);
	else if (ac >= 2 && ft_strncmp(av[1], "echo", 4) == 0 && ft_strlen(av[1]) == 4)
		echo(av, 1);
	if (ac >= 2 && ft_strncmp(av[1], "env", 3) == 0 && ft_strlen (av[1]) == 3)
		{
			path = "/usr/bin/env";
			execv(path, &av[1]);
		}
	//pwd();
	// path = "/usr/bin/ls";
	// execv(path, &av[1]);
	//echo(av);

	//ft_printf("%d", ft_strlen(av[1]));
	//cd(av[1]);
	return (0);
}
