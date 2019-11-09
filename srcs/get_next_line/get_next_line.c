/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:52:55 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/25 19:53:03 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*get_remainder(t_file **lst, int fd)
{
	t_file *prev;
	t_file *tmp;
	t_file *new;

	prev = NULL;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	new = NULL;
	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	new->content = NULL;
	new->fd = fd;
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
		prev->next = new;
	return (new);
}

int		ft_strchar_strlen(char *str, char c, int option)
{
	int n;

	n = 0;
	if (option == 0)
	{
		if (str == NULL)
			return (-1);
		while (str[n])
		{
			if (str[n] == c)
				return (n);
			n++;
		}
		return (-1);
	}
	else if (option == 1)
	{
		if (str == NULL)
			return (0);
		while (str[n])
			n++;
		return (n);
	}
	return (-2);
}

char	*concat_strings(char *s1, char *s2, int max)
{
	char	*new;
	int		len1;
	int		len2;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strchar_strlen(s1, 0, 1);
	len2 = ft_strchar_strlen(s2, 0, 1);
	new = NULL;
	if (!(new = (char*)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = -1;
	while (++i < len1)
		new[i] = s1[i];
	i = -1;
	while (++i < len2 && i < max)
		new[len1 + i] = s2[i];
	new[len1 + len2] = 0;
	if (max < len2)
		new[len1 + max] = 0;
	if (s1 != NULL)
		free(s1);
	return (new);
}

int		trim_remainder(t_file *rmd, char *s2)
{
	char *tmp;

	if (*s2 == 0)
	{
		if (rmd->content != NULL)
			free(rmd->content);
		rmd->content = NULL;
		return (1);
	}
	tmp = rmd->content;
	rmd->content = concat_strings(NULL, s2 + 1, ft_strchar_strlen(s2, 0, 1));
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*lst;
	t_file			*rmd;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	int				n;

	ret = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	rmd = get_remainder(&lst, fd);
	while (ft_strchar_strlen(rmd->content, '\n', 0) == -1
			&& (ret = read(fd, buf, BUFF_SIZE)) > 0
			&& (buf[ret] = 0) == 0)
		rmd->content = concat_strings(rmd->content, buf, BUFF_SIZE);
	if ((rmd->content == NULL || rmd->content[0] == 0)
			&& ret == 0 && (*line = NULL) == NULL)
		return (0);
	if (ret == -1)
		return (-1);
	if (ft_strchar_strlen(rmd->content, '\n', 0) != -1)
		n = ft_strchar_strlen(rmd->content, '\n', 0);
	else
		n = ft_strchar_strlen(rmd->content, 0, 1);
	*line = concat_strings(NULL, rmd->content, n);
	return (trim_remainder(rmd, rmd->content + n));
}
