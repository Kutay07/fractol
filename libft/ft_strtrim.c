/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:07:44 by kbatur            #+#    #+#             */
/*   Updated: 2024/11/13 12:17:09 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;

	if (!s1)
		return (ft_strdup(""));
	begin = 0;
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1) -1;
	while (end > begin && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, begin, end - begin + 1));
}
