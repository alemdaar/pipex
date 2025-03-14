#include "../../header.h"

void free_all (t_cmd *cmd, t_other *other)
{
	t_ind ind;
	t_cmd *tmp;
	t_cmd *tmp2;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
		{
			free(tmp->cmd);
			tmp->cmd =  NULL;
		}
		if (tmp->opt)
		{
			free(tmp->opt);
			tmp->opt =  NULL;
		}
		if (tmp->path_cmd)
		{
			free(tmp->path_cmd);
			tmp->path_cmd = NULL;
		}
		if (tmp->argument)
		{
			ind.i = 0;
			while (tmp->argument[ind.i] && ind.i < tmp->ar)
				free(tmp->argument[ind.i++]);
			free(tmp->argument);

		}
		tmp2 = tmp;
		free (tmp2);
		tmp = tmp->next;
	}
	if (other->paths)
	{
		ind.i = 0;
		while (other->paths[ind.i] && ind.i < other->count_path)
			free(other->paths[ind.i++]);
		free(other->paths);
	}
	return ;
}
