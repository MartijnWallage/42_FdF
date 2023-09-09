/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:25:01 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 15:07:21 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(point2d_t current, point2d_t a, point2d_t b, int dx, int dy)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.rgba == b.rgba)
		return (current.rgba);
	if (dx > dy)
		percentage = percent(a.x, b.x, current.x);
	else
		percentage = percent(a.y, b.y, current.y);
	red = get_light((a.rgba >> 24) & 0xFF,
                    (b.rgba >> 24) & 0xFF,
                    percentage);
	green = get_light((a.rgba >> 16) & 0xFF,
                    (b.rgba >> 16) & 0xFF,
                    percentage);
	blue = get_light((a.rgba >> 8) & 0xFF,
                    (b.rgba >> 8) & 0xFF,
                    percentage);
	return ((red << 24) | (green << 16) | blue << 8 | 0xFF);
}

int	parse_color(char *tabj)
{
	while (*tabj == '-')
		tabj++;
	while (ft_isdigit(*tabj))
		tabj++;
	if (*tabj == ',')
		tabj++;
	else
		return (0xFFFFFFFF);
	if ((ft_strncmp(tabj, "0X", 2) && ft_strncmp(tabj, "0x", 2)))
		return (0xFFFFFFFF);
	tabj += 2;
	ft_striteri(tabj, &make_upper);
	return ((ft_atoi_base(tabj, "0123456789ABCDEF") << 8) | 0xFF);
}

static int	zcolor(double perc)
{
    if (perc < 0.1)
		return (COLOR_ONE);
	else if (perc < 0.2)
		return (COLOR_TWO);
	else if (perc < 0.3)
		return (COLOR_THREE);
	else if (perc < 0.4)
		return (COLOR_FOUR);
	else if (perc < 0.5)
		return (COLOR_FIVE);
	else if (perc < 0.6)
		return (COLOR_SIX);
	else if (perc < 0.7)
		return (COLOR_SEVEN);
	else if (perc < 0.8)
		return (COLOR_EIGHT);
	else if (perc < 0.9)
		return (COLOR_NINE);
	else
		return (COLOR_TEN); 
}

void	set_zcolor(map_t *map)
{
	int		i;
	int		j;
	double	perc;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			perc = percent(map->low, map->high, map->map3d[i][j].z);
			map->map3d[i][j].zcolor = zcolor(perc);
		}
	}
}