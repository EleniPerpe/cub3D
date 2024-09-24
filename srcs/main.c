/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:37 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/25 00:34:29 by rshatra          ###   ########.fr       */
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
// 	check_map_walls(&game, 0, 0);
// 	free_map(&game);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	t_game				game;
	int	map_array_in[128] = { // we will take it later from the map
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
	// to-do: create init_map()
	// to-do: create init_player()
	game.map_array = map_array_in;
	game.map_unit_size = 64;
	game.map_unit_x = 16;
	game.map_unit_y = 8;
	game.name = "CUB3D";
	game.window_height = 512;
	game.window_width = 1024;
	game.player.x_player = 512; // must take the coordinate from the map
	game.player.y_player = 261;
	game.player.angle_player =  - pi / 2 / 2;
	game.player.dx_player = cos (game.player.angle_player) * 5;
	game.player.dy_player = sin (game.player.angle_player) * 5;
	arg_check(argc, argv[1]);
	// ft_memset(&game, 0, sizeof(t_game));
	map_reader(&game, argv[1]);
	if (game.map == NULL)
		ft_error();
	check_map_walls(&game, 0, 0);
	init_mlx(&game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop_hook(game.mlx, keyboard_control, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	// free_map(&game);
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
