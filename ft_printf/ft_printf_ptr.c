/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:27:31 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/07 11:23:59 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_ptr_hex(uintptr_t num)
{
	const char	*hex_digits;
	char		buffer[16 + 1];
	int			index;
	int			start;

	hex_digits = HEX_LOWER;
	index = 16;
	buffer[index--] = '\0';
	if (num == 0)
		buffer[index--] = '0';
	while (num != 0)
	{
		buffer[index--] = hex_digits[num % 16];
		num /= 16;
	}
	start = index + 1;
	while (buffer[start])
	{
		ft_putchar_fd(buffer[start++], 1);
	}
	return (16 - index - 1);
}

int	ft_printf_ptr(void *ptr)
{
	uintptr_t	ptr_val;
	int			count;

	ptr_val = (uintptr_t)ptr;
	count = 2;
	write(1, "0x", 2);
	count += ft_printf_ptr_hex(ptr_val);
	return (count);
}

//Casts a void* to uintptr_t and handles the pointer's address 
//as an unsigned integer.