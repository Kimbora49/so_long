/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddifalla <ddifalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:48 by ddifalla          #+#    #+#             */
/*   Updated: 2024/09/28 13:12:20 by ddifalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct  s_mlx_struct
{
    void    *sol;
    void    *wall;
    void    *exit;
    void    *collectible;
    void    *player;
    
    int     tot_moves;
    int     keypressed;
    int     img_width;
    int     img_height;
    int     win_width;
    int     win_height;
    int     x;
    int     y;
    int     tot_collectible;
    bool    found_exit;
    int     found_collectible;
    int     player_x;
    int     player_y;
    int     starter_P_x;
    int     starter_P_y;
    char    **map;
    void    *mlx_ptr;
    void    *win_ptr;
    bool    end;
}               t_mlx_struct;
