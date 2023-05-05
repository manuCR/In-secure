#include <syslog.h>
#include "Bitacora.hpp"

// Constructor
Bitacora::Bitacora() {

}

void Bitacora::add(string entry) {
    // Se abre la conexión con el servicio syslog
    openlog("Main", LOG_CONS | LOG_PID, LOG_LOCAL5);

    // Se escribe un mensaje de prueba en el nivel de severidad 'info'
    syslog(LOG_INFO, entry);

    // Se cierra la conexión con el servicio syslog
    closelog();    
}


void Bitacora::open(){
    // Se abre la conexión con el servicio syslog
    openlog("Main", LOG_CONS | LOG_PID, LOG_LOCAL5);
      }

void Bitacora::write(string entry){
    // Se escribe un mensaje de prueba en el nivel de severidad 'info'
    syslog(LOG_INFO, entry);
  }

void Bitacora::close(){
    // Se cierra la conexión con el servicio syslog
    closelog();
  }



