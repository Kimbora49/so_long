

int	walk_up(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) - 1][mlx->player_x / 64] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player = mlx_xpm_file_to_image(mlx->mlx_ptr, "sprites/player_back64x64.xpm", &mlx->img_width, &mlx->img_height);
	mlx->player_y -= 64;
	return (0);
}

int	walk_down(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player = mlx_xpm_file_to_image(mlx->mlx_ptr, "sprites/player_front64x64.xpm", &mlx->img_width, &mlx->img_height);
	mlx->player_y += 64;
	return (0);
}

int	walk_left(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64)] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player_x -= 64;
	return (0);
}

int	walk_right(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64)] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player_x += 64;
	return (0);
}