

int	keypress_W(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[mlx->player_y / 64][mlx->player_x / 64] == '0' || (mlx->map[mlx->player_y / 64][mlx->player_x / 64] == 'X')))
		walk_up(mlx);
	else if (mlx->map[mlx->player_y / 64][mlx->player_x / 64] == 'C')
	{
		mlx->found_collectible++;
		walk_up(mlx);
	}
	else if (mlx->map[mlx->player_y / 64][mlx->player_x / 64] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
			ending(mlx);
		walk_up(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}
int	keypress_A(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == '0') || (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == 'X'))
		walk_left(mlx);
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == 'C')
	{
		mlx->found_collectible++;
		walk_left(mlx);
	}
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
			ending(mlx);
		walk_left(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}

int	keypress_S(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == '0') || (mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == 'X'))
		walk_down(mlx);
	else if (mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == 'C')
	{
		mlx->found_collectible++;
			walk_down(mlx);
	}
	else if (mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
			ending(mlx);
		walk_down(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}

int	keypress_D(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == '0') || (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == 'X'))
		walk_right(mlx);
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == 'C')
	{
		mlx->found_collectible++;
		walk_right(mlx);
	}
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
			ending(mlx);
		walk_right(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}


int	keypress(int keypress, t_mlx_struct *mlx)
{
	if(keypress == ESC)
		ft_free_endgame(mlx);
	if(keypress == W)
		keypress_W(mlx);
	if(keypress == A)
		keypress_A(mlx);
	if(keypress == S)
		keypress_S(mlx);
	if(keypress == D)
		keypress_D(mlx);
	return (0);
}
