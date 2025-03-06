/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:19:03 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:14:53 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hdc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		close(STDIN_FILENO);
	}
}

void	do_nothing(int sig)
{
	g_sig = sig;
}

void	readline_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, RESET"\n", ft_strlen(RESET) + 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig = SIGINT;
	}
}
