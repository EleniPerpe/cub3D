/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:29:10 by rshatra           #+#    #+#             */
/*   Updated: 2024/09/27 22:29:15 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_map(t_game *game)
{
	char	map_array_in[16][30] = { // we will take it later from the map


		{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
		{'1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
		{'1','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','1','1','1','0','0','1','1','1','1','1','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','1',' ','1','0','0','1','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
	};
	ft_memcpy(game->map_array, &map_array_in, sizeof(map_array_in));
	game->map_unit_size = 64;
	game->map_unit_x = 30;
	game->map_unit_y = 16;
	game->name = "CUB3D";
	game->window_height = 1080;
	game->window_width = 1920;
}

void init_player(t_game *game)
{
	game->player.x_player = 400; // must take the coordinate from the map
	game->player.y_player = 400;
	game->player.angle_player =   1; //must take it from game.player.start_angle
	game->player.dx_player = cos (game->player.angle_player) * 5; // 5 is the speed of movment
	game->player.dy_player = sin (game->player.angle_player) * 5;
}
