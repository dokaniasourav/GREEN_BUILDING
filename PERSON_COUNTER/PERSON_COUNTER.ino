/*    This is the latest energia sketch on PC Module
*      Folder: last Night Submission
*/
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

#define PERSON_COUNTER 0x01
#define MASTER_MODULE 0x02
//#define sprint(x) Serial.println(x)
Enrf24 radio(P2_7, P2_4, P2_5);  // CE, CSN, IRQ for Person Counter

const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, MASTER_MODULE };  // Sends to Master Module
const uint8_t rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, PERSON_COUNTER};   // Receives from Master Module

#define RECIEVER_IN P1_3
#define RECIEVER_OUT P2_6

#define CONNECTION_STATUS_LED P1_4
#define TOO_LONG 2000

#define TSOP_IN 1
#define TSOP_OUT 0

#define DATA_PIN P2_0
#define LATCH_PIN P2_1
#define CLOCK_PIN P2_2
#define CLEAR_PIN P2_3

#define TEMPRATURE_PIN P1_3

#define DATA_THRES 80
#define CONNECTION_STATUS_LED P1_4
#define PROGRAME_DELAY 2
#define MASTER_AUTO_UPDATE_TIME 120000
#define CONNECTION_STATUS_TIME 2000
#define TEMPERATURE_UPDATE_TIME 3

unsigned long timers[2];
byte tsop_pins[] = { RECIEVER_IN , RECIEVER_OUT };
String msg[] = {"INSIDE","OUTSIDE"};

unsigned long  update_timer, connection_status_timer, checkTime, temperature_update_timer; // TIMERS
unsigned long master_auto_update_time = MASTER_AUTO_UPDATE_TIME;
byte prev_person_count, person_count = 0;
byte prev_temp, current_temp;
byte connection_status = 0, numbers[10];
char send_data[4],recieved_data[4]; //previous_send_data[9];
                    //Length of Maximum data bytes is 8 as last bit is always zero
bool get_confirmation = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial connected");
  radioInIt();
  definePin();
  sevenSegmentStartUp();
  readTemprature();
  send_data[0] = 'P';
  sendDataToMaster('r');  // Request person count from Master Module on startup
  delay(200);
  timers[TSOP_IN] = timers[TSOP_OUT] = millis();
}
