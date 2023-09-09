/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:17:35 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 17:32:23 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	display_menu(mlx_t *mlx)
{
	int	x;
	int	y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Zoom:\t\t\t\t\t\t\t\t\t\tmouse scroll or -+", x, y += 30);
	mlx_put_string(mlx, "Translate:\t\t\t\t\tarrow keys", x, y+=20);
	mlx_put_string(mlx, "Rotate:\t\t\t\t\t\t\t\tr", x, y += 20);
	mlx_put_string(mlx, "Mirror:\t\t\t\t\t\t\t\tt", x, y += 20);
	mlx_put_string(mlx, "Switch colour:\tc", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 35);
	mlx_put_string(mlx, "Isometric:\t\t\t\t\ti", x, y += 30);
	mlx_put_string(mlx, "Dimetric:\t\t\t\t\t\td", x, y += 20);
	mlx_put_string(mlx, "Parallel:\t\t\t\t\t\tp", x, y += 20);
}