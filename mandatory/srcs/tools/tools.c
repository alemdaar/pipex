#include "../../header.h"

int	mystrlen (char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*mixem(t_cmd *cmd, t_other *other, int path_ind)
{
	char *str;
	int	i;
	int j;

	str = malloc (mystrlen(other->paths[path_ind]) + mystrlen(cmd->cmd) + 2);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (other->paths[path_ind][j])
		str[i++] = other->paths[path_ind][j++];
	j = 0;
	str[i++] = '/';
	while (cmd->cmd[j])
		str[i++] = cmd->cmd[j++];
	str[i] = 0;
	return (str);
}
