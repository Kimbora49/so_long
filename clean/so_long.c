

int	main(void)
{
	t_mlx_struct	mlx;

	mlx.found_exit = false;
	mlx.tot_collectible = 0;
	mlx.found_collectible = 0;
	mlx.tot_moves = 0;
	mlx.x = 0;
	mlx.y = 0;
	mlx.img_width = 32;
	mlx.img_height = 32;
	mlx.end = false;
	if (ft_map_parsing(&mlx) == false)
	{
		write(2, "Error\nMap non valide !\n", 23);
		ft_free_endgame(&mlx);
		return (1);
	}
	if (verif_input(&mlx) == false)
	{
		write(2, "Error\nMap non valide !\n", 23);
		ft_free_endgame(&mlx);
		return (1);
	}
	ft_map_parsing(&mlx);
	mlx.found_collectible = 0;
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
	{
		write(2, "Error\nprobleme d'initialisation minilibx veuillez reessayer\n", 60);
		ft_free_endgame(&mlx);
		return (1);
	}
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_width, mlx.win_height, "chasser_pigeon_aller_dans_tori_lejeu.");
	if (mlx.win_ptr == NULL)
	{
		write(2, "Error\nprobleme de creation de la fenetre veuillez reessayer\n", 60);
		ft_free_endgame(&mlx);
		return (1);
	}
	mlx.player = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/player_front64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.collectible = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/collectible64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.exit = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/exit64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.sol = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/sol64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.wall = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/wall64x64.xpm", &mlx.img_width, &mlx.img_height);

	ft_map_display(&mlx);
	mlx_hook(mlx.win_ptr, DestroyNotify, StructureNotifyMask, ft_free_endgame, &mlx);
	mlx_key_hook(mlx.win_ptr, keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
	ft_free_endgame(&mlx);
	return (0);
}