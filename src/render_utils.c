/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 10:38:40 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/16 12:44:51 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	mandelbrot_or_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		*c = (t_complex){fractal->julia_x, fractal->julia_y};
		// c->x = fractal->julia_x;
		// c->y = ;
	}
	else
	{
		*c = *z;
		// c->x = z->x;
		// c->y = z->y;
	}
}

t_complex	burning_ship_next(t_complex z, t_complex c)
{
	t_complex	result;

	z.x = fabs(z.x);
	z.y = fabs(z.y);
	result.x = z.x * z.x - z.y * z.y + c.x;
	result.y = 2 * z.x * z.y + c.y;
	return (result);
}
