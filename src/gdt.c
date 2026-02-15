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

#include "ft_io.h"
#include "ft_terminal.h"

/* 
The GDTR register contains two pieces of information:
limit -> Size of the GDT - 1
base -> Starting address of the GDT in memory
*/
void print_gdt_address(void)
{
    unsigned char gdtr[6];
    
    asm("sgdt %0" : "=m"(gdtr));
    
    unsigned int base = *(unsigned int *)(gdtr + 2);
    ft_printf("GDT base: 0x%x\n", base);
}

void print_stack(void)
{
	unsigned int *esp;
	
	 // Copy the address of the top of the stack into esp.
    asm("mov %%esp, %0": "=r"(esp));

    terminal_setcolor(vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK));
    ft_printf("=== KERNEL STACK ===\n");
    ft_printf("ESP: 0x%x\n", (esp));
    ft_printf("--------------------\n");
	for (int i = 0; i < 8; ++i) {
		ft_printf("[%d] [%x]: 0x%x\n",i, &esp[i], (esp[i]));
	}
    ft_printf("====================\n");
}