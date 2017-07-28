/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_elm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:27:15 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 22:54:03 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				push_elm(void *ptr, char type, t_elm **stk)
{
	if (!stk || !(*stk))
	{
		if (!(*stk = new_elm(ptr, type)))
			return (0);
		return (1);
	}
	if (!add_elm(ptr, type, *stk))
		return (0);
	return (1);
}
