/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/06 21:54:48 by iksaiz-m         ###   ########.fr       */
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

void	enter(char *line, char **envp, t_mini **data)
{
	// char	**commands;
	// int		splits;
	t_mini *adddata;

	adddata = NULL;
	adddata = malloc(sizeof (struct s_mini));
	add_history(line);
	adddata->envp = envp;
	adddata->full_cmd = ft_split(line, ' ');
	// commands = ft_split(line, ' ');
	adddata->splits = ft_count_splits(line, ' ');
	// splits = ft_count_splits(line, ' ');
	// init_shell(splits, commands, envp);
	*data = adddata;
	// init_shell(adddata->splits, adddata->full_cmd, adddata->envp);
	// free_split(commands);
	// free_split(adddata->full_cmd);
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
	t_mini	*data;

	data = NULL;
	while (argc && argv)
	{
		ft_print_user();
		line = readline(" > ");
		if (exist(line) == 0)
			write(1, "\0", 1);
		// if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
		// {
		// 	free(line);
		// 	break ;
		// }
		if (exist(line))
			enter(line, envp, &data);
		if (ft_exit(data))
		{
			free(line);
			break ;
		}
		free (line);
	}
	printf("\033[31mFin.\033[0m\n");
	return (0);
}
/*char c;
  char t;
  
  t = '\''; un character es comilla simple sin que te pete
  c = '\"'; un character es comillas doble sin que te pete */
