/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:43:12 by ddiakova          #+#    #+#             */
/*   Updated: 2021/02/26 17:21:37 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char		*ft_malloctail(void)
{
	char	*dest;

	if (!(dest = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

static char		*ft_create_line_update_tail(char **line, char *tail)
{
	char	*temp;

	*line = ft_substr(tail, 0, find_n(tail));
	temp = tail;
	tail = ft_strdup(&tail[find_n(tail) + 1]);
	free(temp);
	return (tail);
}

static int		ft_free_tail(char *tail)
{
	free(tail);
	return (-1);
}

static int		ft_free_end(char *tail)
{
	free(tail);
	return (0);
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
	{
		tail = ft_create_line_update_tail(line, tail);
		return (1);
	}
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (ret < 0)
			return (ft_free_tail(tail));
		buf[ret] = '\0';
		tail = ft_strjoin(tail, buf);
		if ((ft_strchr_g(tail, '\n')))
		{
			tail = ft_create_line_update_tail(line, tail);
			return (1);
		}
	}
	return (ft_free_end(tail));
}

/*int	main(int ac, char **av)
{
	char *line;
	int fd;
	int ret;
	int countline;

	countline = 1;
	if (ac == 1)
		fd = 0;
	if (ac >= 2)
		fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line))==1)
	{
		printf("line. %d = %s - [%d]\n", countline, line, ret);
		free(line);
		line = NULL;
		countline++;
	}
	printf("line %d = %s - [%d]\n", countline, line, ret);
	free(line);
		line = NULL;
	printf("\nTest de LEAKS\n");
	system("leaks a.out | grep leaked\n"); 
	return 0;
}*/
