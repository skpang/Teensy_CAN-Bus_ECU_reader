#ifndef ecu_reader_h
#define ecu_reader_h

#include <Arduino.h>
 /* Details from http://en.wikipedia.org/wiki/OBD-II_PIDs */
#define MODE1               0x01        //Show current data
#define MODE2               0x02        //Show freeze frame data
#define MODE3               0x03        //Show stored Diagnostic Trouble Codes
#define MODE4               0x04        //Clear Diagnostic Trouble Codes and stored values

#define PID_SUPPORTED       0x00
#define MONITOR_STATUS      0x01
#define ENGINE_COOLANT_TEMP 0x05
#define ENGINE_RPM          0x0C
#define VEHICLE_SPEED       0x0D
#define MAF_SENSOR          0x10
#define THROTTLE            0x11
#define O2_VOLTAGE          0x14

#define MODE1_RESPONSE      0x41
#define MODE3_RESPONSE      0x43
#define MODE4_RESPONSE      0x44
#define PID_REQUEST         0x7DF
#define PID_REPLY           0x7E8


typedef struct{
    
        int coolant_temp;
        int engine_rpm;  
        int throttle_position;
        int vehicle_speed;
        int maf_airflow;
        int o2_voltage;
        int dtc;

}ecu_t;

extern ecu_t old_ecu;

class ecu_reader_class
{
  public:

  ecu_reader_class();
  uint8_t init(uint32_t baud);
  uint8_t request(unsigned char pid,  int *engine_data);  
  private:
  
};
extern ecu_reader_class ecu_reader;


#endif

