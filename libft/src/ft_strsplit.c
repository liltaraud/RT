/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 20:52:53 by ltaraud           #+#    #+#             */
/*   Updated: 2016/09/17 16:34:52 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_wordfinder(char const *s, char c)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == c || s[i] == '\0')
			words++;
	}
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == '\0')
		words = 1;
	return (words);
}

static int			ft_strnlen(char const *s, char c)
{
	int		len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

char				**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**tab;
	int		w;
	int		it;

	tab = NULL;
	w = ft_wordfinder(s, c);
	it = 0;
	if (!s || s == NULL || !c || !(tab = (char **)ft_memalloc(sizeof(*tab)
	* (ft_wordfinder(s, c) + 1))))
		return (NULL);
	i = 0;
	while (it < w)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		tab[it] = ft_strsub(s, i, ft_strnlen((s + i), c));
		it++;
		i += ft_strnlen((s + i), c);
	}
	tab[it] = NULL;
	return (tab);
}
