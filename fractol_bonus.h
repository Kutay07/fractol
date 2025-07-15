/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:55:20 by kbatur            #+#    #+#             */
/*   Updated: 2025/06/29 19:26:36 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# define SIZE 900
# define ITERATION 500
# define JULIA_C_RE -0.75
# define JULIA_C_IM 0.11
# define MANDELBROT_NAME "mandelbrot"
# define JULIA_NAME "julia"
# define BURNING_SHIP_NAME "burning_ship"

typedef enum e_color_scheme
{
	ONE = 0,
	TWO = 1,
	THREE = 2,
}	t_color_scheme;

enum e_keys
{
	ESC = 65307,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65363,
	LEFT = 65361,
	R = 114,
	C = 99,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
};

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP,
}	t_fractal_type;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_view
{
	double			offset_x;
	double			offset_y;
	double			zoom;
	t_color_scheme	color;
}	t_view;

typedef struct s_graphics
{
	void	*mlx;
	void	*window;
	void	*img_ptr;
	char	*addr_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_graphics;

typedef struct s_fractal
{
	t_fractal_type	type;
	int				max_iterations;
	t_view			view;
	t_complex		julia_c;
}	t_fractal;

typedef struct s_program
{
	t_graphics	gfx;
	t_fractal	fractal;
}	t_program;

int			ft_strcmp(const char *s1, const char *s2);
int			set_julia(t_program *program, int argc, char **argv);
void		init_program(t_program *program, char *title);
void		init_fractal(t_fractal *fractal);
int			calculate_fractal(t_program *program);
int			key_hook(int keycode, t_program *program);
int			mouse_hook(int button, int x, int y, t_program *program);
void		exit_manual(int EXIT_TYPE, char *text);
int			close_window(t_program *program);
void		pixel_put(t_program *program, int x, int y, int iteration);
t_complex	get_complex(t_view *view, t_complex *c, int x, int y);
int			julia(t_program *program, int x, int y);
int			mandelbrot(t_program *program, int x, int y);
int			burning_ship(t_program *program, int x, int y);

#endif
