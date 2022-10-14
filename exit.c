/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:14 by asoler            #+#    #+#             */
/*   Updated: 2022/10/09 00:25:53 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exit_program(t_data *data)
{
	free_and_count_array(data->path, free);
	free_hash_table(data);
	(void)data;
	exit(0);
}