/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/12 22:19:12 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

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
	char	*userwithpwd;
	char	*prompt;
	char	*a;

	a = "->";
	pwd = getcwd(NULL, 0);
	username = getenv("USER");
	a = ft_strjoin(username, a);
	userwithpwd = ft_strjoin(username, pwd);
	prompt = ft_strjoin(userwithpwd, "-> ");
	free(a);
	free(pwd);
	free(userwithpwd);
	return (prompt);
}

int	ft_check_input(char *line)
{
	if (!detectopenquotes(line))
		return (g_status = 2, printf("syntax error: dquote\n"), 1);
	if (!check_pipe_redir(line, 0))
		return (g_status = 2, 1);
	if (line[0] == '<' || line[0] == '>' || (line[0] == '>' && line[1] == '>'))
		return (g_status = 2, 1);
	return (0);
}

int	ft_check_dolars(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_for_quotes(char c, int *single_q, int *double_q, int *j)
{
	if (c == '\"' && *single_q == 0)
	{
		*double_q = !*double_q;
		(*j)++;
		return (1);
	}
	else if (c == '\'' && *double_q == 0)
	{
		*single_q = !*single_q;
		(*j)++;
		return (1);
	}
	return (0);
}

char *ft_checkvar_value(char *var_value, t_prompt *env, int i)
{
	char *new_value;

	new_value = NULL;
	while(env)
	{
		if (ft_strncmp(var_value, env->envp, ft_strlen(var_value)) == 0
			&& env->envp[ft_strlen(var_value)] == '=')
		{
			i = ft_strlen(var_value) +1 ;
			new_value = env_split(env->envp, i);
			free(var_value);
			return (new_value);
		}
		env = env->next;
	}
	if ((var_value[0] == '$' || var_value[0] == '0'|| var_value[0] == '?')
		&& ft_strlen(var_value) == 1)
		new_value = ft_asign_rare_value(var_value);
	else
		return (ft_strdup("\"\""));
	return (new_value);
}

char *ft_get_var_value(char *line, int length, int *j)
{
	char *var_value;
	int	x;
	int i;

	x = 0;
	i = *j;
	var_value = ft_calloc(length + 1, (sizeof(char)));
	if (!var_value)
		return (NULL);
	while (length-- > 0)
	{
		i++;
		var_value[x] = line[i];
		x++;
	}
	return (var_value);
}

char *ft_reasign_command(char *var_value, char *commands, int *i, int vname_len)
{
	char	*new_command;
	int		new_len;

	(*i)++;
	new_command = NULL;
	if (var_value == NULL)
		return (new_command);
	new_len = ft_strlen(commands) - vname_len + ft_strlen(var_value);
	new_command = ft_calloc(new_len + 1, (sizeof(char)));
	if (!new_command)
		return (NULL);
	ft_strlcpy(new_command, commands, *i);
	ft_strlcpy(new_command + (*i -1), var_value, new_len +1);
	ft_strlcpy(new_command + (ft_strlen(var_value) + *i -1), commands + (*i -1) + vname_len,
		ft_strlen(commands) - (*i -1) - vname_len +1);
	*i = *i - 1;
	return (new_command);
}

char *ft_check_for_dolar_quotes(char *commands, t_prompt *env, int i)
{
	int s_quote;
	int d_quote;
	char *var_value;
	int x;

	s_quote = 0;
	d_quote = 0;
	x = 0;
	while (commands[i] != '\0')
	{
		if (ft_check_for_quotes(commands[i], &s_quote, &d_quote, &i) == 1)
				continue ;
		if (commands[i] == '$' && s_quote == 0)
			x = ft_check_dolar_length(commands, &i);
		if (x != 0 && commands[i])
		{
			var_value = ft_get_var_value(commands, x, &i);
			var_value = ft_checkvar_value(var_value, env, 0);
			if (ft_reasign_command(var_value, commands, &i, (x + 1)) != NULL)
				commands = ft_reasign_command(var_value, commands, &i, (x + 1));
			else if (ft_reasign_command(var_value, commands, &i, (x + 1)) == NULL)
				commands[i] = '\0';
			}
		i++;
		x = 0;
	}
	return (commands);
}

void	enterdata(char *line, t_mini *data)
{
	add_history(line);
	if (!ft_check_input(line))
	{
		set_bin_path(data);
		data->commands = ft_split(line, ' ');
		int i = 0;
		{
			while (data->commands[i])
			{
				if (ft_check_dolars(data->commands[i]) == 1)
					data->commands[i] = ft_check_for_dolar_quotes(data->commands[i], data->env, 0);
				i++;
			}
		}
		data->ft_count_pipes = ft_count_pipes(data->commands);
		data->splits = ft_count_splits(line, ' ');
		data->nbr_nodes = ft_count_pipes (data->commands) + 1;
		ft_exit (data, 0);
		if(!ft_prepare_nodes(data))
			ft_execute_commands(data);
	}
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

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	g_status = 130;
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	asignenvp(char **envp, t_prompt **data)
{
	t_prompt	*new;
	t_prompt	*last;
	int			i;

	new = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_prompt));
		if (!new)
			return ;
		new->envp = ft_strdup(envp[i]);
		new->next = NULL;
		if (last == NULL)
			*data = new;
		else
			last->next = new;
		last = new;
		i++;
	}
}

void	init_data(t_mini **data, char **envp)
{
	t_mini	*addata;

	addata = malloc(sizeof (struct s_mini));
	if (!addata)
		return ;
	addata->env = NULL;
	addata->execute_envp = envp;
	asignenvp(envp, &addata->env);
	*data = addata;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = NULL;
	print_logo();
	setup_signals();
	init_data(&data, envp);
	while (argc && argv)
	{
		prompt = ft_print_user();
		line = readline(prompt);
		free(prompt);
		if (!line)
			ft_exit (NULL, 1);
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
			enterdata(line, data);
		if (g_status == 512)
			g_status = 2;
		if (g_status == 256)
			g_status = 1;
	}
	return (0);
}
