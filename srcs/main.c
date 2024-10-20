/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:37 by eperperi          #+#    #+#             */
/*   Updated: 2024/10/20 18:50:49 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(void);
void	free_map(t_game *game);
void	finish(t_game *game);
void	delete_texs(t_game *game);

int	main(int argc, char **argv)
{
	t_game				game;

	ft_memset(&game, 0, sizeof(t_game));
	arg_check(argc, argv[1]);
	init_mlx(&game);
	map_reader(&game, argv[1]);
	if (game.map == NULL)
		ft_error();
	init_game(&game);
	loops(&game);
	finish(&game);
	return (EXIT_SUCCESS);
}

void	finish(t_game *game)
{
	free_map(game);
	delete_texs(game);
}

void	delete_texs(t_game *game)
{
	int i;

	i = 0;
	mlx_delete_image(game->mlx, game->tex.north_image);
	mlx_delete_image(game->mlx, game->tex.south_image);
	mlx_delete_image(game->mlx, game->tex.west_image);
	mlx_delete_image(game->mlx, game->tex.east_image);
	mlx_delete_image(game->mlx, game->tex.door);
	mlx_delete_image(game->mlx, game->tex.fire);
	mlx_delete_image(game->mlx, game->tex.intro);
	mlx_delete_image(game->mlx, game->tex.heal_0);
	mlx_delete_image(game->mlx, game->tex.heal_1);
	mlx_delete_image(game->mlx, game->tex.crosshair);
	mlx_delete_image(game->mlx, game->tex.weapon);
	mlx_delete_image(game->mlx, game->tex.gameover);
	mlx_delete_image(game->mlx, game->tex.black_hole);
	while (i < 21)
		mlx_delete_image(game->mlx, game->tex.fire_flame[i++]);
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
