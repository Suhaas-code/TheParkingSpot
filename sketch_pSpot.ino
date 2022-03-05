//My PSpot project
#include <LiquidCrystal_I2C.h>

#define RXD2 16
#define TXD2 17

String CardName[5] = { "Gautam", "Rishi ", "Roopa ", "Govind", "Indira" };
String CardNumber[5] = { "67004AD820D5","2700550E91ED","2700550F017C","2700552C4B15","2700552A8BD3" };

String SlotArray[4] = {"A2","B3","C4","D1"};
int SenseInp[4] = {15,4,18,19};

int count = 0;                                          // count = 0
char input[13];                                         // character array of size 12 
boolean flag = 0;                                       // flag =0

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, 16, 2);  

int GetFreeSlot()
{
  int lFreeSlot = -1;
  for(int i = 0; i < 4; i++)
  {
    if(digitalRead(SenseInp[i]) == 1)
    {
      lFreeSlot = i;
      break;
    }
  }

  return lFreeSlot;
}
void setup() {
  // put your setup code here, to run once:
  // initialize serial:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Sensor Config
  for(int i = 0; i < 5; i++)
  {
    pinMode(SenseInp[i], INPUT);
  }
  
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   PSpot  2.0   ");
  delay(5);
  lcd.setCursor(0, 1);
  lcd.print("  -By Gautam V   ");
  //scrollText(1, "- A Project by Gautam Vhavle", 250, 16);
}

void loop() {
  // put your main code here, to run repeatedly:
  // set cursor to first column, first row
  //lcd.setCursor(0, 0);
  //lcd.print("PSpot 2.0");
  lcd.setCursor(0, 1);
  
  if(Serial2.available())
     {
        count = 0;
        while(Serial2.available() && count < 12)          // Read 12 characters and store them in input array
        {
           input[count] = Serial2.read();
           count++;
           delay(5);
        }
        input[count] = 0;
        //Serial.print(input);                             // Print RFID tag number 
        String strInput = String(input);

        int CardFound = 0;
        for(int i = 0; i < 5; i++)
        {
          if(strInput == CardNumber[i])
          {
            lcd.setCursor(0, 0);
            Serial.println("Hello, "+CardName[i]);
            lcd.print("Hello, "+CardName[i]+"   ");

            int FreeSlot = GetFreeSlot();
            
            if(FreeSlot != -1)
            {
              String strSlot = SlotArray[FreeSlot]; //String(FreeSlot);
              lcd.setCursor(0, 1);
              Serial.println("Park at Slot: "+strSlot);
              lcd.print("Park at Slot: "+strSlot);
            }
            else
            {
              lcd.setCursor(0, 1);
              Serial.println("All Slots are Full");
              lcd.print(" All Slots Full ");
            }
            
            CardFound = 1;
            break;
          }
        }
        if(CardFound == 0)
        {
          lcd.setCursor(0, 0);
          Serial.println(" Invalid Card!  ");
          lcd.print("Invalid Card!");
          lcd.setCursor(0, 1);
          lcd.print("Cannot give Slot");
        }

        delay(5000);
        lcd.setCursor(0, 0);
        lcd.print("   PSpot  2.0   ");
        lcd.setCursor(0, 1);
        lcd.print("  -By Tec-Soc    ");
        //scrollText(1, "- A Project by Tec-Soc      ", 150, 16);
        
        /*if((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) && 
           (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11]))
              Serial.println("No Error");
        else
              Serial.println("Error"); */     
     }
}
