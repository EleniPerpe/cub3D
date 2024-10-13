/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:55:14 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/13 21:33:49 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(1940, 960, "CUB3D", false);
	if (!game->mlx)
		return (1);
	game->mlx_img = mlx_new_image(game->mlx, 1940, 960);
	if (!game->mlx_img)
	{
		mlx_close_window(game->mlx);
		return (1);
	}
	if (mlx_image_to_window(game->mlx, game->mlx_img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		return (1);
	}
	return (0);
}
