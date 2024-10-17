/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:37 by eperperi          #+#    #+#             */
/*   Updated: 2024/10/17 05:13:27 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(void);
void	free_map(t_game *game);

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
	free (game->rend.crosshair_tex);
	free (game->rend.weapon_tex);
	free (game->rend.heal_0);
	free (game->rend.heal_1);
	free (game->rend.intro);
}

void	ft_error_exit(t_game *game, const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free_map(game);
	exit(EXIT_FAILURE);
}
