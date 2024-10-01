/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:10:39 by rshatra           #+#    #+#             */
/*   Updated: 2024/09/30 13:49:45 by eperperi         ###   ########.fr       */
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
		game->player.y_player+= game->player.dy_player;
		game->player.x_player+= game->player.dx_player;
		coordinate_corrector(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) )
	{
		game->player.y_player -= game->player.dy_player;
		game->player.x_player -= game->player.dx_player;
		coordinate_corrector(game);
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.x_player += cos(game->player.angle_player - pi / 2) * 5;
		game->player.y_player += sin(game->player.angle_player - pi / 2) * 5;
		coordinate_corrector(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.x_player += cos(game->player.angle_player + pi / 2) * 5;
		game->player.y_player += sin(game->player.angle_player + pi / 2) * 5;
		coordinate_corrector(game);
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

void coordinate_corrector(t_game *game)
{
	if (game->player.y_player < 1)
		game->player.y_player = 0;
	else if (game->player.y_player > game->window_height - 9) // because the square size is 8 for the player
		game->player.y_player = game->window_height - 9;
	if (game->player.x_player > game->window_width - 9)
		game->player.x_player = game->window_width - 9;
	else if (game->player.x_player < 1)
		game->player.x_player = 0;
}
