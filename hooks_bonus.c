/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:15 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 17:55:16 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	close_window(t_program *program)
{
	mlx_destroy_image(program->gfx.mlx, program->gfx.img_ptr);
	mlx_destroy_window(program->gfx.mlx, program->gfx.window);
	mlx_destroy_display(program->gfx.mlx);
	free(program->gfx.mlx);
	exit(EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_program *program)
{
	double		zoom_factor;
	t_view		*view;
	t_complex	mouse;
	double		old_zoom;

	view = &program->fractal.view;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		zoom_factor = 0.8;
		if (button == SCROLL_UP)
			zoom_factor = 1.2;
		get_complex(view, &mouse, x, y);
		old_zoom = view->zoom;
		view->zoom *= zoom_factor;
		program->fractal.max_iterations = ITERATION
			+ (int)(50 * log10(view->zoom));
		view->offset_x = mouse.re - ((mouse.re - view->offset_x)
				* old_zoom / view->zoom);
		view->offset_y = mouse.im - ((mouse.im - view->offset_y)
				* old_zoom / view->zoom);
		calculate_fractal(program);
	}
	return (0);
}

static void	arrow_moving(int keycode, t_view *view)
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

int	key_hook(int keycode, t_program *program)
{
	t_view	*view;

	view = &program->fractal.view;
	if (keycode == ESC)
		close_window(program);
	else if (keycode == UP || keycode == DOWN
		|| keycode == LEFT || keycode == RIGHT)
	{
		arrow_moving(keycode, view);
		calculate_fractal(program);
	}
	else if (keycode == R)
	{
		init_fractal(&program->fractal);
		calculate_fractal(program);
	}
	else if (keycode == C)
	{
		view->color = (view->color + 1) % 3;
		calculate_fractal(program);
	}
	return (0);
}
