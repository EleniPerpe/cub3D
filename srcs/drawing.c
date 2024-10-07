/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/07 17:01:00 by eperperi         ###   ########.fr       */
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
	draw_cross(game);
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
			if (j <= game->window_height / 2 - 70)
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->c[0], game->c[1], game->c[2], 0));
			else
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->f[0], game->f[1], game->f[2], 0));
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

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (/*game->map[y][x] != '\0'*/ x < 15)
		{
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

// void	draw_ray(t_game *game)
// {
// 	int r_num;
// 	int map_x;
// 	int map_y;
// 	// int mp; // map poistion where the ray hit the axes
// 	int dof;
// 	float ray_x;
// 	float ray_y;
// 	float ray_angle; // ray angle
// 	float xo; //offset which will move us to the next hit point
// 	float yo;

// 	r_num = 0;
// 	ray_angle = game->player.angle_player - 0.523598; // - 30 degree
// 	while (r_num <60)
// 		// check for the horizontal lines:
// 	{
// 		dof = 0;
// 		r_num++;
// 		float hor_distance = 100000;
// 		float hor_x;
// 		float hor_y;
// 		// if (ray_angle > PI + 0.1 && ray_angle < 2 * PI - 0.1) // we must skip any angle near to PI because tan()
// 				//is not accurate and some times gives 0 in vlaues near PI +-
// 				// and we can'y divide on 0
// 		if (sin(ray_angle) < -0.001)
// 		{
// 			ray_y = (int)game->player.y_player / 64 * 64 - 0.001;
// 			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle); // tan(a) = tan(a - 180)
// 			xo = -64 / tan (ray_angle);
// 			yo = -64;
// 		}
// 		else if (sin(ray_angle) > 0.001) /*(ray_angle < PI- 0.1 && ray_angle > 0.1)*/
// 		{
// 			ray_y = (int)game->player.y_player / 64 * 64 + 64.001; // little bit more to make sure that we are inside the tile
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
// 			dof = 18;
// 		}
// 		while ( dof < 18)
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
// 		printf("in hor the rau point is: x=%f y=%f\n",ray_x, ray_y);
// //============================================================================================================
// 		// check for the vertical lines:
// 		dof = 0;
// 		float vir_distance = 100000;
// 		float vir_x;
// 		float vir_y;
// 		if (cos(ray_angle) < -0.01) /*(ray_angle > PI / 2 + 0.01 && ray_angle < 3 * PI / 2 - 0.01)*/
// 		{
// 			ray_x = (int)game->player.x_player / 64 * 64 - 0.001;
// 			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
// 			xo = -64;
// 			yo = -64 * tan(ray_angle);
// 		}
// 		else if (cos(ray_angle) > 0.01) /*(ray_angle < PI / 2 - 0.01 || ray_angle > 3 * PI / 2 + 0.01)*/
// 		{
// 			ray_x = (int)game->player.x_player / 64 * 64 + 64.001;
// 			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
// 			xo = 64;
// 			yo = 64 * tan(ray_angle);
// 		}
// 		else
// 		{
// 			ray_x = game->player.x_player;
// 			ray_y = game->player.y_player;
// 			xo = 0;
// 			yo = 0;
// 			dof = 18;
// 		}
// 		while (dof < 18)
// 		{
// 			map_x = (int)(ray_x) / 64;
// 			map_y = (int)(ray_y) / 64;
// 			if (map_x >= 0 && map_y >= 0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
// 			{
// 				if (game->map[map_y][map_x] == '1')
// 				{
// 					vir_x = ray_x;
// 					vir_y = ray_y;
// 					vir_distance = calculate_dis(game->player.x_player ,game->player.y_player,vir_x,vir_y);
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
// 		printf("in ver the rau point is: x=%f y=%f\n",ray_x, ray_y);
// 		if(vir_distance < hor_distance)
// 		{
// 			ray_x = vir_x;
// 			ray_y = vir_y;
// 		}
// 		if(vir_distance > hor_distance)
// 		{
// 			ray_x = hor_x;
// 			ray_y = hor_y;
// 		}
// 		draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)ray_x, (int)ray_y, pixel_color(0, 0, 255, 255)); // blue
// 		ray_angle += 0.01745329; //next ray
// 		printf("the player angle is: %f\n", game->player.angle_player);
// 		printf("the ray_angle is: %f\n", ray_angle);
// 		printf("the horizintal dis is: %f\n", hor_distance);
// 		printf("the vertical dis is: %f\n", vir_distance);
// 	}
// }

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
	while (r_num <720)
	// check for the horizontal lines:
	{
		dof = 0;
		r_num++;
		float hor_distance = 100000;
		float hor_x;
		float hor_y;
		// if (ray_angle > PI && ray_angle < 2 * PI) // we must skip any angle near to PI because tan()
		        //is not accurate and some times gives 0 in vlaues near PI +-
		        // and we can'y divide on 0
		if (sin(ray_angle) < -0.001)
		{
			ray_y = (int)game->player.y_player / 64 * 64 - 0.001;
			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle); // tan(a) = tan(a - 180)
			xo = -64 / tan (ray_angle);
			yo = -64;
		}
		else if (sin(ray_angle) > 0.001)/*(ray_angle < PI && ray_angle > 0)*/
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
			dof = 25;
		}
		// printf("ray_y: %f\nray_x: %f\nxo: %f\n yo: %f\n",ray_y,ray_x,xo,yo);
		// printf("player angle: %f\n",game->player.angle_player);
		// printf("ray angle: %f\n",ray_angle);
		// printf("player x: %f\nplayer y: %f\n",game->player.x_player,game->player.y_player);
		while ( dof < 25)
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
//=	==========================================================================================================
		// check for the vertical lines:
		dof = 0;
		int flag = 0;
		float ver_distance = 100000;
		float ver_x;
		float ver_y;
		if (cos(ray_angle) < -0.01) /*(ray_angle > PI / 2 + 0.01 && ray_angle < 3 * PI / 2 - 0.01)*/
		{
			// printf("%f\n", ray_angle * 180 / M_PI);
			ray_x = (int)game->player.x_player / 64 * 64 - 0.001;
			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
			xo = -64;
			yo = -64 * tan(ray_angle);
		}
		else if (cos(ray_angle) > 0.01) /*(ray_angle < PI / 2 - 0.01 || ray_angle > 3 * PI / 2 + 0.01)*/
		{
			ray_x = (int)game->player.x_player / 64 * 64 + 64.001;
			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
			xo = 64;
			yo = 64 * tan(ray_angle);
		}
		else if (ray_angle * 180 / M_PI > 45 && ray_angle * 180 / M_PI <= 130)
		{
			ray_x = game->player.x_player;
			ray_y = game->player.y_player;
			xo = 0;
			yo = 0;
			dof = 25;
			flag = 1;
		}
		else
		{
			ray_x = game->player.x_player;
			ray_y = game->player.y_player;
			xo = 0;
			yo = 0;
			dof = 25;
		}
		while (dof < 25)
		{
			map_x = (int)(ray_x) / 64;
			map_y = (int)(ray_y) / 64;
			if (map_x >= 0 && map_y >= 0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
			{
				if (game->map[map_y][map_x] == '1')
				{
					ver_x = ray_x;
					ver_y = ray_y;
					ver_distance = calculate_dis(game->player.x_player ,game->player.y_player,ver_x,ver_y);
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
		float wall_distance;
		wall_distance = 0;
		uint32_t wall_color;
		wall_color = 0;
		mlx_image_t *current_texture = NULL;
		if(ver_distance < hor_distance)
		{
			current_texture = (ray_x > game->player.x_player) ? game->tex.east_image : game->tex.west_image;
			wall_distance = ver_distance;
			if (flag == 1)
				current_texture = game->tex.south_image;
			ray_x = ver_x;
			ray_y = ver_y;
			// wall_color = pixel_color(255, 0, 0, 150);
		}
		else if(ver_distance > hor_distance)
		{
			current_texture = (ray_y > game->player.y_player) ? game->tex.south_image : game->tex.north_image;
			if (flag == 1)
				current_texture = game->tex.south_image;
			// if (ray_y > 0)
       		// 	current_texture = game->tex.south_image; // Ray is pointing down, so hit South wall
			// else
			// 	current_texture = game->tex.north_image;
			wall_distance = hor_distance;
			ray_x = hor_x;
			ray_y = hor_y;
			// wall_color = pixel_color(70, 124, 100, 255);
		}

		float cat = game->player.angle_player - ray_angle;
		wall_distance = wall_distance * cos(cat);
		float line_height = (game->map_unit_size * 960 ) / wall_distance;
		if (line_height > 960 )
			line_height = 960 ;
		int lineOff = 960/2- (line_height/2);
		float hit_pos_x;
		if (ver_distance < hor_distance)
			hit_pos_x = fmod(ray_y, game->map_unit_size) / game->map_unit_size; // Vertical wall hit
		else
			hit_pos_x = fmod(ray_x, game->map_unit_size) / game->map_unit_size; // Horizontal wall hit
		// Convert to texture coordinates (between 0 and texture width)
		uint32_t texture_x = (int)(hit_pos_x * current_texture->width);
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
			texture_y = (int)((y - lineOff) * current_texture->height / line_height);
			
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
			mlx_put_pixel(game->mlx_img, (r_num + 1000), y, clr.color);

			
		}

		
		draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)ray_x, (int)ray_y, pixel_color(0, 0, 255, 255)); // blue
		// draw_wall_line(game, (r_num * 8 + 960), lineOff, (r_num * 8 + 960), lineOff + line_height, wall_color);
		// draw_wall_line(game, (r_num * 8 + 960), lineOff, (r_num * 8 + 960), lineOff + line_height, texture_color);
		ray_angle += 0.01745329/12; //next ray
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

void draw_wall_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color)
{
	// Thickness is 8 pixels, so we'll draw parallel lines offset by thickness / 2
	int thickness = 8;

	// Check if coordinates are outside the window
	if (x1 < 0 || y1 < 0 || x0 < 0 || y0 < 0)
		return;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	// int err = dx - dy;

	for (int w = -thickness / 2; w <= thickness / 2; w++)
	{
		int x_offset = (dy > dx) ? w : 0; // Offset horizontally if line is more vertical
		int y_offset = (dx >= dy) ? w : 0; // Offset vertically if line is more horizontal

		int tx0 = x0 + x_offset;
		int ty0 = y0 + y_offset;
		int tx1 = x1 + x_offset;
		int ty1 = y1 + y_offset;

		// Draw the line with the offset applied
		int temp_dx = abs(tx1 - tx0);
		int temp_dy = abs(ty1 - ty0);
		int temp_err = temp_dx - temp_dy;

		while (1)
		{
			// Ensure pixel is within the window boundaries
			if (tx0 >= 0 && tx0 < game->window_width && ty0 >= 0 && ty0 < game->window_height)
				mlx_put_pixel(game->mlx_img, tx0, ty0, color);

			// Check if we've reached the end point
			if (tx0 == tx1 && ty0 == ty1)
				break;

			int err2 = temp_err * 2;
			if (err2 > -temp_dy)
			{
				temp_err -= temp_dy;
				tx0 += (tx0 < tx1) ? 1 : -1;
			}
			if (err2 < temp_dx)
			{
				temp_err += temp_dx;
				ty0 += (ty0 < ty1) ? 1 : -1;
			}
		}
	}
}

void draw_cross(t_game *game)
{
	uint32_t cross_color;
	int i;
	int reference;

	i = game->window_width * 0.75;
	reference = i + 10;
	cross_color = pixel_color(game->c[0],game->c[1],game->c[2],255); //white
	// cross_color = pixel_color(255,255,255,255); //white
	// draw the hor lines:
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, i, game->window_height / 2 - 70, cross_color);
		i++;
	}
	i = game->window_width * 0.75 + 15;
	reference = i + 10;
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, i, game->window_height / 2 - 70, cross_color);
		i++;
	}
	// draw the verticals lines:
	i = game->window_height * 0.5 - 83;
	reference = i + 10;
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, game->window_width * 0.75 + 12, i, cross_color);
		i++;
	}
	i = game->window_height * 0.5 - 68;
	reference = i + 10;
	while (i < reference)
	{
		mlx_put_pixel(game->mlx_img, game->window_width * 0.75 + 12, i, cross_color);
		i++;
	}

}
