/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:28:12 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/21 00:52:12 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_map_index(t_game *game, int *map_index_x, int *map_index_y)
{
	*map_index_x = (game->player.x_player - 32) / 64 - 4;
	*map_index_y = (game->player.y_player - 32) / 64 - 4;
	if (*map_index_x < 0)
		*map_index_x = 0;
	if (*map_index_y < 0)
		*map_index_y = 0;
}

void	get_tile_color(t_game *game, uint32_t *tile_color, int x, int y)
{
	if (game->ray.map_index_y + y < game->height_map && game->ray.map_index_x
		+ x < (int)ft_strlen(game->map[game->ray.map_index_y + y]))
	{
		if (game->map[game->ray.map_index_y + y]
			[game->ray.map_index_x + x] == '1')
			*tile_color = pixel_color(70, 250, 255, 100);
		else if (game->map[game->ray.map_index_y + y]
			[game->ray.map_index_x + x] == '0')
			*tile_color = pixel_color(255, 255, 255, 150);
		else if (game->map[game->ray.map_index_y + y]
			[game->ray.map_index_x + x] == '2')
			*tile_color = pixel_color(0, 150, 100, 255);
		else if (game->map[game->ray.map_index_y + y]
			[game->ray.map_index_x + x] == '3')
			*tile_color = pixel_color(255, 0, 0, 100);
		else if (game->map[game->ray.map_index_y + y]
			[game->ray.map_index_x + x] == ' '
			|| game->map[game->ray.map_index_y + y]
			[game->ray.map_index_x + x] == '\n')
			*tile_color = pixel_color(0, 0, 0, 255);
		else
			*tile_color = pixel_color(255, 255, 255, 150);
	}
	else
		*tile_color = pixel_color(0, 0, 0, 255);
}

void	draw_minimap(t_game *game)
{
	int			y;
	int			x;
	uint32_t	tile_color;

	get_map_index(game, &game->ray.map_index_x, &game->ray.map_index_y);
	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 9)
		{
			get_tile_color(game, &tile_color, x, y);
			draw_tiles(game, x * 32, y * 32, tile_color);
			x++;
		}
		y++;
	}
}

void	draw_miniplayer(t_game *game)
{
	int	point1[2];
	int	map_index_x;
	int	map_index_y;

	get_map_index(game, &map_index_x, &map_index_y);
	point1[0] = (game->player.x_player) / 64 - map_index_x;
	point1[1] = (game->player.y_player) / 64 - map_index_y;
	point1[0] *= 32;
	point1[1] *= 32;
	draw_tiles(game, point1[0], point1[1], pixel_color(255, 0, 0, 255));
	point1[0] += 16;
	point1[1] += 16;
	draw_line(game, point1, point1[0] + 41
		* cos(game->player.angle_player), point1[1] + 41
		* sin(game->player.angle_player));
}
