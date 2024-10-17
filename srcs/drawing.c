/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 21:50:12 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_window(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->window_width)
	{
		j = 0;
		while (j < game->window_height)
		{
			if (j <= game->window_height / 2 - 30)
			{
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->c[0], game->c[1], game->c[2], 180));
				if (rand() % 10000 < 2)
					mlx_put_pixel(game->mlx_img, i, j, pixel_color(255, 255, 255, 255));
			}
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


void	calculate_ray(t_game *game)
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
		// draw rays:
		// draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)game->rend.wall_x, (int)game->rend.wall_y, pixel_color(0, 0, 255, 255)); // blue
		game->ray.ra += 0.01745329/24; //next ray
		r_num++;
	}
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
		if (game->rend.ver_is_door)
			game->rend.current_texture = game->tex.door;
		else if (game->rend.ver_is_fire)
			game->rend.current_texture = game->tex.fire;
		else
		{
			if (game->ray.rx > game->player.x_player)
				game->rend.current_texture = game->tex.east_image;
			else
				game->rend.current_texture = game->tex.west_image;
		}
		game->rend.wall_distance = game->ray.ver_distance;
		game->rend.wall_x = game->ray.ver_x;
		game->rend.wall_y = game->ray.ver_y;
	}
	else if(game->ray.ver_distance >= game->ray.hor_distance)
	{
		if (game->rend.hor_is_door)
			game->rend.current_texture = game->tex.door;
		else if (game->rend.hor_is_fire)
			game->rend.current_texture = game->tex.fire;
		else
		{
			if (game->ray.ry > game->player.y_player)
				game->rend.current_texture = game->tex.south_image;
			else
				game->rend.current_texture = game->tex.north_image;
		}
		game->rend.wall_distance = game->ray.hor_distance;
		game->rend.wall_x = game->ray.hor_x;
		game->rend.wall_y = game->ray.hor_y;
	}
	if ((flag == 1) && !game->rend.hor_is_door
		&& !game->rend.hor_is_fire)
		game->rend.current_texture = game->tex.south_image;
	fix_fisheye(game);
}

