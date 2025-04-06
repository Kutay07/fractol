/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaypengwin <kutaypengwin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:53:22 by kutaypengwi       #+#    #+#             */
/*   Updated: 2025/04/06 21:47:48 by kutaypengwi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_program *program)
{
	mlx_destroy_image(program->gfx.mlx, program->gfx.img_ptr);
	mlx_destroy_window(program->gfx.mlx, program->gfx.window);
	exit(EXIT_SUCCESS);
}

void	init_program(t_program *program, char *title)
{
	program->gfx.mlx = mlx_init();
	if (!program->gfx.mlx)
		exit_manual(EXIT_FAILURE, "MLX failed");
	program->gfx.window = mlx_new_window(program->gfx.mlx,
			SIZE, SIZE, title);
	program->gfx.img_ptr = mlx_new_image(program->gfx.mlx,
			SIZE, SIZE);
	if (!program->gfx.window || !program->gfx.img_ptr)
	{
		mlx_destroy_window(program->gfx.mlx, program->gfx.window);
		mlx_destroy_image(program->gfx.mlx, program->gfx.img_ptr);
		exit_manual(EXIT_FAILURE, "MLX failed");
	}
	program->gfx.addr_ptr = mlx_get_data_addr(program->gfx.img_ptr,
			&program->gfx.bits_per_pixel, &program->gfx.line_length,
			&program->gfx.endian);
}

void	init_fractal(t_fractal *fractal)
{
	fractal->max_iterations = MAX_ITERATIONS;
	fractal->view.offset_x = 0.0;
	fractal->view.offset_y = 0.0;
	fractal->view.zoom = 1.0;
	fractal->julia_c.re = JULIA_C_RE;
	fractal->julia_c.im = JULIA_C_IM;
}

int	check_arguments(t_program *program, int argc, char **argv)
{
	if (argc == 2 || argc == 4)
	{
		if (ft_strcmp(argv[1], MANDELBROT_NAME) == 0)
			program->fractal.type = MANDELBROT;
		else if (ft_strcmp(argv[1], JULIA_NAME) == 0)
		{
			program->fractal.type = JULIA;
			if (argc == 4)
			{
				program->fractal.julia_c.re = atodbl(argv[2]);
				program->fractal.julia_c.im = atodbl(argv[3]);
			}
		}
		else
			exit_manual(EXIT_SUCCESS, NULL);
	}
	else
		exit_manual(EXIT_SUCCESS, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	int			flag;

	flag = check_arguments(&program, argc, argv);
	if (flag)
		exit_manual(EXIT_SUCCESS, NULL);
	init_program(&program, "Fractol Project");
	init_fractal(&program.fractal);
	calculate_fractal(&program);
	mlx_mouse_hook(program.gfx.window, mouse_hook, &program);
	mlx_key_hook(program.gfx.window, key_hook, &program);
	mlx_hook(program.gfx.window, 17, 0, close_window, &program);
	mlx_loop(program.gfx.mlx);
	return (0);
}
