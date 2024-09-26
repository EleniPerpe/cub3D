/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:22:48 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/26 20:27:34 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "Libft/libft.h"
# include "Get_next_line/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"

# define pi 3.1415926535
# define dir_SO pi / 2
# define dir_NO  (3 * pi / 2)
# define dir_WE pi
# define dir_EA 0

typedef struct s_player
{
	float			x_player;
	float			y_player;
	float			dx_player;
	float			dy_player;
	float			angle_player;
	float			start_angle;
} t_player;

typedef struct s_texture
{
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *west;
	mlx_texture_t *east;
	mlx_image_t *north_image;
	mlx_image_t *south_image;
	mlx_image_t *west_image;
	mlx_image_t *east_image;
}	t_texture;

typedef struct s_game
{
	int			map_fd;
	int			height_map;
	int			width_map;
	const char		*SO;
	const char		*NO;
	const char		*WE;
	const char		*EA;
	int			*C;
	int			*F;
	int			x;
	int			y;
	int			flood_x;
	int			flood_y;
	char		**map;
	int			*start_pos;
	char		orientation;
	// mlx_texture_t SO; instead of mlx_image_t
	// mlx_image_t	*player;
	mlx_image_t	*mlx_img; // new
	const char		*name; // new
	t_texture	tex;
	t_player	player;
	mlx_t		*mlx; // new
	int			window_width;
	int			window_height;
	int			map_unit_x;
	int			map_unit_y;
	int			map_unit_size;
	const int	*map_array; // later must take it from the map file after parsing
}	t_game;

int		arg_check(int argc, char *arg);
void	map_reader(t_game *game, char *map);
void	check_map_walls(t_game *game, int i, int j);
void	ft_error_exit(t_game *game, const char *msg);
int		init_mlx(t_game *game);
void	draw(void *param);
int32_t	pixel_color(int r, int g, int b, int a);
void	keyboard_control(void *param);
void	draw_player(t_game *game);
void	draw_map(t_game *game);
int is_only_spaces(char *str);

#endif
