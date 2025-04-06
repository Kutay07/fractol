/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:32:02 by kbatur            #+#    #+#             */
/*   Updated: 2024/11/13 12:08:17 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	index;

	ret = ft_strdup(s);
	if (ret && s && f)
	{
		index = 0;
		while (ret[index])
		{
			ret[index] = f(index, ret[index]);
			index++;
		}
	}
	return (ret);
}
