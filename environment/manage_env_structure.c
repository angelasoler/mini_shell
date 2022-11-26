/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:42:49 by asoler            #+#    #+#             */
/*   Updated: 2022/10/20 13:18:07 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_envnew(char	*key, char *value)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = ft_strdup(key);
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

void	print_env_lst(t_env *env)
{
	while (env)
	{
		ft_printf("%s=", env->key);
		ft_printf("%s\n", env->value);
		env = env->next;
	}
}