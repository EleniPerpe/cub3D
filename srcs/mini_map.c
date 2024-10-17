/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:28:12 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 01:57:50 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void get_map_index(t_game *game, int *map_index_x, int *map_index_y)
{
	*map_index_x = (game->player.x_player - 32) / 64 - 4;
	*map_index_y = (game->player.y_player - 32) / 64 - 4;
	if (*map_index_x < 0)
		*map_index_x = 0;
	if(*map_index_y < 0)
		*map_index_y = 0;
}

void draw_minimap(t_game *game)
{
	int x;
	int y;
	uint32_t tile_color;
	int map_index_x;
	int map_index_y;

	get_map_index(game, &map_index_x, &map_index_y);
	y = 0;
	while (y < 9)
	{
		x =0;
		while (x < 9)
		{
			if (map_index_y + y < game->height_map && map_index_x + x < (int)ft_strlen(game->map[map_index_y + y]))
			{
				if (game->map[map_index_y + y][map_index_x + x] == '1')
					tile_color = pixel_color(70, 150, 55, 255);
				else if (game->map[map_index_y + y][map_index_x + x] == '0')
					tile_color = pixel_color(255, 255, 255, 255);
				else if (game->map[map_index_y + y][map_index_x + x] == '2')
					tile_color = pixel_color(10, 115, 150, 255);
				else if (game->map[map_index_y + y][map_index_x + x] == ' ' || game->map[map_index_y + y][map_index_x + x] == '\n')
					tile_color = pixel_color(0, 0, 0, 255);
				else
					tile_color = pixel_color(255, 255, 255, 255);
			}
			else
				tile_color = pixel_color(0, 0, 0, 255);
			draw_tiles(game, x * 32, y * 32, tile_color);
			x++;
		}
		y++;
	}
}

void draw_miniplayer(t_game *game)
{
	int x;
	int y;
	int map_index_x;
	int map_index_y;

	get_map_index(game, &map_index_x, &map_index_y);
	x = (game->player.x_player) / 64 - map_index_x;
	y = (game->player.y_player) / 64 - map_index_y;
	draw_tiles(game, x * 32, y * 32, pixel_color(255, 0, 0, 255));
	draw_line(game, x * 32 + 16, y * 32 + 16, x * 32 + 16 + 41
		* cos(game->player.angle_player), y * 32 + 16 + 41
			* sin(game->player.angle_player), pixel_color(255, 0, 0, 255));
}
