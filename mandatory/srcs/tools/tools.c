#include "../../header.h"

int	mystrlen (char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*mixem(char *path, char *cmd)
{
	char *str;
	int	i;
	int j;

	str = malloc (mystrlen(path) + mystrlen(cmd) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (path[j])
		str[i++] = path[j++];
	j = 0;
	while (cmd[j])
		str[i++] = cmd[j++];
	str[i] = 0;
	return (str);
}
