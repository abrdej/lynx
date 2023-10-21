#pragma once

#include <memory>

#include <lynx/net/message.h>

namespace lynx::net {

template <typename connection_type>
using owned_message_type = std::pair<std::shared_ptr<connection_type>, message_type>;

}  // namespace lynx::net
