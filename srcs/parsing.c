/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:13:07 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/24 18:12:54 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		find_width_map(t_game *game, char *reader);
void	fill_map_variables(t_game *game);
void	check_legitimacy(t_game *game, char *C, char *F);
void check_textures(t_game *game);

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
	int		temp_width;

	temp_width = 0;
	game->map_fd = open(map, O_RDONLY);
	if (game->map_fd < 0)
	{
		printf("Error\nCouldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	y = 0;
	fill_map_variables(game);
	reader = get_next_line(game->map_fd);
	game->map = ft_calloc(200, sizeof(char *));
	while (reader != NULL)
	{
		game->map[y] = ft_strdup(reader);
		free(reader);
		reader = get_next_line(game->map_fd);
		y++;
		game->height_map++;
		// game->width_map = find_width_map(game, reader);			
	}
	close(game->map_fd);
}

void fill_map_variables(t_game *game)
{
	char	*variable;
	char 	*C;
	char	*F;

	variable = get_next_line(game->map_fd);
	while (variable != NULL && variable[0] != '1')
	{
		if (ft_strncmp(variable, "SO", 2) == 0)
			game->SO = variable + 5;
		if (ft_strncmp(variable, "NO", 2) == 0)
			game->NO = variable + 5;
		if (ft_strncmp(variable, "WE", 2) == 0)
			game->WE = variable + 5;
		if (ft_strncmp(variable, "EA", 2) == 0)
			game->EA = variable + 5;
		if (ft_strncmp(variable, "C", 1) == 0)
			C = variable;
		if (ft_strncmp(variable, "F", 1) == 0)
			F = variable;
		variable = get_next_line(game->map_fd);			
	}
	check_legitimacy(game, C, F);
}

void	check_legitimacy(t_game *game, char *C, char *F)
{
	int i;
	char **c;
	char **f;

	check_textures(game);
	game->C = ft_malloc(4 * sizeof(int));
	game->F = ft_malloc(4 * sizeof(int));
	c = ft_split(C + 1, ',');
	f = ft_split(F + 1, ',');
	i = 0;
	while (c[i] != NULL && f[i] != NULL)
	{
		game->C[i] = ft_atoi(c[i]);
		game->F[i] = ft_atoi(f[i]);
		if ((game->C[i] < 0 || game->C[i] > 255) || (game->F[i] < 0 || game->F[i] > 255) || i > 2)
		{
			printf("Invalid RGB numbers\n");
			free_split(c);
			free_split(f);
			//free C and F
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void check_textures(t_game *game)
{
	int flag;

	flag = 0;
	if (!(ft_strncmp(game->SO, "path_to_the_south_texture", 25) == 0))
		flag = 1;
	if (!(ft_strncmp(game->WE, "path_to_the_west_texture", 24) == 0))
		flag = 1;
	if (!(ft_strncmp(game->EA, "path_to_the_east_texture", 24) == 0))
		flag = 1;
	if (!(ft_strncmp(game->NO, "path_to_the_north_texture", 25) == 0))
		flag = 1;
	if (flag == 1)
	{
		printf("Invalid textures paths\n");
		exit(EXIT_FAILURE);
	}
}
// int find_width_map(t_game *game, char *reader)
// {
// 	int length;

// 	length = ft_strlen(reader);
// 	while ((reader[length] != ' ' || reader[length] != '\n' 
// 		|| reader[length != '\0']) && length >= 0)
// 		length--;
// 	if (game->width_map < length)
// 		game->width_map = length;
// 	return (game->width_map);
// }
