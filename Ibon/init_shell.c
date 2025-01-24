/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:11:59 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/01/24 19:19:12 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_action(int argc, char **argv, int flag)
{
	char	var_name[128];
	int		var_value[128];
	int		i;

	flag = 0;
	i = 0;
	if (argc == 0)
		printf("h\n");
	if (ft_strncmp(argv[0], "export", 7) == 0)
	{
		while (argv[1][i++] != '=')
			var_name[i] = argv[1][i];
		i++;
		while (argv[1][i++])
			var_value[i] = argv[1][i];
		printf ("%s=%ls\n", var_name, var_value);
	}
	else
		flag = 1;
	return (flag);
}

int	fork_actions(int argc, char **argv, int flag)
{
	pid_t	pid;
	char	*path;

	if (ft_strncmp(argv[0], "ls", 2) == 0 && ft_strlen(argv[0]) == 2)
	{
		pid = fork();
		if (pid == 0)
		{
			path = "/usr/bin/ls";
			execv(path, &argv[0]);
			exit(0);
		}
		wait(NULL);
	}
	else if (argc >= 1 && ft_strncmp(argv[0], "env", 3) == 0 && ft_strlen (argv[0]) == 3)
	{
		pid = fork();
		if (pid == 0)
		{
			path = "/usr/bin/env";
			execv(path, &argv[0]);
			exit(0);
		}
		wait(NULL);
	}
	else
		flag = 1;
	return (flag);
}

int	other_actions(int argc, char **argv, int flag)
{
	flag = 0;
	if (argc == 2 && ft_strncmp(argv[0], "cd", 2) == 0 && ft_strlen(argv[0]) == 2)
		cd(argv[1]);
	else if (argc > 1 && ft_strncmp(argv[0], "echo", 4) == 0 && ft_strlen(argv[0]) == 4
		&& ft_strncmp(argv[1], "-n", 2) == 0 && ft_strlen(argv[1]) == 2)
		echo(argv, 2);
	else if (argc >= 1 && ft_strncmp(argv[0], "echo", 4) == 0 && ft_strlen(argv[0]) == 4)
		echo(argv, 1);
	else if (argc == 1 && ft_strncmp(argv[0], "cd", 2) == 0 && ft_strlen(argv[0]) == 2)
		cd(argv[0]);
	else if (argc == 2 && ft_strncmp(argv[0], "cd", 2) == 0 && ft_strlen(argv[0]) == 2)
		cd(argv[1]);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0 && ft_strlen(argv[0]) == 3)
		pwd(argc);
	else
		flag = 1;
	return (flag);
}

void	init_shell(int argc, char **argv)
{
	int	flag;

	flag = 0;
	flag += fork_actions(argc, argv, flag);
//	printf("%d\n", flag);
	flag += other_actions(argc, argv, flag);
	flag += export_action(argc, argv, flag);
	if (flag == 3)
		printf("Command not found: %s\n", argv[0]);
	return ;
}
