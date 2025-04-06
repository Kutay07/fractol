/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaypengwin <kutaypengwin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:25:05 by kutaypengwi       #+#    #+#             */
/*   Updated: 2025/04/06 21:43:33 by kutaypengwi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_program *program, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
	int			iteration;
	t_view		*view;

	view = &program->fractal.view;
	c.re = ((x / (double)SIZE) * 4 - 2) / view->zoom + view->offset_x;
	c.im = ((y / (double)SIZE) * 4 - 2) / view->zoom + view->offset_y;
	z.re = 0;
	z.im = 0;
	iteration = 0;
	while (iteration < program->fractal.max_iterations
		&& (z.re * z.re + z.im * z.im) < 4.0)
	{
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = temp;
		iteration++;
	}
	return (iteration);
}

int	julia(t_program *program, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
	int			iteration;
	t_view		*view;

	view = &program->fractal.view;
	c = program->fractal.julia_c;
	z.re = (x - SIZE / 2.0) / (0.3 * SIZE * view->zoom) + view->offset_x;
	z.im = (y - SIZE / 2.0) / (0.3 * SIZE * view->zoom) + view->offset_y;
	iteration = 0;
	while (iteration < program->fractal.max_iterations)
	{
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = temp;
		if (z.re * z.re + z.im * z.im > 4.0)
			break ;
		iteration++;
	}
	return (iteration);
}

int	calculate_fractal(t_program *program)
{
	int		x;
	int		y;
	int		iteration;

	mlx_clear_window(program->gfx.mlx, program->gfx.window);
	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			if (program->fractal.type == MANDELBROT)
				iteration = mandelbrot(program, x, y);
			else if (program->fractal.type == JULIA)
				iteration = julia(program, x, y);
			colored_pixel_put(program, x, y, iteration);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(program->gfx.mlx, program->gfx.window,
		program->gfx.img_ptr, 0, 0);
	return (0);
}

void	colored_pixel_put(t_program *program, int x, int y, int iteration)
{
	char	*dst;
	int		rgb[3];
	double	t;
	int		color;

	if (iteration >= program->fractal.max_iterations)
		color = 0x000000;
	else
	{
		t = (double)iteration / program->fractal.max_iterations;
		rgb[0] = (int)(9 * (1 - t) * t * t * t * 255);
		rgb[1] = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		rgb[2] = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		if (rgb[0] > 255)
			rgb[0] = 255;
		if (rgb[1] > 255)
			rgb[1] = 255;
		if (rgb[2] > 255)
			rgb[2] = 255;
		if (rgb[0] < 0)
			rgb[0] = 0;
		if (rgb[1] < 0)
			rgb[1] = 0;
		if (rgb[2] < 0)
			rgb[2] = 0;
		color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	}
	dst = program->gfx.addr_ptr + (y * program->gfx.line_length
			+ x * (program->gfx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
