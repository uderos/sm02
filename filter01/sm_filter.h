#ifndef UDR_SM_FILTER_H
#define UDR_SM_FILTER_H

#include "sm_lib/sm.h"


enum eState {
  STATE_WAIT_CMD,
  STATE_WAIT_CPP_NAME,
  STATE_WAIT_AR_NAME,
  STATE_WAIT_FILE_NAME,
  STATE_WAIT_EOL,
  STATE_DROP_LINE,
};

enum eEventId
{
  EVENT_CPP_COMPILER,
  EVENT_CPP_COMPILER,
  EVENT_AR,
  EVENT_CPP_NAME_TAG,
  EVENT_AR_NAME_TAG,
  EVENT_LINKER_WARN,
  EVENT_EOL,
  EVENT_TEXT,
};

using event_t = udr::ssm::event_base<eEventId>;

class event_text : public event_t
{
  public:
    event_end(const std::string & text) : event_t(EVENT_ID_TEXT), m_text(text) {}
    const std::string & get_text() const { return m_text; }
  private:
    const std::string m_text;
};


class sm_filter : public udr::ssm::sm_base<sm_filter, eEventId, eState>
{
  public:
    sm_filter();
};

using sm_base_t = udr::ssm::sm_base<sm_filter, eEventId, eState>;

#endif // UDR_SM_FILTER_H
