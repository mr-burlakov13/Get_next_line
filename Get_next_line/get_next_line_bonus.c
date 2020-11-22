/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhayward <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:19:46 by lhayward          #+#    #+#             */
/*   Updated: 2020/11/19 20:20:02 by lhayward         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*save_ost(char *ost)
{
	char	*arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ost)
		return (0);
	while (ost[i] != '\0' && ost[i] != '\n')
		i++;
	if (ost[i] == '\0')
	{
		free(ost);
		return (0);
	}
	if (!(arr = (char *)malloc(sizeof(char) * (ft_strlen(ost) - i + 1))))
		return (NULL);
	i++;
	while (ost[i])
		arr[j++] = ost[i++];
	arr[j] = '\0';
	free(ost);
	return (arr);
}

int			get_next_line(int fd, char **line)
{
	static char *ost[1024];
	char		*buf;
	int			nb;

	nb = 42;
	if (fd < 0 || !line || BUFFER_SIZE < 1
			|| !(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (nb != 0 && ft_strchr(ost[fd], '\n') == 0)
	{
		if ((nb = read(fd, buf, BUFFER_SIZE)) < 0)
		{
			free(buf);
			free(ost[fd]);
			return (-1);
		}
		buf[nb] = '\0';
		ost[fd] = ft_strjoin(ost[fd], buf);
	}
	free(buf);
	*line = ft_strdup_mod(ost[fd]);
	ost[fd] = save_ost(ost[fd]);
	if (nb == 0)
		return (0);
	return (1);
}
