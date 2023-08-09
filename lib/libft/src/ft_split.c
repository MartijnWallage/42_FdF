/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:13:16 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:50:30 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_wordlen(const char *s, const char c)
{
	size_t	size;

	size = 0;
	while (s[size] && s[size] != c)
		size++;
	size++;
	return (size);
}

static size_t	count_words(const char *s, const char c)
{
	int		wait;
	size_t	counter;

	wait = 1;
	counter = 0;
	while (*s)
	{
		if (wait && *s != c)
			counter++;
		wait = (*s == c);
		s++;
	}
	return (counter);
}

static void	fill_str(char *tabs, const char *s, size_t wordlen)
{
	size_t	i;

	i = 0;
	while (i < wordlen - 1)
	{
		tabs[i] = *s;
		i++;
		s++;
	}
	tabs[i] = '\0';
}

static void	*free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	wordlen;
	size_t	i;

	words = count_words(s, c);
	tab = malloc((words + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		wordlen = ft_wordlen(s, c);
		tab[i] = malloc(wordlen);
		if (tab[i] == NULL)
			return (free_tab(tab));
		fill_str(tab[i], s, wordlen);
		s += wordlen;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
