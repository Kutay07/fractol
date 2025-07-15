/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:11 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:55:12 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	check_arguments(t_program *program, int argc, char **argv)
{
	if (argc == 2 || argc == 4)
	{
		if (ft_strcmp(argv[1], MANDELBROT_NAME) == 0 && argc == 2)
			program->fractal.type = MANDELBROT;
		else if (ft_strcmp(argv[1], BURNING_SHIP_NAME) == 0 && argc == 2)
			program->fractal.type = BURNING_SHIP;
		else if (ft_strcmp(argv[1], JULIA_NAME) == 0)
		{
			if (!set_julia(program, argc, argv))
				exit_manual(EXIT_SUCCESS, NULL);
		}
		else
			exit_manual(EXIT_SUCCESS, NULL);
	}
	else
		exit_manual(EXIT_SUCCESS, NULL);
}

int	main(int argc, char **argv)
{
	t_program	program;

	check_arguments(&program, argc, argv);
	init_program(&program, "Fractol Project");
	init_fractal(&program.fractal);
	calculate_fractal(&program);
	mlx_mouse_hook(program.gfx.window, mouse_hook, &program);
	mlx_key_hook(program.gfx.window, key_hook, &program);
	mlx_hook(program.gfx.window, 17, 0, close_window, &program);
	mlx_loop(program.gfx.mlx);
	return (0);
}
