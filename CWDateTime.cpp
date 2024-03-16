//**********************************************************************************************
// CWDateTime.cpp
//
// Day of Week Numeric = 'N' or 'w'
// Day of Week Text Full = 'l' (lowercase L)
// Day of Week Text Short = 'D' (lowercase L)
// Day of the Month Numeric = 'd' with leading zeros
// Day of the Month Numeric = 'j' without leading zeros
// Month Numeric = 'n' without leading zeros
// Month Numeric = 'm' with leading zeros
// Month Text Short = 'M'
// Month Text Full = 'F'
// Year Numeric Full = 'Y'
// Year Numeric Short = 'y'
// 12 Hour format = 'g' without leading zeros
// 12 Hour format = 'h' with leading zeros
// Minutes = 'i' with leading zeros
// Seconds = 's' with leading zeros
//
//
//**********************************************************************************************
#include "CWDateTime.h"

const char *dayName[8] = {" ", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//**********************************************************************************************
void CWDateTime::begin()
{
  myTZ.setCache(0);
  myTZ.setLocation(F("America/New York")); 
  myTZ.dateTime();  
  waitForSync();
}
//**********************************************************************************************
void CWDateTime::setTimezone(const char *timeZone)
{
  myTZ.setCache(0);
  //myTZ.setLocation(timeZone);
  waitForSync();
}
//**********************************************************************************************
String CWDateTime::getTimezone()
{
  return myTZ.getTimezoneName(0);
}
//**********************************************************************************************
void CWDateTime::update()
{
  
}
//**********************************************************************************************
String CWDateTime::getFormattedTime()
{
  return myTZ.dateTime();
}
//**********************************************************************************************
char *CWDateTime::getYear(const char *format)    // name
{
  static char buffer[3] = {'\0'};
  strncpy(buffer, myTZ.dateTime("y").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getYear()
{
  return myTZ.dateTime("y").toInt();
}
//**********************************************************************************************
char *CWDateTime::getMonth(const char *format)    // name
{
  static char buffer[3] = {'\0'};
  strncpy(buffer, myTZ.dateTime("m").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getMonth()
{
  return myTZ.dateTime("m").toInt();
}
//**********************************************************************************************
char *CWDateTime::getDay(const char *format)
{
  static char buffer[3] = {'\0'};
  strncpy(buffer, myTZ.dateTime("d").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getDay()
{
  return myTZ.dateTime("d").toInt();
}
//**********************************************************************************************
char *CWDateTime::getWeekday(const char *format)    // name
{
  static char buffer[3] = {'\0'};
  int daynumber = myTZ.dateTime("w").toInt();
  
  //strncpy(buffer, myTZ.dateTime("w").c_str(), sizeof(buffer));
  
  strncpy(buffer, dayName[daynumber], sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getWeekday()
{
  return myTZ.dateTime("w").toInt() - 1;
}
//**********************************************************************************************
char *CWDateTime::getHour(const char *format)
{
  static char buffer[3] = {'\0'};
  //snprintf(buffer, sizeof(buffer), format, myTZ.dateTime("h"));
  strncpy(buffer, myTZ.dateTime("g").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getHour()
{
  return myTZ.dateTime("g").toInt();
}
//**********************************************************************************************
char *CWDateTime::getMinute(const char *format)
{
  static char buffer[3] = {'\0'};
  strncpy(buffer, myTZ.dateTime("i").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getMinute()
{
  return myTZ.dateTime("i").toInt();
}
//**********************************************************************************************
char *CWDateTime::getSecond(const char *format)
{
  static char buffer[3] = {'\0'};
  strncpy(buffer, myTZ.dateTime("s").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getSecond()
{
  return myTZ.dateTime("s").toInt();
}
//**********************************************************************************************
char *CWDateTime::getMilliseconds(const char *format)
{
  static char buffer[3] = {'\0'};
  strncpy(buffer, myTZ.dateTime("v").c_str(), sizeof(buffer));
  return buffer;
}
//**********************************************************************************************
int CWDateTime::getMilliseconds()
{
  return myTZ.dateTime("v").toInt();
}
//**********************************************************************************************
