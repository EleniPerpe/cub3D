/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:10:39 by rshatra           #+#    #+#             */
/*   Updated: 2024/09/25 00:34:44 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	keyboard_control(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		// if (game->player.y_player < game->window_height - 1)
			game->player.y_player+= game->player.dy_player;
			game->player.x_player+= game->player.dx_player;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) )
	{
		// if (game->player.y_player > 0)
			game->player.y_player -= game->player.dy_player;
			game->player.x_player -= game->player.dx_player;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) )
	{
		// if (game->player.x_player > 0)
			game->player.x_player -= game->player.dx_player;
			game->player.y_player += game->player.dy_player;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) )
	{
		// if (game->player.x_player < game->window_width - 1)
			game->player.x_player += game->player.dx_player;
			game->player.y_player -= game->player.dy_player;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) )
	{
		game->player.angle_player -= 0.1;
		if (game->player.angle_player < 0)
			game->player.angle_player += 2 * pi;
		game->player.dx_player = cos (game->player.angle_player) * 5;
		game->player.dy_player = sin (game->player.angle_player) * 5;

	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) )
	{
		game->player.angle_player += 0.1;
		if (game->player.angle_player > 2 * pi)
			game->player.angle_player -= 2 * pi;
		game->player.dx_player = cos (game->player.angle_player) * 5;
		game->player.dy_player = sin (game->player.angle_player) * 5;
	}

}
