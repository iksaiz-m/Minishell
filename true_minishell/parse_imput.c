/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_imput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:14:38 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/04/03 20:25:18 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_redir(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] == '|' && s[i + 1] == '|')
			return (printf("syntax error: pipes\n"), 0);
		else if (s[i] == '>' && (s[i + 1] == '<' || (s[i + 1] == '>'
					&& s[i + 2] == '>' && s[i + 3] != '>')))
			return (printf("syntax error: redir\n"), 0);
		else if (s[i] == '<' && (s[i + 1] == '>' || (s[i + 1] == '<'
					&& s[i + 2] == '<' && s[i + 3] != '<')))
			return (printf("syntax error: redir\n"), 0);
		else if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>'
			&& s[i + 3] == '>')
			return (printf("syntax error: redir\n"), 0);
		else if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<'
			&& s[i + 3] == '<')
			return (printf("syntax error: redir\n"), 0);
		else if (s[i] == '<' && s[i + 1] == '|')
			return (printf("syntax error: redir\n"), 0);
		else if (s[i] == '>' && s[i + 1] == '|')
			return (printf("syntax error: redir\n"), 0);
		i++;
	}
	return (1);
}

int	check_wrong_pipes(char **commands)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (commands[i] != NULL)
	{
		if (!ft_strncmp(commands[i], "|", 1))
		{
			count++;
			if (i == 0 || commands[i + 1] == NULL || \
				!ft_strncmp(commands[i - 1], "<", 1) || \
				!ft_strncmp(commands[i - 1], "<<", 2) || \
				!ft_strncmp(commands[i - 1], ">", 1) || \
				!ft_strncmp(commands[i - 1], ">>", 2) || \
				!ft_strncmp(commands[i - 1], "|", 1))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_wrong_redir(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		if (commands[i + 1] && (!ft_strncmp(commands[i], "<", 1) || !ft_strncmp(commands[i], "<<", 2)
				|| !ft_strncmp(commands[i], ">", 1) || !ft_strncmp(commands[i], ">>", 2))
			&& (!ft_strncmp(commands[i + 1], "<", 1) || !ft_strncmp(commands[i + 1], "<<", 2)
				|| !ft_strncmp(commands[i + 1], ">", 1) || !ft_strncmp(commands[i + 1], ">>", 2)))
			return (0);
		i++;
	}
	if (i != 0 && (!ft_strncmp(commands[i - 1], "<", 1) || \
	!ft_strncmp(commands[i - 1], "<<", 2) || !ft_strncmp(commands[i - 1], ">", 1) || \
	!ft_strncmp(commands[i - 1], ">>", 2)))
		return (0);
	return (1);
}

int	detectopenquotes(char *line)
{
	int		i;
	int		d_quotes;
	int		s_quotes;

	i = 0;
	d_quotes = 0;
	s_quotes = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !s_quotes)
			d_quotes = !d_quotes;
		if (line[i] == '\'' && !d_quotes)
			s_quotes = !s_quotes;
		i++;
	}
	if (s_quotes || d_quotes)
		return (0);
	return (1);
}

//  int	detectquotes(char *line)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\"')
// 			return (1);
// 		if (line[i] == '\'')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	remove_quotes(char	*imput, int i)
{
	int		d_quotes;
	int		s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	while (imput[i])
	{
		if (imput[i] == '\"' && !s_quotes)
		{
			d_quotes = !d_quotes;
			ft_strlcpy(&imput[i], (const char *)&imput[i + 1],
				ft_strlen(&imput[i]));
			continue ;
		}
		else if (imput[i] == '\'' && !d_quotes)
		{
			s_quotes = !s_quotes;
			ft_strlcpy(&imput[i], (const char *)&imput[i + 1],
				ft_strlen(&imput[i]));
			continue ;
		}
		else
			i++;
	}
}
