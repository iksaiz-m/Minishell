/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/04/02 20:52:45 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	b;

	i = 0;
	result = 0;
	b = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			b = 1;
		i++;
	}
	while ((ft_isdigit(str[i])))
	{
		result = result * 10 +(str[i] - '0');
		i++;
	}
	if (b == 1)
		return (result * (-(1)));
	return (result);
}

int	check_exit_num(char *exit_number)
{
	int	i;

	i = 0;
	while(exit_number[i])
	{
		if (exit_number[i] == '-' || exit_number[i] == '+')
			i++;
		if (!ft_isdigit(exit_number[i]))
		{
			printf("bash: exit: %s: numeric argument required\n", exit_number);
			return (2);
		}
		else
		i++;
	}
	return (ft_atoi(exit_number));
}

int	ft_exit(t_mini *data, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		printf("\033[31mexit.\033[0m\n");
		exit(EXIT_SUCCESS);
	}
	if (data->splits <= 2)
	{
		if (ft_strncmp(data->commands[0], "exit", 4) == 0
			&& !data->commands[0][4])
		{
			if (data->splits == 2)
				g_status = check_exit_num(data->commands[1]);
			// printf("free %p\n", data->commands);
			// printf("\033[31mexit.\033[0m\n");
			printf("exit\n");
			free_split(data->commands);
			free(data);
			exit(g_status);
		}
	}
	return (0);
}

void ft_clean(t_mini *data)
{
	char *args[3];
	pid_t	pid;
	
	args[0] = "rm";
	args[1] = TEMP_FILE;
	args[2] = NULL;
	open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		g_status = execve("/bin/rm", args, data->execute_envp);
	}
	wait(NULL);
}
