/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:23:17 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 05:08:00 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	if (!args[1] || (!ft_strncmp("-n", args[1], 3) && !args[2]))
	{
		if (!args[1])
			ft_printf("\n");
		return (0);
	}
	if (!ft_strncmp("-n", args[i], 3))
		i++;
	while (args[i])
	{
		if (i > 1)
			ft_printf(" ", args[i]);
		ft_printf("%s", args[i]);
		i++;
	}
	if (ft_strncmp("-n", args[1], 3))
		ft_printf("\n");
	return (0);
}
