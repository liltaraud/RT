/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 17:53:30 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/13 13:16:29 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	end = 0;
	i = 0;
	start = 0;
	while (*(s + start) == ' ' || *(s + start) == '\t' || *(s + start) == '\n')
		start++;
	if (*(s + start) == '\0')
		return ("\0");
	i = ft_strlen(s) - 1;
	while (*(s + i) == ' ' || *(s + i) == '\t' || *(s + i) == '\n')
	{
		i--;
		end++;
	}
	str = (char *)malloc(sizeof(str) * (ft_strlen(s) - (start + end - 1)));
	if (str)
		str = ft_strsub(s, start, (ft_strlen(s) - end - start));
	return (str);
}
