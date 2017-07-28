/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cparg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 21:52:40 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 14:53:05 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*cparg(char *s, char delim)
{
	size_t			i;
	char			*ret;

	i = 0;
	while (is_pagin(*s))
		s++;
	while (s[i] != '\0' && s[i] != '\n' && s[i] != ' ' && s[i] != '\t' &&
	s[i] != delim)
		i++;
	if (!(ret = ft_strnew(i + 1)))
		return (NULL);
	if (!(ret = ft_strnccpy(ret, s, i + 1, delim)))
		return (NULL);
	return (ret);
}
