/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:03:01 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 15:42:50 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_msh *msh, char **arg, t_env *env_list)
{
	int		ret;
	int		i;
	char	*key;

	i = 1;
	ret = SUCCESS;
	while (arg[i])
	{
		key = arg[i];
		if (check_key(key) < 0)
			ret = handling_error(msh, E_NVALID, key, NULL);
		delete_key_env(env_list, key);
		i ++;
	}
	return (ret);
}
