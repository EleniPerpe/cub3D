/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:37 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/27 22:44:55 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(void);
void	free_map(t_game *game);

// int	main(int argc, char **argv)
// {
// 	t_game				game;

// 	arg_check(argc, argv[1]);
// 	ft_memset(&game, 0, sizeof(t_game));
// 	map_reader(&game, argv[1]);
// 	if (game.map == NULL)
// 		ft_error();
	// check_map_walls(&game, 0, 0);
// 	free_map(&game);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	t_game				game;

	ft_memset(&game, 0, sizeof(t_game));
	init_map(&game);
	init_player(&game);

	arg_check(argc, argv[1]);
	map_reader(&game, argv[1]);
	if (game.map == NULL)
		ft_error();
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop_hook(game.mlx, keyboard_control, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
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
