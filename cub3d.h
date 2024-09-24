/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:22:48 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/24 14:15:00 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "Libft/libft.h"
# include "Get_next_line/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_game
{
	int			map_fd;
	int			height_map;
	int			width_map;
	int			p_c;
	int			c_c;
	int			e_c;
	int			steps;
	int			x;
	int			y;
	int			flood_x;
	int			flood_y;
	char		**map;
	// mlx_texture_t SO;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_t		*mlx;	
}	t_game;

int		arg_check(int argc, char *arg);
void	map_reader(t_game *game, char *map);
void	check_map_walls(t_game *game, int i, int j);
void	ft_error_exit(t_game *game, const char *msg);

#endif