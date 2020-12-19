/*    This is the latest energia sketch on Master Module
*      Folder: last Night Submission
*/
#define DEBUG_ON

#ifdef DEBUG_ON
 #define PRINT(x, ...)  Serial.print(x, ##__VA_ARGS__)
 #define PRINTln(x, ...) Serial.println(x,##__VA_ARGS__)
#else
 #define PRINT(x, ...)
 #define PRINTln(x, ...)
#endif

#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>
#include <Wire.h> 

#define PERSON_COUNTER 0x01
#define MASTER_MODULE 0x02
#define UI_MODULE 0x03

#define CURRENT 0
#define OLD 1
#define SENT 2

Enrf24 radio(P2_3, P2_4, P2_5);  // CE, CSN, IRQ for Master Module

const uint8_t txaddr[2][5] = {{0xDE, 0xAD, 0xBE, 0xEF, PERSON_COUNTER},{0xDE, 0xAD, 0xBE, 0xEF, UI_MODULE}};  // Sender is Master Module
const uint8_t rxaddr[5] = { 0xDE, 0xAD, 0xBE, 0xEF, MASTER_MODULE };   // Receives from UI Module and Person Counter at the same place

#define CONNECTION_STATUS_TIME 2000
#define TX_PINS 8
#define DEVICE_ADD 0x50
#define CHECK_TIME 1500
#define NO_OF_PIR 3
#define NO_OF_AC 3
#define NO_OF_TX 3

bool get_confirmation_ui = false, get_confirmation_pc = false;               //No need for these, change them in all modules:) send_confirmation_ui = false, send_confirmation_pc = false;
char send_data[3], recieved_data[4];
byte PIR_PINS[NO_OF_PIR] = {P1_0, P1_3, P1_4};
bool ui_update=true,pc_update=true,last_pir[3],zeroPersonDataNotTransmitted = false;
bool connection_status_ui, connection_status_pc;

// Three fields in each :- CURRENT, OLD and SENT for Three purposes
byte temperature[3], personCount[3], acStatus[3], performanceIndex[3], pirStatus[2], onIndex[2], averageTemp, pcTemp, uiTemp;

byte t_high, t_med, mofifyPersonCounterFlag, flag;
unsigned long on_count[NO_OF_PIR], off_count[NO_OF_PIR], start, ON_SETTLING_TIME=2000, OFF_SETTLING_TIME=20000, working = 0;
unsigned long connection_status_timer_ui, connection_status_timer_pc;
const uint64_t ac_remote_codes[10]= {0b10000000100010000000000000000000000010100000001000000010,
                                     0b10101000000010001010000000000000000000000000001000000010,
                                     0b10101000000010001010000000000000000000000000001000000010,
                                     0b10100000000000001010000000000000000000000000001000000010,
                                     0b10000010000010001000100000000000000000000000001000000010,
                                     0b10101000001000001000100000000000000000000000001000000010,
                                     0b10001000000000001000100000000000000000000000001000000010,
                                     0b10100010000010001010100000000000000000000000001000000010,
                                     0b10000010001000001010100000000000000000000000001000000010,
                                     0b10101000000000001010100000000000000000000000001000000010};

void setup()
{
  #ifdef DEBUG_ON
  Serial.begin(9600);
  #endif
  delay(100);
  radioInit();
  ioSetup();
  PRINTln("MASTER STARTED");
  moduleUpdate(PERSON_COUNTER,'r',0);
  start = millis();
  byte j = 0;
  while(millis() - start < 2000)
  {
    PRINTln("Startup Request");
    while(++j)
    checkNrfData();
  }
  delay(100);
  acStatus[OLD] = 7;
  transmitAcData();
  analogReference(INTERNAL1V5); // Temperature Internal Reference
}
