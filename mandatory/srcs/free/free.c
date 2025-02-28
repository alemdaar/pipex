#include "../header.h"

void free_all (t_cmd *cmd)
{
	if (cmd->all_path)
		free(cmd->all_path)
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