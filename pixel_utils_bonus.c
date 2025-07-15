/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:06 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:55:07 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	paint_pixel_one(t_program *program, int iteration)
{
	int		rgb[4];
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
		color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	}
	return (color);
}

static int	paint_pixel_two(t_program *program, int iteration)
{
	int		rgb[4];
	int		color;
	double	t;

	if (iteration >= program->fractal.max_iterations)
		color = 0x000000;
	else
	{
		t = (double)iteration / program->fractal.max_iterations;
		rgb[0] = (int)(t * 255);
		rgb[1] = (int)(t * 255);
		rgb[2] = (int)(t * 255);
		color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	}
	return (color);
}

static int	paint_pixel_three(t_program *program, int iteration)
{
	double	t;
	int		color;

	if (iteration >= program->fractal.max_iterations)
		color = 0x000000;
	else
	{
		t = (double)iteration / program->fractal.max_iterations;
		color = (int)(t * 0xFFFFFF);
	}
	return (color);
}

void	pixel_put(t_program *program, int x, int y, int iteration)
{
	char	*dst;
	int		color;

	color = 0;
	if (program->fractal.view.color == ONE)
		color = paint_pixel_one(program, iteration);
	else if (program->fractal.view.color == TWO)
		color = paint_pixel_two(program, iteration);
	else if (program->fractal.view.color == THREE)
		color = paint_pixel_three(program, iteration);
	dst = program->gfx.addr_ptr + (y * program->gfx.line_length
			+ x * (program->gfx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
