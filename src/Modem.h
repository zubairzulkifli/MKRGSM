#ifndef _MODEM_INCLUDED_H
#define _MODEM_INCLUDED_H

#include <Arduino.h>

class ModemUcrHandler {
public:
  virtual void handleUcr(const String& ucr) = 0;
};

class ModemClass {
public:
  ModemClass(Uart& uart, unsigned long baud, int resetPin);

  int begin(bool restart = true);
  void end();

  int autosense(int timeout = 10000);

  int noop();
  int reset();

  size_t write(uint8_t c);
  void send(const char* command);
  void send(const String& command) { send(command.c_str()); }
  int waitForResponse(unsigned long timeout = 100, String* responseDataStorage = NULL);
  int ready();
  void poll();
  void setResponseDataStorage(String* responseDataStorage);
  void setUcrHandler(ModemUcrHandler* handler);

private:
  Uart* _uart;
  unsigned long _baud;
  int _resetPin;

  enum {
    AT_COMMAND_IDLE,
    AT_RECEIVING_RESPONSE
  } _atCommandState;
  int _ready;
  String _buffer;
  String* _responseDataStorage;
  ModemUcrHandler* _ucrHandler;
};

extern ModemClass MODEM;

#endif