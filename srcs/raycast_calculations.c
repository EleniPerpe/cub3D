/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:53:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/20 20:43:31 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_horizontal_intraction(t_game *game, int *dof)
{
	if (sin(game->ray.ra) < -0.001)
	{
		game->ray.ry = (int)game->player.y_player / 64 * 64 - 0.001;
		game->ray.rx = game->player.x_player - (game->player.y_player - game->ray.ry) / tan(game->ray.ra); // tan(a) = tan(a - 180)
		game->ray.rx_step = -64 / tan (game->ray.ra);
		game->ray.ry_step = -64;
		*dof = 0;
	}
	else if (sin(game->ray.ra) > 0.001)
	{
		game->ray.ry = (int)game->player.y_player / 64 * 64 + 64.001;
		game->ray.rx = game->player.x_player - (game->player.y_player - game->ray.ry) / tan(game->ray.ra);
		game->ray.ry_step = 64;
		game->ray.rx_step = 64 / tan(game->ray.ra);
		*dof = 0;
	}
	else
	{
		game->ray.rx = game->player.x_player;
		game->ray.ry = game->player.y_player;
		*dof = 25;
	}
}

void	calculate_vertical_intraction(t_game *game,int *dof, int *flag)
{
	if (cos(game->ray.ra) < -0.001)
	{
		game->ray.rx = (int)game->player.x_player / 64 * 64 - 0.001;
		game->ray.ry = game->player.y_player - (game->player.x_player - game->ray.rx) * tan(game->ray.ra);
		game->ray.rx_step = -64;
		game->ray.ry_step = -64 * tan(game->ray.ra);
		*dof = 0;
	}
	else if (cos(game->ray.ra) > 0.001)
	{
		game->ray.rx = (int)game->player.x_player / 64 * 64 + 64.001;
		game->ray.ry = game->player.y_player - (game->player.x_player - game->ray.rx) * tan(game->ray.ra);
		game->ray.rx_step = 64;
		game->ray.ry_step = 64 * tan(game->ray.ra);
		*dof = 0;
	}
	else
	{
		game->ray.rx = game->player.x_player;
		game->ray.ry = game->player.y_player;
		*dof = 25;
		if (game->ray.ra * 180 / M_PI > 45 && game->ray.ra * 180 / M_PI <= 130)
			*flag = 1;
	}
}

bool	is_hor_wall(t_game *game)
{
	if (game->map[game->ray.map_index_y][game->ray.map_index_x] == '1')
		return (true) ;
	else if (game->map[game->ray.map_index_y][game->ray.map_index_x] == '2')
	{
		game->rend.hor_is_door = true;
		return (true) ;
	}
	else if (game->map[game->ray.map_index_y][game->ray.map_index_x] == '3')
	{
		game->rend.hor_is_fire = true;
		return (true) ;
	}
	return (false);
}

void	get_hor_point(t_game *game,int dof)
{
	while (dof < 25)
	{
		game->ray.map_index_x = (int) (game->ray.rx) / 64 ;
		game->ray.map_index_y = (int) (game->ray.ry) / 64 ;
		game->ray.hor_x = game->ray.rx;
		game->ray.hor_y = game->ray.ry;
		game->ray.hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.hor_x,game->ray.hor_y);
		if (game->ray.map_index_x >= 0 && game->ray.map_index_y >=0 && game->ray.map_index_y < game->height_map && game->ray.map_index_x < (int)ft_strlen(game->map[game->ray.map_index_y]) - 1)
		{
			if (is_hor_wall(game))
				break ;
			else
			{
				game->ray.rx += game->ray.rx_step;
				game->ray.ry += game->ray.ry_step;
				dof++;
			}
		}
		else
			break ;
	}
}

bool	is_ver_wall(t_game *game)
{
	if (game->map[game->ray.map_index_y][game->ray.map_index_x] == '1')
		return (true);
	else if (game->map[game->ray.map_index_y][game->ray.map_index_x] == '2')
	{
		game->rend.ver_is_door = true;
		return (true);
	}
	else if (game->map[game->ray.map_index_y][game->ray.map_index_x] == '3')
	{
		game->rend.ver_is_fire = true;
		return (true);
	}
	return (false);
}

void	get_ver_point(t_game *game, int dof)
{
	while (dof < 25)
	{
		game->ray.map_index_x = (int)(game->ray.rx) / 64;
		game->ray.map_index_y = (int)(game->ray.ry) / 64;
		game->ray.ver_x = game->ray.rx;
		game->ray.ver_y = game->ray.ry;
		game->ray.ver_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.ver_x,game->ray.ver_y);
		if (game->ray.map_index_x >= 0 && game->ray.map_index_y >= 0 && game->ray.map_index_y < game->height_map && game->ray.map_index_x < (int)ft_strlen(game->map[game->ray.map_index_y]) - 1 )
		{
			if (is_ver_wall(game))
				break ;
			else
			{
				game->ray.rx += game->ray.rx_step;
				game->ray.ry += game->ray.ry_step;
				dof++;
			}
		}
		else
			break;
	}
}
