/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:57:24 by eperperi          #+#    #+#             */
/*   Updated: 2024/10/10 18:34:20 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_map_variables(t_game *game);
void	process_variable(t_game *game, char *variable, int *i);
int		check_for_assign(t_game *game, char *variable);
int		assign_texture(const char **destination, char *variable, char *prefix);
void	check_unique_textures(t_game *game);

void	fill_map_variables(t_game *game)
{
	char	*variable;
	int		i;

	i = 0;
	variable = get_next_line(game->map_fd);
	while (variable != NULL)
	{
		process_variable(game, variable, &i);
		if (i == 6)
			break ;
		variable = get_next_line(game->map_fd);
	}
	check_unique_textures(game);
	check_textures(game);
}

void	process_variable(t_game *game, char *variable, int *i)
{
	int	j;

	j = 0;
	while (variable[j] && !ft_isalpha(variable[j]))
		j++;
	if (variable[j])
	{
		*i += check_for_assign(game, variable);
		if (*i == 6)
			return ;
	}
	else
	{
		while (*variable)
		{
			if (*variable != ' ' && *variable != '\n' && *variable != '\t')
			{
				printf("Not enough variables!\n");
				exit(EXIT_FAILURE);
			}
			variable++;
		}
	}
}

int	check_for_assign(t_game *game, char *variable)
{
	int	i;

	i = 0;
	i += assign_texture(&game->so, variable, "SO");
	i += assign_texture(&game->we, variable, "WE");
	i += assign_texture(&game->ea, variable, "EA");
	i += assign_texture(&game->no, variable, "NO");
	if (ft_strnstr(variable, "C", ft_strlen(variable)) != NULL)
		i += check_rgb(variable, &game->c);
	if (ft_strnstr(variable, "F", ft_strlen(variable)) != NULL)
		i += check_rgb(variable, &game->f);
	return (i);
}

int	assign_texture(const char **destination, char *variable, char *prefix)
{
	int		i;
	char	*needle;
	char	*temp;

	i = 0;
	needle = ft_strnstr(variable, prefix, ft_strlen(variable));
	if (needle != NULL)
	{
		while (needle[i + 2] == ' ' || needle[i + 2] == '\t')
			i++;
		temp = ft_strdup(needle + (i + 2));
		if (*destination != NULL)
			{
				printf("Error\nWrong textures!\n");
				exit(EXIT_FAILURE);
			}
		*destination = ft_malloc(sizeof(char ) * ft_strlen(temp));
		ft_strlcpy((char *)*destination, temp, ft_strlen(temp));
		// printf(".%s.\n",  *destination);
		free(temp);
		return (1);
	}
	return (0);
}

void	check_unique_textures(t_game *game)
{
	if ((ft_strncmp(game->so, game->no, ft_strlen(game->so)) == 0)
		|| (ft_strncmp(game->so, game->ea, ft_strlen(game->so)) == 0)
		|| (ft_strncmp(game->so, game->we, ft_strlen(game->so)) == 0))
	{
		printf("No allowed to use the same texture!\n");
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(game->no, game->ea, ft_strlen(game->no)) == 0)
		|| (ft_strncmp(game->no, game->we, ft_strlen(game->no)) == 0))
	{
		printf("No allowed to use the same texture!\n");
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(game->ea, game->we, ft_strlen(game->ea)) == 0))
	{
		printf("No allowed to use the same texture!\n");
		exit(EXIT_FAILURE);
	}
}
