/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:15:18 by kbatur            #+#    #+#             */
/*   Updated: 2024/11/15 14:39:27 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	k_strcat(char *dest, char *src, size_t index)
{
	size_t	i;
	size_t	j;

	i = index;
	j = 0;
	while (src && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	i = k_strcat(ret, (char *)s1, i);
	i = k_strcat(ret, (char *)s2, i);
	return (ret);
}
