/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:41:54 by edecoste          #+#    #+#             */
/*   Updated: 2023/06/30 11:08:55 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (++i < n + 1)
		((char *) s)[i - 1] = '\0';
}
