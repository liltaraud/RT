/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:21:11 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 22:53:56 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elm				*new_elm(void *ptr, char type)
{
	t_elm			*ret;

	if (!(ret = malloc(sizeof(struct s_elm))))
		return (NULL);
	ret->next = NULL;
	ret->elm = ptr;
	ret->type = type;
	return (ret);
}
