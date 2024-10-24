/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:13:07 by eperperi          #+#    #+#             */
/*   Updated: 2024/10/23 14:40:59 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_textures(t_game *game);
int		is_only_spaces(char *str);
void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path);
void	ft_error_tex(void);
void	check_wall_boarders(int x, int y, t_game *game);

void	map_reader(t_game *game, char *map)
{
	char	*reader;

	game->map_fd = open(map, O_RDONLY);
	if (game->map_fd < 0)
	{
		printf("Error\nCouldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	fill_map_variables(game);
	reader = get_next_line(game->map_fd);
	while (is_only_spaces(reader) == 0)
	{
		free(reader);
		reader = get_next_line(game->map_fd);
	}
	fill_real_map(game, reader);
	find_map_width(game);
	find_start_pos(game);
	check_wall_boarders(game->start_pos[0], game->start_pos[1], game);
	ft_setup_temp_map(game, game->start_pos[0], game->start_pos[1]);
	close(game->map_fd);
}

void	check_wall_boarders(int x, int y, t_game *game)
{
	(void)game;
	if (x == 0 || y == 0)
	{
		printf("No closed map!\n");
		exit(EXIT_FAILURE);
	}
	if (y + 1 == ' ' || y + 1 == '\0' || y + 1 == '\n')
	{
		printf("No closed map!\n");
		exit(EXIT_FAILURE);
	}
	if (x + 1 >= game->height_map)
	{
		printf("No closed map!\n");
		exit(EXIT_FAILURE);
	}
}

int	is_only_spaces(char *str)
{
	int	i;

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

void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path)
{
	mlx_texture_t	*temp_texture;

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
