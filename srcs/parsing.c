/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:13:07 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/24 14:13:57 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	arg_check(int argc, char *arg)
{
	int	argv_len;

	if (argc != 2)
	{
		printf("NOT THE RIGHT AMOUNT OF ARGUMENTS\n");
		exit(EXIT_FAILURE);
	}
	argv_len = ft_strlen(arg);
	if (ft_strncmp(arg + argv_len - 4, ".cub", 5) != 0)
	{
		printf("NOT A MAP\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	check_map_walls(t_game *game, int i, int j)
{
	while (i < game->height_map)
	{
		j = 0;
		while (j < game->width_map)
		{
			if ((i == 0 || i == game->height_map - 1) && game->map[i][j] != '1')
				ft_error_exit(game, "Error\nThere are no walls around!");
			if ((j == 0 || j == game->width_map - 1) && game->map[i][j] != '1')
				ft_error_exit(game, "Error\nThere are no walls around!");
			j++;
		}
		i++;
	}
	// check_valid_assets(game);
	// check_unknown(game);
}
void	map_reader(t_game *game, char *map)
{
	char	*reader;
	int		y;

	game->map_fd = open(map, O_RDONLY);
	if (game->map_fd < 0)
	{
		printf("Error\nCouldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	y = 0;
	game->map = ft_calloc(200, sizeof(char *));
	reader = get_next_line(game->map_fd);
	while (reader != NULL)
	{
		game->map[y] = ft_strdup(reader);
		free(reader);
		reader = get_next_line(game->map_fd);
		y++;
		game->height_map++;
	}
	close(game->map_fd);
	// game->width_map = map_width(game->map[0]);
}