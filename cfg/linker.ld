/* Define the entry point */
ENTRY(_start)

SECTIONS {

	/* The start address 
	The code that the user will type will be stored at this address. */
	. = 2M; 

	/* BLOCK(4K) means the memory is divided into 4 KB blocks
    ALIGN(4K) means this is where we start writing in memory */
	.text BLOCK(4K) : ALIGN(4K)
	{
		/* the Multiboot header */
		*(.multiboot)
		
		/* the code */
		*(.text)
	}

	/* Place where the data I want to read but not modify is stored */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* The place where the data you can read AND modify is stored */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* the place where space is reserved for variables that don’t have a value yet */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		/* Variables that the compiler has not yet managed to classify */
		*(COMMON)

		/* global variables */
		*(.bss)
	}

	/* Set GDT at address 0x00000800 */
	.gdt 0x00000800 :
	{
		*(.gdt)
	}

}

