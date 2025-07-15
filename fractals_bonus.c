/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:24 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:55:25 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	calculate_iteration(t_program *program, t_complex z, t_complex c)
{
	int		iteration;
	double	temp;

	iteration = 0;
	while (iteration < program->fractal.max_iterations
		&& (z.re * z.re + z.im * z.im) < 4.0)
	{
		temp = z.re * z.re - z.im * z.im + c.re;
		if (program->fractal.type == BURNING_SHIP)
		{
			z.im = 2 * fabs(z.re * z.im) + c.im;
			z.re = fabs(temp);
		}
		else
		{
			z.im = 2 * z.re * z.im + c.im;
			z.re = temp;
		}
		iteration++;
	}
	return (iteration);
}

int	mandelbrot(t_program *program, int x, int y)
{
	t_complex	z;
	t_complex	c;
	t_view		*view;
	int			iteration;

	view = &program->fractal.view;
	get_complex(view, &c, x, y);
	z.re = 0;
	z.im = 0;
	iteration = calculate_iteration(program, z, c);
	return (iteration);
}

int	julia(t_program *program, int x, int y)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	t_view		*view;

	view = &program->fractal.view;
	c = program->fractal.julia_c;
	get_complex(view, &z, x, y);
	iteration = calculate_iteration(program, z, c);
	return (iteration);
}

int	burning_ship(t_program *program, int x, int y)
{
	t_complex	z;
	t_complex	c;
	t_view		*view;
	int			iteration;

	view = &program->fractal.view;
	get_complex(view, &c, x, y);
	z.re = 0;
	z.im = 0;
	iteration = calculate_iteration(program, z, c);
	return (iteration);
}
