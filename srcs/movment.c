/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:10:39 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/13 21:57:11 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void coordinate_corrector(t_game *game, char c);

void	keyboard_control(void *param)
{
	t_game  *game;
	game = param;

	// int new_x;
	// int new_y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		// new_x = (int)game->player.x_player + game->player.dx_player * 14;
		// new_y = (int)game->player.y_player + game->player.dy_player * 14;
		// if (game->map[new_y / 64][new_x /64] != '1')
		// {
			game->player.y_player+= game->player.dy_player;
			game->player.x_player+= game->player.dx_player;
		// }
		coordinate_corrector(game, 'W');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) )
	{
		// new_x = (int)game->player.x_player - game->player.dx_player * 14;
		// new_y = (int)game->player.y_player - game->player.dy_player * 14;
		// if (game->map[new_y / 64][new_x /64] != '1')
		// {
			game->player.y_player -= game->player.dy_player;
			game->player.x_player -= game->player.dx_player;
		// }
		coordinate_corrector(game, 'S');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.x_player += cos(game->player.angle_player - PI / 2) * 7;
		game->player.y_player += sin(game->player.angle_player - PI / 2) * 7;
		coordinate_corrector(game, 'A');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.x_player += cos(game->player.angle_player + PI / 2) * 7;
		game->player.y_player += sin(game->player.angle_player + PI / 2) * 7;
		coordinate_corrector(game, 'D');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) )
	{
		game->player.angle_player -= 0.05;
		if (game->player.angle_player < 0)
			game->player.angle_player += 2 * PI;
		game->player.dx_player = cos (game->player.angle_player) * 5;
		game->player.dy_player = sin (game->player.angle_player) * 5;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) )
	{
		game->player.angle_player += 0.05;
		if (game->player.angle_player > 2 * PI)
			game->player.angle_player -= 2 * PI;
		game->player.dx_player = cos (game->player.angle_player) * 5;
		game->player.dy_player = sin (game->player.angle_player) * 5;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
	{
		game->player.dx_player = cos (game->player.angle_player) * 20; // 20 is the speed of movement
		game->player.dy_player = sin (game->player.angle_player) * 20;
	}
}

void coordinate_corrector(t_game *game, char c)
{
	if (game->player.y_player < 1)
		game->player.y_player = 1;
	//the down else if must be change to take the map height as limiter not the window height
	else if (game->player.y_player > game->window_height - 9) // because the square size is 8 for the player
		game->player.y_player = game->window_height - 9;
	// the same for width, it must be compared with the map width
	if (game->player.x_player > game->window_width - 9)
		game->player.x_player = game->window_width - 9;
	else if (game->player.x_player < 1)
		game->player.x_player = 1;
	if (game->map[((int)game->player.y_player)/ 64][((int)game->player.x_player)/64]== '1')
	{
		if (c == 'W')
		{
			game->player.y_player-= game->player.dy_player;
			game->player.x_player-= game->player.dx_player;
		}
		else if ( c == 'S')
		{
			game->player.y_player+= game->player.dy_player;
			game->player.x_player+= game->player.dx_player;
		}
		else if (c == 'A')
		{
			game->player.x_player += cos(game->player.angle_player + PI / 2) * 7;
			game->player.y_player += sin(game->player.angle_player + PI / 2) * 7;
		}
		else if (c == 'D')
		{
			game->player.x_player -= cos(game->player.angle_player + PI / 2) * 7;
			game->player.y_player -= sin(game->player.angle_player + PI / 2) * 7;
		}
	}
}
