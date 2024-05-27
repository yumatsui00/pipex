/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:35:19 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/03 12:35:38 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	ft_strlcpy(char *dst, const char *src, int size)
{
	int	i;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	i = ft_strlen(src);
	return (i);
}

char	*ft_strjoin_pipe(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ans;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (len == 0)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (len + 2));
	if (!ans)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		ans[i] = s1[i];
	ans[i++] = '/';
	j = -1;
	while (s2 && s2[++j])
		ans[i + j] = s2[j];
	ans[i + j] = '\0';
	return (ans);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*ans;

	ans = (char *)malloc(ft_strlen(s1) + 1);
	if (!ans)
		return (NULL);
	dup = ans;
	while (*s1)
	{
		*ans = *s1;
		s1++;
		ans++;
	}
	*ans = '\0';
	return (dup);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		n--;
		s1++;
		s2++;
	}
	if (n > 0)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	return (0);
}
