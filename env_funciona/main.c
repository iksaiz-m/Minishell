/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/17 20:32:37 by iksaiz-m         ###   ########.fr       */
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
	return (prompt);
}

void	enter(t_mini *data)
{
	int	i;

	i = 0;
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	if (init_shell(data->splits, data->commands, data->env, &data))
		not_builtin_command(&data);
	free_split(data->commands);
	// free(data->splits);
}

void printaddata(t_prompt *adddata)
{
	printf("FUCKTHIS\n");
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
}

void	asignenvp(char **envp, t_prompt **data)
{
	t_prompt	*new;
	t_prompt	*last;
	char	**temp;
	int		i;

	temp = split_env(envp);
	if (!temp)
	{
        printf("Error: split_env devolvió NULL\n");
        return;
    }
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

void	unset(char **argv, t_prompt **data)
{
	int	i;
	t_prompt *unset;

	unset = *data;
	i = 1;
	printf("HOLA 6\n");
	while (argv[i])
	{
		remove_env(argv[i], &unset);
		i++;
	}
}



void	enterdata(char *line, t_mini *data)
{
	add_history(line);
	if (!detectopenquotes(line))
	{
		printf("syntax error: dquote\n");
		return ;
	}
	data->commands = ft_split(line, ' ');
	data->splits = ft_count_splits(line, ' ');
	ft_exit(data);
	enter(data);
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
void	init_data(t_mini **data, char **envp)
{
	t_mini	*addata;

	addata = malloc(sizeof (struct s_mini));
	if (!addata)
		return ;
	addata->env = NULL; //initialize structure
	asignenvp(envp, &addata->env); //asign env to structure
	*data = addata; //
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = NULL;
	print_logo();
	// signal(SIGUSR1, signal_received);
	// signal(SIGUSR2, signal_received);

	init_data(&data, envp); //Initialize env variables
	while (argc && argv)
	{
		prompt = ft_print_user();
		line = readline(prompt);
		free(prompt);
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
			enterdata(line, data);
	}
	return (0);
}
/*char c;
  char t;
  
  t = '\''; un character es comilla simple sin que te pete
  c = '\"'; un character es comillas doble sin que te pete */
