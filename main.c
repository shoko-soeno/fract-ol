/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:54:25 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/25 22:54:18 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KEY_ESC 53
#define WIDTH 500
#define HEIGHT 500
#define MAX_ITER 50
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_DESTROY 17

#define ZOOM_IN_FACTOR 1.1
#define ZOOM_OUT_FACTOR 0.9
#define MAX_ZOOM 10.0
#define MIN_ZOOM 0.1

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
	double	zoom;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		pos_x;
	int		pos_y;
	int		radius;
	t_data	img;
}				t_vars;

void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int ft_pick_color(t_data *data)
{
	int	i;
	double tmp_r;

	i = 0;
	while(pow(data->z_r, 2.0) + pow(data->z_i, 2.0) <= 4 && i < MAX_ITER)
	{
		tmp_r = pow(data->z_r, 2.0) - pow(data->z_i, 2.0) + data->c_r;
		data->z_i = 2 * data->z_r * data->z_i + data->c_i;
		data->z_r = tmp_r;
		i++;
	}
	if (i == MAX_ITER)
	 	return 0;
	int g = (int)(100 + 127 * sin(i * 0.05));
	int b = (int)(10 + 80 * cos(i * 0.05));
	int r = (int)(255 * (i / (float)MAX_ITER));

	return (r << 16) | (g << 8) | b;
}

int	ft_draw_mandelbrot(t_data *data) {
	int	x;
	int	y;

	data->delta_r = (data->max_r - data->min_r) / (double)WIDTH / data->zoom;
	data->delta_i = (data->max_i - data->min_i) / (double)HEIGHT / data->zoom;
	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data->c_r = data->min_r + x * data->delta_r;
			data->c_i = data->min_i + y * data->delta_i;
			data->z_r = 0;
			data->z_i = 0;
			ft_mlx_pixel_put(data, x, y, ft_pick_color(data));
			x++;
		}
		y++;
	}
	return 0;
}

int render_next_frame(void *param)
{
	t_vars *vars = (t_vars *)param;
	ft_draw_mandelbrot(&vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return 0;
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		printf("escape!!!\n");
		exit(0);
	}
	return 0;
}

int handle_mouse(int button, int x, int y, void *param)
{
	t_vars *vars = (t_vars *)param;

	(void)x;
	(void)y;
	if (button == 4 && vars->img.zoom < MAX_ZOOM)
		vars->img.zoom *= ZOOM_IN_FACTOR;
	else if (button == 5 && vars->img.zoom > MIN_ZOOM)
		vars->img.zoom *= ZOOM_OUT_FACTOR;
	ft_draw_mandelbrot(&vars->img);
	return 0;
}

int close_window(void *param){
	t_vars *vars = (t_vars *)param;

	(void)vars;
	
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int main(void)
{
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
	vars.img.zoom = 1.0;
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_hook(vars.win, ON_MOUSEDOWN, 0, handle_mouse, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, close_window, &vars);
	mlx_mouse_hook(vars.win, handle_mouse, &vars);

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	return (EXIT_SUCCESS);
}
