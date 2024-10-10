// old version of functions


// ############################################################################################################
// void	draw_ray(t_game *game)
// {
// 	int r_num;
// 	int map_x;
// 	int map_y;
// 	// int mp; // map poistion where the ray hit the axes
// 	int dof;
// 	float ray_x;
// 	float ray_y;
// 	float ray_angle; // ray angle
// 	float xo; //offset which will move us to the next hit point
// 	float yo;

// 	r_num = 0;
// 	ray_angle = game->player.angle_player - 0.523598; // - 30 degree
// 	while (r_num <60)
// 		// check for the horizontal lines:
// 	{
// 		dof = 0;
// 		r_num++;
// 		float hor_distance = 100000;
// 		float hor_x;
// 		float hor_y;
// 		// if (ray_angle > PI + 0.1 && ray_angle < 2 * PI - 0.1) // we must skip any angle near to PI because tan()
// 				//is not accurate and some times gives 0 in vlaues near PI +-
// 				// and we can'y divide on 0
// 		if (sin(ray_angle) < -0.001)
// 		{
// 			ray_y = (int)game->player.y_player / 64 * 64 - 0.001;
// 			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle); // tan(a) = tan(a - 180)
// 			xo = -64 / tan (ray_angle);
// 			yo = -64;
// 		}
// 		else if (sin(ray_angle) > 0.001) /*(ray_angle < PI- 0.1 && ray_angle > 0.1)*/
// 		{
// 			ray_y = (int)game->player.y_player / 64 * 64 + 64.001; // little bit more to make sure that we are inside the tile
// 			ray_x = game->player.x_player - (game->player.y_player - ray_y) / tan(ray_angle);
// 			yo = 64;
// 			xo = 64 / tan(ray_angle);
// 		}
// 		else
// 		{
// 			ray_x = game->player.x_player;
// 			ray_y = game->player.y_player;
// 			xo = 0;
// 			yo = 0;
// 			dof = 18;
// 		}
// 		while ( dof < 18)
// 		{
// 			map_x = (int) (ray_x) / 64 ;
// 			map_y = (int) (ray_y) / 64 ;

// 			if (map_x >= 0 && map_y >=0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
// 			{
// 				if (game->map[map_y][map_x] == '1')
// 				{
// 					hor_x = ray_x;
// 					hor_y = ray_y;
// 					hor_distance = calculate_dis(game->player.x_player ,game->player.y_player,hor_x,hor_y);
// 					break ;
// 				}
// 				else
// 				{
// 					ray_x += xo;
// 					ray_y += yo;
// 					dof++;
// 				}
// 			}
// 			else
// 				break ;
// 		}
// 		printf("in hor the rau point is: x=%f y=%f\n",ray_x, ray_y);
// //============================================================================================================
// 		// check for the vertical lines:
// 		dof = 0;
// 		float vir_distance = 100000;
// 		float vir_x;
// 		float vir_y;
// 		if (cos(ray_angle) < -0.01) /*(ray_angle > PI / 2 + 0.01 && ray_angle < 3 * PI / 2 - 0.01)*/
// 		{
// 			ray_x = (int)game->player.x_player / 64 * 64 - 0.001;
// 			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
// 			xo = -64;
// 			yo = -64 * tan(ray_angle);
// 		}
// 		else if (cos(ray_angle) > 0.01) /*(ray_angle < PI / 2 - 0.01 || ray_angle > 3 * PI / 2 + 0.01)*/
// 		{
// 			ray_x = (int)game->player.x_player / 64 * 64 + 64.001;
// 			ray_y = game->player.y_player - (game->player.x_player - ray_x) * tan(ray_angle);
// 			xo = 64;
// 			yo = 64 * tan(ray_angle);
// 		}
// 		else
// 		{
// 			ray_x = game->player.x_player;
// 			ray_y = game->player.y_player;
// 			xo = 0;
// 			yo = 0;
// 			dof = 18;
// 		}
// 		while (dof < 18)
// 		{
// 			map_x = (int)(ray_x) / 64;
// 			map_y = (int)(ray_y) / 64;
// 			if (map_x >= 0 && map_y >= 0 && map_x < (int)ft_strlen(game->map[map_y]) - 1 && map_y < game->height_map)
// 			{
// 				if (game->map[map_y][map_x] == '1')
// 				{
// 					vir_x = ray_x;
// 					vir_y = ray_y;
// 					vir_distance = calculate_dis(game->player.x_player ,game->player.y_player,vir_x,vir_y);
// 					break;
// 				}
// 				else
// 				{
// 					ray_x += xo;
// 					ray_y += yo;
// 					dof++;
// 				}
// 			}
// 			else
// 				break;
// 		}
// 		printf("in ver the rau point is: x=%f y=%f\n",ray_x, ray_y);
// 		if(vir_distance < hor_distance)
// 		{
// 			ray_x = vir_x;
// 			ray_y = vir_y;
// 		}
// 		if(vir_distance > hor_distance)
// 		{
// 			ray_x = hor_x;
// 			ray_y = hor_y;
// 		}
// 		draw_line(game, (int)game->player.x_player, (int)game->player.y_player, (int)ray_x, (int)ray_y, pixel_color(0, 0, 255, 255)); // blue
// 		ray_angle += 0.01745329; //next ray
// 		printf("the player angle is: %f\n", game->player.angle_player);
// 		printf("the ray_angle is: %f\n", ray_angle);
// 		printf("the horizintal dis is: %f\n", hor_distance);
// 		printf("the vertical dis is: %f\n", vir_distance);
// 	}
// }
// ############################################################################################################

// void draw_wall_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color)
// {
// 	// Thickness is 8 pixels, so we'll draw parallel lines offset by thickness / 2
// 	int thickness = 8;

// 	// Check if coordinates are outside the window
// 	if (x1 < 0 || y1 < 0 || x0 < 0 || y0 < 0)
// 		return;

// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	// int err = dx - dy;

// 	for (int w = -thickness / 2; w <= thickness / 2; w++)
// 	{
// 		int x_offset = (dy > dx) ? w : 0; // Offset horizontally if line is more vertical
// 		int y_offset = (dx >= dy) ? w : 0; // Offset vertically if line is more horizontal

// 		int tx0 = x0 + x_offset;
// 		int ty0 = y0 + y_offset;
// 		int tx1 = x1 + x_offset;
// 		int ty1 = y1 + y_offset;

// 		// Draw the line with the offset applied
// 		int temp_dx = abs(tx1 - tx0);
// 		int temp_dy = abs(ty1 - ty0);
// 		int temp_err = temp_dx - temp_dy;

// 		while (1)
// 		{
// 			// Ensure pixel is within the window boundaries
// 			if (tx0 >= 0 && tx0 < game->window_width && ty0 >= 0 && ty0 < game->window_height)
// 				mlx_put_pixel(game->mlx_img, tx0, ty0, color);

// 			// Check if we've reached the end point
// 			if (tx0 == tx1 && ty0 == ty1)
// 				break;

// 			int err2 = temp_err * 2;
// 			if (err2 > -temp_dy)
// 			{
// 				temp_err -= temp_dy;
// 				tx0 += (tx0 < tx1) ? 1 : -1;
// 			}
// 			if (err2 < temp_dx)
// 			{
// 				temp_err += temp_dx;
// 				ty0 += (ty0 < ty1) ? 1 : -1;
// 			}
// 		}
// 	}
// }
// ############################################################################################################
