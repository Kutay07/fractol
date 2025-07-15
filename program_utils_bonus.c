/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:00 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:55:01 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	init_program(t_program *program, char *title)
{
	program->gfx.mlx = mlx_init();
	if (!program->gfx.mlx)
		exit_manual(EXIT_FAILURE, "MLX failed!\n");
	program->gfx.window = mlx_new_window(program->gfx.mlx,
			SIZE, SIZE, title);
	program->gfx.img_ptr = mlx_new_image(program->gfx.mlx,
			SIZE, SIZE);
	if (!program->gfx.window || !program->gfx.img_ptr)
	{
		mlx_destroy_window(program->gfx.mlx, program->gfx.window);
		mlx_destroy_image(program->gfx.mlx, program->gfx.img_ptr);
		exit_manual(EXIT_FAILURE, "MLX failed!\n");
	}
	program->gfx.addr_ptr = mlx_get_data_addr(program->gfx.img_ptr,
			&program->gfx.bits_per_pixel, &program->gfx.line_length,
			&program->gfx.endian);
}

void	exit_manual(int EXIT_TYPE, char *text)
{
	int	size;

	size = 0;
	if (text)
	{
		while (text[size])
			size++;
		write(1, text, size);
	}
	write(1, "\nUsage:				./fractol <fractal_type> [julia_c]\n", 47);
	write(1, "Example:			./fractol julia -0.7 0.27015\n\n", 42);
	write(1, "Available fractals: mandelbrot, julia, burning_ship\n", 53);
	write(1, "For Julia fractal, provide c value as well.\n", 45);
	exit(EXIT_TYPE);
}
