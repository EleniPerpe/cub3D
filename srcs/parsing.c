/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:13:07 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/30 20:55:35 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		fill_map_variables(t_game *game);
int		check_rgb(char *variable, int **color);
void	check_textures(t_game *game);
int		assign_texture(const char **destination, char *variable, char *prefix);
int		is_only_spaces(char *str);
void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path);
void	ft_error_tex(void);
void	find_map_width(t_game *game);
void	find_start_pos(t_game *game);
void	check_walls( t_game *game, int x, int y);

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
	if (info_count != 6)
	{
		printf("Error\nNot enough map info!\n");
		exit(EXIT_FAILURE);
	}
	reader = get_next_line(game->map_fd);
	while (is_only_spaces(reader) == 0)
		reader = get_next_line(game->map_fd);
	game->map = ft_calloc(200, sizeof(char *));
	while (reader != NULL)
	{
		game->map[y] = ft_strdup(reader);
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
			free(game->map[y]);
			game->map[y] = NULL;
		}
		else
			break ;
		y--;
		game->height_map--;
	}
	find_map_width(game);
	find_start_pos(game);
	// check_walls(game, game->start_pos[0], game->start_pos[1]);
	close(game->map_fd);
}

void check_walls( t_game *game, int x, int y)
{
	if (x < 0 || x >= game->height_map
		|| y < 0 || y >= game->width_map + 1)
		return ;
	if (game->map[x][y] == '1')
		return ;
	if (game->map[x][y] == '0' && (x - 1 == -1 || y - 1 == -1
		|| x == game->height_map - 1))
	{
		printf("No closed map!\n");
		exit(EXIT_FAILURE);
	}
	if (game->map[x][y] == ' ' || game->map[x][y] == '\n')
	{
		printf("No closed map!\n");
		exit(EXIT_FAILURE);
	}
	game->map[x][y] = '1';
	check_walls(game, x - 1, y);
	check_walls(game, x + 1, y);
	check_walls(game, x, y - 1);
	check_walls(game, x, y + 1);
}

void find_start_pos(t_game *game)
{
	int x;
	int y;
	int flag;

	y = 0;
	flag = 0;
	game->start_pos = ft_malloc(sizeof(int) * 2);
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (ft_isalpha(game->map[y][x]))
			{
				if (game->map[y][x] != 'N' && game->map[y][x] != 'E' && game->map[y][x] != 'W' && game->map[y][x] != 'S')
				{
					printf("Wrong player character!\n");
					exit(EXIT_FAILURE); //remove
				}
				else
				{
					game->orientation = game->map[y][x];
					game->start_pos[0] = y;
					game->start_pos[1] = x;
					flag++;
				}
			}
			x++;
		}
		y++;
	}
	if (flag != 1)
	{
		printf("Insufficient characters\n");
		free(game->start_pos);
		exit(EXIT_FAILURE);
	}
}

void find_map_width(t_game *game)
{
	int x;
	int y;
	int	temp;

	y = 0;
	temp = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			x++;
		}
		while (game->map[y][x - 1] == ' ' || game->map[y][x - 1] == '\n')
			x--;
		if (x > temp)
			temp = x;
		y++;
	}
	game->width_map = temp;
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
	int		alpha;

	i = 0;
	alpha = 0;
	variable = get_next_line(game->map_fd);
	while (variable != NULL)
	{
		j = 0;
		while (variable[j] != '\0')
		{
			if (ft_isalpha(variable[j]))
				break;
        	j++;
		}
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
			if (i == 6)
				break ;
		}
		else
		{
			j = 0;
			while (variable[j] != '\0')
			{
				if (variable[j] == ' ' || variable[j] == '\n' || variable[j] == '\t')
					j++;
				else
				{
					printf("variable[] = %d, error!!!\n", variable[j]);
					exit(EXIT_FAILURE);
				}
			}
		}
		variable = get_next_line(game->map_fd);
	}
	// printf("Path SO: .%s.", game->SO);
	// printf("Path NO: .%s.", game->NO);
	// printf("Path WE: .%s.", game->WE);
	// printf("Path EA: .%s.", game->EA);
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
int assign_texture(const char **destination, char *variable, char *prefix)
{
	int i = 0;
	char *needle;
	char *temp;

	needle = ft_strnstr(variable, prefix, ft_strlen(variable));
	if (needle != NULL)
	{
		while (needle[i + 2] == ' ')
			i++;
		temp = ft_strdup(needle + (i + 2));
		*destination = ft_malloc(sizeof(char ) * ft_strlen(temp));
		ft_strlcpy((char *)*destination, temp, ft_strlen(temp));
		free(temp);
		// printf("%s\n\n", *destination);
		return (1);
	}
	return (0);
}

void check_textures(t_game *game)
{
	// (void)game;
	ft_load_image(game, &game->tex.east_image, game->EA);
	ft_load_image(game, &game->tex.west_image, game->WE);
	ft_load_image(game, &game->tex.south_image, game->SO);
	ft_load_image(game, &game->tex.north_image, game->NO);

	// int flag;
	// printf("Path NO: |%s|\n", game->NO);
	// printf("Path SO: |%s|\n", game->SO);
	// printf("Path WE: |%s|\n", game->WE);
	// printf("Path EA: |%s|\n", game->EA);
	// // flag = 0;

	// Waiting info about the resizing

	// if (mlx_resize_image(game->tex.east_image, 40, 40) == false ||
	// mlx_resize_image(game->tex.west_image, 40, 40) == false ||
	// mlx_resize_image(game->tex.south_image, 40, 40) == false ||
	// mlx_resize_image(game->tex.north_image, 40, 40) == false)
	// {
	// 	printf("Couldn't load the image!\n");
	// 	exit(EXIT_FAILURE);
	// }
}
void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path)
{
	(void)game;
	(void)image;
	(void)file_path;
// 	mlx_texture_t	*temp_texture;

// 	temp_texture = mlx_load_png(file_path);
// 	if (temp_texture == NULL)
// 	{
// 		mlx_terminate(game->mlx);
// 		ft_error_tex();
// 	}
// 	// printf("%p\n",game->mlx);
// 	*image = mlx_texture_to_image(game->mlx, temp_texture);
// 	if (*image == NULL)
// 	{
// 		mlx_terminate(game->mlx);
// 		ft_error_tex();
// 	}
// 	mlx_delete_texture(temp_texture);
}

void	ft_error_tex(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
