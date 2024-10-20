/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:11:09 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/21 01:14:05 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	coordinate_corrector(t_game *game, char c)
{
	if (game->map[((int)game->player.y_player) / 64]
		[((int)game->player.x_player) / 64] == '1')
	{
		if (c == 'W')
		{
			game->player.y_player -= game->player.dy_player;
			game->player.x_player -= game->player.dx_player;
		}
		else if (c == 'S')
		{
			game->player.y_player += game->player.dy_player;
			game->player.x_player += game->player.dx_player;
		}
	}
}

void	coordinate_corrector2(t_game *game, char c)
{
	if (game->map[((int)game->player.y_player) / 64]
		[((int)game->player.x_player) / 64] == '1')
	{
		if (c == 'A')
		{
			game->player.x_player += cos(game->player.angle_player
					+ PI / 2) * 7;
			game->player.y_player += sin(game->player.angle_player
					+ PI / 2) * 7;
		}
		else if (c == 'D')
		{
			game->player.x_player -= cos(game->player.angle_player
					+ PI / 2) * 7;
			game->player.y_player -= sin(game->player.angle_player
					+ PI / 2) * 7;
		}
	}
}
