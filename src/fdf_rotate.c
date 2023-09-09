/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:38:43 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 18:16:42 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

/*
** Rotate coordinate by y axis
*/

void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

/*
** Rotate coordinate by z axis
*/

point3d_t	*rotate_z(point3d_t *point, double gamma)
{
	point3d_t	*new_point;
	double previous_x;
	double previous_y;

	new_point = malloc(sizeof(point3d_t));
	if (!new_point)
		handle_error(strerror(errno));
	previous_x = point->x;
	previous_y = point->y;
	new_point->x = previous_x * cos(gamma) - previous_y * sin(gamma);
	new_point->y = previous_x * sin(gamma) + previous_y * cos(gamma);
	return (new_point);
}
