/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/11 01:44:46 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(void *param)
{
	t_game	*game;

	game = param;
	clean_window(game);
	// draw_player(game);
	// draw_map(game);
	// draw_miniplayer(game);
	draw_ray(game);
	draw_minimap(game);
	draw_cross(game);
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
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->f[0], game->f[1], game->f[2], 150));
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

// void	draw_ray(t_game *game)
// {
// 	int r_num;
// 	int map_x;
// 	int map_y;
// 	int dof;
// 	float ray_x;
// 	float ray_y;
// 	float ray_angle;
// 	float xo;
// 	float yo;
// 	r_num = 0;
// 	ray_angle = game->player.angle_player - 0.523598; // - 30 degree
// 	while (r_num < 1440)
// 	// check for the horizontal lines:
// 	{
// 		dof = 0;
// 		float hor_distance = 100000;
// 		float hor_x;
// 		float hor_y;
// 		if (sin(ray_angle) < -0.001)
// 		{
// 			ray_y = (int)game->player.y_player / 64 * 64 - 0.001;
// 			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle); // tan(a) = tan(a - 180)
// 			xo = -64 / tan (ray_angle);
// 			yo = -64;
// 		}
// 		else if (sin(ray_angle) > 0.001)
// 		{
// 			ray_y = (int)game->player.y_player / 64 * 64 + 64.001;
// 			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle);
// 			yo = 64;
// 			xo = 64 / tan(ray_angle);
// 		}
// 		else
// 		{
// 			ray_x = game->player.x_player;
// 			ray_y = game->player.y_player;
// 			xo = 0;
// 			yo = 0;
// 			dof = 25;
// 		}
// 		while ( dof < 25)
// 		{
// 			map_x = (int) (ray_x) / 64 ;
// 			map_y = (int) (ray_y) / 64 ;
// 			if (map_x >= 0 && map_y >=0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
// 			{
// 				if (game->map[map_y][map_x] == '1')
// 				{
// 					hor_x = ray_x;
// 					hor_y = ray_y;
// 					hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,hor_x,hor_y);
// 					break ;
// 				}
// 				else
// 				{
// 					ray_x += xo;
// 					ray_y += yo;
// 					dof++;
// 				}
// 			}
// 			else
// 				break ;
// 		}
// //=	==========================================================================================================
// 		// check for the vertical lines:
// 		dof = 0;
// 		int flag = 0;
// 		float ver_distance = 100000;
// 		float ver_x;
// 		float ver_y;
// 		if (cos(ray_angle) < -0.01)
// 		{
// 			ray_x = (int)game->player.x_player / 64 * 64 - 0.001;
// 			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
// 			xo = -64;
// 			yo = -64 * tan(ray_angle);
// 		}
// 		else if (cos(ray_angle) > 0.01)
// 		{
// 			ray_x = (int)game->player.x_player / 64 * 64 + 64.001;
// 			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
// 			xo = 64;
// 			yo = 64 * tan(ray_angle);
// 		}
// 		else if (ray_angle * 180 / M_PI > 45 && ray_angle * 180 / M_PI <= 130)
// 		{
// 			ray_x = game->player.x_player;
// 			ray_y = game->player.y_player;
// 			xo = 0;
// 			yo = 0;
// 			dof = 25;
// 			flag = 1;
// 		}
// 		else
// 		{
// 			ray_x = game->player.x_player;
// 			ray_y = game->player.y_player;
// 			xo = 0;
// 			yo = 0;
// 			dof = 25;
// 		}
// 		while (dof < 25)
// 		{
// 			map_x = (int)(ray_x) / 64;
// 			map_y = (int)(ray_y) / 64;
// 			if (map_x >= 0 && map_y >= 0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
// 			{
// 				if (game->map[map_y][map_x] == '1')
// 				{
// 					ver_x = ray_x;
// 					ver_y = ray_y;
// 					ver_distance = calculate_dis(game->player.x_player ,game->player.y_player,ver_x,ver_y);
// 					break;
// 				}
// 				else
// 				{
// 					ray_x += xo;
// 					ray_y += yo;
// 					dof++;
// 				}
// 			}
// 			else
// 				break;
// 		}
// 		float wall_distance;
// 		wall_distance = 0;
// 		uint32_t wall_color;
// 		wall_color = 0;
// 		mlx_image_t *current_texture = NULL;
// 		if(ver_distance < hor_distance)
// 		{
// 			current_texture = (ray_x > game->player.x_player) ? game->tex.east_image : game->tex.west_image;
// 			wall_distance = ver_distance;
// 			if (flag == 1)
// 				current_texture = game->tex.south_image;
// 			ray_x = ver_x;
// 			ray_y = ver_y;
// 		}
// 		else if(ver_distance > hor_distance)
// 		{
// 			current_texture = (ray_y > game->player.y_player) ? game->tex.south_image : game->tex.north_image;
// 			if (flag == 1)
// 				current_texture = game->tex.south_image;
// 			wall_distance = hor_distance;
// 			ray_x = hor_x;
// 			ray_y = hor_y;
// 		}

// 		float cat = game->player.angle_player - ray_angle;
// 		wall_distance = wall_distance * cos(cat);
// 		float line_height = (game->map_unit_size * 960 ) / wall_distance;
// 		if (line_height > 960 )
// 			line_height = 960 ;
// 		int lineOff = 960/2- (line_height/2);
// 		float hit_pos_x;
// 		if (ver_distance < hor_distance)
// 			hit_pos_x = fmod(ray_y, game->map_unit_size) / game->map_unit_size; // Vertical wall hit
// 		else
// 			hit_pos_x = fmod(ray_x, game->map_unit_size) / game->map_unit_size; // Horizontal wall hit
// 		// Convert to texture coordinates (between 0 and texture width)
// 		uint32_t texture_x = (uint32_t)(hit_pos_x * current_texture->width);
// 		if (texture_x < 0)
// 			texture_x = 0;
// 		if (texture_x >= current_texture->width)
// 			texture_x = current_texture->width - 1;
// 		// Loop over each vertical line of the wall
// 		// Loop over the height of the wall slice
// 		uint32_t texture_y;
// 		uint32_t texture_color;
// 		for (int y = lineOff; y < lineOff + line_height; y++)
// 		{
// 			// Scale the y-coordinate to the texture height
// 			texture_y = (uint32_t)((y - lineOff) * current_texture->height / line_height);

// 			// Ensure texture coordinates are within bounds
// 			if (texture_y < 0)
// 				texture_y = 0;
// 			if (texture_y >= current_texture->height)
// 				texture_y = current_texture->height - 1;

// 			// Sample the texture color from (texture_x, texture_y)
// 			texture_color = ((uint32_t *)current_texture->pixels)[texture_y * current_texture->width + texture_x];

// 			t_color clr;

// 		clr.channel[ALPHA] = (texture_color >> 24) & 0xFF; // Extract Alpha
// 		clr.channel[RED] = (texture_color >> 16) & 0xFF;   // Extract Red
// 		clr.channel[GREEN] = (texture_color >> 8) & 0xFF;   // Extract Green
// 		clr.channel[BLUE] = texture_color & 0xFF;

// 			// Draw the pixel on the screen with the new color
// 			mlx_put_pixel(game->mlx_img, (r_num), y, clr.color);
// 		}
// 		// draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)ray_x, (int)ray_y, pixel_color(0, 0, 255, 255)); // blue
// 		ray_angle += 0.01745329/24; //next ray
// 		r_num++;
// 	}
// }


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
	uint32_t cross_color;
	int i;
	int reference;

	i = game->window_width * 0.5;
	reference = i + 10;
	cross_color = pixel_color(255,0,0,255); //white
	// draw the hor lines:
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, i, game->window_height / 2, cross_color);
		i++;
	}
	i = game->window_width * 0.5 + 15;
	reference = i + 10;
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, i, game->window_height / 2, cross_color);
		i++;
	}
	// draw the verticals lines:
	i = game->window_height * 0.5 - 13;
	reference = i + 10;
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, game->window_width * 0.5 + 12, i, cross_color);
		i++;
	}
	i = game->window_height * 0.5 + 3;
	reference = i + 10;
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, game->window_width * 0.5 + 12, i, cross_color);
		i++;
	}

}

void	draw_ray(t_game *game)
{
	int r_num;
	int dof;
	int flag;

	flag = 0;
	r_num = 0;
	game->ray.ra = game->player.angle_player - 0.523598; // - 30 degree
	while (r_num < 1440)
	{
		printf("%f\n", game->player.angle_player);
		calculate_horizontal_intraction(game, &dof);
		get_hor_point(game, dof);
		calculate_vertical_intraction(game, &dof, &flag);
		get_ver_point(game, dof);
//=	==========================================================================================================
		float wall_distance;
		wall_distance = 0;
		uint32_t wall_color;
		wall_color = 0;
		mlx_image_t *current_texture = NULL;
		if(game->ray.ver_distance < game->ray.hor_distance)
		{
			current_texture = (game->ray.rx > game->player.x_player) ? game->tex.east_image : game->tex.west_image;
			wall_distance = game->ray.ver_distance;
			if (flag == 1)
				current_texture = game->tex.south_image;
			game->ray.rx = game->ray.ver_x;
			game->ray.ry = game->ray.ver_y;
		}
		else if(game->ray.ver_distance > game->ray.hor_distance)
		{
			current_texture = (game->ray.ry > game->player.y_player) ? game->tex.south_image : game->tex.north_image;
			if (flag == 1)
				current_texture = game->tex.south_image;
			wall_distance = game->ray.hor_distance;
			game->ray.rx = game->ray.hor_x;
			game->ray.ry = game->ray.hor_y;
		}

		float cat = game->player.angle_player - game->ray.ra;
		wall_distance = wall_distance * cos(cat);
		float line_height = (game->map_unit_size * 960 ) / wall_distance;
		if (line_height > 960 )
			line_height = 960 ;
		int lineOff = 960/2- (line_height/2);
		float hit_pos_x;
		if (game->ray.ver_distance < game->ray.hor_distance)
			hit_pos_x = fmod(game->ray.ry, game->map_unit_size) / game->map_unit_size; // Vertical wall hit
		else
			hit_pos_x = fmod(game->ray.rx, game->map_unit_size) / game->map_unit_size; // Horizontal wall hit
		// Convert to texture coordinates (between 0 and texture width)
		uint32_t texture_x = (uint32_t)(hit_pos_x * current_texture->width);
		if (texture_x < 0)
			texture_x = 0;
		if (texture_x >= current_texture->width)
			texture_x = current_texture->width - 1;
		// Loop over each vertical line of the wall
		// Loop over the height of the wall slice
		uint32_t texture_y;
		uint32_t texture_color;
		for (int y = lineOff; y < lineOff + line_height; y++)
		{
			// Scale the y-coordinate to the texture height
			texture_y = (uint32_t)((y - lineOff) * current_texture->height / line_height);

			// Ensure texture coordinates are within bounds
			if (texture_y < 0)
				texture_y = 0;
			if (texture_y >= current_texture->height)
				texture_y = current_texture->height - 1;

			// Sample the texture color from (texture_x, texture_y)
			texture_color = ((uint32_t *)current_texture->pixels)[texture_y * current_texture->width + texture_x];

			t_color clr;

		clr.channel[ALPHA] = (texture_color >> 24) & 0xFF; // Extract Alpha
		clr.channel[RED] = (texture_color >> 16) & 0xFF;   // Extract Red
		clr.channel[GREEN] = (texture_color >> 8) & 0xFF;   // Extract Green
		clr.channel[BLUE] = texture_color & 0xFF;

			// Draw the pixel on the screen with the new color
			mlx_put_pixel(game->mlx_img, (r_num), y, clr.color);
		}
		draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)game->ray.rx, (int)game->ray.ry, pixel_color(0, 0, 255, 255)); // blue
		game->ray.ra += 0.01745329/24; //next ray
		r_num++;
	}
}
