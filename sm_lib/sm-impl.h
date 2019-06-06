#ifndef UDR_SM_IMPL_H
#define UDR_SM_IMPL_H

#include "sm_exh.h"

namespace udr {
namespace ssm {

template <typename EVENT_ID_T>
event_base<EVENT_ID_T>::event_base(const EVENT_ID_T event_id) :
  m_event_id(event_id)
{
}

template <typename EVENT_ID_T>
EVENT_ID_T event_base<EVENT_ID_T>::id() const
{
  return m_event_id;
}

//---------------------------------------------------------------------------
template <typename SM_T, typename EVENT_ID_T, typename STATE_ID_T>
sm_base<SM_T, EVENT_ID_T, STATE_ID_T>::sm_base(
  const trans_table_t & trans_table,
  const STATE_ID_T & initial_state) :
  m_trans_table(trans_table),
  m_current_state(initial_state)
{
}

//---------------------------------------------------------------------------
template <typename SM_T, typename EVENT_ID_T, typename STATE_ID_T>
STATE_ID_T sm_base<SM_T, EVENT_ID_T, STATE_ID_T>::get_current_state() const
{
  return m_current_state;
}

//---------------------------------------------------------------------------
template <typename SM_T, typename EVENT_ID_T, typename STATE_ID_T>
STATE_ID_T sm_base<SM_T, EVENT_ID_T, STATE_ID_T>::process_event(const event_base<EVENT_ID_T> & event)
{
  for (const auto & row : m_trans_table)
  {
    if ((row.current_state == m_current_state) &&
        (row.event_id == event.id()))
    {
      SM_T & sm_ref = dynamic_cast<SM_T &>(*this);
      const bool trans_allowed = row.guard_fn(sm_ref,
                                              row.current_state,
                                              event,
                                              row.next_state);
      if (trans_allowed)
      {
        perform_state_trans(row, event);
        return m_current_state;
      }
    }
  }

  throw sm_exh_unhandled_event<STATE_ID_T, event_base<EVENT_ID_T>>(m_current_state, event);
}

//---------------------------------------------------------------------------
template <typename SM_T, typename EVENT_ID_T, typename STATE_ID_T>
void sm_base<SM_T, EVENT_ID_T, STATE_ID_T>::perform_state_trans(
  const trans_table_row_t & trans_table_row,
  const event_base<EVENT_ID_T> & event)
{

  SM_T & sm_ref = dynamic_cast<SM_T &>(*this);

  trans_table_row.action_fn(sm_ref,
                            trans_table_row.current_state,
                            trans_table_row.next_state,
                            event);

  m_current_state = trans_table_row.next_state;
}

} // namespace ssm
} // namespace udr
#endif // UDR_SM_IMPL_H
