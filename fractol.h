/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/16 13:03:11 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx/mlx.h"
// # include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 500
# define HEIGHT 500
# define KEY_ESC 53
# define ON_MOUSE_LEFT 1
# define ON_MOUSE_RIGHT 2
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17
# define ON_KEYDOWN 2
# define ZOOMIN_MAX 0.0000000000001
# define ZOOMOUT_MAX 16
# define W_UP 13
# define S_DOWN 1
# define D_RIGHT 2
# define A_LEFT 0
# define PLUS 24
# define MINUS 27

//color
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFFFF00
# define PURPLE 0x660066

typedef struct s_complex {
	double	x;
	double	y;
}				t_complex;
//x real, y imaginary

typedef struct s_img {
	void	*img_ptr;
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_fractal {
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;

	double	escape_value;
	size_t	iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;

int		ft_strncmp(char *s1, char *s2, int n);
int		ft_printf(const char *str, ...);
void	fractal_init(t_fractal *fractal);
void	fractal_render(t_fractal *fractal);
void	mandelbrot_or_julia(t_complex *z, t_complex *c, t_fractal *fractal);
double	map(double num, double new_min, double new_max, double old_max);
int		close_window(t_fractal *fractal);
int		key_hook(int keycode, t_fractal *fractal);
int		mouse_handler(int button, int x, int y, t_fractal *fractal);
int		julia_track(int x, int y, t_fractal *fractal);
t_complex burning_ship_next(t_complex z, t_complex c);

#endif