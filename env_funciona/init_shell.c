/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:11:59 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/03/29 18:40:38 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lscopy(t_prompt **list, char *content)
{
	t_prompt	*new_list;
	t_prompt	*tmp;

	new_list = (t_prompt*)malloc(sizeof(t_prompt));
	new_list->envp = content;
	new_list->next = NULL;
	if (*list == NULL)
		*list = new_list;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_list;
	}
}

t_prompt	*dup_env(t_prompt *original_env)
{
	t_prompt	*env_dup;
	t_prompt	*temp;
	
	temp = original_env;
	// printaddata(original_env);
	env_dup = NULL;
	// while(temp)
	// {
	// 	printf("%s\n", temp->envp);
	// 	temp = temp->next;
	// }
	while (temp != NULL)
	{
		ft_lscopy(&env_dup,  temp->envp);
		temp = temp->next;
	}
	return (env_dup);
}

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z')
		&& (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}
int	ft_is_equal_simbol(char *argv)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			x = 1;
		i++;
	}
	return (x);
}

int check_env_name(char *argv, int x)
{
	int	i;
	char **var_name;

	i = 0;
	var_name = ft_split(argv, '=');
	x = ft_is_equal_simbol(argv);
	while (var_name[0][i])
	{
		if (!ft_isalpha(var_name[0][i]))
		{
			printf("not valid in this context:\n");
			free(var_name);
			return (-1);
		}
		i++;
	}
	if (x == 1 && !var_name[1])
		x = 2;
	return (x);
}

int	fork_actions(int argc, char **argv, int flag, t_prompt *env)
{
	int			i;
	int			x;
	t_prompt	*tmp;
	char		*true_env;

	i = 0;
	if (argc == 1 && ft_strncmp(argv[0], "env", 3) == 0 && !argv[0][3])
		printaddata(env);
	else if (ft_strncmp(argv[0], "export", 6) == 0 && !argv[0][6] && !argv[1])
	{
		tmp = dup_env(env);
		ft_lstsort(tmp, 1);
		printaddata(tmp);
		free(tmp);
	}
	else if ((ft_strncmp(argv[0], "export", 6) == 0 && !argv[0][6]) && argc > 1)
	{
		while(argv[i + 1])
		{
			x = check_env_name(argv[i + 1], 0);
			if (x == 0)
			{
				true_env = ft_strjoin(argv[i + 1], "=");
				asign_env_value(true_env, &env);
				free(true_env);
			}
			else if (x == -1)
				return (flag);
			else
				asign_env_value(argv[i + 1], &env);
			i++;
		}
	}
		// export(argv, env);
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

int	init_shell(int argc, char **argv, t_prompt *env, t_mini **data)
{
	int	flag;

	flag = 0;
	flag += fork_actions(argc, argv, flag, env);
	flag += other_actions(argc, argv, data);
	// flag += export_action(argc, argv);
	if (flag == 2)
		return (1);
	return(0) ;
}
