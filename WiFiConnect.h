//**********************************************************************
#ifndef WiFiConnect_h
#define WiFiConnect_h

#include <WiFiManager.h>
#include <ezTime.h>

WiFiManager wifiManager;
Timezone myTZ;

struct WiFiConnect 
{
    std::vector<const char *> _menu = {"wifi","exit"};
    char timezone[40] = "America/New_York";
    bool shouldSaveConfig = false;

    void saveTimezone(const char* value) 
      {
      Serial.print("Save: ");
      Serial.println(value);
      myTZ.setCache(0);
      myTZ.setLocation(value);
      shouldSaveConfig = false;
      }

    String loadTimezone() 
      {
      myTZ.setCache(0);
      String tz = myTZ.getTimezoneName();
      Serial.print("Load: ");
      Serial.println(tz);
      return tz;
      }
    
    void connect() 
      {
      bool resp; 
      //wifiManager.resetSettings(); 
      wifiManager.setSaveConfigCallback([&](){ shouldSaveConfig = true; });
      
      sprintf(timezone, "%s", loadTimezone().c_str());
      WiFiManagerParameter timezoneParam("tz", "Inform your timezone (e.g. America/New York)", timezone, 36);

      wifiManager.setTitle("PacMan Wifi Setup");
      wifiManager.setMenu(_menu);
      wifiManager.addParameter(&timezoneParam);
      //wifiManager.addParameter("America/New York");
      
      resp = wifiManager.autoConnect("PacMan-Wifi");
      
      if (!resp) 
        {
        Serial.println("Failed to connect");
        delay(3000);
        ESP.restart();
        } 
      else 
        {
        Serial.println("connected!");
        if (shouldSaveConfig) 
          {
          saveTimezone(timezoneParam.getValue());
          }
       }
      }

    boolean isConnected() 
      {
      return WiFi.status() == WL_CONNECTED;
      }
};

#endif
//**********************************************************************
