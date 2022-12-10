/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:42:49 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 20:50:21 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

t_env	*ft_envnew(char	*key, char *value)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	if (key)
		lst->key = ft_strdup(key);
	else
		lst->key = NULL;
	if (value)
		lst->value = ft_strdup(value);
	else
		lst->value = NULL;
	lst->next = NULL;
	return (lst);
}

void	ft_env_addback(t_env **lst, t_env *new)
{
	t_env	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

void	ft_envdelone(t_env *env, void (*del)(void*))
{
	if (!env || !del)
		return ;
	del(env->key);
	del(env->value);
	free(env);
}

void	ft_envclear(t_env **env, void (*del)(void *))
{
	t_env	*p;
	t_env	*p_next;

	if (!env || !del)
		return ;
	p = *env;
	while (p)
	{
		p_next = p->next;
		ft_envdelone(p, del);
		p = p_next;
	}
	*env = NULL;
}

void	print_env_lst(t_env *env, int flag_export)
{
	while (env)
	{
		if (flag_export)
			ft_printf("declare -x ");
		ft_printf("%s=", env->key);
		if (!flag_export)
			ft_printf("%s\n", env->value);
		else
			ft_printf("\"%s\"\n", env->value);
		env = env->next;
	}
}
