/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:34:38 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/07 10:17:35 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(const char specifier, va_list args)
{
	int	char_count;

	char_count = 0;
	if (specifier == 'c')
		char_count += ft_printf_char(va_arg(args, int));
	else if (specifier == 's')
		char_count += ft_printf_str(va_arg(args, char *));
	else if (specifier == 'p')
		char_count += ft_printf_ptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		char_count += ft_printf_int(va_arg(args, int));
	else if (specifier == 'u')
		char_count += ft_printf_uint(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		char_count += ft_printf_hex(va_arg(args, unsigned int), specifier);
	else
		char_count = ft_printf_char(specifier);
	return (char_count);
}

int	ft_printf(const char *str, ...)
{
	size_t		count;
	va_list		args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str != '%')
			count += ft_printf_char(*str);
		else if (*str == '%' && *(str + 1))
			count += handle_format(*(++str), args);
		if (*str)
			str++;
	}
	va_end(args);
	return (count);
}

// int main(){
// 	char *s = NULL;
// 	printf("%s, %p\n", s, s);
// 	ft_printf("%s, %p\n", s, s);
// }