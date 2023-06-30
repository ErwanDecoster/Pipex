/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:43:08 by edecoste          #+#    #+#             */
/*   Updated: 2023/06/30 11:08:55 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		res = (char *)ft_calloc(1, sizeof(char));
		return (res);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s[start + i] && i < len && start < ft_strlen(s))
	{
		res[i] = s[start + i];
		i++;
	}
	return (res);
}
