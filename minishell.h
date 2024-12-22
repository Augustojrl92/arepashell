/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:09 by layala-s          #+#    #+#             */
/*   Updated: 2024/12/22 18:17:11 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define STATUS 1
# define INPUT 1024
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <errno.h>
