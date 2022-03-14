/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:17:40 by spoliart          #+#    #+#             */
/*   Updated: 2022/03/14 18:50:14 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool motus(const char *word, const char *exclude, const char *contains, const char *red, const char *yellow)
{
	size_t	nb_contains = 0;
	char	*tmp = strdup(contains);

	for (size_t i = 0; word[i]; i++) {
		for (size_t j = 0; exclude[j]; j++) {
			if (word[i] == exclude[j]) {
				free(tmp);
				return (false);
			}
		}
		for (size_t j = 0; tmp[j]; j++) {
			if (word[i] == tmp[j]) {
				tmp[j] = '=';
				nb_contains++;
				break ;
			}
		}
		if (red[i] != '.' && red[i] != word[i])
			return (false);
		else if (yellow[i] == word[i])
			return (false);
	}
	free(tmp);
	if (strlen(contains) != nb_contains)
		return (false);
	return (true);
}

int main(int ac, char **av)
{
	if (ac != 5) {
		dprintf(2, "usage: ./motus [exclude char] [contains char] [known char place] [not this place char]\n");
		return (EXIT_FAILURE);
	}
	size_t	printed = 1;
	char	*exclude = av[1];
	char	*contains = av[2];
	char	*red = av[3];
	char	*yellow = av[4];

	int		fd;
	fd = open("words.txt", O_RDONLY);
	if (fd < 0) {
		dprintf(2, "open error: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}

	char	*line;
	char	**words;
	int		ret = get_next_line(fd, &line);
	if (ret == -1) {
		dprintf(2, "gnl error\n");
		return (EXIT_FAILURE);
	}
	words = ft_split(line, " ");
	free(line);

	size_t	i;
	for (i = 0; words[i]; i++) {
		if (motus(words[i], exclude, contains, red, yellow) == true)
			printf("word %ld: [%s]\n", printed++, words[i]);
	}
	printf("total given words: %ld\n", i);

	ft_free_tab(words, NULL);

	return (EXIT_SUCCESS);
}
