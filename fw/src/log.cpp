#include "log.h"

#include "Arduino.h"

void log_setup() {
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
}