/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:45:14 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/06 17:11:19 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*ps1;

	ps1 = (char *)malloc((sizeof(*s1) * ft_strlen(s1)) + 1);
	if (ps1 != NULL)
		ft_strcpy(ps1, s1);
	return (ps1);
}
