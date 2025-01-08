/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:26:37 by layala-s          #+#    #+#             */
/*   Updated: 2025/01/08 16:26:39 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef enum e_states {
    EMPTY,          // 0
    INVALID,        // 1
    NOT_OPERATOR,   // 2
    QUOT,           // 3
    ENDQ,           // 4
    PIPE,           // 5
    RED_IN_QUOTE,   // 6
    RED_IN_D_QUOTE, // 7
    RED_OUT_QUOTE,  // 8
    RED_OUT_D_QUOTE,// 9
    LAST            // 10
} t_states;

int	get_state(int prev, int curr);
int	is_operator(char c);

#endif
