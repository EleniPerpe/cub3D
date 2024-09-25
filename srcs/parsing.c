/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:13:07 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/25 19:56:13 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		find_width_map(t_game *game, char *reader);
int		fill_map_variables(t_game *game);
int		check_rgb(char *variable, int **color);
void	check_textures(t_game *game);
int		assign_texture(char **destination, char *variable, char *prefix);
int		is_only_spaces(char *str);

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
	int		info_count;

	info_count = 0;
	game->map_fd = open(map, O_RDONLY);
	if (game->map_fd < 0)
	{
		printf("Error\nCouldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	y = 0;
	info_count = fill_map_variables(game);
	reader = get_next_line(game->map_fd);
	// printf("Ayti epistrefei : %s.\n", reader);
	while (is_only_spaces(reader) == 0)
		reader = get_next_line(game->map_fd);
	game->map = ft_calloc(200, sizeof(char *));
	while (reader != NULL)
	{
		game->map[y] = ft_strdup(reader);
		// printf("...%s, %d\n", game->map[y], y);
		free(reader);
		reader = get_next_line(game->map_fd);
		y++;
		game->height_map++;
	}
	y -= 1;
	while (y >= 0)
	{
		if (is_only_spaces(game->map[y]) == 0)
		{
			// printf("Hi and y : %d\n", y);
			free(game->map[y]);
			game->map[y] = NULL;
		}
		else
			break ;
		y--;
		game->height_map--;
	}
			// printf("Hi and y at the end is: %d\n", y);
	// y = 0;
	// while (game->map[y] != NULL)
	// {
	// 	printf("/%s\n", game->map[y]);
	// 	y++;
	// }
	close(game->map_fd);
}

int is_only_spaces(char *str)
{
    int i =

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

int fill_map_variables(t_game *game)
{
	char	*variable;
	int		i;
	int		j;

	i = 0;
	variable = get_next_line(game->map_fd);
	while (variable != NULL)
	{
		j = 0;
		while (variable[j] != '\0' && isdigit(variable[j]))
        	j++;
		if ((variable[j]) != '\0')
		{
			i += assign_texture(&game->SO, variable, "SO");
			i += assign_texture(&game->WE, variable, "WE");
			i += assign_texture(&game->EA, variable, "EA");
			i += assign_texture(&game->NO, variable, "NO");
			if (ft_strnstr(variable, "C", ft_strlen(variable)) != NULL)
				i += check_rgb(variable, &game->C);
			if (ft_strnstr(variable, "F", ft_strlen(variable)) != NULL)
				i += check_rgb(variable, &game->F);
			if (i != 6)
				variable = get_next_line(game->map_fd);
			else
				break ;
		}
	}
	check_textures(game);
	return (i);
}


int	check_rgb(char *variable, int **color)
{
	int i;
	char **c;
	int	count;

	count = 0;
	i = 0;
	while (variable[i] == ' ' || isalpha(variable[i]))
		i++;
	c = ft_split(variable + i, ',');
	while (c[count] != NULL)
    	 count++;
	if (count != 3)
	{
		printf("Invalid RGB numbers\n");
		free_split(c);
		exit(EXIT_FAILURE);
	}
	*color = ft_malloc(3 * sizeof(int));
	i = 0;
	while (c[i] != NULL)
	{
		(*color)[i] = ft_atoi(c[i]);
		if (((*color)[i] < 0 || (*color)[i] > 255) || i > 3)
		{
			printf("Invalid RGB numbers\n");
			free_split(c);
			// free(color);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (1);
}
int assign_texture(char **destination, char *variable, char *prefix)
{
	int i = 0;
	char *needle;

	needle = ft_strnstr(variable, prefix, ft_strlen(variable));
	if (needle != NULL)
	{
		while (needle[i + 2] == ' ')
			i++;
		*destination = ft_strdup(needle + (i + 2));
		return (1);
	}
	return (0);
}

void check_textures(t_game *game)
{
	int flag;

	flag = 0;
	if (game->SO == NULL || !(ft_strncmp(game->SO, "./path_to_the_south_texture", 27) == 0))
		flag = 1;
	else if (game->WE == NULL || !(ft_strncmp(game->WE, "./path_to_the_west_texture", 24) == 0))
		flag = 1;
	else if (game->EA == NULL || !(ft_strncmp(game->EA, "./path_to_the_east_texture", 24) == 0))
		flag = 1;
	else if (game->NO == NULL || !(ft_strncmp(game->NO, "./path_to_the_north_texture", 25) == 0))
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
