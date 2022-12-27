/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:35:51 by asoler            #+#    #+#             */
/*   Updated: 2022/12/27 19:51:02 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# define EXECUTER_H

typedef struct s_inter
{
	int	**fd;
	int	*id;
}	t_inter;

typedef struct s_main
{
	char	**argv;
	char	**envp;
	int		argc;
	int		n_args;
	int		status;
	int		ret;
	t_inter	inter;
}	t_main;

int		verify_access(char *path, int mode);
int		is_absolute_path(char *arg);
void	print_cmd_error(char *arg, int message);

#endif
