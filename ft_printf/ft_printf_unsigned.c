/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:09:32 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/06 23:23:28 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_uint(unsigned int n)
{
	unsigned long	nb;
	int				count;

	nb = (unsigned long)n;
	count = 0;
	if (nb > 9)
	{
		count += ft_printf_uint(nb / 10);
	}
	ft_putchar_fd((nb % 10) + '0', 1);
	return (count + 1);
}
