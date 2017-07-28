/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:55:02 by ttrossea          #+#    #+#             */
/*   Updated: 2017/04/29 17:38:53 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrlast(const char *s, int c, int c_before)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c_before)
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		else
			i++;
	if ((char)c == '\0')
		return ((char *)&s[i]);
	else
		return (NULL);
}
