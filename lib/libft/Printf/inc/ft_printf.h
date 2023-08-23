/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:34:02 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/13 15:27:03 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define DEC		"0123456789"
# define HEX_LOWER	"0123456789abcdef"
# define HEX_UPPER	"0123456789ABCDEF"

typedef struct s_print
{
	va_list	args;
	int		hash;
	int		width;
	int		precision;
	char	padding;
	int		point;
	int		dash;
	int		len;
	int		sign;
	int		space;
	int		neg;
}				t_print;

/* ft_printf.c*/
int				ft_printf(const char *format, ...);
/* read_modifiers.c*/
int				read_flags(t_print *tab, const char *format, int i);
int				read_width(t_print *tab, const char *format, int i);
int				read_precision(t_print *tab, const char *format, int i);
/* conversions.c */
void			ft_parse_char(t_print *tab);
void			ft_parse_str(t_print *tab);
void			ft_parse_int(t_print *tab);
void			ft_parse_uns(t_print *tab);
/* conversions_hex.c */
void			ft_parse_hex(t_print *tab, char *base, char *zerox);
void			ft_parse_pnt(t_print *tab);
/* conversions_utils.c */
int				ft_atoi_start_to_end(const char *str, int start, int end);
unsigned int	ft_numdigits(size_t nbr, unsigned int baselen);
/* put_conversions.c */
unsigned int	ft_putstr(char *str, int strlen);
unsigned int	ft_putnbr_base(ssize_t nbr, char *base);
int				put_padding(char c, int len);
int				put_sign_or_space(t_print *tab);
/* utils.c */
unsigned int	ft_strlen(const char *str);
int				is_in_set(const char c, const char *set);
int				printf_min(int a, int b);
int				printf_max(int a, int b);

#endif
