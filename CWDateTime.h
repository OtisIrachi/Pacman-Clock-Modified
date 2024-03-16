#ifndef CWDateTimeCf_h
#define CWDateTimeCf_h

#include <Arduino.h>

#include <ezTime.h>
#include <WiFi.h>

class CWDateTime
{
private:
  Timezone myTZ;

public:
  void begin();
  void setTimezone(const char *timeZone);
  String getTimezone();
  void update();
  String getFormattedTime();

  char *getHour(const char *format);
  char *getMinute(const char *format);
  char *getSecond(const char *format);
  char *getYear(const char *format);
  char *getMonth(const char *format);
  char *getDay(const char *format);
  char *getWeekday(const char *format);  
  char *getMilliseconds(const char *format);
  int getHour();
  int getMinute();
  int getSecond();
  int getYear();
  int getMonth();
  int getDay();
  int getWeekday();  
  int getMilliseconds();
};
#endif
