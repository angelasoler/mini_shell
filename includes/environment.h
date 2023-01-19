/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:43:30 by asoler            #+#    #+#             */
/*   Updated: 2022/12/31 06:33:57 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define ENVIRONMENT_H

# define TABLE_SIZE 10

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

unsigned int	hash(char *name);
t_env			*ft_envnew(char	*key, char *value);
int				count_env_var(t_env **lst);
void			ft_env_addback(t_env **lst, t_env *new);
void			ft_envdelone(t_env *env, void (*del)(void*));
void			ft_envclear(t_env **env, void (*del)(void *));
void			print_env_lst(t_env *env, int flag_export);
void			free_lst(t_env *env);
int				free_and_count_array(char **array, void (*f)(void *));

#endif
