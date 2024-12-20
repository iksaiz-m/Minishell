/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:51:54 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/12/18 21:13:35 by iksaiz-m         ###   ########.fr       */
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

	path = av;
	//pwd = getcwd(NULL, 0);
	//printf("%s\n", pwd);
	chdir(path);
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	//ls(path, av);
}

void	echo(char **av)
{	
	int i;

	i = 0;
	if (ft_strncmp(av[1], "echo", 4) == 0 && ft_strlen(av[1]) == 4 && ft_strlen(av[2]) != 2)
	{
		i = 2;
		while (av[i])
		{
			printf("%s", av[i]);
			i++;
		}
		printf("\n");
	}
	else if (ft_strncmp(av[1], "echo", 4) == 0 && ft_strlen(av[1]) == 4
		&& ft_strncmp(av[2], "-n", 2) == 0 && ft_strlen(av[2]) == 2)
	{
		i = 3;
		while (av[i])
		{
			printf("%s", av[i]);
			i++;
		}
	}
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

	//cd(av[1]);
	path = "/usr/bin/ls";
	execv(path, &av[1]);
	//pwd();
	// path = "/usr/bin/ls";
	// execv(path, &av[1]);
	//echo(av);

	//ft_printf("%d", ft_strlen(av[1]));
	//cd(av[1]);
	return (0);
}
