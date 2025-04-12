/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:29:18 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/12 22:29:32 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char *)malloc(count * size);
	if (!result)
		return (NULL);
	while (i < count * size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

char	*env_split(char const *s, int start)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = start;
	while (s[start])
	{
		start++;
		i++;
	}
	result = ft_calloc(i + 1, (sizeof(char)));
	if (!result)
		return (NULL);
	i = 0;
	while (s[len])
	{
		result[i] = s[len];
		i++;
		len++;
	}
	return (result);
}

static size_t	getnums(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count += 1;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	nums;
	char	*str;

	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nums = getnums(n);
	str = ft_calloc(nums + 1, (sizeof(char)));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = (-1) * n;
		i++;
	}
	while (n)
	{
		str[--nums] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char *ft_asign_rare_value(char *var_value)
{
	char *new_value;
	int	pid;

	pid = 0;
	new_value = NULL;
	if (var_value[0] == '$')
	{
		pid = getpid();
		new_value = ft_itoa(pid);
	}
	else if (var_value[0] == '0')
		new_value = ft_strdup("Minishell");
	else if (var_value[0] == '?')
		new_value = ft_itoa(g_status);
	free(var_value);
	return (new_value);
}

int	ft_check_dolar_length(char *line, int *j)
{
	int length;
	int	i;

	length = 0;
	i = *j;
	while (line[i] &&  line [i] != '\"' && line [i] != '\'')
	{
		i++;
		if (line[i] == '?' || line[i] == '$' || line[i] == '0')
		{
			if (length == 0)
			{
				length++;
				break;
			}
			break;;
		}
		else if (!line[i] ||  line [i] == '\"' || line [i] == '\'')
			break;
		else
			length++;
	}
	return (length);
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

char *expam(char *commands, t_prompt *env, int i)
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
/*
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
}*/
