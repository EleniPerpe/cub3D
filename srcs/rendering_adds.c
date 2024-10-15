/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_adds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:36:55 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/16 01:37:16 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_weapon(t_game *game)
{
	mlx_image_to_window(game->mlx, *game->rend.weapon_tex, game->window_width - 650 , game->window_height - 312);
}

void draw_cross(t_game *game)
{
	mlx_image_to_window(game->mlx, *game->rend.crosshair_tex, game->window_width/2 - 30 , game->window_height/2 - 30);
}

void draw_health(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->player.health)
	{
		mlx_image_to_window(game->mlx, *game->rend.heal_1, (1020 + (i * 20)), 20);
		i++;
	}
	while (i < 20)
	{
		mlx_image_to_window(game->mlx, *game->rend.heal_0, (1020 + (i * 20)), 20);
		i++;
	}
}
