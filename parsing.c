/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddifalla <ddifalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:01:50 by ddifalla          #+#    #+#             */
/*   Updated: 2024/09/17 21:00:00 by ddifalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"

char **ft_map_parsing(void)
{
    char    **map;
    char    *map_line;
    int     fd;
    int     i;
    int     j;

    map_line = "0";
    fd = open("map.ber", O_RDWR);
    i = 0;
    while (get_next_line(fd) != NULL)
        i++;
    map = (char **)malloc(sizeof(char *) * (i + 1));
    if(map == NULL)
        return (0);
    fd = open("map.ber", O_RDWR);
    j = 1;
    while(map_line != NULL)
    {
        map_line = get_next_line(fd);
        map[j] = map_line;
        j++;
    }
    return (map);
}

int main()
{
    int i = 1;

    char **map = ft_map_parsing();
    while (map[i])
    {
        printf("%s", map[i]);
        i++;
    }
    return (0);
}
