/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:07:39 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/14 15:34:44 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_init_tab(t_print *tab)
{
	tab->hash = 0;
	tab->width = 0;
	tab->precision = 0;
	tab->padding = ' ';
	tab->point = 0;
	tab->dash = 0;
	tab->len = 0;
	tab->sign = 0;
	tab->space = 0;
	tab->neg = 0;
}

/*  %[flags][width][.precision]conversion */
static int	ft_eval_format(t_print *tab, const char *format, int i)
{
	i = read_flags(tab, format, i);
	i = read_width(tab, format, i);
	i = read_precision(tab, format, i);
	if (format[i] == 'c')
		ft_parse_char(tab);
	else if (format[i] == 's')
		ft_parse_str(tab);
	else if (format[i] == 'p')
		ft_parse_pnt(tab);
	else if (format[i] == 'd' || format[i] == 'i')
		ft_parse_int(tab);
	else if (format[i] == 'u')
		ft_parse_uns(tab);
	else if (format[i] == 'x')
		ft_parse_hex(tab, HEX_LOWER, "0x");
	else if (format[i] == 'X')
		ft_parse_hex(tab, HEX_UPPER, "0X");
	else if (format[i] == '%')
		tab->len += write(1, "%", 1);
	return (i);
}

static int	read_format(const char *format, t_print *tab)
{
	int	chars_written;
	int	i;

	chars_written = 0;
	i = -1;
	while (format[++i])
	{
		ft_init_tab(tab);
		if (format[i] == '%')
		{
			i = ft_eval_format(tab, format, i + 1);
			chars_written += tab->len;
		}
		else
			chars_written += write(1, &format[i], 1);
	}
	return (chars_written);
}

int	ft_printf(const char *format, ...)
{
	int		chars_written;
	t_print	*tab;

	if (format == NULL)
		return (-1);
	tab = malloc(sizeof(t_print));
	if (tab == NULL)
		return (-1);
	va_start(tab->args, format);
	chars_written = read_format(format, tab);
	va_end(tab->args);
	free(tab);
	return (chars_written);
}
