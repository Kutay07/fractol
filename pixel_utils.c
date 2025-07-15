/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:54:07 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:54:08 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	pixel_put(t_program *program, int x, int y, int iteration)
{
	char	*dst;
	int		color;

	color = 0;
	color = paint_pixel_one(program, iteration);
	dst = program->gfx.addr_ptr + (y * program->gfx.line_length
			+ x * (program->gfx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
