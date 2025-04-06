/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:58:08 by kbatur            #+#    #+#             */
/*   Updated: 2024/10/12 14:36:59 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	needle_len;

	index = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (ft_strlen(haystack) < len)
		len = ft_strlen(haystack);
	while (index + needle_len <= len)
	{
		if (ft_strncmp(&haystack[index], needle, needle_len) == 0)
			return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
