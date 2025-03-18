/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_full_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:40:29 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/18 10:40:30 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) || \
	!ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6) || \
	!ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3) || \
	!ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

/*char	*set_full_path(t_node *node)
	char	*path;

    path = ft_strjoin("/usr/bin/", node->full_cmd[0]);
    if (access(path, X_OK) == 0)
        return (path);
}*/
char	*find_env_var(t_prompt **env_var, char *name)
{
	t_prompt	*current;

	current = *env_var;
	while (current)
	{
		if (!ft_strncmp(current->envp, name, 5))
			return (current->envp);
		current = current->next;
	}
	return (NULL);
}


char	**set_bin_path(t_mini *data)
{
	char	*path;
	char	**bin_path;

	path = find_env_var(&(data->env), "PATH=");
	path = ft_strdup(path + 5);
	if (path)
		return(bin_path = ft_split(path, ':'));
	else
		return(bin_path = NULL);
}

char	*set_full_path(t_node *node, char **bin_path)
{
	char	*path;
	int		i;

	i = 0;

    if (access(node->full_cmd[0], X_OK) == 0)
        return (node->full_cmd[0]);
	else if (bin_path && node->full_cmd && !is_builtin(node->full_cmd[0]))
	{
		while (bin_path[i] != NULL)
		{
			path = ft_strjoin(ft_strjoin(bin_path[i], "/"), node->full_cmd[0]);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			i++;
		}
		return (ft_strdup(node->full_cmd[0]));
	}
	return (NULL);
}

int	is_redirection(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, "<", 1) || \
	!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

int	count_cmd(char **commands)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (commands[i] != NULL)
	{
		if (is_redirection(commands[i]))
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

char	**set_full_cmd(char **commands, int i, int cmd)
{
	char	**full_cmd;

	cmd = count_cmd(commands);
	i = 0;
	if (cmd > 0)
		full_cmd = malloc(sizeof(char *) * (cmd + 1));
	else
		return (NULL);
	if (!full_cmd)
		return (NULL);
	cmd = 0;
	while (commands[i] != NULL)
	{
		if (is_redirection(commands[i]))
			i++;
		else
			full_cmd[cmd++] = commands[i];
		i++;
	}
	full_cmd[cmd] = NULL;
	return (full_cmd);
}
