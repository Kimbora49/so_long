/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddifalla <ddifalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:58:52 by ddifalla          #+#    #+#             */
/*   Updated: 2024/07/08 16:58:03 by ddifalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include<stdio.h>
# include<unistd.h>
# include<fcntl.h>
# include<stdlib.h>

char	*get_next_line(int fd);
char	*ft_storage(int fd, char *str);
char	*ft_get_line(char *str);
char	*ft_next(char *str);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
#endif
