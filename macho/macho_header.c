#include "magic.h"
#include <stdio.h>

void	magic_init(t_magic_data *data)
{
	
}

extern t_magic	g_magic;

char magic_isset()
{
}

t_magic_val	*magic_get(uint32_t key)
{
	static size_t	node_visited = 0;
	int				index;

	index = ((int)key) % HT_MAGIC_SIZE;
	if 
	while (!magic_isset(key, index))
	{
		if (node_visited == HT_MAGIC_SIZE)
			return NULL;
		_magic_visit(node_visited++);
	}
}

int		main(int ac, char **av)
{
//	printf("%s\n", g_magic[0].val.str);
	printf("%lu\t%lu",sizeof(ptr),sizeof(uint8_t));
	return (0);
}
