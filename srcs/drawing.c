/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:12:00 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/21 01:06:12 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_window(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->window_width)
	{
		j = 0;
		while (j < game->window_height)
		{
			if (j <= game->window_height / 2 - 30)
			{
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->c[0],
						game->c[1], game->c[2], 180));
				if (rand() % 10000 < 2)
					mlx_put_pixel(game->mlx_img, i, j,
						pixel_color(255, 255, 255, 255));
			}
			else
				mlx_put_pixel(game->mlx_img, i, j, pixel_color(game->f[0],
						game->f[1], game->f[2], 60));
			j++;
		}
		i++;
	}
}

void	draw_tiles(t_game *game, int xo, int yo, uint32_t tile_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			mlx_put_pixel(game->mlx_img, xo + j, yo + i, tile_color);
			j++;
		}
		i++;
	}
}

void	get_next_ponit(int *point1, int *d, int *err, int *point2)
{
	err[1] = err[0] * 2;
	if (err[1] > -d[1])
	{
		err[0] -= d[1];
		if (point1[0] < point2[0])
			point1[0] += 1;
		else
			point1[0] -= 1;
	}
	if (err[1] < d[0])
	{
		err[0] += d[0];
		if (point1[1] < point2[1])
			point1[1] += 1;
		else
			point1[1] -= 1;
	}
}

void	draw_line(t_game *game, int *point1, int x1, int y1)
{
	int			d[2];
	int			err[2];
	int			point2[2];

	point2[0] = x1;
	point2[1] = y1;
	d[0] = abs(x1 - point1[0]);
	d[1] = abs(y1 - point1[1]);
	err[0] = d[0] - d[1];
	while (1)
	{
		mlx_put_pixel(game->mlx_img, point1[0], point1[1],
			pixel_color(255, 0, 0, 255));
		if (point1[0] == x1 && point1[1] == y1)
			break ;
		get_next_ponit(point1, d, err, point2);
	}
}

float	calculate_dis(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
