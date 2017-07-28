/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpline.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 21:52:40 by ttrossea          #+#    #+#             */
/*   Updated: 2015/12/17 22:31:26 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*cpline(char *s)
{
	size_t			i;
	char			*ret;

	i = 0;
	while (is_pagin(*s))
		s++;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (!(ret = ft_strnew(i)))
		return (NULL);
	if (!(ft_strncpy(ret, s, i)))
		return (NULL);
	return (ret);
}
