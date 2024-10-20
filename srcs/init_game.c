/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:29:10 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/20 21:52:47 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_map(t_game *game)
{
	game->map_unit_size = 64;
	game->map_unit_x = 30;
	game->map_unit_y = 16;
	game->name = "CUB3D";
	game->window_height = 960;
	game->window_width = 1440;
	game->frame_count = 0;
	game->frame_count2 = 0;
}

void	init_player(t_game *game)
{
	game->player.x_player = game->start_pos[1] * 64 + 32;
	game->player.y_player = game->start_pos[0] * 64 + 32;
	if (game->orientation == 'N')
		game->player.angle_player = (3 * PI / 2);
	else if (game->orientation == 'S')
		game->player.angle_player = PI / 2;
	else if (game->orientation == 'E')
		game->player.angle_player = 0;
	else if (game->orientation == 'W')
		game->player.angle_player = PI;
	game->player.dx_player = cos (game->player.angle_player) * 5;
	game->player.dy_player = sin (game->player.angle_player) * 5;
	game->player.health = 600;
	game->intro = true;
	game->player.dead = false;
}
