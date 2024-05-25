/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/25 12:43:51 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KEY_ESC 53
#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 50

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	max_r;
	double	min_r;
	double	max_i;
	double	min_i;
	double	delta_r;
	double	delta_i;
} t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		pos_x;
	int		pos_y;
	int		radius;
	t_data	img;
}				t_vars;

void ft_my_mlx_pixel_put(t_data *data, int x, int y, int color) {
	char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int ft_pick_color(int iter) {
    if (iter == MAX_ITER)
        return 0; // マンデルブロ集合内部の点は黒色

    // 色成分を計算
    int g = (int)(100 + 127 * sin(iter * 0.03)); // 緑色成分
    int b = (int)(10 + 80 * cos(iter * 0.05));  // 青色成分
    int r = (int)(255 * (iter / (float)MAX_ITER)); // 反復回数が多いほど赤色を強くする

    return (r << 16) | (g << 8) | b;
}

int	ft_draw_mandelbrot(t_data *data) {
	double	x, y, tmp_r;
	int		iter;

	//画像の一ピクセルが複素平面上でどれだけの実部の範囲をカバーするか
	data->delta_r = (data->max_r - data->min_r) / (double)WIDTH;
	data->delta_i = (data->max_i - data->min_i) / (double)HEIGHT;
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			data->c_r = data->min_r + x * data->delta_r;
			data->c_i = data->min_i + y * data->delta_i;
			data->z_r = 0;
			data->z_i = 0;
			for (iter = 0; data->z_r * data->z_r + data->z_i * data->z_i <= 4 && iter < MAX_ITER; iter++) {
				tmp_r = data->z_r * data->z_r - data->z_i * data->z_i + data->c_r;
				data->z_i = 2 * data->z_r * data->z_i + data->c_i;
				data->z_r = tmp_r;
			}
			ft_my_mlx_pixel_put(data, x, y, ft_pick_color(iter));
		}
	}
	return 0;
}

int render_next_frame(void *param) {
	t_vars *vars = (t_vars *)param;
	ft_draw_mandelbrot(&vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return 0;
}

int main(void) {
	t_vars vars = {0};

	vars.mlx = mlx_init();
	if (!vars.mlx) {
		fprintf(stderr, "Error initializing MLX\n");
		return EXIT_FAILURE;
	}
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Mandelbrot");
	if (!vars.win) {
		fprintf(stderr, "Error creating window\n");
		return EXIT_FAILURE;
	}

	vars.img.max_r = 2.0;
	vars.img.min_r = -2.0;
	vars.img.max_i = 2.0;
	vars.img.min_i = -2.0;

	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

	return EXIT_SUCCESS;
}




// #include "./minilibx/mlx.h"
// #include <stdio.h>
// #include <stdlib.h> 
// #include <math.h>
// #define KEY_ESC 53
// #define WIDTH 800
// #define HEIGHT 600
// #define MAX_ITER 50

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	double	z_r;          // Zの実部
// 	double	z_i;          // Zの虚部
// 	double	c_r;          // Cの実部
// 	double	c_i;          // Cの虚部
// 	int		max_it;       // 最大繰り返し回数
// 	double	max_r;        // 実数部の最大値
// 	double	min_r;        // 実数部の最小値
// 	double	max_i;        // 虚数部の最大値
// 	double	min_i;        // 虚数部の最小値
// 	double	delta_r;      // 実数部の増分
// 	double	delta_i;      // 虚数部の増分
// } t_data;


// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// 	int		pos_x;
// 	int		pos_y;
// 	int		radius;
// 	t_data	img;
// }				t_vars;

// unsigned int ft_pick_color(int iter) {
// 	int r, g, b;

// 	if (iter == MAX_ITER)
// 		return ft_rgb_to_hex(0, 0, 0);

// 	r = (iter * 9) % 256;
// 	g = (iter * 9) % 256;
// 	b = (iter * 9) % 256;
	
// 	return ft_rgb_to_hex(r, g, b);
// }

// void ft_my_mlx_pixel_put(t_data *data, int x, int y, int color) {
// 	char *dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int	ft_draw_mandelbrot(t_data *data)
// {
// 	double	x;
// 	double	y;
// 	int		iter;
// 	double	tmp_r;

// 	data->delta_r = (data->max_r - data->min_r) / (double)WIDTH;
// 	data->delta_i = (data->max_i - data->min_i) / (double)HEIGHT;
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH) {
// 			data->c_r = data->min_r + x * data->delta_r;
// 			data->c_i = data->min_i + y * data->delta_i;
// 			data->z_r = 0;
// 			data->z_i = 0;
// 			iter = 0;
// 			while (pow(data->z_r, 2.0) + pow(data->z_i, 2.0) <= 4 && iter < data->max_it) {
// 				tmp_r = pow(data->z_r, 2.0) - pow(data->z_i, 2.0) + data->c_r;
// 				data->z_i = 2 * data->z_r * data->z_i + data->c_i;
// 				data->z_r = tmp_r;
// 				iter++;
// 			}
// 			ft_my_mlx_pixel_put(data, x, y, ft_pick_color(iter));
// 			x++;
// 		}
// 		y++;
// 	}
// 	return 0;
// }

// int render_next_frame(void *param)
// {
// 	t_vars *vars = (t_vars *)param;
// 	ft_draw_mandelbrot(&vars->img);
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
// 	return 0;
// }

// int key_hook(int keycode, t_vars *vars) {
// 	switch (keycode) {
// 		case 13: // W
// 			vars->pos_y -= 10;
// 			break;
// 		case 0: // A
// 			vars->pos_x -= 10;
// 			break;
// 		case 1: // S
// 			vars->pos_y += 10;
// 			break;
// 		case 2: // D
// 			vars->pos_x += 10;
// 			break;
// 		case 7: // キー 'x'
// 			vars->radius += 10;
// 			break;
// 		case 6: // キー 'z'
// 			vars->radius = (vars->radius > 5) ? vars->radius - 10 : 10;
// 			break;
// 	}
// 	return 0;
// }

// int main(void) {
// 	t_vars vars;

// 	vars.mlx = mlx_init();
// 	if (vars.mlx == NULL) {
// 		fprintf(stderr, "Error initializing MLX\n");
// 		return EXIT_FAILURE;
// 	}
// 	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Mandelbrot");
// 	if (vars.win == NULL) {
// 		fprintf(stderr, "Error creating window\n");
// 		return EXIT_FAILURE;
// 	}
// 	vars.pos_x = WIDTH / 2;
// 	vars.pos_y = HEIGHT / 2;
// 	vars.radius = 100;
// 	vars.img.max_it = MAX_ITER;
// 	vars.img.max_r = 2.0;
// 	vars.img.min_r = -2.0;
// 	vars.img.max_i = 2.0;
// 	vars.img.min_i = -2.0;

// 	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
// 	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

// 	mlx_key_hook(vars.win, key_hook, &vars);
// 	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
// 	mlx_loop(vars.mlx);

// 	return EXIT_SUCCESS;
// }





// /***************************
// #include "./minilibx/mlx.h"
// #include <stdio.h>
// #include <stdlib.h> 
// #include <math.h>
// #define KEY_ESC 53
// #define WIDTH 800
// #define HEIGHT 600
// #define MAX_ITER 100

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	double	z_r;          // Zの実部
// 	double	z_i;          // Zの虚部
// 	double	c_r;          // Cの実部
// 	double	c_i;          // Cの虚部
// 	int		max_it;       // 最大繰り返し回数
// 	double	max_r;        // 実数部の最大値
// 	double	min_r;        // 実数部の最小値
// 	double	max_i;        // 虚数部の最大値
// 	double	min_i;        // 虚数部の最小値
// 	double	delta_r;      // 実数部の増分
// 	double	delta_i;      // 虚数部の増分
// }			t_data;


// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// 	int		pos_x;
// 	int		pos_y;
// 	int		radius;
// 	t_data	img;
// }				t_vars;

// #include "./minilibx/mlx.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define KEY_ESC 53
// #define WIDTH 800
// #define HEIGHT 600
// #define MAX_ITER 100

// int	mandelbrot(double a, double b)
// {
// 	double x;
// 	double y;
// 	int n;

// 	x = 0;
// 	y = 0;
// 	n = 0;
// 	while ((x*x + y*y) <= 4 && n < MAX_ITER)
// 	{
// 		double temp = (x*x + y*y) + a;
// 		y = 2*x*y + b;
// 		x = temp;
// 		n++;
// 	}
// 	return n;
// }

// void draw_mandelbrot(void *mlx, void *win) {
// 	for (int px = 0; px < WIDTH; px++) {
// 		for (int py = 0; py < HEIGHT; py++) {
// 			double x0 = (px - WIDTH / 2.0) * 4.0 / WIDTH;
// 			double y0 = (py - HEIGHT / 2.0) * 4.0 / HEIGHT;
// 			int color = mandelbrot(x0, y0);
// 			int rgb = (color == MAX_ITER) ? 0 : (255 * color / MAX_ITER) << 16;
// 			mlx_pixel_put(mlx, win, px, py, rgb);
// 		}
// 	}
// }

// int render_next_frame(void *param)
// {
// 	t_vars *vars = param;

// 	mlx_clear_window(vars->mlx, vars->win);
// 	draw_mandelbrot(vars, vars->win);
// 	return 0;
// }

// int key_hook(int keycode, t_vars *vars) {
// 	switch (keycode) {
// 		case 13: // W
// 			vars->pos_y -= 10;
// 			break;
// 		case 0: // A
// 			vars->pos_x -= 10;
// 			break;
// 		case 1: // S
// 			vars->pos_y += 10;
// 			break;
// 		case 2: // D
// 			vars->pos_x += 10;
// 			break;
// 		case 7: // キー 'x'
// 			vars->radius += 10;
// 			break;
// 		case 6: // キー 'z'
// 			vars->radius = (vars->radius > 5) ? vars->radius - 10 : 10;
// 			break;
// 	}
// 	return 0;
// }

// int main(void) {
// 	t_vars vars;

// 	vars.mlx = mlx_init();
// 	if (vars.mlx == NULL) {
// 		fprintf(stderr, "Error initializing MLX\n");
// 		return EXIT_FAILURE;
// 	}
// 	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Mandelbrot");
// 	if (vars.win == NULL) {
// 		fprintf(stderr, "Error creating window\n");
// 		return EXIT_FAILURE;
// 	}
// 	vars.pos_x = WIDTH / 2;
// 	vars.pos_y = HEIGHT / 2;
// 	vars.radius = 100;

// 	mlx_key_hook(vars.win, key_hook, &vars);
// 	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
// 	mlx_loop(vars.mlx);

// 	return EXIT_SUCCESS;
// }
// */
// /********************************************************/
// // #include "./minilibx/mlx.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <math.h>

// // #define KEY_ESC 53
// // #define WIDTH 800
// // #define HEIGHT 600
// // #define MAX_ITER 100

// // typedef struct s_data {
// //     void    *img;
// //     char    *addr;
// //     int     bits_per_pixel;
// //     int     line_length;
// //     int     endian;
// //     double  z_r;
// //     double  z_i;
// //     double  c_r;
// //     double  c_i;
// //     int     max_it;
// //     double  max_r;
// //     double  min_r;
// //     double  max_i;
// //     double  min_i;
// //     double  delta_r;
// //     double  delta_i;
// // } t_data;

// // typedef struct s_vars {
// //     void    *mlx;
// //     void    *win;
// //     int     pos_x;
// //     int     pos_y;
// //     int     radius;
// //     t_data  img;
// // } t_vars;

// // int ft_rgb_to_hex(int r, int g, int b) {
// //     return (r << 16) | (g << 8) | b;
// // }

// // int ft_gradation(double norm, double square) {
// //     int r = (int)(9 * (1 - norm) * square * 255);
// //     int g = (int)(15 * (1 - norm) * (1 - square) * 255);
// //     int b = 255 - g;
// //     return ft_rgb_to_hex(r, g, b);
// // }

// // unsigned int ft_pick_color(t_data *data) {
// //     int i;
// //     int color;
// //     double tmp_r;

// //     i = 0;
// //     while (pow(data->z_r, 2.0) + pow(data->z_i, 2.0) <= 4 && i < data->max_it) {
// //         tmp_r = pow(data->z_r, 2.0) - pow(data->z_i, 2.0) + data->c_r;
// //         data->z_i = 2 * data->z_r * data->z_i + data->c_i;
// //         data->z_r = tmp_r;
// //         i++;
// //     }
// //     if (i == data->max_it)
// //         color = ft_rgb_to_hex(255, 255, 255);
// //     else
// //         color = ft_gradation((double)i / (double)data->max_it, pow(data->z_r, 2.0));
// //     return color;
// // }

// // void ft_my_mlx_pixel_put(t_data *data, int x, int y, int color) {
// //     char *dst;

// //     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// //     *(unsigned int*)dst = color;
// // }

// // int ft_draw_mandelbrot(t_data *data) {
// //     int x;
// //     int y;

// //     data->delta_r = (data->max_r - data->min_r) / (double)WIDTH;
// //     data->delta_i = (data->max_i - data->min_i) / (double)HEIGHT;
// //     y = 0;
// //     while (y < HEIGHT) {
// //         x = 0;
// //         while (x < WIDTH) {
// //             data->c_r = data->min_r + x * data->delta_r;
// //             data->c_i = data->min_i + y * data->delta_i;
// //             data->z_r = 0;
// //             data->z_i = 0;
// //             ft_my_mlx_pixel_put(data, x, y, ft_pick_color(data));
// //             x++;
// //         }
// //         y++;
// //     }
// //     return 0;
// // }

// // int key_hook(int keycode, t_vars *vars) {
// //     switch (keycode) {
// //         case 13: // W
// //             vars->pos_y -= 10;
// //             break;
// //         case 0: // A
// //             vars->pos_x -= 10;
// //             break;
// //         case 1: // S
// //             vars->pos_y += 10;
// //             break;
// //         case 2: // D
// //             vars->pos_x += 10;
// //             break;
// //         case 7: // キー 'x'
// //             vars->radius += 10;
// //             break;
// //         case 6: // キー 'z'
// //             vars->radius = (vars->radius > 5) ? vars->radius - 10 : 10;
// //             break;
// //     }
// //     return 0;
// // }

// // int render_next_frame(void *param) {
// //     t_vars *vars = (t_vars *)param;
// //     mlx_clear_window(vars->mlx, vars->win);
// //     ft_draw_mandelbrot(&vars->img);
// //     return 0;
// // }

// // int main(void) {
// //     t_vars vars;

// //     vars.mlx = mlx_init();
// //     if (vars.mlx == NULL) {
// //         fprintf(stderr, "Error initializing MLX\n");
// //         return EXIT_FAILURE;
// //     }
// //     vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Mandelbrot");
// //     if (vars.win == NULL) {
// //         fprintf(stderr, "Error creating window\n");
// //         return EXIT_FAILURE;
// //     }
// //     vars.pos_x = WIDTH / 2;
// //     vars.pos_y = HEIGHT / 2;
// //     vars.radius = 100;
// //     vars.img.max_it = MAX_ITER;
// //     vars.img.max_r = 2.0;
// //     vars.img.min_r = -2.0;
// //     vars.img.max_i = 2.0;
// //     vars.img.min_i = -2.0;

// //     vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
// //     vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

// //     mlx_key_hook(vars.win, key_hook, &vars);
// //     mlx_loop_hook(vars.mlx, render_next_frame, &vars);
// //     mlx_loop(vars.mlx);

// //     return EXIT_SUCCESS;
// // }