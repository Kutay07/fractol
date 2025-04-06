/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaypengwin <kutaypengwin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:56:56 by kutaypengwi       #+#    #+#             */
/*   Updated: 2025/04/06 21:50:34 by kutaypengwi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
#include <stdlib.h>
#include <stdio.h>

# define SIZE 500
# define MAX_ITERATIONS 200
# define JULIA_C_RE -0.75
# define JULIA_C_IM 0.11

/*
./fractol julia -0.7 0.27015 (Klasik "Dendrit" şekli)
./fractol julia -0.8 0.156 (Spiral formları)
./fractol julia -0.4 0.6 (Daha kaotik bir görüntü)
./fractol julia 0.285 0.01 (Ejderha şekli)
./fractol julia -0.835 -0.2321 (Tavuskuşu tüyüne benzer)
./fractol julia -0.75 0.11 (Spiral ve döngüler)
./fractol julia 0.355 0.355 (Küçük adacıklar)
./fractol julia 0 -0.8 (Yin-yang benzeri)
*/

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA,
} t_fractal_type;

# define MANDELBROT_NAME "mandelbrot"
# define JULIA_NAME "julia"

enum e_keys
{
	ESC = 65307,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65363,
	LEFT = 65361,
	R = 114,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
};

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_view
{
	double	offset_x;
	double	offset_y;
	double	zoom;
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
	int			width;
	int			height;
	char		*title;
}	t_program;

void	init_program(t_program *program, char *title);
void	init_fractal(t_fractal *fractal);
void	colored_pixel_put(t_program *program, int x, int y, int color);
int		calculate_fractal(t_program *program);
int		mandelbrot(t_program *program, int x, int y);
int		julia(t_program *program, int x, int y);
int		key_hook(int keycode, t_program *program);
int		mouse_hook(int button, int x, int y, t_program *program);
int		check_arguments(t_program *program,int argc, char **argv);
void	exit_manual(int EXIT_TYPE, char *text);
int		close_window(t_program *program);
int		ft_strcmp(const char *s1, const char *s2);
double	atodbl(char *s);
#endif
