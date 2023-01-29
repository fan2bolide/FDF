/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 05:17:30 by bajeanno          #+#    #+#             */
/*   Updated: 2022/11/19 06:50:23 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_start(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i] && ft_isset(s[i], set))
		i++;
	return (i);
}

static int	ft_get_end(char const *s, char const *set)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i > 0 && ft_isset(s[i], set))
		i--;
	if (i == 0)
		return (0);
	return (i + 1);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		i;
	char	*res;
	int		start;
	int		end;

	start = ft_get_start(s, set);
	end = ft_get_end(s, set);
	if (end == 0)
		return (ft_calloc(1, 1));
	res = ft_strnew(end - start);
	if (res == NULL)
		return (NULL);
	s += start;
	i = 0;
	while (i < end - start)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}
