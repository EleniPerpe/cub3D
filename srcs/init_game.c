/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:29:10 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/10 18:44:46 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_map(t_game *game)
{
	game->map_unit_size = 64;
	game->map_unit_x = 30;
	game->map_unit_y = 16;
	game->name = "CUB3D";
	game->window_height = 1080;
	game->window_width = 1440;
}

void init_player(t_game *game)
{
	game->player.x_player = game->start_pos[1] * 64 + 32;
	game->player.y_player = game->start_pos[0] * 64 + 32;
	if (game->orientation == 'N')
		game->player.angle_player =   DIR_NO;
	else if (game->orientation == 'S')
		game->player.angle_player =   DIR_SO;
	else if (game->orientation == 'E')
		game->player.angle_player =   DIR_EA;
	else if (game->orientation == 'W')
		game->player.angle_player =   DIR_WE;
	// game->player.angle_player = 0;
	game->player.dx_player = cos (game->player.angle_player) * 5; // 5 is the speed of movment
	game->player.dy_player = sin (game->player.angle_player) * 5;
}
