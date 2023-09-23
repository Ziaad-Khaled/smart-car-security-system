#include <Arduino_FreeRTOS.h>

 #include <MFRC522.h>
 #include <SPI.h>
 #include <EEPROM.h>

#include <Arduino_FreeRTOS.h>
//#include <semphr.h>

#define RST_PIN         12           // Configurable, see typical pin layout above
#define SS_PIN          13          // Configurable, see typical pin layout above

#define echoPinRight 43 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinRight 42 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinLeft 40 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinLeft 41 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long durationRight; // variable for the duration of sound wave travel
int distanceRight; // variable for the distance measurement
long durationLeft; // variable for the duration of sound wave travel
int distanceLeft; // variable for the distance measurement


MFRC522 mfrc522(SS_PIN, RST_PIN);  // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;          //create a MIFARE_Key struct named 'key', which will hold the card information

//this is the block number we will write into and then read.
int block=2;  

byte blockcontent[16] = {"Last-Minute-Engg"};  //an array with 16 bytes to be written into one of the 64 card blocks is defined
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //all zeros. This can be used to delete a block.

//This array is used for reading out a block.
byte readbackblock[18];

const int beltSwitch = 2;
const int buzzer = 3;
const int engineButton = 4;
const int ldrSensor = 7;
const int led = 6;
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;



bool engineOldState = false;
bool engineIsStarted = false;

void vTaskOpenBuzzer(void* pvParameters);
void vNightVision(void* pvParameters);
void vStartEngine(void* pvParameters);
//no light -> high
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(beltSwitch, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(engineButton, INPUT_PULLUP);
  pinMode(ldrSensor, INPUT);
  pinMode(led, OUTPUT);
   pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an INPUT
 

  xTaskCreate(StartEngine,"StartEngine", 1000,NULL,1,NULL );
  xTaskCreate(TaskOpenBuzzer,"TaskOpenBuzzer", 1000,NULL,1,NULL );
  xTaskCreate(TaskNightVision,"TaskNightVision", 1000,NULL,1,NULL );
  xTaskCreate(TaskUltrasonicRight,"TaskUltrasonicRight", 1000,NULL,1,NULL );
  xTaskCreate(TaskUltrasonicLeft,"TaskUltrasonicLeft", 1000,NULL,1,NULL );



  

  SPI.begin();               // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
    Serial.println("Scan a MIFARE Classic card");
  
  // Prepare the security key for the read and write functions.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
}

void loop() {
//  bool engineButtonState = digitalRead(engineButton);
//  Serial.print("engine: ");
//  Serial.println(engineButtonState);
//    if (engineButtonState != engineOldState && engineButtonState == HIGH)
//    {
//      engineIsStarted = !engineIsStarted;
//    }
//  engineOldState = engineButtonState;
//  if (engineIsStarted)
//    {
//       bool beltSwitchState = digitalRead(beltSwitch);
//
//        
//      //semaphore
//      if (!beltSwitchState)
//      {
//        tone(buzzer, 1000); // Send 1KHz sound signal...
//        //delay(1000);        // ...for 1 sec
//        noTone(buzzer);     // Stop sound...
//        //delay(1000);        // ...for 1sec
//      }
//      else
//      {
//        noTone(buzzer);
//      }
//    }
//    else
//    {
//      noTone(buzzer);
//    }
//   int ldrSensorState = digitalRead(ldrSensor);
//  
//    if (engineIsStarted)
//    {
//      if (ldrSensorState)
//      {
//        digitalWrite(led, HIGH);
//      }
//      else
//      {
//        digitalWrite(led, LOW);
//      }
//    }
//    else{
//        digitalWrite(led, LOW);
//    }
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
//
//  //Ultrasonic Right
//   // Clears the trigPin condition
//  digitalWrite(trigPinRight, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//  digitalWrite(trigPinRight, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinRight, LOW);
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  durationRight = pulseIn(echoPinRight, HIGH);
//  // Calculating the distance
//  distanceRight = durationRight * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
//  // Displays the distance on the Serial Monitor
//  Serial.print("Distance Right: ");
//  Serial.print(distanceRight);
//  Serial.println(" cm");
//
//   //Ultrasonic Left
//   // Clears the trigPin condition
//  digitalWrite(trigPinLeft, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//  digitalWrite(trigPinLeft, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPinLeft, LOW);
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  durationLeft = pulseIn(echoPinLeft, HIGH);
//  // Calculating the distance
//  distanceLeft = durationLeft * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
//  // Displays the distance on the Serial Monitor
//  Serial.print("Distance Left: ");
//  Serial.print(distanceLeft);
//  Serial.println(" cm");
//
//   // RFID
//
//    // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) {
//    return;
//  }
//  
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) 
//  {
//    return;
//  }
//    Serial.println("card selected");
//         
//   //the blockcontent array is written into the card block
//   writeBlock(block, blockcontent);
//   
//   //read the block back
//   readBlock(block, readbackblock);
//   //uncomment below line if you want to see the entire 1k memory with the block written into it.
//   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
//   
//   //print the block contents
//   Serial.print("read block: ");
//   for (int j=0 ; j<16 ; j++)
//   {
//     Serial.write (readbackblock[j]);
//   }
//   Serial.println("");

  ////////////////////////////////////////////////
}



//Write specific block    
int writeBlock(int blockNumber, byte arrayAddress[]) 
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  
  //writing the block 
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  Serial.println("block was written");
}



//Read specific block
int readBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }

//reading a block
byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println(mfrc522.GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  Serial.println("block was read");
}
void moveForward(){
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, LOW);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH);
}
void moveBackward(){
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, HIGH);
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
}

void moveRight(){
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, HIGH);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, LOW);
}

void moveLeft(){
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, LOW);
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, HIGH);
}

void TaskUltrasonicRight(void* pvParameters)
{
  //Ultrasonic Right
  // Clears the trigPin condition
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationRight = pulseIn(echoPinRight, HIGH);
  // Calculating the distance
  distanceRight = durationRight * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Right: ");
  Serial.print(distanceRight);
  Serial.println(" cm");
}

void TaskUltrasonicLeft(void* pvParameters)
{
  //Ultrasonic Left
  // Clears the trigPin condition
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationLeft = pulseIn(echoPinLeft, HIGH);
  // Calculating the distance
  distanceLeft = durationLeft * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance Left: ");
  Serial.print(distanceLeft);
  Serial.println(" cm");
}

void TaskOpenBuzzer(void* pvParameters)
{
  while (1)
  {

    if (engineIsStarted)
    {
      bool beltSwitchState = digitalRead(beltSwitch);
      //semaphore
      if (!beltSwitchState)
      {
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1sec
      }
      else
      {
        noTone(buzzer);
      }
    }
  }
}
void TaskNightVision(void* pvParameters)
{
  while (1)
  {
    bool ldrSensorState = digitalRead(ldrSensor);
    if (engineIsStarted)
    {
      if (ldrSensorState)
      {
        digitalWrite(led, HIGH);
      }
      else
      {
        digitalWrite(led, LOW);
      }
    }
     else{
        digitalWrite(led, LOW);
    }

  }
}
void StartEngine(void* pvParameters)
{
  while (1)
  {
    bool engineButtonState = digitalRead(engineButton);
//    Serial.print("engine button state:");
     Serial.println(engineIsStarted);

    if (engineButtonState != engineOldState && engineButtonState == HIGH)
    {
      engineIsStarted = HIGH;
    }
    engineOldState = engineButtonState;

  }
  
 
}
