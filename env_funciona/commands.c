/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:12:02 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/26 17:15:59 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *clean_command(char *str)
{
    if (!str)
        return (NULL);
    if (strncmp(str, "/usr/bin/", 9) == 0)
        return (strdup(str + 9));
    if (strncmp(str, "/bin/", 5) == 0)
        return (strdup(str + 5));
    return (strdup(str));
}

void	not_builtin_command(t_mini **data)
{
//	int	i;
	t_mini *current = *data;
	pid_t	pid;
	char	*path;
  char    *little;
//	int		i;

//	i = 0;
    little = clean_command(current->commands[0]);
	path = ft_strjoin("/usr/bin/", little);
	printf("Que coño es path : %s\n", path);
	free(little);
	if (current->commands[0])
	{
		pid = fork();
		if (pid == 0)
		{
			execv(path, &current->commands[0]);
            //execv(path, current->commands);
			exit(0);
		}
		wait(NULL);
	}
	free(path);
}
/*i = 0;
	while (current->commands[i])
	{
		printf("%i: %s\n", i, current->commands[i]);
		i++;
	}*/