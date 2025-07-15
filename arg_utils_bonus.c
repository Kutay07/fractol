/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:34 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 20:12:09 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static double	ft_atodbl(char *str)
{
	double	result[2];
	double	factor;
	int		sign;
	int		i;

	result[0] = 0.0;
	result[1] = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] != '.')
		result[0] = result[0] * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		factor = 0.1;
		while (str[i])
		{
			result[1] += (str[i++] - '0') * factor;
			factor *= 0.1;
		}
	}
	return (sign * (result[0] + result[1]));
}

static int	check_int(const char *s, int len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != '.')
			return (0);
		i++;
	}
	if (len == 0)
		return (0);
	i = 0;
	if (len == -1)
	{
		if (!s[i])
			return (0);
		len = 17;
	}
	while (s[i] && i < len)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_double(const char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		i++;
		sign++;
	}
	while (s[i++])
	{
		if (s[i] == '-' || s[i] == '+')
			return (0);
		else if (s[i] == '.')
		{
			if (check_int(&s[sign], i - sign) == 1
				&& check_int(&s[i + 1], -1) == 1)
				return (1);
			else
				return (0);
		}
	}
	i = check_int(&s[sign], -1);
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	index;

	index = 0;
	while (s1[index] && s2[index])
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

int	set_julia(t_program *program, int argc, char **argv)
{
	program->fractal.type = JULIA;
	program->fractal.julia_c.re = JULIA_C_RE;
	program->fractal.julia_c.im = JULIA_C_IM;
	if (argc == 4)
	{
		if (check_double(argv[2]) && check_double(argv[3]))
		{
			program->fractal.julia_c.re = ft_atodbl(argv[2]);
			program->fractal.julia_c.im = ft_atodbl(argv[3]);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}
