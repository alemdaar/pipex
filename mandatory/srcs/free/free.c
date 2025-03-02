#include "../../header.h"

void free_all (t_cmd *cmd)
{
	t_ind ind;

	if (cmd->cmd)
	{
		ind.i = 0;
		while (ind.i < 2)
			free(cmd->cmd[ind.i++]);
		free(cmd->cmd);
	}
	if (cmd->opt)
	{
		ind.i = 0;
		while (ind.i < 2)
			free(cmd->opt[ind.i++]);
		free(cmd->opt);
	}
	if (cmd->paths)
	{
		ind.i = 0;
		while (ind.i < cmd->count_path)
			free(cmd->paths[ind.i++]);
		free(cmd->paths);
	}
	return ;
}

void zerod_2(char ***str, int count)
{
	int	i;

	i = 0;
	while (i < count)
		str[0][i++] = NULL;
	return ;
}

void zerod_1(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
		str[0][i++] = 0;
	return ;
}