/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:16:46 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 12:28:20 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i ++;
	}
	free(strs);
}

void	free_all_the_stuffs(t_msh *msh)
{
	int			i;
	t_exec_mat	*cur_mat;

	i = 0;
	while (i <= msh->pipe_cnt)
	{
		cur_mat = &msh->ex_mat[i];
		delete_all_token(&cur_mat->token_list);
		if (cur_mat->arg)
			free_strs(cur_mat->arg);
		if (cur_mat->cmd)
			free(cur_mat->cmd);
		i ++;
	}
	free(msh->ex_mat);
	if (msh->path != NULL)
		free_strs(msh->path);
	msh->ex_mat = NULL;
	msh->path = NULL;
	msh->token_list = NULL;
	msh = 0;
}
