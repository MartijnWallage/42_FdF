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

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// get the red channel
int get_r(int rgba)
{
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    return (rgba & 0xFF);
}

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