#include "shtests.h"

void	memleak_1_shdisplay(void)
{
	t_shdisplay		display;

	display = shdisplay_construct();
	shdisplay_add_block(&display.blocks,
		shdata_block_construct(ft_strdup("emil"), 4));
	shdisplay_add_block(&display.blocks,
		shdata_block_construct(ft_strdup("leosha"), 4));
	shdisplay_add_block(&display.blocks,
		shdata_block_construct(ft_strdup("kek"), 4));
	ft_putnbr(display.blocks.count);
	shdisplay_destruct(&display);
	FREE_TESTS();
}
