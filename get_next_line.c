/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:43:12 by ddiakova          #+#    #+#             */
/*   Updated: 2021/02/26 17:25:17 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int		find_n(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\n')
	{
		i++;
	}
	return (i);
}

static char		*ft_malloctail(void)
{
	char	*dest;

	if (!(dest = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

static int		ft_create_line_update_tail(char **line, char **tail)
{
	char	*temp;

	*line = ft_substr(*tail, 0, find_n(*tail));
	temp = *tail;
	*tail = ft_strdup(*tail + find_n(*tail) + 1);
	free(temp);
	return (1);
}

static int		ft_free(char *tail, int ret)
{
	free(tail);
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	static char		*tail;
	char			buf[BUFFER_SIZE + 1];

	if (fd == -1 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (tail == NULL)
		tail = ft_malloctail();
	if ((ft_strchr_g(tail, '\n')))
		return (ft_create_line_update_tail(line, &tail));
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (ret < 0)
			return (ft_free(tail, -1));
		buf[ret] = '\0';
		tail = ft_strjoin(tail, buf);
		if ((ft_strchr_g(tail, '\n')))
			return (ft_create_line_update_tail(line, &tail));
	}
	return (ft_free(tail, 0));
}
