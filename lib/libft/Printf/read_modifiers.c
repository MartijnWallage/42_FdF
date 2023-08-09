/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_modifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:02:31 by mwallage          #+#    #+#             */
/*   Updated: 2023/05/30 18:20:13 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	read_flags(t_print *tab, const char *format, int i)
{
	while (is_in_set(format[i], "#-'0+ "))
	{
		if (format[i] == '#')
			tab->hash = 1;
		else if (format[i] == '-')
			tab->dash = 1;
		else if (format[i] == '0')
			tab->padding = '0';
		else if (format[i] == '+')
			tab->sign = 1;
		else if (format[i] == ' ')
			tab->space = 1;
		i++;
	}
	if (tab->dash)
		tab->padding = ' ';
	tab->space = (tab->space && !tab->sign);
	return (i);
}

int	read_width(t_print *tab, const char *format, int i)
{
	int	end;

	if (format[i] > '0' && format[i] <= '9')
	{
		end = i;
		while (format[end] >= '0' && format[end] <= '9')
			end++;
		tab->width = ft_atoi_start_to_end(format, i, end);
		i = end;
	}
	return (i);
}

int	read_precision(t_print *tab, const char *format, int i)
{
	int	end;

	if (format[i] == '.')
	{
		tab->padding = ' ';
		tab->point = 1;
		i++;
		end = i;
		while (format[end] >= '0' && format[end] <= '9')
			end++;
		tab->precision = ft_atoi_start_to_end(format, i, end);
		i = end;
	}
	return (i);
}
