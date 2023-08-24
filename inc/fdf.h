/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:30:52 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 15:57:46 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

# define	WIDTH	800
# define	HEIGHT	450

typedef struct	point2d_s
{
	int32_t		x;
	int32_t		y;
	point2d_s	*right;
	point2d_s	*down;
	int			rgba;
}			point2d_t;

typedef struct	point3d_s
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
	point3d_s	*right;
	point3d_s	*down;
	int			rgba;
}			point3d_t;


typedef struct map_s
{
	int				rows;
	int				cols;
	unsigned int	interval;
	point3d_t		*map3d;
	point2d_t		*projection;
}					map_t;

typedef struct	ft_hook_s
{
	mlx_t		*mlx;
	map_t		*map;
	mlx_image_t	*image;
}			ft_hook_t;

/* fdf_parse.c */
void		parse_map(int, map_t *);
int			valid_filename(const char *);
void		get_cols(int, map_t *);
void		get_rows(int, map_t *);
map_t		*parse_input(int, char **);

/* fdf_error.c */
void		handle_error(const char *);
void		error_map(int, map_t *, char *);

/* fdf_draw.c */
void		draw_grid(mlx_image_t *, map_t *);
void		draw_lines(mlx_image_t *, map_t *);
void		draw_image(mlx_image_t *, map_t *);

/* fdf_project.c */
void		iso_project(map_t *map);

/* fdf_hooks.c */
void		ft_hook(void* param);

#endif
