/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:03:55 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/02 20:30:22 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_return(char *s1)
{
	free(s1);
	return (NULL);
}

int	ft_strlen_g(char *s)
{
	int	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	find_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strchr(char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_nextline(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ans;

	len = ft_strlen_g(s1) + ft_strlen_g(s2);
	if (len == 0)
		return (free_return(s1));
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (free_return(s1));
	i = 0;
	while (s1 && s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2 && s2[++j])
		ans[i + j] = s2[j];
	ans[i + j] = '\0';
	free(s1);
	return (ans);
}
