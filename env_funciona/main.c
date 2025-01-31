/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/01/30 10:42:30 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_user(void)
{
	char	*pwd;
	char	*username;

	pwd = getcwd(NULL, 0);
	username = getenv("USER");
	printf("\033[37;44m%s\033[0m", username);
	printf("\033[32m %s\033[0m\n", pwd);
	return ;
}

void	enter(char *line, char **envp)
{
	char	**commands;
	int		splits;

	add_history(line);
	commands = ft_split(line, ' ');
	splits = ft_count_splits(line, ' ');
	init_shell(splits, commands, envp);
	free_split(commands);
}

int	exist(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line [i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	char	*line;

	while (argc && argv)
	{
		ft_print_user();
		line = readline(" > ");
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
		{
			free(line);
			break ;
		}
		if (exist(line))
			enter (line, envp);

		free (line);
	}
	printf("\033[31mFin.\033[0m\n");
	return (0);
}
