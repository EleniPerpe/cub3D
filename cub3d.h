/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:22:48 by eperperi          #+#    #+#             */
/*   Updated: 2024/10/20 18:40:11 by rshatra          ###   ########.fr       */
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

# define PI 3.1415926535
# define DIR_SO PI / 2
# define DIR_NO  (3 * PI / 2)
# define DIR_WE PI
# define DIR_EA 0

enum channel
{
	ALPHA,
	RED,
	GREEN,
	BLUE,
};

typedef struct s_raycast
{
	float		rx;
	float		ry;
	float		ra;
	float		rx_step;
	float		ry_step;
	float		hor_distance;
	float		hor_x;
	float		hor_y;
	float		ver_distance;
	float		ver_x;
	float		ver_y;

}			t_raycast;

typedef struct s_rend
{
	float		wall_distance;
	float		wall_x;
	float		wall_y;
	float		texture_pos_x_rate;
	uint32_t	texture_x;
	uint32_t	texture_y;
	mlx_image_t	*current_texture;
	float		wall_height;
	bool 		hor_is_door;
	bool 		ver_is_door;
	bool 		hor_is_fire;
	bool 		ver_is_fire;
	bool 		hor_is_flame;
	bool 		ver_is_flame;

}			t_rend;

typedef union s_color
{
	uint8_t		channel[4];
	uint32_t	color;
}			t_color;

typedef struct s_player
{
	float			x_player;
	float			y_player;
	float			dx_player;
	float			dy_player;
	float			angle_player;
	float			start_angle;
	int				mouse_pos;
	int				health;
	bool			dead;
}	t_player;

typedef struct s_texture
{
	mlx_image_t	*north_image;
	mlx_image_t	*south_image;
	mlx_image_t	*west_image;
	mlx_image_t	*east_image;
	mlx_image_t	*door;
	mlx_image_t	*fire;
	mlx_image_t	*intro;
	mlx_image_t	*heal_0;
	mlx_image_t	*heal_1;
	mlx_image_t	*crosshair;
	mlx_image_t	*weapon;
	mlx_image_t	*gameover;
	mlx_image_t	*black_hole;
	mlx_image_t	*fire_flame[21];
}	t_texture;


typedef struct s_game
{
	int				map_fd;
	int				height_map;
	int				width_map;
	const char		*so;
	const char		*no;
	const char		*we;
	const char		*ea;
	int				*c;
	int				*f;
	char			**map;
	int				*start_pos;
	char			orientation;
	mlx_image_t		*mlx_img;
	const char		*name;
	t_texture		tex;
	t_player		player;
	mlx_t			*mlx;
	int				window_width;
	int				window_height;
	int				map_unit_x;
	int				map_unit_y;
	int				map_unit_size;
	t_raycast		ray;
	t_rend			rend;
	bool			intro;
	int				frame_count;
	int				frame_count2;
}	t_game;

int32_t	pixel_color(int r, int g, int b, int a);
uint32_t	get_color(uint32_t	texture_color);
int		arg_check(int argc, char *arg);
void	map_reader(t_game *game, char *map);
void	ft_error_exit(t_game *game, const char *msg);
int		init_mlx(t_game *game);
void	draw(void *param);
void	keyboard_control(void *param);
void	clean_window(t_game *game);
void	draw_player(t_game *game);
void	draw_miniplayer(t_game *game);
void	draw_map(t_game *game);
void	draw_minimap(t_game *game);
int		is_only_spaces(char *str);
void	init_map(t_game *game);
void	init_player(t_game *game);
void	draw_tiles_boarders(t_game *game, int xo, int yo, uint32_t tile_color);
void	draw_tiles(t_game *game, int xo, int yo, uint32_t tile_color);
void	calculate_ray(t_game *game);
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color);
void	coordinate_corrector(t_game *game, char c);
void	fill_real_map(t_game *game, char *reader);
void	find_map_width(t_game *game);
void	find_start_pos(t_game *game);
void	fill_map_variables(t_game *game);
void	check_textures(t_game *game);
int		check_rgb(char *variable, int **color);
void	ft_setup_temp_map(t_game *game, char ***temp_map);
void	check_walls(char **map, int x, int y, t_game *game);
float	calculate_dis(float x1, float y1, float x2, float y2);
void	draw_cross(t_game *game);
void	mouse_move(double x, double y, void *param);
void	calculate_horizontal_intraction(t_game *game, int *dof);
void	calculate_vertical_intraction(t_game *game,int *dof, int *flag);
void	get_hor_point(t_game *game,int dof);
void	get_ver_point(t_game *game,int dof);
void	reset_rays(t_game * game,int *flag);
void	get_wall(t_game *game, int flag);
void	render_walls(t_game *game, int r_num);
void	ft_error_tex(void);
void	draw_weapon(t_game *game);
void	sw(t_game *game);
void	ad(t_game *game);
void	left_right(t_game *game);
void	loops(t_game *game);
void	init_game(t_game *game);
void	draw_health(t_game *game);
void	draw_tex_slice(t_game *game, int shift_to_center, int r_num, int offset);
void	draw_far_slice(t_game *game, int r_num, int shift_to_down);
void	draw_close_slice(t_game *game,  int r_num, int offset);
void	draw_health_section(t_game *game, mlx_image_t *heal, int x, int y);
void	check_fire(t_game *game);

#endif
