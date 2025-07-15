/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:29 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:55:30 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

t_complex	get_complex(t_view *view, t_complex *c, int x, int y)
{
	double	scale;

	scale = (1.0 / (0.3 * view->zoom * SIZE));
	c->re = (x - SIZE / 2.0) * scale + view->offset_x;
	c->im = (y - SIZE / 2.0) * scale + view->offset_y;
	return (*c);
}

static int	get_fractal_iteration(t_program *program, int x, int y)
{
	int	iteration;

	iteration = 0;
	if (program->fractal.type == MANDELBROT)
		iteration = mandelbrot(program, x, y);
	else if (program->fractal.type == JULIA)
		iteration = julia(program, x, y);
	else if (program->fractal.type == BURNING_SHIP)
		iteration = burning_ship(program, x, y);
	return (iteration);
}

int	calculate_fractal(t_program *program)
{
	int		x;
	int		y;
	int		iteration;

	iteration = 0;
	mlx_clear_window(program->gfx.mlx, program->gfx.window);
	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			iteration = get_fractal_iteration(program, x, y);
			pixel_put(program, x, y, iteration);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(program->gfx.mlx, program->gfx.window,
		program->gfx.img_ptr, 0, 0);
	return (0);
}

void	init_fractal(t_fractal *fractal)
{
	fractal->max_iterations = ITERATION;
	fractal->view.color = ONE;
	fractal->view.offset_x = 0.0;
	fractal->view.offset_y = 0.0;
	fractal->view.zoom = 1.0;
}
