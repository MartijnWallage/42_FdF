/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 15:55:48 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* static void	iso(int32_t *x, int32_t *y, int32_t z)
{
    int32_t previous_x;
    int32_t previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.46373398);
    *y = -z + (previous_x + previous_y) * sin(0.46373398);
}

void	project_iso(map_t *map, mlx_image_t *image)
{
} */