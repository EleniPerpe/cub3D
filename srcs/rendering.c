/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:07:41 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/14 16:08:43 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_weapon(t_game *game)
{
	mlx_image_to_window(game->mlx, *game->rend.weapon_tex, game->window_width - 650 , game->window_height - 312);
}

void	render_walls(t_game *game, int r_num)
{
	float		wall_height;
	int			shift_to_center;

	wall_height = (game->map_unit_size * game->window_height) / game->rend.wall_distance; // the wall height depending on how far it is from the player
	if (wall_height > game->window_height) // for safty
		wall_height = game->window_height;
	shift_to_center = game->window_height/2- (wall_height/2); // to center the wall in the middle of the window (middle of the height)
	if (game->ray.ver_distance < game->ray.hor_distance)
		game->rend.texture_pos_x_rate = fmod(game->rend.wall_y, game->map_unit_size) / game->map_unit_size;
		// Vertical wall hit: example: wall_y = 160
		// fmod(160, 64) = 32 which is in the middle of the block
		// texture_pos_x = 32 / 64 = 0.5 that means it is in the half way from the texture width
	else
		game->rend.texture_pos_x_rate = fmod(game->rend.wall_x, game->map_unit_size) / game->map_unit_size; // Horizontal wall hit
	// Convert to texture coordinates (between 0 and texture width)
	// so if hit_po_x = 0.5 --> texture_pos_x * game->rend.current_texture->width will take the middle of the texture
	// so by knowing texture_pos_x we can take the color from the texture from the right place in it
	draw_tex_slice(game, wall_height, shift_to_center, r_num);
}

void	draw_tex_slice(t_game *game, float wall_height, int shift_to_center, int r_num)
{
	uint32_t	texture_color;
	int			y;

	y = shift_to_center;
	game->rend.texture_x = (uint32_t)(game->rend.texture_pos_x_rate * game->rend.current_texture->width);
	while (y < shift_to_center + wall_height)
	{
		// Scale the y-coordinate to the texture height
		game->rend.texture_y = (uint32_t)((y - shift_to_center) * game->rend.current_texture->height / wall_height);
		// Sample the texture color from (texture_x, texture_y)
		texture_color = ((uint32_t *)game->rend.current_texture->pixels)
			[game->rend.texture_y * game->rend.current_texture->width + game->rend.texture_x];
		// Draw the pixel on the screen with the new color
		mlx_put_pixel(game->mlx_img, (r_num ), y, get_color(texture_color));
		y++;
	}
}

