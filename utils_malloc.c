/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:06:28 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/17 20:32:51 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_mallocator(void *content, const size_t size)
{
    *(void **)content = malloc(size);
    if (!(*(void **)content))
        return (EXIT_FAILURE);
    memset(*(void **)content, 0, size);
    return (EXIT_SUCCESS);
}

void    my_freetator(void *content)
{
    if (*(void **)content)
    {
        free(*(void **)content);
        *(void **)content = NULL;
    }
}