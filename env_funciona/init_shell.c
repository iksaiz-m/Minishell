/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:11:59 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/03/15 20:35:01 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_action(int argc, char **argv)
{
	char	var_name[128];
	int		var_value[128];
	int		i;
	int		flag;

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

int	fork_actions(int argc, char **argv, int flag, t_mini **data)
{
	//pid_t	pid;
	//char	*path;
	printf("HOLA\n");
	int		i;
	t_mini *env;

	i = 0;
	printf("HOLA 2\n");
	env = *data;
	/*if ((ft_strncmp(argv[0], "ls", 2) == 0 && !argv[0][2])
		|| (ft_strncmp(argv[0], "/bin/ls", 7) == 0 && !argv[0][7]))
	{
		pid = fork();
		if (pid == 0)
		{
			path = "/usr/bin/ls";
			execv(path, &argv[0]);
			exit(0);
		}
		wait(NULL);
	}*/
	printf("HOLA 3\n");
	if (argc == 1 && ft_strncmp(argv[0], "env", 3) == 0 && !argv[0][3])
	{
		printf("HOLA 4\n");
		printaddata(env->env);
	}
	else
		flag = 1;
	return (flag);
}

int	other_actions(int argc, char **argv, t_mini **data)
{
	int	flag;
	t_mini *env;

	env = *data;
	flag = 0;
	if (argc > 1 && ft_strncmp(argv[0], "echo", 4) == 0 && !argv[0][4]
		&& ft_strncmp(argv[1], "-n", 2) == 0 && !argv[1][2])
		echo(argv, 2);
	else if (argc >= 1 && ft_strncmp(argv[0], "echo", 4) == 0 && !argv[0][4])
		echo(argv, 1);
	else if (argc == 1 && ft_strncmp(argv[0], "cd", 2) == 0 && !argv[0][2])
		cd(argc, argv[0]);
	else if (argc == 2 && ft_strncmp(argv[0], "cd", 2) == 0 && !argv[0][2])
		cd(argc, argv[1]);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0 && !argv[0][3])
		pwd(argc);
	else if (ft_strncmp(argv[0], "unset", 5) == 0 && !argv[0][5])
		unset(argv, &env->env);
	else
		flag = 1;
	return (flag);
}

int	init_shell(int argc, char **argv, char **envp, t_mini **data)
{
	int	flag;
	t_mini	*ada;
	if (!envp)
		printf("ok\n");
	flag = 0;
	ada = *data;
	printf("%s-> %d\n", ada->commands[0], 2);
	flag += fork_actions(argc, argv, flag, data);
	printf("%s-> %d\n", ada->commands[0], 3);
	flag += other_actions(argc, argv, data);
	flag += export_action(argc, argv);
	if (flag == 3)
		return (1);
		// printf("Command not found: %s\n", argv[0]);
	return(0) ;
}
