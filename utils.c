/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaypengwin <kutaypengwin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:12:52 by kutaypengwi       #+#    #+#             */
/*   Updated: 2025/04/06 21:36:48 by kutaypengwi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_manual(int EXIT_TYPE, char *text)
{
	ft_putstr_fd("Usage: ./fractol <fractal_type> [julia_c]\n", 1);
	ft_putstr_fd("Available fractals: mandelbrot, julia\n", 1);
	ft_putstr_fd("For Julia fractal, provide c value as well.\n", 1);
	ft_putstr_fd("Example: ./fractol julia -0.7 0.27015\n\n", 1);
	if (text && EXIT_TYPE == EXIT_FAILURE)
		perror(text);
	exit(EXIT_TYPE);
}

double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - 48);
	if ('.' == *s)
		++s;
	while (*s)
	{
		pow /= 10;
		fractional_part = fractional_part + (*s++ - 48) * pow;
	}
	return ((integer_part + fractional_part) * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] && s2[index])
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

int	mouse_hook(int button, int x, int y, t_program *program)
{
	double	zoom_factor;
	t_view	*view;
	double	mouse_re;
	double	mouse_im;
	double	old_zoom;

	view = &program->fractal.view;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		zoom_factor = 0.8;
		if (button == SCROLL_UP)
			zoom_factor = 1.2;
		mouse_re = ((x / (double)SIZE) * 4 - 2) / view->zoom + view->offset_x;
		mouse_im = ((y / (double)SIZE) * 4 - 2) / view->zoom + view->offset_y;
		old_zoom = view->zoom;
		view->zoom *= zoom_factor;
		program->fractal.max_iterations = MAX_ITERATIONS
			+ (int)(50 * log10(view->zoom));
		view->offset_x = mouse_re - ((mouse_re - view->offset_x)
				* old_zoom / view->zoom);
		view->offset_y = mouse_im - ((mouse_im - view->offset_y)
				* old_zoom / view->zoom);
		calculate_fractal(program);
	}
	return (0);
}

int	key_hook(int keycode, t_program *program)
{
	t_view	*view;

	view = &program->fractal.view;
	if (keycode == ESC)
		close_window(program);
	else if (keycode == UP || keycode == DOWN
		|| keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == UP)
			view->offset_y -= 0.1 / view->zoom;
		else if (keycode == DOWN)
			view->offset_y += 0.1 / view->zoom;
		else if (keycode == LEFT)
			view->offset_x -= 0.1 / view->zoom;
		else if (keycode == RIGHT)
			view->offset_x += 0.1 / view->zoom;
	}
	else if (keycode == R)
		init_fractal(&program->fractal);
	calculate_fractal(program);
	return (0);
}
