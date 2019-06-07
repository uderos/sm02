#ifndef UDR_SM_H
#define UDR_SM_H

#include <functional>
#include <vector>

namespace udr {
namespace ssm {

template <typename EVENT_ID_T>
class event_base
{
  public:
    event_base(const EVENT_ID_T event_id);
    virtual ~event_base() = default;
    EVENT_ID_T id() const;
  private:
    const EVENT_ID_T m_event_id;
};

template <typename SM_T, typename EVENT_ID_T, typename STATE_ID_T>
class sm_base
{
  public:

    ///////////////////////////////////////////////////////////////////
    // Construction - Data
    ///////////////////////////////////////////////////////////////////
    using guard_fn_t  = std::function<bool(SM_T &,
                                           const STATE_ID_T &,
                                           const event_base<EVENT_ID_T> &,
                                           const STATE_ID_T &)>;

    using action_fn_t = std::function<void(SM_T &,
                                           const STATE_ID_T &,
                                           const STATE_ID_T &,
                                           const event_base<EVENT_ID_T> &)>;

    struct trans_table_row_t
    {
      STATE_ID_T current_state;
      EVENT_ID_T event_id;
      STATE_ID_T next_state;
      guard_fn_t guard_fn;
      action_fn_t action_fn;

      trans_table_row_t(const STATE_ID_T  & current_state_in,
                        const EVENT_ID_T  & event_id_in,
                        const STATE_ID_T  & next_state_in,
                        const guard_fn_t  & guard_fn_in,
                        const action_fn_t & action_fn_in);

      trans_table_row_t(const STATE_ID_T & current_state_in,
                        const EVENT_ID_T & event_id_in,
                        const STATE_ID_T & next_state_in);

      trans_table_row_t(const STATE_ID_T & current_state_in,
                        const EVENT_ID_T & event_id_in,
                        const STATE_ID_T & next_state_in,
                        const guard_fn_t & guard_fn_in);

      trans_table_row_t(const STATE_ID_T  & current_state_in,
                        const EVENT_ID_T  & event_id_in,
                        const STATE_ID_T  & next_state_in,
                        const action_fn_t & action_fn_in);
    };

    using trans_table_t = std::vector<trans_table_row_t>;

    ///////////////////////////////////////////////////////////////////
    // Construction - Methods
    ///////////////////////////////////////////////////////////////////
    sm_base(const trans_table_t & trans_table,
            const STATE_ID_T & initial_state);

    virtual ~sm_base() = default;

    ///////////////////////////////////////////////////////////////////
    // Execution
    ///////////////////////////////////////////////////////////////////
    STATE_ID_T process_event(const event_base<EVENT_ID_T> & event);


    ///////////////////////////////////////////////////////////////////
    // Misc / helper methods
    ///////////////////////////////////////////////////////////////////
    STATE_ID_T get_current_state() const;


  private:

    const trans_table_t m_trans_table;
    STATE_ID_T m_current_state;

    void perform_state_trans(const trans_table_row_t & trans_table_row,
                             const event_base<EVENT_ID_T> & event);
};

template <typename EVENT_ID_T>
bool operator==(const event_base<EVENT_ID_T> & e1,
                const event_base<EVENT_ID_T> & e2)
{
  return e1.id() == e2.id();
}

} // namespace ssm
} // namespace udr

#include "sm-impl.h"

#endif // UDR_SM_H
