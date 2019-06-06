#include <iostream>
#include "sm01.h"

static bool default_guard_fn(sm01 & sm,
                        const eState & from_state,
                        const event_t & event,
                        const eState & to_state)
{
  std::cout << __FUNCTION__ << "() called"
            << " from_state=" << from_state
            << " event_id=" << event.id()
            << " to_state=" << to_state
            << " transition allowed"
            << std::endl;
  return true;
}

static bool result_guard_fn(sm01 & sm,
                            const eState & from_state,
                            const event_t & event,
                            const eState & to_state)
{
  const event_end & e = dynamic_cast<const event_end &>(event);
  const bool result = e.get_result();

  std::cout << __FUNCTION__ << "() called"
            << " from_state=" << from_state
            << " event_id=" << event.id()
            << " to_state=" << to_state
            << (result ? " allowed" : " NOT allowed")
            << std::endl;
  return result;
}

static void default_action_fn(sm01 & sm,
                        const eState & from_state,
                        const eState & to_state,
                        const event_t & event)
{
  std::cout << __FUNCTION__ << "() called"
            << " from_state=" << from_state
            << " to_state=" << to_state
            << " event_id=" << event.id()
            << std::endl;
}


static const sm_base_t::trans_table_t sm01_trans_table {
  sm_base_t::trans_table_row_t(STATE_IDLE,  EVENT_ID_ONE, STATE_ONE,    default_guard_fn, default_action_fn),
  sm_base_t::trans_table_row_t(STATE_ONE,   EVENT_ID_TWO, STATE_TWO,    default_guard_fn, default_action_fn),
  sm_base_t::trans_table_row_t(STATE_TWO,   EVENT_ID_END, STATE_END,    result_guard_fn,  default_action_fn),
  sm_base_t::trans_table_row_t(STATE_TWO,   EVENT_ID_END, STATE_ERROR,  default_guard_fn, default_action_fn),
};

sm01::sm01() : sm_base_t(sm01_trans_table, STATE_IDLE)
{
}

