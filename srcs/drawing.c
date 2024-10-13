/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/13 23:06:26 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(void *param)
{
	t_game	*game;

	game = param;
	clean_window(game);
	// draw_player(game);
	// draw_miniplayer(game);
	// draw_map(game);
	draw_ray(game);
	// draw_minimap(game);
	draw_cross(game);
	draw_weapon(game);
}

void	clean_window(t_game *game)
{
	int i;
	int j;

	i = 0;
	while ( i <game->window_width)
	{
		j= 0;
		while ( j <game->window_height)
		{
			if (j <= game->window_height / 2 - 30)
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->c[0], game->c[1], game->c[2], 180));
			else
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->f[0], game->f[1], game->f[2], 60));
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	uint32_t	color;
	int	i;
	int	j;

	i = 0;
	color = pixel_color(255, 0, 0, 255);
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mlx_put_pixel(game->mlx_img, game->player.x_player + i, game->player.y_player + j, color);
			j++;
		}
		i++;
	}
}

void	draw_tiles(t_game *game, int xo, int yo, uint32_t tile_color)
{
	int i;
	int j;

	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < (64/(game->window_width/(9*32))))
		while (j < 32)
		{
			mlx_put_pixel(game->mlx_img, xo + j, yo + i, tile_color);
			j++;
		}
		i++;
	}
}

void draw_map(t_game *game)
{
	int x;
	int y;
	int xo;
	int yo;
	uint32_t tile_color;

	y = 0;
	while (game->map[y] != NULL)
	{
		x =0;
		while (x < 15)
		{
			if (game->map[y][x] == '1')
				tile_color = pixel_color(0, 100, 100, 255);
			else if (game->map[y][x] == '0')
				tile_color = pixel_color(255, 255, 255, 255);
			else if (game->map[y][x] == ' ' || game->map[y][x] == '\n')
				tile_color = pixel_color(0, 0, 0, 255);
			xo = x * game->map_unit_size;
			yo = y * game->map_unit_size;
			draw_tiles_boarders(game, xo, yo, tile_color);
			x++;
		}
		y++;
	}
}
void	draw_tiles_boarders(t_game *game, int xo, int yo, uint32_t tile_color)
{
	int i;
	int j;
	int GRIDLINE_WIDTH;
	uint32_t gridline_color;

	gridline_color = pixel_color(0, 0, 0, 255);
	GRIDLINE_WIDTH = 1;
	i = 0;
	while (i < game->map_unit_size)
	{
		j = 0;
		while (j < game->map_unit_size)
		{
			// Check if the current pixel is within the gridline width
			if (i < GRIDLINE_WIDTH || i >= game->map_unit_size - GRIDLINE_WIDTH ||
				j < GRIDLINE_WIDTH || j >= game->map_unit_size - GRIDLINE_WIDTH)
				mlx_put_pixel(game->mlx_img, xo + j, yo + i, gridline_color); // Draw the gridline (border)
			else
				mlx_put_pixel(game->mlx_img, xo + j, yo + i, tile_color); // Draw the tile's color
			j++;
		}
		i++;
	}
}

int32_t	pixel_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color)
{
	if (x1 < 0 || y1 < 0 || x0 < 0 || y0 < 0)
		return;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int err = dx - dy;

	while (1)
	{
		if (x0 >= 0 && x0 < game->window_width && y0 >= 0 && y0 < game->window_height)
			mlx_put_pixel(game->mlx_img, x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;

		int err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += (x0 < x1) ? 1 : -1;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += (y0 < y1) ? 1 : -1;
		}
	}
}

float calculate_dis(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void draw_cross(t_game *game)
{
	char			*cross_path;
	mlx_texture_t	*temp_texture;
	mlx_image_t		**image;

	image = malloc(sizeof(mlx_image_t *));
	cross_path = "./textures/aim _crosshair.png";
	temp_texture = mlx_load_png(cross_path);
	if (temp_texture == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	*image = mlx_texture_to_image(game->mlx, temp_texture);
	if (*image == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	mlx_delete_texture(temp_texture);
	mlx_image_to_window(game->mlx, *image, game->window_width/2 - 30 , game->window_height/2 - 30);
	free (image);
}

void	draw_ray(t_game *game)
{
	int r_num;
	int dof;
	int flag;

	r_num = 0;
	game->ray.ra = game->player.angle_player - 0.523598; // - 30 degree
	while (r_num < 1440)
	{
		reset_rays(game, &flag);
		calculate_horizontal_intraction(game, &dof);
		get_hor_point(game, dof);
		calculate_vertical_intraction(game, &dof, &flag);
		get_ver_point(game, dof);
		get_wall(game, flag);
		render_walls(game, r_num);
//=	==========================================================================================================
		// draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)game->rend.wall_x, (int)game->rend.wall_y, pixel_color(0, 0, 255, 255)); // blue
		game->ray.ra += 0.01745329/24; //next ray
		r_num++;
	}
}
void	reset_rays(t_game * game,int *flag)
{
	game->ray.hor_distance = 100000;
	game->ray.ver_distance = 100000;
	game->ray.rx = 0;
	game->ray.ry = 0;
	game->ray.rx_step = 0;
	game->ray.ry_step = 0;
	game->ray.hor_x = 0;
	game->ray.hor_y = 0;
	game->ray.ver_x = 0;
	game->ray.ver_y = 0;
	*flag = 0;
}

void	fix_fisheye(t_game *game)
{
	float fish_eye;

	fish_eye = game->player.angle_player - game->ray.ra;
	if (fish_eye < 0) // safty
		fish_eye += 2 * PI;
	if (fish_eye > 2 * PI)
		fish_eye -= 2 * PI;
	game->rend.wall_distance = game->rend.wall_distance * cos(fish_eye);
}

void	get_wall(t_game *game, int flag)
{
	game->rend.wall_distance = 0;
	game->rend.current_texture = NULL;
	if(game->ray.ver_distance < game->ray.hor_distance)
	{
		 if (game->ray.rx > game->player.x_player)
			game->rend.current_texture = game->tex.east_image;
		else
			game->rend.current_texture = game->tex.west_image;
		game->rend.wall_distance = game->ray.ver_distance;
		game->rend.wall_x = game->ray.ver_x;
		game->rend.wall_y = game->ray.ver_y;
	}
	else if(game->ray.ver_distance >= game->ray.hor_distance)
	{
		if (game->ray.ry > game->player.y_player)
			game->rend.current_texture = game->tex.south_image;
		else
			game->rend.current_texture = game->tex.north_image;
		game->rend.wall_distance = game->ray.hor_distance;
		game->rend.wall_x = game->ray.hor_x;
		game->rend.wall_y = game->ray.hor_y;
	}
	// if (flag ==1)
	// {
	// 	printf("flag is: %d\n", flag);
	// 	exit (1);
	// }
	if (flag == 1)
		game->rend.current_texture = game->tex.south_image;
	fix_fisheye(game);
}

void	render_walls(t_game *game, int r_num)
{
	float		wall_height;
	int			shift_to_center;

	wall_height = (game->map_unit_size * game->window_height) / game->rend.wall_distance; // the wall height depending on how far it is from the player
	if (wall_height > game->window_height) // for safty
		wall_height = game->window_height;
	shift_to_center = game->window_height/2- (wall_height/2); // to center the wall in the middle of the window (middle of the height)
	if (game->ray.ver_distance < game->ray.hor_distance)
		game->rend.texture_pos_x_rate = fmod(game->rend.wall_y, game->map_unit_size) / game->map_unit_size;
		// Vertical wall hit: example: wall_y = 160
		// fmod(160, 64) = 32 which is in the middle of the block
		// texture_pos_x = 32 / 64 = 0.5 that means it is in the half way from the texture width
	else
		game->rend.texture_pos_x_rate = fmod(game->rend.wall_x, game->map_unit_size) / game->map_unit_size; // Horizontal wall hit
	// Convert to texture coordinates (between 0 and texture width)
	// so if hit_po_x = 0.5 --> texture_pos_x * game->rend.current_texture->width will take the middle of the texture
	// so by knowing texture_pos_x we can take the color from the texture from the right place in it
	draw_tex_slice(game, wall_height, shift_to_center, r_num);
}

uint32_t	get_color(uint32_t	texture_color)
{
		t_color clr;

		clr.channel[ALPHA] = (texture_color >> 24) & 0xFF; // Extract Alpha
		clr.channel[RED] = (texture_color >> 16) & 0xFF;   // Extract Red
		clr.channel[GREEN] = (texture_color >> 8) & 0xFF;   // Extract Green
		clr.channel[BLUE] = texture_color & 0xFF;
		return (clr.color);
}

void	draw_tex_slice(t_game *game, float wall_height, int shift_to_center, int r_num)
{
	uint32_t	texture_color;
	int			y;

	y = shift_to_center;
	game->rend.texture_x = (uint32_t)(game->rend.texture_pos_x_rate * game->rend.current_texture->width);
	while (y < shift_to_center + wall_height)
	{
		// Scale the y-coordinate to the texture height
		game->rend.texture_y = (uint32_t)((y - shift_to_center) * game->rend.current_texture->height / wall_height);
		// Sample the texture color from (texture_x, texture_y)
		texture_color = ((uint32_t *)game->rend.current_texture->pixels)
			[game->rend.texture_y * game->rend.current_texture->width + game->rend.texture_x];
		// Draw the pixel on the screen with the new color
		mlx_put_pixel(game->mlx_img, (r_num ), y, get_color(texture_color));
		y++;
	}
}

void draw_weapon(t_game *game)
{
	char			*cross_path;
	mlx_texture_t	*temp_texture;
	mlx_image_t		**image;

	image = malloc(sizeof(mlx_image_t *));
	cross_path = "./textures/weapon.png";
	temp_texture = mlx_load_png(cross_path);
	if (temp_texture == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	*image = mlx_texture_to_image(game->mlx, temp_texture);
	if (*image == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	mlx_delete_texture(temp_texture);
	mlx_image_to_window(game->mlx, *image, game->window_width - 650 , game->window_height - 312);
	free (image);
}
