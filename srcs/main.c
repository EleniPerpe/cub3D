/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:37 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/24 15:13:24 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

void	ft_error(void);
void	free_map(t_game *game);

int	main(int argc, char **argv)
{
	t_game				game;

	arg_check(argc, argv[1]);
	ft_memset(&game, 0, sizeof(t_game));
	map_reader(&game, argv[1]);
	if (game.map == NULL)
		ft_error();
	check_map_walls(&game, 0, 0);
	free_map(&game);
	return (EXIT_SUCCESS);
}

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height_map)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	ft_error_exit(t_game *game, const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free_map(game);
	exit(EXIT_FAILURE);
}
