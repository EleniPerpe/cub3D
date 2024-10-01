/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/01 23:57:06 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(void *param)
{
	t_game	*game;

	game = param;
	clean_window(game);
	draw_map(game);
	draw_player(game);
	draw_ray(game);
}

void	clean_window(t_game *game)
{
	// to draw a black window in the empty places
	uint32_t	color;
	int i;
	int j;

	i = 0;
	color = pixel_color(0, 0, 0, 255);
	while ( i <game->window_width)
	{
		j= 0;
		while ( j <game->window_height)
		{
			mlx_put_pixel(game->mlx_img, i, j, color);
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
	// printf("player_x = %f\nplayer_y: %f\n",game->player.x_player, game->player.y_player);
	// printf("player angle = %f\n",game->player.angle_player);
	color = pixel_color(255, 0, 0, 255);  // Red color
	while (i < 8)  // Loop over tile height
	{
		j = 0;
		while (j < 8)  // Loop over tile width
		{
			mlx_put_pixel(game->mlx_img, game->player.x_player + i, game->player.y_player + j, color);
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

	// y = 0;
	// while (game->map[y] != NULL)
	// {
	// 	x = 0;
	// 	while (game->map[y][x] != '\0')
	// 	{
	// 		printf("%c", game->map[y][x]);
	// 		x++;
	// 	}
	// 	y++;
	// }

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{

			// printf("the line is %d  ", y);
			// printf("the char is %c\n", game->map[y][x]);
			// if (game->map[y][x] == '\0')
			// 	break ;
			// Determine the color of the tile based on the map array
			if (game->map[y][x] == '1')
				tile_color = pixel_color(0, 100, 100, 255);
			else if (game->map[y][x] == '0')
				tile_color = pixel_color(255, 255, 255, 255);
			else if (game->map[y][x] == ' ' || game->map[y][x] == '\n')
				tile_color = pixel_color(0, 0, 0, 255);
			// Calculate the top-left corner of the tile
			xo = x * game->map_unit_size;
			// x = 0 ===> xo = 0
			// x = 1 ===> xo = 64 which will move us to the next block
			// x = mao_unit_x - 1 ===> xo = 1024
			yo = y * game->map_unit_size;
			// then we will color a square around this point each time
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

void	draw_ray(t_game *game)
{
	int r_num;
	int map_x;
	int map_y;
	// int mp; // map poistion where the ray hit the axes
	int dof;
	float ray_x;
	float ray_y;
	float ray_angle; // ray angle
	float xo; //offset which will move us to the next hit point
	float yo;

	r_num = 0;
	ray_angle = game->player.angle_player - 0.523598; // - 30 degree
	while (r_num <60)
		// check for the horizontal lines:
	{
		dof = 0;
		r_num++;
		float hor_distance = 100000;
		float hor_x;
		float hor_y;
		if (ray_angle > PI + 0.01 && ray_angle < 2 * PI - 0.01) // we must skip any angle near to PI because tan()
				//is not accurate and some times gives 0 in vlaues near PI +-
				// and we can'y divide on 0
		{
			ray_y = (int)game->player.y_player / 64 * 64 - 0.001;
			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle); // tan(a) = tan(a - 180)
			xo = -64 / tan (ray_angle);
			yo = -64;
		}
		else if (ray_angle < PI- 0.01 && ray_angle > 0.01)
		{
			ray_y = (int)game->player.y_player / 64 * 64 + 64.001; // little bit more to make sure that we are inside the tile
			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle);
			yo = 64;
			xo = 64 / tan(ray_angle);
		}
		else
		{
			ray_x = game->player.x_player;
			ray_y = game->player.y_player;
			xo = 0;
			yo = 0;
			dof = 8;
		}
		// printf("ray_y: %f\nray_x: %f\nxo: %f\n yo: %f\n",ray_y,ray_x,xo,yo);
		// printf("player angle: %f\n",game->player.angle_player);
		// printf("ray angle: %f\n",ray_angle);
		// printf("player x: %f\nplayer y: %f\n",game->player.x_player,game->player.y_player);
		while ( dof < 18)
		{
			map_x = (int) (ray_x) / 64 ;
			map_y = (int) (ray_y) / 64 ;

			// if ( map_x < game->window_width / 64 && map_x >= 0 && map_y < game->window_height / 64&& map_y >=0)
			// thank you boss
			if (map_x >= 0 && map_y >=0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
			{
				if (game->map[map_y][map_x] == '1')
				{
					hor_x = ray_x;
					hor_y = ray_y;
					hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,hor_x,hor_y);
					break ;
				}
				else
				{
					ray_x += xo;
					ray_y += yo;
					dof++;
				}
			}
			else
				break ;
		}
		// draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)ray_x, (int)ray_y, pixel_color(0, 255, 0, 255)); //green
//============================================================================================================
		// check for the vertical lines:
		dof = 0;
		float vir_distance = 100000;
		float vir_x;
		float vir_y;
		if (ray_angle > PI / 2 + 0.01 && ray_angle < 3 * PI / 2 - 0.01)
		{
			ray_x = (int)game->player.x_player / 64 * 64 - 0.001;
			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
			xo = -64;
			yo = -64 * tan(ray_angle);
		}
		else if (ray_angle < PI / 2 - 0.01 || ray_angle > 3 * PI / 2 + 0.01)
		{
			ray_x = (int)game->player.x_player / 64 * 64 + 64.001;
			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
			xo = 64;
			yo = 64 * tan(ray_angle);
		}
		else
		{
			ray_x = game->player.x_player;
			ray_y = game->player.y_player;
			xo = 0;
			yo = 0;
			dof = 8;
		}
		while (dof < 18)
		{
			map_x = (int)(ray_x) / 64;
			map_y = (int)(ray_y) / 64;
			if (map_x >= 0 && map_y >= 0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
			{
				if (game->map[map_y][map_x] == '1')
				{
					vir_x = ray_x;
					vir_y = ray_y;
					vir_distance = calculate_dis(game->player.x_player ,game->player.y_player,vir_x,vir_y);
					break;
				}
				else
				{
					ray_x += xo;
					ray_y += yo;
					dof++;
				}
			}
			else
				break;
		}
		if(vir_distance < hor_distance)
		{
			ray_x = vir_x;
			ray_y = vir_y;
		}
		if(vir_distance > hor_distance)
		{
			ray_x = hor_x;
			ray_y = hor_y;
		}
		draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)ray_x, (int)ray_y, pixel_color(0, 0, 255, 255)); // blue
		ray_angle += 0.01745329; //next ray
	}
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color)
{
	// uint32_t color = pixel_color(0, 255, 0, 255);
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
