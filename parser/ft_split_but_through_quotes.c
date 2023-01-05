/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_but_through_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:04:51 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/05 03:00:08 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_words(char const *s, char delimiter)
{
	size_t	words;
	size_t	i;

	i = 0;
	while (s[i] == delimiter)
		i++;
	if (!s[i])
		return (0);
	words = 1;
	while (s[i])
	{
		pass_through_quotes((char *)s, &i, NULL);
		if (s[i] == delimiter && s[i + 1] && s[i + 1] != delimiter)
			words++;
		i++;
	}
	return (words);
}

static void	result_array(char	***dest, char *src, char delimiter)
{
	int		i;
	int		j;
	char	delimiter_str[2];

	if (!src)
		return ;
	delimiter_str[0] = delimiter;
	delimiter_str[1] = '\0';
	i = 0;
	j = 0;
	while (src[i] == delimiter)
			i++;
	while (src[i])
	{
		(*dest)[j] = ft_worddup(src + i, delimiter_str);
		i += ft_strlen((*dest)[j]);
		i += (src[i] != '\0');
		j++;
		while (src[i] == delimiter)
			i++;
	}
	(*dest)[j] = NULL;
}

char	**ft_split_but_through_quotes(char const *s, char delimiter)
{
	char	**result;
	size_t	size;

	if (*s == 0)
	{
		result = malloc(sizeof(char *) * 1);
		result[0] = (char *)0;
		return (result);
	}
	size = count_words(s, delimiter);
	result = calloc(sizeof(char *), (size + 1));
	if (!result)
		return (0);
	result_array(&result, (char *)s, delimiter);
	return (result);
}
