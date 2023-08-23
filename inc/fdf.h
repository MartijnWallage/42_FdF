/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:30:52 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/23 15:51:53 by mwallage         ###   ########.fr       */
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
	int32_t	x;
	int32_t	y;
	int32_t	value;
	int		rgba;
}			point2d_t;

typedef struct	point3d_s
{
	int32_t	x;
	int32_t	y;
	int32_t	z;
}			point3d_t;

typedef struct map_s
{
	int				rows;
	int				cols;
	unsigned int	interval;
	point2d_t		*map2d;
	point3d_t		*map3d;
}					map_t;

#endif
