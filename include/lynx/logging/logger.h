#pragma once

#include <cstring>

#include <boost/exception/all.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/exception.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/console.hpp>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace logging = boost::log;

using logger_t = logging::sources::severity_logger<logging::trivial::severity_level>;

BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(my_logger, logger_t) {
  namespace logging = boost::log;
  logger_t lg;
  return lg;
}

#define LOG(LEVEL)                                             \
  BOOST_LOG_SEV(my_logger::get(), logging::trivial::LEVEL)     \
    << boost::log::add_value("Line", __LINE__)                 \
    << boost::log::add_value("Filename", __FILENAME__)         \
    << boost::log::add_value("Function", __FUNCTION__)


inline void init_logging() {
  logging::add_common_attributes();

  logging::register_simple_filter_factory<logging::trivial::severity_level, char>("Severity");
  logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

  auto syslog_format(logging::expressions::stream
                         << "["
                         << logging::expressions::format_date_time<boost::posix_time::ptime>(
                             "TimeStamp",
                             "%Y-%m-%d %H:%M:%S") << "] ["
                         << logging::trivial::severity << "] ["
                         << logging::expressions::attr<std::string>("Filename") << ":"
                         << logging::expressions::attr<std::string>("Function") << ":"
                         << logging::expressions::attr<int>("Line") << "] "
                         << logging::expressions::smessage
  );

  logging::add_console_log(std::cout, logging::keywords::format = syslog_format);

  logging::add_file_log(logging::keywords::file_name  = "sys_%d_%m_%Y.%N.log",
                        logging::keywords::format = syslog_format);
}
