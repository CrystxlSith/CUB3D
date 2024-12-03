#include "../../includes/cub3d.h"

int	map_width(int index, char **input)
{
	int	index_y;
	int	width;

	width = 0;
	index_y = 0;
	while (input[index][index_y])
	{
		width++;
		index_y++;
	}
	return (width);
}

int	map_length(int index, char **input)
{
	int	index_x;
	int	length;

	length = 0;
	index_x = 0;
	while (input[index_x][index])
	{
		length++;
		index_x++;
	}
	return (length);
}

int	count_words(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		count++;
		i++;
	}
	return (count);
}
