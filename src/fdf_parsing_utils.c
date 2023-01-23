/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:03:43 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 03:41:10 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "fdf.h"

t_list	*fdf_list_from_file(char *input_path)
{
	t_list	*list;
	t_list	*curr;
	int		input_fd;
	char	*line;

	input_fd = open(input_path, O_RDONLY);
	line = get_next_line(input_fd);
	if (!line)
		return (NULL);
	list = ft_lstnew(line);
	curr = list;
	while (line)
	{
		line = get_next_line(input_fd);
		curr->next = ft_lstnew(line);
		if (!curr->next)
			return (ft_lstclear(&list, free), NULL);
		curr = curr->next;
	}
	return (list);
}

void	fdf_tab_destroy(t_point **tab, int height)
{
	int	i;

	i = 0;
	while (tab[i] && i < height)
		free(tab[i++]);
	free(tab);
}

size_t	count_strs(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return (count);
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	return (count);
}
