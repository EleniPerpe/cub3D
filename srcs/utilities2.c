/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:15:46 by rshatra           #+#    #+#             */
/*   Updated: 2024/10/24 15:42:54 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error_tex(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	keep_loading(t_game *game)
{
	ft_load_image(game, &game->tex.fire_flame[0], "./textures/fire/fl1.png");
	ft_load_image(game, &game->tex.fire_flame[1], "./textures/fire/fl2.png");
	ft_load_image(game, &game->tex.fire_flame[2], "./textures/fire/fl3.png");
	ft_load_image(game, &game->tex.fire_flame[3], "./textures/fire/fl4.png");
	ft_load_image(game, &game->tex.fire_flame[4], "./textures/fire/fl5.png");
	ft_load_image(game, &game->tex.fire_flame[5], "./textures/fire/fl6.png");
	ft_load_image(game, &game->tex.fire_flame[6], "./textures/fire/fl7.png");
	ft_load_image(game, &game->tex.fire_flame[7], "./textures/fire/fl8.png");
	ft_load_image(game, &game->tex.fire_flame[8], "./textures/fire/fl9.png");
	ft_load_image(game, &game->tex.fire_flame[9], "./textures/fire/fl10.png");
	ft_load_image(game, &game->tex.fire_flame[10], "./textures/fire/fl11.png");
	ft_load_image(game, &game->tex.fire_flame[11], "./textures/fire/fl12.png");
	ft_load_image(game, &game->tex.fire_flame[12], "./textures/fire/fl13.png");
	ft_load_image(game, &game->tex.fire_flame[13], "./textures/fire/fl14.png");
	ft_load_image(game, &game->tex.fire_flame[14], "./textures/fire/fl15.png");
	ft_load_image(game, &game->tex.fire_flame[15], "./textures/fire/fl16.png");
	ft_load_image(game, &game->tex.fire_flame[16], "./textures/fire/fl17.png");
	ft_load_image(game, &game->tex.fire_flame[17], "./textures/fire/fl18.png");
	ft_load_image(game, &game->tex.fire_flame[18], "./textures/fire/fl19.png");
	ft_load_image(game, &game->tex.fire_flame[19], "./textures/fire/fl20.png");
	ft_load_image(game, &game->tex.fire_flame[20], "./textures/fire/fl21.png");
}

void	free_temp(t_game *game, char **temp)
{
	int	i;

	i = 0;
	while (i < game->height_map)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}
