/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_jmp_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 18:01:36 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/01 17:16:34 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

char		*scn_jmp_next_line(char *ptr)
{
	if (!ptr || !*ptr)
		return (NULL);
	while (*ptr && *ptr != '\n')
		ptr++;
	while (*ptr && *ptr == '\n')
		ptr++;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	if (ft_isalpha(*ptr) || *ptr == '<')
		return (ptr);
	return (NULL);
}
