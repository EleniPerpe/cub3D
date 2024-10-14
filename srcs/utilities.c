/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:09:17 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/14 16:10:24 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_rays(t_game * game,int *flag)
{
	game->ray.hor_distance = 100000;
	game->ray.ver_distance = 100000;
	game->ray.rx = 0;
	game->ray.ry = 0;
	game->ray.rx_step = 0;
	game->ray.ry_step = 0;
	game->ray.hor_x = 0;
	game->ray.hor_y = 0;
	game->ray.ver_x = 0;
	game->ray.ver_y = 0;
	*flag = 0;
}

uint32_t	get_color(uint32_t	texture_color)
{
		t_color clr;

		clr.channel[ALPHA] = (texture_color >> 24) & 0xFF; // Extract Alpha
		clr.channel[RED] = (texture_color >> 16) & 0xFF;   // Extract Red
		clr.channel[GREEN] = (texture_color >> 8) & 0xFF;   // Extract Green
		clr.channel[BLUE] = texture_color & 0xFF;
		return (clr.color);
}

int32_t	pixel_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
