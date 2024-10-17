/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_adds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:36:55 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 04:23:21 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_weapon(t_game *game)
{
	mlx_image_to_window(game->mlx, *game->rend.weapon_tex, game->window_width - 650 , game->window_height - 312);
}

void draw_cross(t_game *game)
{
	draw_health_section(game, *game->rend.crosshair_tex, game->window_width/2 - 30 , game->window_height/2 - 30);
	// mlx_image_to_window(game->mlx, *game->rend.crosshair_tex, game->window_width/2 - 30 , game->window_height/2 - 30);
}

void draw_health_section(t_game *game, mlx_image_t *heal, int x, int y)
{
	uint32_t m;
	uint32_t n;
	uint32_t texture_color;

	m = 0;
	while (m < heal->height)
	{
		n = 0;
		while (n < heal->width)
		{
			texture_color = ((uint32_t *)heal->pixels)[m * heal->width + n];
			if (texture_color >= 1000000000)
				mlx_put_pixel(game->mlx_img, x + n, y + m, get_color(texture_color));
			n++;
		}
		m++;
	}
}

void draw_health(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->player.health)
	{
		draw_health_section(game, *game->rend.heal_1, (1020 + (i * 20)), 20);
		i++;
	}
	while (i < 20)
	{
		draw_health_section(game, *game->rend.heal_0, (1020 + (i * 20)), 20);
		i++;
	}
}
