/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:05:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/29 20:15:32 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_array_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		ft_printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
}

void	print_file_lst(t_file *lst)
{
	while (lst)
	{
		ft_printf("\tfile: %s\ttype: %i\tfd: %d\n",
			(char *)lst->name, lst->type, lst->fd);
		lst = lst->next;
	}
}

void	print_cmd_lst(t_cmd *lst)
{
	while (lst)
	{
		ft_printf("line: %s\n", (char *)lst->line);
		ft_printf("exec: %s\n", (char *)lst->exec_cmd);
		print_array_args((char **)lst->args);
		ft_printf("type: %d\n", lst->type);
		print_file_lst(lst->outfiles);
		print_file_lst(lst->infiles);
		lst = lst->next;
	}
}
