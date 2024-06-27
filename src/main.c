/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/06/27 18:21:23 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void    get_map(t_cb *cb, char **argv)
{
	(void)cb;
    int i = 0;
    while (argv[1][i])
        printf("%c\n", argv[1][i++]);
}

void    cub3d(char **argv)
{
    t_cb cb;

	ft_bzero(&cb, sizeof(t_cb));
    get_map(&cb, argv);
}

int main(int argc, char **argv)
{
    if (argc == 2)
        cub3d(argv);
    return 0;
}