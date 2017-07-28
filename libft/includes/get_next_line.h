/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 16:35:48 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/23 14:58:51 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <unistd.h>
# include "stdlib.h"

# define BUFF_SIZE 500

int					get_next_line(int const fd, char **line);

typedef struct		s_d
{
	char			*bckn;
	char			*buf;
}					t_d;
#endif
