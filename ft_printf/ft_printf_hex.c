/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:15:37 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/07 10:15:39 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_hex(unsigned int num, const char specifier)
{
	const char	*hex_digits;
	int			count;

	count = 0;
	if (specifier == 'x')
		hex_digits = HEX_LOWER;
	else if (specifier == 'X')
		hex_digits = HEX_UPPER;
	else
		return (-1);
	if (num >= 16)
		count += ft_printf_hex(num / 16, specifier);
	ft_putchar_fd(hex_digits[num % 16], 1);
	return (count + 1);
}

//On a 64-bit system the size of a pointer is usually 64 bytes, 
//while unsigned int is typically 32 bits
//passing pointer to this function could result in the loss of the
//upper bits of the pointer
//Recursive calling carries the risk of causing a stack overflow
//when dealing with pointer values that have many digits