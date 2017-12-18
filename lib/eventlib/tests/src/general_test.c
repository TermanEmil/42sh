#include "eventlibtests.h"

void	general_test(void)
{
	t_hashtab	*events;

	events = events_construct(10);
	event_add(events, "event1_say1",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 1"));
	event_add(events, "event1_say2",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 2"));
	event_add(events, "event1_say3",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 3"));
	event_add(events, "event1_say4",
		event_instance_construct((t_handler_f*)&ft_putendl, "[event1]: 4"));
	
	event_add(events, "free_events",
		event_instance_construct((t_handler_f*)&events_destruct, &events));

	events_run_iter_matching(events, "event1*", (t_cmp_f*)&std_htab_str_match);
	events_run_first(events, "free_events");
	
	FREE_TESTS();
}
