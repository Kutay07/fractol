/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaypengwin <kutaypengwin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:35:15 by kutaypengwi       #+#    #+#             */
/*   Updated: 2025/04/06 12:35:33 by kutaypengwi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - 48);
	if ('.' == *s)
		++s;
	while (*s)
	{
		pow /= 10;
		fractional_part = fractional_part + (*s++ - 48) * pow;
	}
	return ((integer_part + fractional_part) * sign);
}
// Renk hesaplama fonksiyonu - farklı renk geçişleri için
int	create_color(double iterations, t_fractal *fractal)
{
	int r;
	int g;
	int b;
	double t;

	// İterasyon değerinin tam sayı ve kesirli kısmını ayır
	// int int_part = (int)iterations;
	// double frac_part = iterations - int_part;

	// Normalize edilmiş değer
	t = iterations / fractal->max_iterations;

	// Farklı renk şemalarına göre renk hesapla
	if (fractal->color.scheme == PSYCHEDELIC)
	{
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (fractal->color.scheme == BLUE_PURPLE)
	{
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		b = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	}
	else if (fractal->color.scheme == FIRE)
	{
		r = (int)(255 * t * t);
		g = (int)(255 * t * (1 - t));
		b = (int)(255 * (1 - t) * (1 - t));
	}
	else if (fractal->color.scheme == GRAYSCALE)
	{
		r = g = b = (int)(t * 255);
	}
	else // RAINBOW veya varsayılan
	{
		// double freq = 0.1;
		// // Kesirli kısmı da hesaba katarak daha smooth geçişler sağla
		// r = (int)(255 * sin(freq * iterations + 0));
		// g = (int)(255 * sin(freq * iterations + 2));
		// b = (int)(255 * sin(freq * iterations + 4));
		
		// // İki renk arasında karıştırma (color lerp) yaparak daha smooth geçişler sağla
		// if (frac_part > 0.0)
		// {
		// 	int r2 = (int)(255 * sin(freq * (int_part + 1) + 0));
		// 	int g2 = (int)(255 * sin(freq * (int_part + 1) + 2));
		// 	int b2 = (int)(255 * sin(freq * (int_part + 1) + 4));
			
		// 	r = (int)((1 - frac_part) * r + frac_part * r2);
		// 	g = (int)((1 - frac_part) * g + frac_part * g2);
		// 	b = (int)((1 - frac_part) * b + frac_part * b2);
		// }
	}
	
	// Baz renk ile modifiye et
	// r = (r + ((fractal->color.base_color >> 16) & 0xFF)) / 2;
	// g = (g + ((fractal->color.base_color >> 8) & 0xFF)) / 2;
	// b = (b + (fractal->color.base_color & 0xFF)) / 2;
	
	// RGB renk değerlerini sınırla (0-255 arası)
	r = (r > 255) ? 255 : (r < 0) ? 0 : r;
	g = (g > 255) ? 255 : (g < 0) ? 0 : g;
	b = (b > 255) ? 255 : (b < 0) ? 0 : b;
	
	return ((r << 16) | (g << 8) | b);
}

// Mouse olayları için hook fonksiyonu
int	mouse_hook(int button, int x, int y, t_program *program)
{
	double	zoom_factor;
	t_view	*view;

	view = &program->fractal.view;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		// Yakınlaştırma/uzaklaştırma faktörü
		zoom_factor = (button == SCROLL_UP) ? 1.2 : 0.8;
		
		// Mouse pozisyonunu karmaşık düzlem koordinatlarına dönüştür
		double mouse_re = ((x / (double)program->width) * 4 - 2) / view->zoom + view->offset_x;
		double mouse_im = ((y / (double)program->height) * 4 - 2) / view->zoom + view->offset_y;
		
		// Zoom uygulamasından önce eski zoom değerini kaydet
		double old_zoom = view->zoom;

		// Zoom'u güncelle
		view->zoom *= zoom_factor;

		// Zoom seviyesine göre iterasyon sayısını ayarla
		// program->fractal.max_iterations = 100 + (int)(50 * log10(view->zoom));
		program->fractal.max_iterations = 100 + (int)(50 * log10(view->zoom));
		// if (program->fractal.max_iterations < 100)
		// 	program->fractal.max_iterations = 100;

		// Mouse pozisyonunu merkez olarak kabul ederek offset değerlerini güncelle
		view->offset_x = mouse_re - ((mouse_re - view->offset_x) * old_zoom / view->zoom);
		view->offset_y = mouse_im - ((mouse_im - view->offset_y) * old_zoom / view->zoom);
		
		// Yeni görüntüyü hesapla ve çiz
		calculate_fractal(program);
	}
	return (0);
}

// Klavye tuşlarıyla renk değiştirme fonksiyonu
void change_color(int key, t_fractal *fractal)
{
	// Renk şemasını değiştir
	if (key == P)
	{
		fractal->color.scheme = (fractal->color.scheme + 1) % 5; // 5 farklı renk şeması
		return;
	}

	// Baz renk değerini modifiye et
	if (key == R) // R tuşu - kırmızıyı artır
		fractal->color.base_color += 0x100000;
	else if (key == G) // G tuşu - yeşili artır
		fractal->color.base_color += 0x001000;
	else if (key == B) // B tuşu - maviyi artır
		fractal->color.base_color += 0x000010;
	else if (key == F) // F tuşu - kırmızıyı azalt
		fractal->color.base_color -= 0x100000;
	else if (key == V) // V tuşu - yeşili azalt
		fractal->color.base_color -= 0x001000;
	else if (key == N) // N tuşu - maviyi azalt
		fractal->color.base_color -= 0x000010;
}

// Klavye olayları için hook fonksiyonu
int	key_hook(int keycode, t_program *program)
{
	t_view	*view;

	view = &program->fractal.view;

	if (keycode == ESC) // ESC tuşu - çıkış
	{
		mlx_destroy_window(program->gfx.mlx, program->gfx.window);
		exit(0);
	}
	else if (keycode == UP) // Yukarı ok tuşu - yukarı kaydır
		view->offset_y -= 0.1 / view->zoom;
	else if (keycode == DOWN) // Aşağı ok tuşu - aşağı kaydır
		view->offset_y += 0.1 / view->zoom;
	else if (keycode == LEFT) // Sol ok tuşu - sola kaydır
		view->offset_x -= 0.1 / view->zoom;
	else if (keycode == RIGHT) // Sağ ok tuşu - sağa kaydır
		view->offset_x += 0.1 / view->zoom;
	else if (keycode == R)
		init_fractal(&program->fractal); // R tuşu - fraktalı sıfırla
	// else if (keycode == P || keycode == R || keycode == G || keycode == B || 
	// 		keycode == F || keycode == V || keycode == N)
	// 	change_color(keycode, &program->fractal); // Renk değiştirme
	else if (keycode == M) // M tuşu - iterasyon sayısını artır
		program->fractal.max_iterations += 10;
	else if (keycode == C && program->fractal.max_iterations > 10) // C tuşu - iterasyon sayısını azalt
		program->fractal.max_iterations -= 10;

	calculate_fractal(program); // Değişiklikleri uygula ve yeniden çiz
	return (0);
}

// Piksel çizme fonksiyonu
void	pixel_put(t_program *program, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < program->width && y >= 0 && y < program->height)
	{
		dst = program->gfx.addr_ptr + (y * program->gfx.line_length + 
				x * (program->gfx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// Mandelbrot fraktalı hesaplama
double mandelbrot(t_program *program, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		x_temp;
	int			iterations;
	t_view		*view;
	double      smooth_value;

	view = &program->fractal.view;
	
	c.re = ((x / (double)program->width) * 4 - 2) / view->zoom + view->offset_x;
	c.im = ((y / (double)program->height) * 4 - 2) / view->zoom + view->offset_y;
	
	z.re = 0;
	z.im = 0;
	iterations = 0;
	
	while (iterations < program->fractal.max_iterations && 
			(z.re * z.re + z.im * z.im) < 4.0)
	{
		x_temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.re * z.im + c.im;
		z.re = x_temp;
		iterations++;
	}
	
	if (iterations < program->fractal.max_iterations)
	{
		// Smooth coloring için logaritmik skala
		smooth_value = iterations + 1 - log(log(z.re * z.re + z.im * z.im)) / log(2.0);
		return smooth_value;
	}
	
	return iterations;
}

// Tüm fraktalı hesapla ve çiz
int	calculate_fractal(t_program *program)
{
	int	x;
	int	y;
	double	iterations_value;

	y = 0;
	while (y < program->height)
	{
		x = 0;
		while (x < program->width)
		{
			// Fraktal tipine göre hesapla
			if (program->fractal.type == MANDELBROT)
				iterations_value = mandelbrot(program, x, y);
			// Diğer fraktaller için benzer güncelleme

			// Renklendirme
			// calculate_fractal içerisindeki çağrıyı güncelle
			if (iterations_value < program->fractal.max_iterations)
				pixel_put(program, x, y, create_color(iterations_value, &program->fractal));
			else
				pixel_put(program, x, y, 0x000000); // Küme içindeki noktalar siyah            
			x++;
		}
		y++;
	}
	
	// Görüntüyü pencereye yerleştir
	mlx_put_image_to_window(program->gfx.mlx, program->gfx.window, 
		program->gfx.img_ptr, 0, 0);
		
	// Bilgi panelini çiz
	draw_info_panel(program);
	
	return (0);
}

// Bilgi paneli çizme fonksiyonu
void	draw_info_panel(t_program *program)
{
	char	info[256];
	char	fractal_name[20];
	//char	color_scheme[20];
	
	// Fraktal tipine göre isim ata
	if (program->fractal.type == MANDELBROT)
		strcpy(fractal_name, "Mandelbrot");
	else if (program->fractal.type == JULIA)
		strcpy(fractal_name, "Julia");
	else if (program->fractal.type == BURNING_SHIP)
		strcpy(fractal_name, "Burning Ship");
	else if (program->fractal.type == TRICORN)
		strcpy(fractal_name, "Tricorn");
	else
		strcpy(fractal_name, "Celtic Mandelbar");
	
	// Renk şemasına göre isim ata
	// if (program->fractal.color.scheme == PSYCHEDELIC)
	// 	strcpy(color_scheme, "Psychedelic");
	// else if (program->fractal.color.scheme == BLUE_PURPLE)
	// 	strcpy(color_scheme, "Blue-Purple");
	// else if (program->fractal.color.scheme == FIRE)
	// 	strcpy(color_scheme, "Fire");
	// else if (program->fractal.color.scheme == GRAYSCALE)
	// 	strcpy(color_scheme, "Grayscale");
	// else
	// 	strcpy(color_scheme, "Rainbow");
	
	// Bilgi metinlerini oluştur
	sprintf(info, "Fractal: %s | Zoom: %.2f | Iterations: %d", 
		fractal_name, program->fractal.view.zoom, program->fractal.max_iterations);
	
	// Panel arkaplanı için koyu yarı-saydam dikdörtgen çiz
	int i, j;
	for (i = 0; i < 20; i++)
		for (j = 0; j < program->width; j++)
			pixel_put(program, j, i, 0x80000000);
	
	// Bilgi metnini çiz
	mlx_string_put(program->gfx.mlx, program->gfx.window, 10, 15, 0xFFFFFF, info);
	
	// Renk şeması bilgisini çiz
	// sprintf(info, "Color Scheme: %s | Base Color: #%06X", 
	// 	color_scheme, program->fractal.color.base_color & 0xFFFFFF);
	// mlx_string_put(program->gfx.mlx, program->gfx.window, 
	// 	program->width / 2, 15, 0xFFFFFF, info);
}

// Program başlatma
int	init_program(t_program *program, char *title)
{
	// MLX başlat
	program->gfx.mlx = mlx_init();
	if (!program->gfx.mlx)
		return (1);
	
	// Genişlik ve yükseklik ata
	program->width = SIZE;
	program->height = SIZE;
	program->title = title;

	// Pencere oluştur
	program->gfx.window = mlx_new_window(program->gfx.mlx, 
			program->width, program->height, program->title);
	if (!program->gfx.window)
		return (1);
	
	// Görüntü oluştur
	program->gfx.img_ptr = mlx_new_image(program->gfx.mlx, 
			program->width, program->height);
	if (!program->gfx.img_ptr)
		return (1);
	
	// Görüntü verilerine erişim
	program->gfx.addr_ptr = mlx_get_data_addr(program->gfx.img_ptr, 
			&program->gfx.bits_per_pixel, &program->gfx.line_length, 
			&program->gfx.endian);
	
	return (0);
}

// Fraktal başlatma
void	init_fractal(t_fractal *fractal)
{
	// fractal->type = type;
	fractal->max_iterations = 100;
	fractal->view.offset_x = 0.0;
	fractal->view.offset_y = 0.0;
	fractal->view.zoom = 1.0;
	fractal->color.base_color = 0xFFFFFF;
	fractal->color.scheme = PSYCHEDELIC; // Varsayılan renk şeması
	fractal->is_julia_lock = false;

	// Julia için varsayılan c değeri
	// if (type == JULIA)
	// {
	// 	fractal->julia_c.re = julia_c->re;
	// 	fractal->julia_c.im = julia_c->im;
	// }
	// else
	// {
	// 	fractal->julia_c.re = -0.7;
	// 	fractal->julia_c.im = 0.27015;
	// }
}

t_fractal_type  get_fractal_type(char *type_str)
{
	if (strcmp(type_str, "mandelbrot") == 0)
		return MANDELBROT;
	else if (strcmp(type_str, "julia") == 0)
		return JULIA;
	else if (strcmp(type_str, "burning_ship") == 0)
		return BURNING_SHIP;
	else if (strcmp(type_str, "tricorn") == 0)
		return TRICORN;
	else if (strcmp(type_str, "celtic_mandelbar") == 0)
		return CELTIC_MANDELBAR;
	else
		return INVALID_TYPE;
}
// Pencere kapatma fonksiyonu
int	close_window(t_program *program)
{
	mlx_destroy_window(program->gfx.mlx, program->gfx.window);
	exit(0);
	return (0);
}

// Ana program
int check_arguments(int argc, char **argv, t_fractal_type *fractal_type, t_complex *julia_c)
{
	if (argc < 2 || argc > 4)
		return (1);
	*fractal_type = get_fractal_type(argv[1]);
	if (*fractal_type == INVALID_TYPE)
		return (1);
	if (*fractal_type == JULIA)
	{
		julia_c->re = atodbl(argv[2]);
		julia_c->im = atodbl(argv[3]);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_program	program;
	int			flag;

	flag = check_arguments(argc, argv, &program.fractal.type, &program.fractal.julia_c);
	if (flag)
	{
		ft_putstr_fd("Usage: ./fractol <fractal_type> [julia_c]\n", 1);
		ft_putstr_fd("Available fractals: mandelbrot, julia, burning_ship, tricorn, celtic_mandelbar\n", 1);
		return (1);
	}
	flag = init_program(&program, "Fractol Project");
	if (flag)
	{
		ft_putstr_fd("Error: Program initialization failed\n", 1);
		return (1);
	}

	// Fraktal başlat
	init_fractal(&program.fractal);

	// Fraktalı hesapla ve çiz
	calculate_fractal(&program);

	// Mouse ve klavye olayları için hook fonksiyonlarını ayarla
	mlx_mouse_hook(program.gfx.window, mouse_hook, &program);
	mlx_key_hook(program.gfx.window, key_hook, &program);
	
	// Pencere X (kapat) tuşu için hook ayarla
	mlx_hook(program.gfx.window, 17, 0, close_window, &program);
	
	// MLX olaylarını bekle
	mlx_loop(program.gfx.mlx);
	
	return (0);
}
