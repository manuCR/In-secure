#include "Bitacora.hpp"
#include <syslog.h>

Bitacora::Bitacora() {}

void Bitacora::add(std::string entry) {
  openlog("Main", LOG_CONS | LOG_PID, LOG_LOCAL5);
  syslog(LOG_INFO, "%s", entry.c_str());
  closelog();
}

void Bitacora::open() {
  openlog("Main", LOG_CONS | LOG_PID, LOG_LOCAL5);
}

void Bitacora::write(std::string entry) {
  syslog(LOG_INFO, "%s", entry.c_str());
}

void Bitacora::close() {
  closelog();
}
