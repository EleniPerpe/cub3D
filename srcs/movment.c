/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:10:39 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 05:15:50 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void coordinate_corrector(t_game *game, char c);

void	keyboard_control(void *param)
{
	t_game  *game;

	game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
	{
		game->player.dx_player = cos (game->player.angle_player) * 17; // 20 is the speed of movement
		game->player.dy_player = sin (game->player.angle_player) * 17;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		game->intro = false;
	sw(game);
	ad(game);
	left_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void coordinate_corrector(t_game *game, char c)
{
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

void	sw(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (!mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		{
			game->player.dx_player = cos (game->player.angle_player) * 5;
			game->player.dy_player = sin (game->player.angle_player) * 5;
		}
		game->player.y_player+= game->player.dy_player;
		game->player.x_player+= game->player.dx_player;
		coordinate_corrector(game, 'W');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) )
	{
		if (!mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		{
			game->player.dx_player = cos (game->player.angle_player) * 5;
			game->player.dy_player = sin (game->player.angle_player) * 5;
		}
		game->player.y_player -= game->player.dy_player;
		game->player.x_player -= game->player.dx_player;
		coordinate_corrector(game, 'S');
	}
}

void	ad(t_game *game)
{
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
}

void	left_right(t_game *game)
{
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
}
void	mouse_move(double x, double y, void *param)
{
	t_game  *game;

	(void)y;
	static int previous_x;
	game = param;

	if (x > previous_x)
	{
		game->player.angle_player += 0.07;
		if (game->player.angle_player > 2 * PI)
			game->player.angle_player -= 2 * PI;
		game->player.dx_player = cos (game->player.angle_player) * 5;
		game->player.dy_player = sin (game->player.angle_player) * 5;
	}
	else if (x < previous_x)
	{
		game->player.angle_player -= 0.07;
		if (game->player.angle_player < 0)
			game->player.angle_player += 2 * PI;
		game->player.dx_player = cos (game->player.angle_player) * 5;
		game->player.dy_player = sin (game->player.angle_player) * 5;
	}
	mlx_set_mouse_pos(game->mlx, game->window_width / 2, game->width_map / 2);
	previous_x = game->window_width / 2;
}
