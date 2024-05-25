/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:19:42 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/07 08:51:00 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_int(int n)
{
	long	nb;
	int		count;

	nb = (long)n;
	count = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
		count = 1;
	}
	if (nb > 9)
	{
		count += ft_printf_int(nb / 10);
	}
	ft_putchar_fd((nb % 10) + '0', 1);
	return (count + 1);
}
