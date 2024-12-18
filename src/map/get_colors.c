/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:01 by agiliber          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:48 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	open_texture(char *texture)
{
	int	fd;

	fd = open(texture, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

int	check_colors(char *color)
{
	char	**colors;
	int		i;

	colors = ft_split(color, ',');
	if (!colors)
		return (-1);
	i = 0;
	while (colors[i])
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (-1);
		i++;
	}
	free_everything(colors);
	return (0);
}

char	*get_file_color(char *file)
{
	int		i;
	char	*color;

	i = 0;
	if (!file)
		return (NULL);
	while (file[i] != ' ')
		i++;
	if (!file)
		return (NULL);
	i++;
	color = ft_strdup(&file[i]);
	if (check_colors(color) == -1)
		return (NULL);
	return (color);
}

int	get_colors(t_game_data *game, char *file)
{
	if (!file)
		return (-1);
	if (file[0] == 'F')
	{
		game->floor_color = NULL;
		game->floor_color = get_file_color(file);
		if (game->floor_color == NULL)
			return (-1);
	}
	else if (file[0] == 'C')
	{
		game->ceiling_color = NULL;
		game->ceiling_color = get_file_color(file);
		if (game->ceiling_color == NULL)
			return (-1);
	}
	return (0);
}

int	texture_verify(t_game_data *game)
{
	(void)game;
	if (check_texture_files("textures/dark_oak_trapdoor.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/obsidian.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/suspicious_gravel_0.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/polished_blackstone_bricks_0.xpm") \
		== -1)
		return (-1);
	if (check_texture_files("textures/tuff.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/dragon_egg.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/black_terracotta.xpm") == -1)
		return (-1);
	return (0);
}
