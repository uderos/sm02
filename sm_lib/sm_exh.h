#ifndef UDR_SM_EXH_H
#define UDR_SM_EXH_H

#include <stdexcept>
#include <sstream>
#include <string>

namespace udr {
namespace ssm {

template <typename STATE_T, typename EVENT_T>
class sm_exh_unhandled_event : public std::runtime_error
{
  public:
    sm_exh_unhandled_event(const STATE_T & current_state, const EVENT_T & event) : 
      std::runtime_error("Unhandled event='" + 
                         std::to_string(event.id()) + 
                         "' current_state=" + 
                         std::to_string(current_state))
    {
    }

    /**
    virtual const char * what() const noexcept { return m_msg.c_str(); }

  private:
    std::string m_msg;
    **/
};


} // namespace ssm
} // namespace udr
#endif // UDR_SM_EXH_H
