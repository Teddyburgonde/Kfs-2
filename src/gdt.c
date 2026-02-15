/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:36:38 by tebandam          #+#    #+#             */
/*   Updated: 2026/02/15 07:54:21 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf"
# include "terminal.h"

/*

### Exercice 1
Écris le code pour récupérer la valeur de ESP dans une variable.

### Exercice 2
Affiche cette valeur avec `ft_printf` (format hexadécimal `%x`).

### Exercice 3
Lis et affiche les 4 premières valeurs sur la stack.

move source, destination

*/

void print_stack(void)
{
	int esp; 
	
	esp = 0;
	// copy l'adresse du sommet de la stack et met la dans esp.
    asm("mov %0, %%esp": "=r"(esp));
    ft_printf("ESP = 0x%x\n", esp);
}