#include "eventlibtests.h"

void	remove_add_test(void)
{
	t_hashtab	*events;

	events = events_construct(0);
	event_add(events, "event1_say1",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 1"));
	event_add(events, "event1_say2",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 2"));
	event_add(events, "event1_say3",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 3"));
	event_add(events, "event1_say4",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 4"));

	events_remove_with_key(events, "event1_say1");

	for (int i = 0; i < 100; i++)
	{
		event_add(events, "event1_rolling1",
			event_instance_construct((t_handler_f*)&ft_putendl, "rolling1"));
	}

	event_add(events, "event1_roll2",
		event_instance_construct((t_handler_f*)&ft_putendl, "rolling2"));

	events_rm_iter_matching(events, "event1_rolling*", (t_cmp_f*)&std_htab_str_match);

	event_add(events, "free_events",
		event_instance_construct((t_handler_f*)&events_destruct, &events));

	events_run_iter_matching(events, "event1*", (t_cmp_f*)&std_htab_str_match);
	events_run_first(events, "free_events");
	
	FREE_TESTS();	
}
