/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:40:47 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/09/12 17:42:05 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*b;

	b = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!b)
		return (NULL);
	ft_strlcpy(b, s1, ft_strlen(s1) + 1);
	return (b);
}
/*char	*ft_strndup(const char *s1, size_t n)
{
	char	*b;

	b = ft_calloc((n + 1), sizeof(char));
	if (!b)
		return (free(b), NULL);
	ft_strlcpy(b, s1, n + 1);
	return (b);
}*/
/*int main()
{
	char *a = "amigos";
	
	//printf("Original: %s\n", strdup(a));
	printf("ft: %s", ft_strdup(a));
	return (0);
}*/