/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:00:22 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/04/12 19:12:48 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z')
		&& (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}

t_prompt	*ft_lstlast(t_prompt *lst)
{
	t_prompt	*last;
	t_prompt	*first;
	int		i;
	int		t;

	i = 0;
	first = lst;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	t = i - 1;
	while (t > 0)
	{
		t--;
		first = first->next;
	}
	last = first;
	return (last);
}

void	ft_lstadd_back(t_prompt **lst, t_prompt *new)
{
	t_prompt	*temporal;

	temporal = ft_lstlast(*lst);
	if (!temporal)
		*lst = new;
	else
		temporal->next = new;
}

int	ft_is_equal_simbol(char *argv)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			x = 1;
		i++;
	}
	return (x);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' || i == n - 1)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	a = (unsigned char *) dst;
	b = (unsigned char *) src;
	if (!a && !b)
		return (dst);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joinstring;
	size_t	i;
	size_t	k;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	joinstring = (char *)malloc((i + k + 1) * sizeof(char));
	if (!joinstring)
		return (NULL);
	ft_memcpy(joinstring, s1, i);
	ft_memcpy(joinstring + i, s2, k);
	joinstring[i + k] = '\0';
	return (joinstring);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	str = (char *)malloc (sizeof (char) * (i + 1));
	if (str)
	{
		while (j < i)
		{
			str[j] = s1[j];
			j++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

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


