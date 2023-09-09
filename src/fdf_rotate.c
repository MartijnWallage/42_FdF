/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:38:43 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 21:51:48 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_x(double *y, double *z, double alpha)
{
	double previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

/*
** Rotate coordinate by y axis
*/

void	rotate_y(double *x, double *z, double beta)
{
	double previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

/*
** Rotate coordinate by z axis
*/

void	rotate_z(double *x, double *y, double gamma)
{
	double previous_x;
	double previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

void	rotate_all(map_t *map, char axis)
{
	int i;
	int j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (axis == 'x')
				rotate_x(&(map->map3d[i][j].y), &(map->map3d[i][j].z), 0.01);
			else if (axis == 'y')
				rotate_y(&(map->map3d[i][j].x), &(map->map3d[i][j].z), 0.01);
			else if (axis == 'z')
				rotate_x(&(map->map3d[i][j].x), &(map->map3d[i][j].y), 0.01);
		}
	}
}
