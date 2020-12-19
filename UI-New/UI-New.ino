/*    This is the latest energia sketch on UI Module
*      Folder: last Night Submission
*/
#include <Enrf24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#define UI_MODULE 0x03
#define MASTER_MODULE 0x02
#define F(x) x

Enrf24 radio(P2_3, P2_4, P2_5);  // P2.0=CE, P2.1=CSN, P2.2=IRQ For UI Module
LiquidCrystal lcd(P2_2, P2_1, P2_0, P1_4, P1_3, P1_0);

const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, MASTER_MODULE };
const uint8_t rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, UI_MODULE };

byte person[7] = {
  B01110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010
};

byte tower[8] = {
  B11111,
  B01010,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
byte low_signal[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B11000
};

byte mid_signal1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01100,
  B11100
};

byte mid_signal2[8] = {
  B00000,
  B00000,
  B00000,
  B00010,
  B00110,
  B01110,
  B11110
};
byte high_signal[8] = {
  B00000,
  B00001,
  B00001,
  B00011,
  B00111,
  B01111,
  B11111
};
#define SELECT_PIN P2_7
#define NEXT_PIN P2_6

#define SETCUR lcd.setCursor(0,1);
#define CLR lcd.clear();
#define SELECT digitalRead(SELECT_PIN)
#define NEXT digitalRead(NEXT_PIN)
#define NOMINAL_DELAY delay(5);

//#define TEMPERATURE_PIN P1_2

#define TOTAL_ITEMS_IN_SUB_MENU 9         // Not using this Now ...
#define TOTAL_ITEMS_IN_MAIN_MENU 3
#define TOTAL_ITEMS_IN_PERFORMANCE_MENU 4

#define MASTER_AUTO_UPDATE_TIME 120000
#define MENU_TIMEOUT 15000
#define LAST_DATA_RECIEVED_TIME 30000
#define CONNECTION_STATUS_TIME 5000
#define LCD_UPDATE_TIME 5000
#define BUTTON_PRESS_TIME 300

//#define CONNECTION_STATUS_LED P1_1
//#define BUSY_LED 1

unsigned long button_pressed_timer, master_auto_update_time = MASTER_AUTO_UPDATE_TIME, last_data_recieved_timer;
unsigned long connection_status_timer,  menu_display_timer, update_timer, checkTime;

byte person_count ,prev_person_count ,current_temp = 0, temperature, prev_temp;
byte performance_index, prev_performance_index, connection_status , prev_connection_status;
byte command_to_send, ac_status=0;

char send_data[4],recieved_data[4];

bool send_confirmation = false ,get_confirmation = false;

char* m_menu[TOTAL_ITEMS_IN_MAIN_MENU][2]={{" CANCEL/GO_BACK"," TO MAIN MENU"},{"   SET PERSON"," COUNTER VALUE"},{"SET PERFORMANCE","     INDEX"}};
//const PROGMEM String s_menu[] = {"0. POWER_OFF   ","1. POWER_ON     ","2. FAN_SLOW    ","3. FAN_MEDIUM  ","4. FAN_HIGH    " ,"5. AUTO_SWING  ","6. TEMPRATURE ","7. RESET ALL ","CANCEL/GO BACK"};
char* p_menu[TOTAL_ITEMS_IN_PERFORMANCE_MENU][2] = {{"      HIGH","PERFORMANCE MODE"},{"  NORMAL POWER","      MODE"},{"  ULTRA SAVING","  ECONOMY MODE"},{" CANCEL/GO_BACK","  TO MAIN MENU"}};

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial Connection set up");
  delay(10);
  //pinMode(CONNECTION_STATUS_LED,1);
  //digitalWrite(CONNECTION_STATUS_LED,1);
  delay(500);
  definePin();
  radioInIt();
  readTemperature();
  send_data[0] = 'U';
  sendDataToMaster('r',0);
  lcdInIt();
  resetAllTimers();
  //digitalWrite(CONNECTION_STATUS_LED,0);
}
