/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:01:50 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/01/24 20:12:46 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **argv)
{
	char	**pos;

	if (argv == NULL)
		return ;
	pos = argv;
	while (*pos != NULL)
		free(*(pos++));
	free(argv);
}

int	ft_count_splits(char const *s, char c)
{
	int	count;
	int	first_letter;

	count = 0;
	first_letter = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (first_letter == 0)
			{
				count++;
				first_letter = 1;
			}
		}
		else
			first_letter = 0;
		s++;
	}
	return (count);
}

static int	ft_sub_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	**ft_free_mem(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i--]);
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		splits;
	int		i;
	int		len;
	char	**result;

	splits = ft_count_splits(s, c);
	result = (char **)malloc((splits + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < splits)
	{
		while (*s == c)
			s++;
		len = ft_sub_len(s, c);
		result[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!result[i])
			return (ft_free_mem(result, i));
		ft_strlcpy(result[i], s, len + 1);
		s = s + len;
		i++;
	}
	result[splits] = NULL;
	return (result);
}
