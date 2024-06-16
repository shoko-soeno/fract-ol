/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:48:56 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/16 17:34:49 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	close_window(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		exit(EXIT_SUCCESS);
	}
	ft_printf("%d\n", keycode);
	if (keycode == A_LEFT)
		fractal->shift_x += (0.5 * fractal->zoom);	
	else if (keycode == D_RIGHT)
		fractal->shift_x -= (0.5 * fractal->zoom);	
	else if (keycode == W_UP)
		fractal->shift_y -= (0.5 * fractal->zoom);	
	else if (keycode == S_DOWN)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keycode == PLUS && fractal->iteration < 200)
		fractal->iteration += 10;
	else if (keycode == MINUS && fractal->iteration > 20)
		fractal->iteration -= 10;
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	// double	mapped_mouse_x;
	// double	mapped_mouse_y;

	// (void)x, (void)y;
	// mapped_mouse_x = (x/(double)WIDTH *4 -2) * fractal->zoom + fractal->shift_x;
	// mapped_mouse_y = (2 - y/(double)HEIGHT *4) * fractal->zoom + fractal->shift_y;
	if (button == ON_MOUSEDOWN && fractal->zoom < ZOOMOUT_MAX)
	{
		fractal->shift_x += (x/(double)WIDTH *4 -2) / (0.5 - 1);
		fractal->shift_y += (mapped_mouse_y - fractal->shift_y) / (0.5 - 1);
		fractal->zoom /= 0.5;
	}
	else if (button == ON_MOUSEUP && fractal->zoom > ZOOMIN_MAX)
	{
		fractal->shift_x += (mapped_mouse_x - fractal->shift_x) * 0.5;
		fractal->shift_y += (mapped_mouse_y - fractal->shift_y) * 0.5;
		fractal->zoom *= 0.5;
	}
	
	//debug
	// printf("shift_x %lf mouse_x %lf zoom %lf\n", fractal->shift_x, mapped_mouse_x, fractal->zoom);
	// printf("shift_y %lf mouse_y %lf zoom %lf\n", fractal->shift_x, mapped_mouse_y, fractal->zoom);
	fractal_render(fractal);
	return (0);
}
/*
x,y ox,oy

*/


// int	julia_track(int x, int y, t_fractal *fractal)
// {
// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 	{
// 		fractal->julia_x = (map(x, -2, +2, WIDTH) * fractal->zoom)
// 			+ fractal->shift_x;
// 		fractal->julia_y = (map(y, +2, -2, HEIGHT) * fractal->zoom)
// 			+ fractal->shift_y;
// 		fractal_render(fractal);
// 	}
// 	return (0);
// }
