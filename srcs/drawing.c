/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/09/25 20:21:32 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(void *param)
{
	t_game	*game;

	game = param;
	draw_map(game);
	draw_player(game);
}

void	draw_player(t_game *game)
{
	uint32_t	color;

	color = pixel_color(255, 0, 0, 255);  // Red color
	for (int i = 0; i < 8; i++)  // Loop over tile height
	{
		for (int j = 0; j < 8; j++)  // Loop over tile width
		{
			mlx_put_pixel(game->mlx_img, game->player.x_player + i, game->player.y_player + j, color);
		}
	}
	printf("the angel is : %f\n",game->player.angle_player);
}

void draw_map(t_game *game)
{
	int GRIDLINE_WIDTH = 1;
	int x;
	int y;
	int xo;
	int yo;
	int i;
	int j;

	uint32_t tile_color;
	uint32_t gridline_color;

	y = 0;
	i = 0;
	gridline_color = pixel_color(0, 0, 0, 255);

	while (y < game->map_unit_y)
	{
		x = 0;
		while (x < game->map_unit_x)
		{
			// Determine the color of the tile based on the map array
			if (game->map_array[y * game->map_unit_x + x] == 1)
				tile_color = pixel_color(0, 100, 100, 255);
			else
				tile_color = pixel_color(255, 255, 255, 255);
			// Calculate the top-left corner of the tile
			xo = x * game->map_unit_size;
			// x = 0 ===> xo = 0
			// x = 1 ===> xo = 64 which will move us to the next block
			// x = mao_unit_x - 1 ===> xo = 1024
			yo = y * game->map_unit_size;
			// then we will color a square around this point each time
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
			x++;
		}
		y++;
	}
}

int32_t	pixel_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
