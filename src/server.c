/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:31:44 by amalangi          #+#    #+#             */
/*   Updated: 2024/01/25 12:40:22 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	check_pid_init(int pid, int init)
{
	if (!pid)
	{
		ft_printf("%s is bad pid\n", pid);
		exit(1);
	}
	if (kill(pid, 0) < 0)
	{
		ft_printf("ERROR with pid: %d, can't send signal\n", pid);
		exit(1);
	}
	if (!init)
		init = ft_printf("\nClient [%d]: ", pid);
	return (init);
}

void	handler(int sig, siginfo_t *data, void *ptr)
{
	static char	c = 0;
	static int	bit = 7;
	static int	init = 0;

	(void)ptr;
	init = check_pid_init(data->si_pid, init);
	if (sig == SIGUSR1)
		c += 1 << bit;
	else if (sig == SIGUSR2)
		c += 0 << bit;
	bit--;
	if (bit == -1 && c)
	{
		write(1, &c, 1);
		bit = 7;
		c = 0;
	}
	else if (!bit && !c)
	{
		init = 0;
		bit = 7;
		c = 0;
		kill(data->si_pid, SIGUSR2);
	}
	kill(data->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	registry;

	sigemptyset(&registry.sa_mask);
	registry.sa_sigaction = handler;
	registry.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &registry, 0);
	sigaction(SIGUSR2, &registry, 0);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		sleep(1);
	}
	return (0);
}
