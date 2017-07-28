/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 06:56:37 by ttrossea          #+#    #+#             */
/*   Updated: 2017/04/04 15:00:22 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"

char				*ft_read_file(char *filename)
{
	int			v[2];
	char		*old;
	char		*buf;
	char		*ret;

	if ((v[0] = open(filename, O_RDONLY)) == -1 ||
					!(ret = ft_strnew(1)))
		return (NULL);
	ret[0] = '\0';
	while ((v[1] = get_next_line(v[0], &buf)) == 1)
	{
		old = ret;
		if (v[1] == 1)
			if (!(ret = ft_strjoin(ret, "\n")))
				return (NULL);
		free(old);
		old = ret;
		if (!(ret = ft_strjoin(ret, buf)))
			return (NULL);
		free(old);
		free(buf);
	}
	free(buf);
	return (close(v[0]) == 0 && v[1] != -1 ? ret : NULL);
}
