/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:53:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/21 01:30:29 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_horizontal_intraction(t_game *game, int *dof)
{
	if (sin(game->ray.ra) < -0.001)
	{
		game->ray.ry = (int)game->player.y_player / 64 * 64 - 0.001;
		game->ray.rx = game->player.x_player - (game->player.y_player
				- game->ray.ry) / tan(game->ray.ra);
		game->ray.rx_step = -64 / tan (game->ray.ra);
		game->ray.ry_step = -64;
	}
	else if (sin(game->ray.ra) > 0.001)
	{
		game->ray.ry = (int)game->player.y_player / 64 * 64 + 64.001;
		game->ray.rx = game->player.x_player - (game->player.y_player
				- game->ray.ry) / tan(game->ray.ra);
		game->ray.ry_step = 64;
		game->ray.rx_step = 64 / tan(game->ray.ra);
	}
	else
	{
		game->ray.rx = game->player.x_player;
		game->ray.ry = game->player.y_player;
		*dof = 25;
	}
}

void	calculate_vertical_intraction(t_game *game, int *dof, int *flag)
{
	if (cos(game->ray.ra) < -0.001)
	{
		game->ray.rx = (int)game->player.x_player / 64 * 64 - 0.001;
		game->ray.ry = game->player.y_player - (game->player.x_player
				- game->ray.rx) * tan(game->ray.ra);
		game->ray.rx_step = -64;
		game->ray.ry_step = -64 * tan(game->ray.ra);
	}
	else if (cos(game->ray.ra) > 0.001)
	{
		game->ray.rx = (int)game->player.x_player / 64 * 64 + 64.001;
		game->ray.ry = game->player.y_player - (game->player.x_player
				- game->ray.rx) * tan(game->ray.ra);
		game->ray.rx_step = 64;
		game->ray.ry_step = 64 * tan(game->ray.ra);
	}
	else
	{
		game->ray.rx = game->player.x_player;
		game->ray.ry = game->player.y_player;
		*dof = 25;
		if (game->ray.ra * 180 / M_PI > 45 && game->ray.ra * 180 / M_PI <= 130)
			*flag = 1;
	}
}
