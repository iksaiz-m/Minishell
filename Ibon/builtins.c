/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:04:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/01/25 19:00:05 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int argc)
{
	char	*pwd;

	if (argc > 1)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}
// void	ls(char *path, char *av)
// {
// 	 //readdir(dirp);
// 	 execv(path, &av);
// }

void	cd(int argc, char *av)
{
	char	*path;
//	char	*pwd;
	char	*user;

//	pwd = NULL;
	//printf("av: %s\n", av);
	if (argc == 1)
	{
		path = "/home/";
		user = getenv("USER");
		path = ft_strjoin(path, user);
	}
	else
		path = av;
	//pwd = getcwd(NULL, 0);
	//printf("%s\n", pwd); 
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	/* return error of some sort, don't continue */
	}
	/*else
		pwd = getcwd(NULL, 0);
	//printf("%s\n", pwd);
*/}

void	echo(char **av, int flag)
{
	int	i;

	i = 1;
	if (flag == 2)
		i = 2;
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
//  Para la comprobacion del -n o cosas asi en vez de usar ft_strlen comprobar que no haya siguiente
//	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && !av[i][3])