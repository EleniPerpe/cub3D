/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:25:23 by eperperi          #+#    #+#             */
/*   Updated: 2024/09/24 17:25:42 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}
