/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrodrigo <vrodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:00:02 by vrodrigo          #+#    #+#             */
/*   Updated: 2020/02/12 16:33:36 by vrodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_final_line(char **save, char **line)
{
	if (ft_strchr(*save, '\0'))
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
}

int		ft_checkfd(ssize_t *res, char **save)
{
	if (*res < 0)
	{
		if (*save != NULL)
		{
			free(*save);
			*save = NULL;
		}
		return (-1);
	}
	return (0);
}

int		ft_get_line(ssize_t res, char **save, char **line)
{
	char	*found_line;
	char	*tmp;

	if (!res && !*save)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (ft_checkfd(&res, &*save))
		return (-1);
	if ((found_line = ft_strchr(*save, '\n')))
	{
		*found_line = '\0';
		*line = ft_strdup(*save);
		tmp = ft_strdup(found_line + 1);
		free(*save);
		*save = tmp;
		return (1);
	}
	else
		ft_final_line(&*save, &*line);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*save[4096];
	ssize_t			res;
	char			*tmp;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 ||
		(!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while ((res = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[res] = '\0';
		if (!save[fd])
			save[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(save[fd], buff);
			free(save[fd]);
			save[fd] = tmp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	buff = NULL;
	return (ft_get_line(res, &save[fd], &*line));
}
