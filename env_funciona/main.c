/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/13 19:58:53 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_print_user(void)
{
	char	*pwd;
	char	*username;
	char	*simbol;
	char	*userwithpwd;

	pwd = getcwd(NULL, 0);
	username = getenv("USER");
	simbol = " \n> ";
	userwithpwd = ft_strjoin(username, pwd);
	userwithpwd = ft_strjoin(userwithpwd, simbol);
	// printf("\033[37;44m%s\033[0m", username);
	// printf("\033[32m %s\033[0m\n", pwd);
	return (userwithpwd);
}

// void	enter(char *line, char **envp, t_mini **data)
// {
// 	char	**commands;
// 	int		splits;
// 	t_mini *adddata;

// 	// adddata = NULL;
// 	adddata = malloc(sizeof (struct s_mini));
// 	add_history(line);
// 	adddata->envp = envp;
// 	adddata->full_cmd = ft_split(line, ' ');
// 	commands = ft_split(line, ' ');
// 	adddata->splits = ft_count_splits(line, ' ');
// 	splits = ft_count_splits(line, ' ');
// 	init_shell(splits, commands, envp);
// 	*data = adddata;
// 	//init_shell(adddata->splits, adddata->full_cmd, adddata->envp);
// 	free_split(commands);
// 	//free_split(adddata->full_cmd);
// }
void	enterdata(char *line, char **envp, t_mini **data)
{
	t_mini	*adddata;

	adddata = malloc(sizeof (struct s_mini));
	if (!adddata)
		return ;
	add_history(line);
	adddata->envp = envp;
	adddata->commands = ft_split(line, ' ');
	adddata->splits = ft_count_splits(line, ' ');
	*data = adddata;
}

void	enter(t_mini *data)
{
	int	i;

	i = 0;
	if (!parsequotes(data))
	{
		printf("syntax error: dquote\n");
		return ;
	}
	while (data->commands[i])
		remove_quotes(data->commands[i++]);
	init_shell(data->splits, data->commands, data->envp);
	free_split(data->commands);
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = NULL;
	// signal(SIGUSR1, signal_received);
	// signal(SIGUSR2, signal_received);
	while (argc && argv)
	{
		prompt = ft_print_user();
		// printf("\033[37;44m%s\033[0m", getenv("USER"));
		// printf("\033[32m %s\033[0m\n", getcwd(NULL, 0));
		// printf("var home--->   %s\n", getenv("HOME"));
		line = readline(prompt);
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
			enterdata(line, envp, &data);
		// enter(line, envp, &data);
		if (ft_exit(data))
		{
			free(line);
			break ;
		}
		enter(data);
		// if (ft_exit(data))
		// {
		// 	free(line);
		// 	break ;
		// }
		//free (line);
	}
	printf("\033[31mFin.\033[0m\n");
	return (0);
}
/*char c;
  char t;
  
  t = '\''; un character es comilla simple sin que te pete
  c = '\"'; un character es comillas doble sin que te pete */
