/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:29:10 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 05:13:14 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_map(t_game *game)
{
	game->map_unit_size = 64;
	game->map_unit_x = 30;
	game->map_unit_y = 16;
	game->name = "CUB3D";
	game->window_height = 960;
	game->window_width = 1440;
}

void init_player(t_game *game)
{
	game->player.x_player = game->start_pos[1] * 64 + 32;
	game->player.y_player = game->start_pos[0] * 64 + 32;
	if (game->orientation == 'N')
		game->player.angle_player =   DIR_NO;
	else if (game->orientation == 'S')
		game->player.angle_player =   DIR_SO;
	else if (game->orientation == 'E')
		game->player.angle_player =   DIR_EA;
	else if (game->orientation == 'W')
		game->player.angle_player =   DIR_WE;
	game->player.dx_player = cos (game->player.angle_player) * 5; // 5 is the speed of movment
	game->player.dy_player = sin (game->player.angle_player) * 5;
	game->player.health = 13;
	game->intro = true;
}

void	init_weapon_rendering(t_game *game)
{
		char			*cross_path;
	mlx_texture_t	*temp_texture;

	game->rend.weapon_tex = malloc(sizeof(mlx_image_t *));
	cross_path = "./textures/weapon.png";
	temp_texture = mlx_load_png(cross_path);
	if (temp_texture == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	*game->rend.weapon_tex = mlx_texture_to_image(game->mlx, temp_texture);
	if (*game->rend.weapon_tex == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	mlx_delete_texture(temp_texture);
}
void	init_crosshair_rendering(t_game *game)
{
	char			*cross_path;
	mlx_texture_t	*temp_texture;

	game->rend.crosshair_tex = malloc(sizeof(mlx_image_t *));
	cross_path = "./textures/aim _crosshair.png";
	temp_texture = mlx_load_png(cross_path);
	if (temp_texture == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	*game->rend.crosshair_tex = mlx_texture_to_image(game->mlx, temp_texture);
	if (*game->rend.crosshair_tex == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	mlx_delete_texture(temp_texture);
}

void	init_heal_rendering(t_game *game)
{
	char			*h0_path;
	char			*h1_path;
	mlx_texture_t	*temp_texture0;
	mlx_texture_t	*temp_texture1;

	game->rend.heal_0 = malloc(sizeof(mlx_image_t *));
	game->rend.heal_1 = malloc(sizeof(mlx_image_t *));
	h0_path = "./textures/Heal_0.png";
	h1_path = "./textures/Heal_1.png";
	temp_texture0 = mlx_load_png(h0_path);
	temp_texture1 = mlx_load_png(h1_path);
	if (temp_texture0 == NULL || temp_texture1 == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex(); //free!!!
	}
	*game->rend.heal_0 = mlx_texture_to_image(game->mlx, temp_texture0);
	*game->rend.heal_1 = mlx_texture_to_image(game->mlx, temp_texture1);
	if (*game->rend.heal_0 == NULL || *game->rend.heal_1 == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex(); //free!!!!
	}
	mlx_delete_texture(temp_texture0);
	mlx_delete_texture(temp_texture1);
}

void	intro(t_game *game)
{
	char			*intro_path;
	mlx_texture_t	*temp_texture;

	game->rend.intro = malloc(sizeof(mlx_image_t *));
	intro_path = "./textures/intro.png";
	temp_texture = mlx_load_png(intro_path);
	if (temp_texture == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	*game->rend.intro = mlx_texture_to_image(game->mlx, temp_texture);
	if (*game->rend.intro == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	mlx_delete_texture(temp_texture);
}
