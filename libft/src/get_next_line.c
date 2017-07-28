/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrosea <ttrosea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 16:09:11 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 15:48:05 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char					*fill_line(char *line, char *buf)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = line;
	while (buf[i] && buf[i] != '\n')
		i++;
	line = (char *)ft_memalloc(i + ft_strlen(tmp) + 1);
	i = 0;
	while (tmp[i])
	{
		line[i] = tmp[i];
		i++;
	}
	while (buf[j] && buf[j] != '\n')
	{
		line[i] = buf[j];
		i++;
		j++;
	}
	free(tmp);
	return (line);
}

static int					malloc_all(t_d **gnl, char **line)
{
	if (!(*line = (char *)ft_memalloc(sizeof(char))))
		return (-1);
	if (!(*gnl))
	{
		if (!(*gnl = (t_d *)ft_memalloc(sizeof(t_d))))
			return (-1);
		if (!((*gnl)->buf = (char *)ft_memalloc(BUFF_SIZE + 1)))
			return (-1);
		(*gnl)->bckn = NULL;
	}
	return (1);
}

int							get_next_line(int const fd, char **line)
{
	static t_d			*gnl = NULL;
	int					rd;

	if (BUFF_SIZE == 0 || fd < 0 || line == NULL || !(malloc_all(&gnl, line)))
		return (-1);
	while (gnl->bckn || (rd = read(fd, gnl->buf, BUFF_SIZE)))
	{
		if (gnl->bckn)
		{
			*line = fill_line(*line, gnl->bckn + 1);
			if ((gnl->bckn = ft_strchr(gnl->bckn + 1, '\n')))
				return (1);
			rd = read(fd, gnl->buf, BUFF_SIZE);
		}
		if (rd == -1)
			return (-1);
		gnl->buf[rd] = '\0';
		*line = fill_line(*line, gnl->buf);
		if ((gnl->bckn = ft_strchr(gnl->buf, '\n')))
			return (1);
	}
	return (**line ? 1 : 0);
}
