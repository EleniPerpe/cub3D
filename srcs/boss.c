/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:09:35 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 02:12:26 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_game(t_game *game)
{
	init_map(game);
	init_player(game);
	init_weapon_rendering(game);
	init_crosshair_rendering(game);
	init_heal_rendering(game);
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
	clean_window(game);
	// draw_player(game);
	// draw_map(game);
	calculate_ray(game);
	draw_minimap(game);
	draw_miniplayer(game);
	draw_cross(game);
	draw_weapon(game);
	draw_health(game);
}
