#ifndef UDR_EVENT_FACTORY_H
#define UDR_EVENT_FACTORY_H

#include <memory>
#include "sm_lib/sm.h"

template <typename EVENT_ID_T>
class event_factory
{
  public:

    using event_base_t = udr::ssm::event_base<EVENT_ID_T>;
    using event_ptr = std::unique_ptr<event_base_t>;

    event_factory() = default;

    virtual ~event_base() = default;

    event_ptr create_event(const std::string & text_token) const;
};

template <typename EVENT_ID_T>
event_factory<EVENT_ID_T>::event_ptr
event_factory<EVENT_ID_T>::create_event(const std::string & text_token) const
{
  if (text_token == "g++") return std::make_unique<event_base_t>(EVENT_CPP_COMPILER);
  if (text_token == "c++") return std::make_unique<event_base_t>(EVENT_CPP_COMPILER);
  if (text_token == "ar") return std::make_unique<event_base_t>(EVENT_AR);
  if (text_token == "-o") return std::make_unique<event_base_t>(EVENT_CPP_NAME_TAG);
  if (text_token == "-cr") return std::make_unique<event_base_t>(EVENT_AR_NAME_TAG);
  if (text_token == "/usr/bin/ld:") return std::make_unique<event_base_t>(EVENT_LINKER_WARN);
  if (text_token == "\n") return std::make_unique<event_base_t>(EVENT_EOL);
  
  return std::make_unique<event_text>(EVENT_TEXT, text_token);
}

#endif // UDR_EVENT_FACTORY_H
