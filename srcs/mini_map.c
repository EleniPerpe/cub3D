/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:28:12 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/10 15:34:47 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void get_map_index(t_game *game, int *map_index_x, int *map_index_y)
{
	*map_index_x = game->player.x_player/64 - 4;
	*map_index_y = game->player.y_player/64 - 4;
	if (*map_index_x < 0)
		*map_index_x = 0;
	else if(*map_index_x > game->window_width/64 - 13)
		*map_index_x = game->window_width/64 - 13;
	if(*map_index_y < 0)
		*map_index_y = 0;
	else if(*map_index_y > game->window_height/64 - 13)
		*map_index_y = game->window_height/64 - 13;
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
			if (game->map[map_index_y + y][map_index_x + x] == '1')
				tile_color = pixel_color(70, 150, 55, 255);
			else if (game->map[map_index_y + y][map_index_x + x] == '0')
				tile_color = pixel_color(255, 255, 255, 255);
			else if (game->map[map_index_y + y][map_index_x + x] == ' ' || game->map[map_index_y + y][map_index_x + x] == '\n')
				tile_color = pixel_color(0, 0, 0, 255);
			draw_tiles(game, x * 32, y * 32, tile_color);
			x++;
		}
		y++;
	}
}

void	draw_miniplayer(t_game *game)
{
	uint32_t	color;
	int	i;
	int	j;

	i = 0;
	int x = game->player.x_player / (game->window_width/ (9*32));
	int y = game->player.y_player / (game->window_height/(9*32));
	color = pixel_color(255, 0, 0, 255);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(game->mlx_img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
