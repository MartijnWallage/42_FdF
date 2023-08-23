/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:40:00 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/13 15:27:03 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_parse_hex(t_print *tab, char *base, char *zerox)
{
	unsigned int	nb;
	unsigned int	numdigits;
	unsigned int	numlen;
	unsigned int	paddinglen;

	nb = va_arg(tab->args, unsigned int);
	if (nb == 0)
		tab->hash = 0;
	numdigits = ft_numdigits(nb, 16);
	numlen = printf_max(tab->precision, numdigits);
	if (nb == 0 && tab->point && !tab->precision)
		numlen = 0;
	paddinglen = printf_max(0, tab->width - numlen - 2 * (tab->hash));
	if (tab->hash && tab->padding == '0')
		tab->len += write(1, zerox, 2);
	if (!tab->dash)
		tab->len += put_padding(tab->padding, paddinglen);
	if (tab->hash && tab->padding == ' ')
		tab->len += write(1, zerox, 2);
	if (tab->point)
		tab->len += put_padding('0', tab->precision - numdigits);
	if (numlen)
		tab->len += ft_putnbr_base(nb, base);
	if (tab->dash)
		tab->len += put_padding(' ', paddinglen);
}

static int	handle_nullptr(t_print *tab, void *ptr)
{
	unsigned int	paddinglen;

	if (ptr == NULL)
	{
		paddinglen = printf_max(0, tab->width - 5);
		if (!tab->dash)
			tab->len += put_padding(' ', paddinglen);
		tab->len += write(1, "(nil)", 5);
		if (tab->dash)
			tab->len += put_padding(' ', paddinglen);
		return (1);
	}
	return (0);
}

void	ft_parse_pnt(t_print *tab)
{
	void			*ptr;
	size_t			nb;
	unsigned int	numdigits;
	unsigned int	paddinglen;
	unsigned int	numlen;

	ptr = va_arg(tab->args, void *);
	if (handle_nullptr(tab, ptr))
		return ;
	nb = (size_t) ptr;
	numdigits = ft_numdigits(nb, 16);
	numlen = printf_max(tab->precision, numdigits) + 2;
	paddinglen = printf_max(0, tab->width - numlen);
	if (tab->padding == '0')
		tab->len += write(1, "0x", 2);
	if (!tab->dash)
		tab->len += put_padding(tab->padding, paddinglen);
	if (tab->padding == ' ')
		tab->len += write(1, "0x", 2);
	if (tab->point)
		tab->len += put_padding('0', tab->precision - numdigits);
	tab->len += ft_putnbr_base(nb, HEX_LOWER);
	if (tab->dash)
		tab->len += put_padding(' ', paddinglen);
}
