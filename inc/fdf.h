/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:30:52 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/17 11:52:40 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

# define	WIDTH	800
# define	HEIGHT	450

typedef struct	point2d_s
{
	float	x;
	float	y;
}			point2d_t;

typedef struct	point3d_s
{
	float	x;
	float	y;
	float	z;
}			point3d_t;

typedef struct map_s
{
	int			rows;
	int			cols;
	point2d_t	*map2d;
	point3d_t	*map3d;
}				map_t;

#endif
