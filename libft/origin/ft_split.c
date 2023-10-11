/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:07:27 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strnum(char *s, char c)
{
	int	str_num;
	int	ind;

	ind = 0;
	str_num = 0;
	if (!s[ind])
		return (0);
	while (s[ind])
	{
		if (s[ind] != c && (s[ind + 1] == c || s[ind + 1] == 0))
			str_num ++;
		ind ++;
	}
	return (str_num);
}

static char	*make_alloc(char *str, int len, int ind)
{
	int		i;
	char	*cp;

	i = 0;
	cp = (char *) malloc(sizeof(char) * (len + 1));
	if (!cp)
		return (0);
	while (i < len)
	{
		cp[i] = str[ind + i];
		i ++;
	}
	cp[i] = '\0';
	return (cp);
}

static char	**free_all(char **splstr, int idx)
{
	while (idx >= 0)
	{
		free(splstr[idx]);
		idx --;
	}
	free(splstr);
	return (0);
}

static char	**split_str(char **splstr, char *str, char c)
{
	int	ind;
	int	subind;
	int	splind;

	ind = 0;
	subind = 0;
	splind = 0;
	while (str[ind])
	{
		if (str[ind] != c)
		{
			while (str[ind + subind] != c && str[ind + subind])
				subind ++;
			splstr[splind] = make_alloc(str, subind, ind);
			if (!splstr[splind])
				return (free_all(splstr, splind));
			splind ++;
			ind += subind;
			subind = 0;
		}
		if (str[ind])
			ind ++;
	}
	splstr[splind] = 0;
	return (splstr);
}

char	**ft_split(char *s, char c)
{
	int		str_num;
	char	**spl_str;

	str_num = ft_strnum(s, c);
	spl_str = (char **) malloc (sizeof(char *) * (str_num + 1));
	if (!spl_str)
		return (0);
	if (!str_num)
	{
		spl_str[0] = 0;
		return (spl_str);
	}
	return (split_str(spl_str, s, c));
}

/*
#include <stdio.h>
int main(int ac, char **av) {
	(void) ac;
	char **sp = ft_split(av[1], av[2][0]);
	for (int i = 0; i <= ft_strnum(av[1], av[2][0]); i ++)
		printf("%s\n", sp[i]);
}
*/
