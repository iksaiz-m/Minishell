/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_imput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:14:38 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/02/13 19:52:21 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsequotes(t_mini *data)
{
	int		d_quotes;
	int		s_quotes;
	int		i;
	int		t;

	d_quotes = 0;
	s_quotes = 0;
	t = 0;
	i = 0;
	while (data->commands[i])
	{
		while (data->commands[i][t])
		{
			if (data->commands[i][t] == '\"' && !s_quotes)
				d_quotes = !d_quotes;
			else if (data->commands[i][t] == '\'' && !d_quotes)
				s_quotes = !s_quotes;
			t++;
		}
		t = 0;
		i++;
	}
	if (s_quotes || d_quotes)
		return (0);
	return (1);
}

void	remove_quotes(char	*imput)
{
	int		i;
	int		d_quotes;
	int		s_quotes;

	i = 0;
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
		i++;
	}
}
