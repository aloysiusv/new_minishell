/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutur_la_chaussure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:53:06 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/14 22:59:27 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int main(int ac, char **av) {

    int x = 1;
    (void)ac;
    while (av[x]) {
        printf("-> %s\n", av[x]);
        x++;
    }
    return (0);
}

/*
->minishell ./a.out tutur"la"chaussure
-> [tuturlachaussure]
➜  minishell ./a.out tutur "la" chaussure
-> [tutur]
-> [la]
-> [chaussure]
➜  minishell ./a.out $USER               
-> [lrandria]
➜  minishell gcc -Wall -Wextra -Werror -fsanitize=address -g3 tutur_la_chaussure.c
➜  minishell ./a.out $USER'$USER'
-> lrandria$USER
➜  minishell ./a.out "$USER'$USER'"
-> lrandria'lrandria' 
*/