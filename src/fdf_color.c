/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:25:01 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/29 18:21:43 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	radiant(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

static double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

int	get_color(t_point2d current, t_point2d a, t_point2d b)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (a.rgba == b.rgba)
		return (a.rgba);
	if (abs(b.x - a.x) > abs(b.y - a.y))
		percentage = percent(a.x, b.x, current.x);
	else
		percentage = percent(a.y, b.y, current.y);
	red = radiant((a.rgba >> 24) & 0xFF, (b.rgba >> 24) & 0xFF, percentage);
	green = radiant((a.rgba >> 16) & 0xFF, (b.rgba >> 16) & 0xFF, percentage);
	blue = radiant((a.rgba >> 8) & 0xFF, (b.rgba >> 8) & 0xFF, percentage);
	return ((red << 24) | (green << 16) | blue << 8 | 0xFF);
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

void	set_zcolor(t_map *map)
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
			perc = percent(map->low, map->high, map->grid3d[i][j].z);
			map->grid3d[i][j].zcolor = zcolor(perc);
		}
	}
}
