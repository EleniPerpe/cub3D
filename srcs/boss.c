/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:09:35 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 23:01:27 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_game(t_game *game)
{
	init_map(game);
	init_player(game);
}

void	loops(t_game *game)
{
	mlx_loop_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, keyboard_control, game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(game->mlx, mouse_move, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	draw(void *param)
{
	t_game	*game;

	game = param;
	if (game->intro)
		mlx_image_to_window(game->mlx, game->tex.intro, 0 , 0);
	else if (game->player.dead)
	{
		mlx_delete_image(game->mlx, game->mlx_img);
		mlx_delete_image(game->mlx, game->tex.weapon);
		mlx_image_to_window(game->mlx, game->tex.gameover, 0 , 0);
	}
	else
	{
		mlx_delete_image(game->mlx, game->tex.intro);
		clean_window(game);
		// draw_player(game);
		// draw_map(game);
		calculate_ray(game);
		draw_minimap(game);
		draw_miniplayer(game);
		draw_cross(game);
		draw_weapon(game);
		check_fire(game);
		draw_health(game);
	}
}

void	check_fire(t_game *game)
{
	int x_map_index;
	int y_map_index;
	int i;
	int j;

	x_map_index = (game->player.x_player) / 64;
	y_map_index = (game->player.y_player) / 64;
	j = 0;
	if (game->map[y_map_index][x_map_index] == '3')
	{
			while (j < game->window_width)
			{
				i = 0;
				while (i < game->window_height)
				{
					if (i % 2 == 1)
						mlx_put_pixel(game->mlx_img, j, i, pixel_color(150, 0, 0, 150));
					i++;
				}
				j++;
		}
		game->player.health--;
	}
	if (game->player.health < 30)
		game->player.dead = true;
}
