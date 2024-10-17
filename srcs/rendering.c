/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:07:41 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 04:16:07 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void render_walls(t_game *game, int r_num)
{
	int		shift_to_down;
	int		offset;

	offset = 0;
	game->rend.wall_height = game->map_unit_size * (game->window_height) / game->rend.wall_distance;
	if (game->rend.wall_height > game->window_height)
		offset = (game->rend.wall_height - game->window_height) / 2;
	shift_to_down = game->window_height / 2 - (game->rend.wall_height / 2);
	if (game->ray.ver_distance < game->ray.hor_distance)
		game->rend.texture_pos_x_rate = fmod(game->rend.wall_y, game->map_unit_size) / game->map_unit_size;
	else
		game->rend.texture_pos_x_rate = fmod(game->rend.wall_x, game->map_unit_size) / game->map_unit_size;
	draw_tex_slice(game, shift_to_down, r_num, offset);
}

void draw_tex_slice(t_game *game, int shift_to_down, int r_num, int offset)
{
	game->rend.texture_x = (uint32_t)(game->rend.texture_pos_x_rate * game->rend.current_texture->width);
	if (game->rend.texture_x >= game->rend.current_texture->width)
		game->rend.texture_x = game->rend.current_texture->width - 1;
	if (game->rend.wall_height <= game->window_height)
		draw_far_slice(game, r_num, shift_to_down);
	else
		draw_close_slice(game, r_num, offset);
}


void	draw_far_slice(t_game *game, int r_num, int shift_to_down)
{
	uint32_t	texture_color;
	int			y;
	float		texture_step;
	float		texture_y;

	y = shift_to_down;
	texture_y = 0;
	texture_step = (float)game->rend.current_texture->height / game->rend.wall_height;
	while (y < shift_to_down + game->rend.wall_height)
	{
		game->rend.texture_y = (uint32_t)texture_y;
		if (game->rend.texture_y >= game->rend.current_texture->height)
			game->rend.texture_y = game->rend.current_texture->height - 1;
		texture_color = ((uint32_t *)game->rend.current_texture->pixels)
			[game->rend.texture_y * game->rend.current_texture->width + game->rend.texture_x];
		mlx_put_pixel(game->mlx_img, r_num, y, get_color(texture_color));
		y++;
		texture_y += texture_step;
	}
}

void	draw_close_slice(t_game *game,  int r_num, int offset)
{
	uint32_t	texture_color;
	int			y;
	float		texture_step;
	float		texture_y;

	y = 0;
	texture_step = (float)game->rend.current_texture->height / game->rend.wall_height;
	texture_y = offset * texture_step;
	while (y < game->window_height)
	{
		game->rend.texture_y = (uint32_t)texture_y % game->rend.current_texture->height;
		if (game->rend.texture_y >= game->rend.current_texture->height)
			game->rend.texture_y = game->rend.current_texture->height - 1;
		texture_color = ((uint32_t *)game->rend.current_texture->pixels)
			[game->rend.texture_y * game->rend.current_texture->width + game->rend.texture_x];
		mlx_put_pixel(game->mlx_img, r_num, y, get_color(texture_color));
		y++;
		texture_y += texture_step;
	}
}
