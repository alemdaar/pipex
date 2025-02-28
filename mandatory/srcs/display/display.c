#include "../../header.h"

void myputstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void why_exit(char *str, int type)
{
	myputstr(str);
	exit(type);
}
