/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:17:35 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/20 15:29:12 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	display_menu(mlx_t *mlx)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Switch colour:\tc", x, y += 30);
	mlx_put_string(mlx, "Zoom:\t\t\t\t\t\t\t\t\t\tmouse scroll or -+", x, y += 20);
	mlx_put_string(mlx, "Translate:\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(mlx, "Angle x:\t\t\t\t\t\t\ta", x, y += 20);
	mlx_put_string(mlx, "Angle y:\t\t\t\t\t\t\ts", x, y += 20);
	mlx_put_string(mlx, "Rotate x:\t\t\t\t\t\tx + < or x + >", x, y += 20);
	mlx_put_string(mlx, "Rotate y:\t\t\t\t\t\ty + < or y + >", x, y += 20);
	mlx_put_string(mlx, "Rotate z:\t\t\t\t\t\tz + < or z + >", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 35);
	mlx_put_string(mlx, "Isometric:\t\t\t\t\t1", x, y += 30);
	mlx_put_string(mlx, "Dimetric:\t\t\t\t\t\t2", x, y += 20);
	mlx_put_string(mlx, "Trimetric:\t\t\t\t\t3", x, y += 20);
}
