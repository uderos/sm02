#include <iostream>

#include "sm01.h"

template <typename EVENT_T>
static void post_event_helper(sm01 & sm, const EVENT_T & event)
{
  const eState current_state = sm.get_current_state();
  sm.process_event(event);
  const eState next_state = sm.get_current_state();
  std::cout << "Posting event_id=" << event.id()
            << " state: " << current_state << " ==> " << next_state
            << std::endl;
}

static void test01()
{
  std::cout << __FUNCTION__ << "() BEGIN" << std::endl;

  try
  {
    sm01 sm;

    post_event_helper(sm, event_t(EVENT_ID_ONE));
    post_event_helper(sm, event_t(EVENT_ID_TWO));
    post_event_helper(sm, event_end(true));
  }
  catch (const std::exception & e)
  {
    std::cout << "EXCEPTION: " << e.what() << std::endl;
  }
}


int main()
{
  test01();

  return 0;
}

