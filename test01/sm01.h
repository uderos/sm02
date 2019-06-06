#ifndef UDR_SM01_H
#define UDR_SM01_H

#include "sm_lib/sm.h"


enum eState {
  STATE_IDLE,
  STATE_ONE,
  STATE_TWO,
  STATE_END
};

enum eEventId
{
  EVENT_ID_ONE,
  EVENT_ID_TWO,
  EVENT_ID_END
};

using event_t = udr::ssm::event_base<eEventId>;

class event_end : public event_t
{
  public:
    event_end(const bool result) : event_t(EVENT_ID_END), m_result(result) {}
    bool get_result() const { return m_result; }
  private:
    bool m_result;
};


class sm01 : public udr::ssm::sm_base<sm01, eEventId, eState>
{
  public:
    sm01();
};

using sm_base_t = udr::ssm::sm_base<sm01, eEventId, eState>;

#endif // UDR_SM01_H
