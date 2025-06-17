/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:49:51 by miguel-f          #+#    #+#             */
/*   Updated: 2025/06/17 13:04:33 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

/**
 * Imprime una cadena de caracteres en la salida estándar.
 * Si el puntero es NULL, imprime "(null)".
 * Devuelve el número de caracteres impresos.
 */
int	ft_printstr(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		s = "(null)";
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

/**
 * Imprime un número en la base especificada.
 * Soporta números negativos para base 10.
 * Devuelve el número de caracteres impresos.
 */
int	ft_putnbr(long long nbr, int base)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		i += write (1, "-", 1);
	}
	if (nbr >= base)
		i += ft_putnbr((nbr / base), base);
	i += write(1, &"0123456789abcdef"[nbr % base], 1);
	return (i);
}

/**
 * Implementación simplificada de printf.
 * Soporta los formatos: %s (cadena), %d (entero decimal), %x (hexadecimal).
 * Devuelve el número total de caracteres impresos.
 */
int	ft_printf(const char *s, ...)
{
	int		i;
	int		c;
	va_list	args;

	i = 0;
	c = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] != '%')
			c += write(1, &s[i], 1);
		else
		{
			i++;
			if (s[i] == 's')
				c += ft_printstr(va_arg(args, char *));
			if (s[i] == 'd')
				c += ft_putnbr(va_arg(args, int), 10);
			if (s[i] == 'x')
				c += ft_putnbr(va_arg(args, unsigned int), 16);
		}
		i++;
	}
	va_end (args);
	return (c);
}
