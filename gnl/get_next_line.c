/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddifalla <ddifalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:58:40 by ddifalla          #+#    #+#             */
/*   Updated: 2024/07/08 16:54:24 by ddifalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	verif_end(char **str)//verifier si nous sommes a la fin du dossier
{
	if (*str[0] == '\0')//si str est vide ('\0')
	{
		free(*str);//on free la string
		*str = NULL;//on l'assigne a nul
	}
}

char	*ft_storage(int fd, char *str)//je stock ce que je lis dans str
{
	char	*buff;//contient un certain nombre de caractere du fichier que lit read
	int		bytes;//nombre de caractere lu par la fonction read

	bytes = 1;//on assigne bytes a 1 car la condition pour lire est tant que c'est different de superieur a 0 
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));//on alloue buff avec la taille de buffersize + '\0'
	if (!buff)//securiter
		return (NULL);//si buff est vide on l'assigne a null
	while (!ft_strchr(str, '\n') && bytes != 0)//tant qu'il n'y a pas de '\n' dans str, je lis la suite
	{
		bytes = (read(fd, buff, BUFFER_SIZE));//bytes = nombre de bytes lu par read
		if (bytes == -1)//en cas d'erreur
		{
			free(buff);
			free(str);
			return (NULL);//on free tout et on return null
		}
		buff[bytes] = '\0';//'\0' est ajouter a la fin de buff
		str = ft_strjoin(str, buff);//on ajoute buff a str
	}
	verif_end(&str);//on verifie si str est vide (& car c'est un tableau de tableau)
	free(buff);
	return (str);
}

char	*ft_get_line(char *str)//je recupere ma ligne 
{
	int		i;
	char	*line;

	i = 0;
	if (!str)//securiter
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;//on avance jusqu'au '\n' ou '\0' pour avoir la taille de ma ligne
	line = malloc(sizeof(char) * (i + 2));//on alloue la place pour line avec la taille de str + '\n' + '\0'
	if (!line)//securiter
		return (NULL);
	i = 0;//on reinitialise i a 0
	while (str[i] && str[i] != '\n')//tant qu'on ne trouve pas de '\n'
	{
		line[i] = str[i];//on copie str dans line
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;//on avance d'un
	}
	line[i] = '\0';//on ajoute le '\0'
	return (line);
}

char	*ft_next(char *str)//je recupere le reste (apres le '\n')
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	if (!str)//securiter
		return (NULL);
	while (str[i] != '\n' && str[i])//tant qu'on ne trouve pas de '\n' (sauter la premiere ligne)
		i++;
	if (!str[i])//securiter
	{
		free(str);
		return (NULL);
	}
	newstr = malloc(sizeof(char) * (ft_strlen(str) - i + 1));//on alloue la place de newstr (pour y mettre ce qu'il reste) tout ce qu'il y a apres le '\n'
	if (!newstr)//securiter
		return (free(str), NULL);
	i++;
	while (str[i])
		newstr[j++] = str[i++];//on met str dans newstr
	newstr[j] = '\0';//on ajoute le '\0' a la fin
	free(str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)//si il y a une erreur ou rien a lire
		return (NULL);
	str = ft_storage(fd, str);//je rempli ma ligne str en lisant le fichier fd
	if (!str)//securiter
	{
		free (str);
		return (NULL);
	}
	line = ft_get_line(str);//line = notre ligne decouper par la fonction get line de str
	if (!line)//securiter
	{
		free(str);
		return (NULL);
	}
	str = ft_next(str);//on actualise str pour garder ce qu'il reste 
	return (line);
}
