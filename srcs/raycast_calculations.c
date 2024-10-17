/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:53:01 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/17 21:06:38 by rshatra          ###   ########.fr       */
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
		game->ray.rx_step = 0;
		game->ray.ry_step = 0;
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
		game->ray.rx_step = 0;
		game->ray.ry_step = 0;
		*dof = 25;
		if (game->ray.ra * 180 / M_PI > 45 && game->ray.ra * 180 / M_PI <= 130)
			*flag = 1;
	}
}

void	get_hor_point(t_game *game,int dof)
{
	int map_x;
	int map_y;

	while (dof < 25)
	{
		map_x = (int) (game->ray.rx) / 64 ;
		map_y = (int) (game->ray.ry) / 64 ;
		if (map_x >= 0 && map_y >=0 && map_y < game->height_map && map_x < (int)ft_strlen(game->map[map_y]) - 1)
		{
			if (game->map[map_y][map_x] == '1')
			{
				game->ray.hor_x = game->ray.rx;
				game->ray.hor_y = game->ray.ry;
				game->ray.hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.hor_x,game->ray.hor_y);
				break ;
			}
			else if (game->map[map_y][map_x] == '2')
			{
				game->ray.hor_x = game->ray.rx;
				game->ray.hor_y = game->ray.ry;
				game->ray.hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.hor_x,game->ray.hor_y);
				game->rend.hor_is_door = true;
				break ;
			}
			else if (game->map[map_y][map_x] == '3')
			{
				game->ray.hor_x = game->ray.rx;
				game->ray.hor_y = game->ray.ry;
				game->ray.hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.hor_x,game->ray.hor_y);
				game->rend.hor_is_fire = true;
				break ;
			}
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

void	get_ver_point(t_game *game,int dof)
{
	int map_x;
	int map_y;
	while (dof < 25)
	{
		map_x = (int)(game->ray.rx) / 64;
		map_y = (int)(game->ray.ry) / 64;

		if (map_x >= 0 && map_y >= 0 && map_y < game->height_map && map_x < (int)ft_strlen(game->map[map_y]) - 1 )
		{
			if (game->map[map_y][map_x] == '1')
			{
				game->ray.ver_x = game->ray.rx;
				game->ray.ver_y = game->ray.ry;
				game->ray.ver_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.ver_x,game->ray.ver_y);
				break;
			}
			else if (game->map[map_y][map_x] == '2')
			{
				game->ray.ver_x = game->ray.rx;
				game->ray.ver_y = game->ray.ry;
				game->ray.ver_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.ver_x,game->ray.ver_y);
				game->rend.ver_is_door = true;
				break;
			}
			else if (game->map[map_y][map_x] == '3')
			{
				game->ray.ver_x = game->ray.rx;
				game->ray.ver_y = game->ray.ry;
				game->ray.ver_distance = calculate_dis(game->player.x_player ,game->player.y_player,game->ray.ver_x,game->ray.ver_y);
				game->rend.ver_is_fire = true;
				break;
			}
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
