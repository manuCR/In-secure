#include "Bitacora.hpp"
#include <syslog.h>

// Constructor
Bitacora::Bitacora() {}

void Bitacora::add(std::string entry) {
  // Se abre la conexión con el servicio syslog
  openlog("Main", LOG_CONS | LOG_PID, LOG_LOCAL5);
  // Se escribe un mensaje de prueba en el nivel de severidad 'info'
  syslog(LOG_INFO, "%s", entry.c_str());
  // Se cierra la conexión con el servicio syslog
  closelog();
}

void Bitacora::open() {
  // Se abre la conexión con el servicio syslog
  openlog("Main", LOG_CONS | LOG_PID, LOG_LOCAL5);
}

void Bitacora::write(std::string entry) {
  // Se escribe un mensaje de prueba en el nivel de severidad 'info'
  syslog(LOG_INFO, "%s", entry.c_str());
}

void Bitacora::close() {
  // Se cierra la conexión con el servicio syslog
  closelog();
}
