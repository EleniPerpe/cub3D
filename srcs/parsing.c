/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:13:07 by eperperi          #+#    #+#             */
/*   Updated: 2024/10/20 18:56:07 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
void	check_textures(t_game *game);
int		is_only_spaces(char *str);
void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path);
void	ft_error_tex(void);

void	map_reader(t_game *game, char *map)
{
	char	*reader;
	char	**temp_map;
	game->map_fd = open(map, O_RDONLY);
	if (game->map_fd < 0)
	{
		printf("Error\nCouldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	fill_map_variables(game);
	reader = get_next_line(game->map_fd);
	while (is_only_spaces(reader) == 0)
		reader = get_next_line(game->map_fd);
	fill_real_map(game, reader);
	find_map_width(game);
	find_start_pos(game);
	ft_setup_temp_map(game, &temp_map);
	check_walls(temp_map, game->start_pos[0], game->start_pos[1], game);
	free_split(temp_map);
	close(game->map_fd);
}

int is_only_spaces(char *str)
{
	int i;
	i = 0;
	if (str[0] == '\n')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	keep_loading(t_game *game)
{
	ft_load_image(game, &game->tex.fire_flame[0], "./textures/fire/flame1.png");
	ft_load_image(game, &game->tex.fire_flame[1], "./textures/fire/flame2.png");
	ft_load_image(game, &game->tex.fire_flame[2], "./textures/fire/flame3.png");
	ft_load_image(game, &game->tex.fire_flame[3], "./textures/fire/flame4.png");
	ft_load_image(game, &game->tex.fire_flame[4], "./textures/fire/flame5.png");
	ft_load_image(game, &game->tex.fire_flame[5], "./textures/fire/flame6.png");
	ft_load_image(game, &game->tex.fire_flame[6], "./textures/fire/flame7.png");
	ft_load_image(game, &game->tex.fire_flame[7], "./textures/fire/flame8.png");
	ft_load_image(game, &game->tex.fire_flame[8], "./textures/fire/flame9.png");
	ft_load_image(game, &game->tex.fire_flame[9], "./textures/fire/flame10.png");
	ft_load_image(game, &game->tex.fire_flame[10], "./textures/fire/flame11.png");
	ft_load_image(game, &game->tex.fire_flame[11], "./textures/fire/flame12.png");
	ft_load_image(game, &game->tex.fire_flame[12], "./textures/fire/flame13.png");
	ft_load_image(game, &game->tex.fire_flame[13], "./textures/fire/flame14.png");
	ft_load_image(game, &game->tex.fire_flame[14], "./textures/fire/flame15.png");
	ft_load_image(game, &game->tex.fire_flame[15], "./textures/fire/flame16.png");
	ft_load_image(game, &game->tex.fire_flame[16], "./textures/fire/flame17.png");
	ft_load_image(game, &game->tex.fire_flame[17], "./textures/fire/flame18.png");
	ft_load_image(game, &game->tex.fire_flame[18], "./textures/fire/flame19.png");
	ft_load_image(game, &game->tex.fire_flame[19], "./textures/fire/flame20.png");
	ft_load_image(game, &game->tex.fire_flame[20], "./textures/fire/flame21.png");
}


void	check_textures(t_game *game)
{
	ft_load_image(game, &game->tex.east_image, game->ea);
	ft_load_image(game, &game->tex.west_image, game->we);
	ft_load_image(game, &game->tex.south_image, game->so);
	ft_load_image(game, &game->tex.north_image, game->no);
	ft_load_image(game, &game->tex.door, "./textures/door.png");
	ft_load_image(game, &game->tex.fire, "./textures/fire.png");
	ft_load_image(game, &game->tex.intro, "./textures/intro.png");
	ft_load_image(game, &game->tex.heal_0, "./textures/heal_0.png");
	ft_load_image(game, &game->tex.heal_1, "./textures/heal_1.png");
	ft_load_image(game, &game->tex.weapon, "./textures/weapon.png");
	ft_load_image(game, &game->tex.crosshair, "./textures/crosshair.png");
	ft_load_image(game, &game->tex.gameover, "./textures/gameover.png");
	ft_load_image(game, &game->tex.black_hole, "./textures/blackhole.png");
	keep_loading(game);
}

void    ft_load_image(t_game *game, mlx_image_t **image, const char *file_path)
{
	mlx_texture_t   *temp_texture;
	temp_texture = mlx_load_png(file_path);
	if (temp_texture == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	*image = mlx_texture_to_image(game->mlx, temp_texture);
	if (*image == NULL)
	{
		mlx_terminate(game->mlx);
		ft_error_tex();
	}
	mlx_delete_texture(temp_texture);
}

void    ft_error_tex(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
