/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:25:01 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/07 18:40:27 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int    project_color(map_t *map, int i, int j)
{
    point3d_t   *point;
    double      perc;
    
    point = &(map->map3d[i][j]);
    if (!map->z_color)
        return (point->rgba);
    perc = percent(map->low, map->high, point->z_unparsed);
    if (perc < 0.2)
		return (COLOR_DISCO);
	else if (perc < 0.4)
		return (COLOR_BRICK_RED);
	else if (perc < 0.6)
		return (COLOR_FLAMINGO);
	else if (perc < 0.8)
		return (COLOR_JAFFA);
	else
		return (COLOR_SAFFRON); 
}

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