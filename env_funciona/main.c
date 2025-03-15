/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/15 20:42:24 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_logo(void)
{
	printf(GREEN "\n==== Welcome to minishell by Ibon & Iker ====\n");
	printf("A minimal shell implementation | 42 School Project\n\n");
	printf(MAGENTA "███╗   ███╗██╗███╗   ██╗██╗██╗██╗██╗\n" \
			"████╗ ████║██║████╗  ██║██║██║██║██║\n" \
			"██╔████╔██║██║██╔██╗ ██║██║██║██║██║\n" \
			"██║╚██╔╝██║██║██║╚██╗██║██║██║██║██║\n" \
			"██║ ╚═╝ ██║██║██║ ╚████║██║██║██║██║\n" \
			"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝╚═╝╚═╝\n" \
			"                                      \n" RST);
}

char	*ft_print_user(void)
{
	char	*pwd;
	char	*username;
	char	*simbol;
	char	*userwithpwd;
	char	*prompt;

	pwd = getcwd(NULL, 0);
	username = getenv("USER");
	simbol = " \n> ";
	userwithpwd = ft_strjoin(username, pwd);
	prompt = ft_strjoin(userwithpwd, simbol);
	free(pwd);
	free(userwithpwd);
	// printf("\033[37;44m%s\033[0m", username);
	// printf("\033[32m %s\033[0m\n", pwd);
	return (prompt);
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
void	enter(t_mini *data)
{
	int	i;

	i = 0;
	// if (!parsequotes(data))
	// {
	// 	printf("syntax error: dquote\n");
	// 	return ;
	// }
	printf("%s-> %d\n", data->commands[0], 1);
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	if(init_shell(data->splits, data->commands, &data->env->envp, &data))
		not_builtin_command(&data);
	free_split(data->commands);
	free(data);
}

int	checklenght(t_prompt *stack)
{
	t_prompt	*tmp;
	int		i;

	i = 0;
	tmp = stack;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->envp);
		// i++;
		tmp = tmp->next;
	}
	return (i);
}

void printaddata(t_prompt *adddata)
{
	while (adddata)
	{
		printf("%s\n", adddata->envp);
		adddata = adddata->next;
	}
}

void	remove_env(char *argv, t_prompt **data)
{
	t_prompt	*tmp;
	t_prompt	*var;

	var = NULL;
	tmp = *data;
	printf("HOLA 7\n");

	while(tmp)
	{
		// Comparamos el valor de la variable de entorno con argv
		if (ft_strncmp(argv, tmp->envp, ft_strlen(argv)) == 0 
			&& tmp->envp[ft_strlen(argv)] == '=')
		{
			// Si estamos eliminando el primer nodo (cabeza de lista)
			if (var == NULL)
				*data = tmp->next;
			else
				var->next = tmp->next;
			// Liberamos el espacio de memoria de la variable de entorno y el nodo
			free(tmp->envp);
			free(tmp);
			return;  // Terminamos la función después de eliminar el nodo
		}
		// Continuamos recorriendo la lista
		var = tmp;
		tmp = tmp->next;
	}
		printf("HOLA 8\n");
}

void	asignenvp(char **envp, t_prompt **data)
{
	t_prompt	*new;
	t_prompt	*last;
	char	**temp;
	int		i;

	temp = split_env(envp);
	new = NULL;
	last = NULL;
	i = 0;
	while (temp[i])
	{
		new = malloc(sizeof(t_prompt));
		if (!new)
			return ;
		new->envp = strdup(temp[i]);
		new->next = NULL;
		if (last == NULL)
			*data = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	free(temp);
}

// void	remove_env(char *argv, t_prompt *data)
// {
// 	t_prompt	*tmp;
// 	t_prompt	*var;

// 	var = NULL;
// 	tmp = data;
	
// 	while(tmp)
// 	{
// 		if (ft_strncmp(argv, tmp->envp, ft_strlen(argv)) == 0 
// 			&& tmp->envp[0] == argv[0])
// 		{
// 			if (var == NULL)
// 				data = tmp->next;
// 			else
// 				var->next = tmp->next;
// 			return (free(tmp->envp), free(tmp));
// 			// break;
// 		}
// 			printf("HOLA");
// 		var = tmp;
// 		tmp = tmp->next;
// 	}

		// var = mini->env;
		// while (var)
		// {
		// 	if (!ft_strcmp(var->name, node->full_cmd[1])
		// 		&& ft_strcmp(node->full_cmd[1], "?"))
		// // 	{
		// 		if (prev == NULL)
		// 			mini->env = var->next;
		// 		else
		// 			prev->next = var->next;
		// 		return (free(var->content), free(var->name), free(var));
		// 	// }
		// 	prev = var;
		// 	var = var->next;

void	unset(char **argv, t_prompt **data)
{
	int	i;
	t_prompt *unset;

	unset = *data;
	i = 1;
	// char *join;
	printf("HOLA 6\n");
	while (argv[i])
	{
		remove_env(argv[i], &unset);
		// while (envp[i])
		// {
		// 	if (ft_strncmp(argv[i], envp[i], ft_strlen(argv[i])) == 0 && envp[i][0] == argv[i][0])
		// 		envp = unset_split(envp, i);
		// 	i++;
		// }
		// free(join);
		i++;
	}
	// printaddata(*data);
	// printf("\n");
	// printaddata(*data);
}



void	enterdata(char *line, t_mini **data)
{
	t_mini	*adddata;
	// char	**temp;

	add_history(line);
	if (!detectopenquotes(line))
	{
		printf("syntax error: dquote\n");
		return ;
	}
	adddata = malloc(sizeof (struct s_mini));
	if (!adddata)
		return ;
	// adddata->envp = envp;

	// while(envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// while(temp[i])
	// {
	// 	printf("%s\n", temp[i]);
	// 	i++;
	// }
	// adddata->envp = split_env(envp);
	// asignenvp(temp, &adddata->env);
	// checklenght(adddata);
	// printaddata(adddata);

	// if (detectopenquotes(line) == 1)
	// 	adddata->commands = ft_splitquotes(line, ' ', '\'', '\"');
	adddata->commands = ft_split(line, ' ');
	// adddata->splits = ft_count_splits(line, ' ');
	// adddata->splits = ft_num_word(line, ' ');
	adddata->splits = ft_count_splits(line, ' ');
	*data = adddata;
	ft_exit(*data);
	enter(*data);
}

int	exist(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *) b)[i] = (unsigned char) c;
		i++;
	}
	return (b);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = malloc(sizeof (struct s_mini));
	if (!data)
		return (0);
	print_logo();
	// signal(SIGUSR1, signal_received);
	// signal(SIGUSR2, signal_received);
	// ft_memset(data, 0, sizeof(data));
	asignenvp(envp, &data->env);
	while (argc && argv)
	{
		prompt = ft_print_user();
		line = readline(prompt);
		free(prompt);
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
		{
			printaddata(data->env);
			enterdata(line, &data);
		}
	}
	return (0);
}
/*char c;
  char t;
  
  t = '\''; un character es comilla simple sin que te pete
  c = '\"'; un character es comillas doble sin que te pete */
