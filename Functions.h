////////////////////////////////////////////////////////////////////////////
// Titlu proiect: Smart Car (Radio control)                               //
// Autor: Aninu                                                           //
// Versiune: V 2.0                                                        //
// URL: https://aninu.xyz/post/smart-car-v1/                              //
// GitHub: https://github.com/aaninu/Arduino_Car                          //
////////////////////////////////////////////////////////////////////////////

/** Include librariile necesare. */
#include "Settings.h"
#include "Radio.h"

//////////////////////////////////////////////////////////////////////
void DebugMode_Setup();
void DebugMode_Msg(String text);
void DebugMode_Msg(String text, int valoare);
void DebugMode_Msg(String text, bool valoare);
void DebugMode_Msg(String text, char* valoare);
void DebugMode_Msg(String text, String valoare);
void DebugMode_Serial();
void Radio_Decode_Variable(String Variabila, bool Value);
void Radio_DecodeInt_Value(String sVariabila, int iValoare);
void LEDs_Setup();
void Control_LED_Pozitii();
void Control_LED_FazaLunga();
void Control_LED_Stop();
void System_LED_LeftRight();
void Control_LED_Left();
void Control_LED_Right();
void Control_LED_Avarii();
void Motor_Setup();
void Control_Motor_Top();
void Control_Motor_Bottom();
void Control_Motor_Left(bool status);
void Control_Motor_Right(bool status);
void Control_Motor_Full_OFF();
void Buzzer_Setup();
void Control_Buzzer();
//////////////////////////////////////////////////////////////////////

/** Se foloseste pentru afisarea mesajelor de debug */
void DebugMode_Setup(){
  if (DebugMode){
    Serial.begin(9600);
    DebugMode_Msg("DebugMode_Setup() ...");
  }
}

void DebugMode_Msg(String text){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.println(text);
  }
}
void DebugMode_Msg(String text, int valoare){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.print(text);
    Serial.print(" {");
    Serial.print(valoare);
    Serial.println("}");
  }
}
void DebugMode_Msg(String text, bool valoare){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.print(text);
    Serial.print(" {");
    Serial.print(valoare);
    Serial.println("}");
  }
}
void DebugMode_Msg(String text, char* valoare){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.print(text);
    Serial.print(" {");
    Serial.print(valoare);
    Serial.println("}");
  }
}
void DebugMode_Msg(String text, String valoare){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.print(text);
    Serial.print(" {");
    Serial.print(valoare);
    Serial.println("}");
  }
}

/** Init Serial Comunication */
void DebugMode_Serial(){
  if (Serial.available() > 0){
    DebugSerialValue = Serial.read();
    DebugMode_Msg("Serial.read():", DebugSerialValue);
  }
}

/** Radio Var/Val Received */
void Radio_Decode_Variable(String Variabila, bool Value){
  if (Variabila.equals(COD_LED_Pozitii)){
    LED_Pozitii = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_LED_Pozitii]", Value);
  }else if (Variabila.equals(COD_LED_FazaLunga)){
    LED_FazaLunga = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_LED_FazaLunga]", Value);
  }else if (Variabila.equals(COD_LED_Left)){
    LED_Left = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_LED_Left]", Value);
  }else if (Variabila.equals(COD_LED_Right)){
    LED_Right = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_LED_Right]", Value);
  }else if (Variabila.equals(COD_LED_Avarii)){
    LED_Avarii = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_LED_Avarii]", Value);
  }else if (Variabila.equals(COD_Motor_Top)){
    Motor_Top = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_Motor_Top]", Value);
  }else if (Variabila.equals(COD_Motor_Bottom)){
    Motor_Bottom = Value;
    DebugMode_Msg("Radio_Decode_Variable(...): [COD_Motor_Bottom]", Value);
  }else{
    DebugMode_Msg("Radio_Decode_Variable(...):", Variabila);
    
  }
}

/** Decode int value */
void Radio_DecodeInt_Value(String sVariabila, int iValoare){
  if (sVariabila == COD_Motor_Servo){
    if (iValoare < 400){
      Motor_Right = false;
      Motor_Left = true;
      Control_Motor_Left(true);
    }else if (iValoare > 600){
      Motor_Left = false;
      Motor_Right = true;
      Control_Motor_Right(true);
    }else{
      Motor_Left = false;
      Motor_Right = false;
      Control_Motor_Left(false);
      Control_Motor_Right(false);
    }
  }else{
    DebugMode_Msg("Radio_DecodeInt_Value(...):" + sVariabila + ": ", iValoare);
  }
}


/** Setup PIN Leds */
void LEDs_Setup(){
  pinMode(PIN_LED_PozitieFata, OUTPUT);  
  pinMode(PIN_LED_FazaLunga, OUTPUT); 
  pinMode(PIN_LED_GoDown, OUTPUT); 
  pinMode(PIN_LED_PozitieSpate, OUTPUT); 
  pinMode(PIN_LED_Stop, OUTPUT); 
  pinMode(PIN_LED_Stanga, OUTPUT); 
  pinMode(PIN_LED_Dreapta, OUTPUT); 
  DebugMode_Msg("LEDs_Setup() ...");
}

/** Control LED pozitii */
void Control_LED_Pozitii(){
  if (LED_Pozitii != oLED_Pozitii){
    digitalWrite(PIN_LED_PozitieFata, LED_Pozitii);
    digitalWrite(PIN_LED_PozitieSpate, LED_Pozitii);  
    oLED_Pozitii = LED_Pozitii;
  }
}

/** Control LED pozitii */
void Control_LED_FazaLunga(){
  if (oLED_FazaLunga != LED_FazaLunga){
    digitalWrite(PIN_LED_FazaLunga, LED_FazaLunga);
    oLED_FazaLunga = LED_FazaLunga;
  }
}

/** Control LED Stop */
void Control_LED_Stop(){
  if (oLED_Stop != LED_Stop){
    digitalWrite(PIN_LED_Stop, LED_Stop);
    digitalWrite(PIN_LED_Stop, LED_Stop);
    oLED_Stop = LED_Stop;
  }
}

/** LED Left / Right Control Timed */
void System_LED_LeftRight(){
  if (LED_Avarii == true){
    if (LED_Semnal_Timer == 0){
      digitalWrite(PIN_LED_Stanga, true);
      digitalWrite(PIN_LED_Dreapta, true);  
    }else if (LED_Semnal_Timer == 500){
      digitalWrite(PIN_LED_Stanga, false);
      digitalWrite(PIN_LED_Dreapta, false);  
    }else if (LED_Semnal_Timer == 1000)
      LED_Semnal_Timer = -1;
    LED_Semnal_Timer += 1;
  }else if (LED_Left == true){
    if (LED_Semnal_Timer == 0){
      digitalWrite(PIN_LED_Stanga, true);
    }else if (LED_Semnal_Timer == 300){
      digitalWrite(PIN_LED_Stanga, false); 
    }else if (LED_Semnal_Timer == 600)
      LED_Semnal_Timer = -1;
    LED_Semnal_Timer += 1;
  }else if (LED_Right == true){
    if (LED_Semnal_Timer == 0){
      digitalWrite(PIN_LED_Dreapta, true);  
    }else if (LED_Semnal_Timer == 300){
      digitalWrite(PIN_LED_Dreapta, false);  
    }else if (LED_Semnal_Timer == 600)
      LED_Semnal_Timer = -1;
    LED_Semnal_Timer += 1;
  }else{
    LED_Semnal_Timer = 0;
  }
}

/** Control LED Left */
void Control_LED_Left(){
  if (oLED_Left != LED_Left){
    LED_Right = false;
    if (LED_Left == false) digitalWrite(PIN_LED_Stanga, false);
    oLED_Left = LED_Left;
  }
}

/** Control LED Right */
void Control_LED_Right(){
  if (oLED_Right != LED_Right){
    LED_Left = false;
    if (LED_Right == false) digitalWrite(PIN_LED_Dreapta, false);
    oLED_Right = LED_Right;
  }
}

/** Control LED Avarii */
void Control_LED_Avarii(){
  if (oLED_Avarii != LED_Avarii){
    LED_Left = false;
    LED_Right = false;
    if (LED_Avarii == false){
      digitalWrite(PIN_LED_Stanga, false);
      digitalWrite(PIN_LED_Dreapta, false);
    }
    oLED_Avarii = LED_Avarii;
  }
}

/** Se initializeaza pinii pentru motoare. */
void Motor_Setup(){
  pinMode(PIN_Motor_A_Top, OUTPUT);
  pinMode(PIN_Motor_A_Bottom, OUTPUT);
  pinMode(PIN_Motor_B_Top, OUTPUT);
  pinMode(PIN_Motor_B_Bottom, OUTPUT);
  pinMode(PIN_Motor_C_Top, OUTPUT);
  pinMode(PIN_Motor_C_Bottom, OUTPUT);
  pinMode(PIN_Motor_D_Top, OUTPUT);
  pinMode(PIN_Motor_D_Bottom, OUTPUT);
  DebugMode_Msg("Motor_Setup() ...");
}

/** Se foloseste pentru deplasarea masinii inainte. */
void Control_Motor_Top(){
  if (oMotor_Top != Motor_Top && !Motor_Left && !Motor_Right){
    digitalWrite(PIN_Motor_A_Top, Motor_Top);
    digitalWrite(PIN_Motor_B_Top, Motor_Top);
    digitalWrite(PIN_Motor_C_Top, Motor_Top);
    digitalWrite(PIN_Motor_D_Top, Motor_Top);
    LED_Stop = false;
    
    /* Se opresc motoarele pentru deplasarea masinii in spate. */
    digitalWrite(PIN_Motor_A_Bottom, false);
    digitalWrite(PIN_Motor_B_Bottom, false);
    digitalWrite(PIN_Motor_C_Bottom, false);
    digitalWrite(PIN_Motor_D_Bottom, false);
    digitalWrite(PIN_LED_GoDown, false);
    Buzzer_Status = false;
    digitalWrite(PIN_Buzzer, false);
    oMotor_Top = Motor_Top;
  }
}

/** Se foloseste pentru deplasarea masinii in spate. */
void Control_Motor_Bottom(){
  if (oMotor_Bottom != Motor_Bottom && !Motor_Left && !Motor_Right){
    digitalWrite(PIN_Motor_A_Bottom, Motor_Bottom);
    digitalWrite(PIN_Motor_B_Bottom, Motor_Bottom);
    digitalWrite(PIN_Motor_C_Bottom, Motor_Bottom);
    digitalWrite(PIN_Motor_D_Bottom, Motor_Bottom);
    digitalWrite(PIN_LED_GoDown, Motor_Bottom);
    Buzzer_Status = Motor_Bottom;
    LED_Stop = false;


    /* Se opresc motoarele pentru deplasarea masinii inainte. */
    digitalWrite(PIN_Motor_A_Top, false);
    digitalWrite(PIN_Motor_B_Top, false);
    digitalWrite(PIN_Motor_C_Top, false);
    digitalWrite(PIN_Motor_D_Top, false);
    oMotor_Bottom = Motor_Bottom;
  }
}

/** Se foloseste pentru rotirea masinii la stanga */
void Control_Motor_Left(bool status){
  if (status == true){
    digitalWrite(PIN_Motor_A_Bottom, true);
    digitalWrite(PIN_Motor_C_Bottom, true);
    digitalWrite(PIN_Motor_B_Top, true);
    digitalWrite(PIN_Motor_D_Top, true);
    DebugMode_Msg("Control_Motor_Right(true): sunt active motoarele pentru rotirea la stanga.");
  }else{
    Control_Motor_Full_OFF();
  }
}

/** Se foloseste pentru rotirea masinii la dreapta */
void Control_Motor_Right(bool status){
  if (status == true){
    digitalWrite(PIN_Motor_B_Bottom, true);
    digitalWrite(PIN_Motor_D_Bottom, true);
    digitalWrite(PIN_Motor_A_Top, true);
    digitalWrite(PIN_Motor_C_Top, true);
    DebugMode_Msg("Control_Motor_Right(true): sunt active motoarele pentru rotirea la dreapta.");
  }else{
    Control_Motor_Full_OFF();
  }
}

/** Se foloseste pentru a opri toate motoarele. */
void Control_Motor_Full_OFF(){
  digitalWrite(PIN_Motor_A_Top, false);
  digitalWrite(PIN_Motor_B_Top, false);
  digitalWrite(PIN_Motor_C_Top, false);
  digitalWrite(PIN_Motor_D_Top, false);
  digitalWrite(PIN_Motor_A_Bottom, false);
  digitalWrite(PIN_Motor_B_Bottom, false);
  digitalWrite(PIN_Motor_C_Bottom, false);
  digitalWrite(PIN_Motor_D_Bottom, false);
  DebugMode_Msg("Control_Motor_Full_OFF(): toate motoarele au fost setate ca fiind oprite.");
}

/** Se initializeaza PIN-ul pentru buzzer */
void Buzzer_Setup(){
  pinMode(PIN_Buzzer, OUTPUT);
  DebugMode_Msg("Buzzer_Setup() ...");
}

/** Se foloseste pentru a controla sunetul emis de buzzer */
void Control_Buzzer(){
  if (Buzzer_Status == true){
    if (Buzzer_Timer == 0){
      digitalWrite(PIN_Buzzer, true);
    }else if(Buzzer_Timer == 250){
      digitalWrite(PIN_Buzzer, false);
    }else if (Buzzer_Timer == 600){
      Buzzer_Timer = -1;  
    }
    Buzzer_Timer += 1;
  }else{
    Buzzer_Timer = 0;
    digitalWrite(PIN_Buzzer, false);
  }
}


// Init Sensor Top PIN
void Setup_SensorTop(){
  // Init Sensor
  pinMode(PIN_ST_echo, INPUT);
  pinMode(PIN_ST_trig, OUTPUT);
  DebugMode_Msg("Setup_SensorTop() ...");
}

// Init Sensor Bottom PIN
void Setup_SensorBottom(){
  // Init Sensor
  pinMode(PIN_SB_echo, INPUT);
  pinMode(PIN_SB_trig, OUTPUT);
  DebugMode_Msg("Setup_SensorBottom() ...");
}

/** Se foloseste pentru a opri masina automat daca sunt obstacole la mersul inainte. */
void Sensor_Top(){
  if (Motor_Top && Sensor_TOP_STATUS){
    long duration, distance;
    digitalWrite(PIN_ST_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_ST_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ST_trig, LOW);
    duration = pulseIn(PIN_ST_echo, HIGH);
    distance = (duration/2) / 29.1;
    // Check condition for stop car 
    if (distance <= 20){
      Serial.println("[DebugMODE]: Sensor_Top(): failsafe [<20].");
      Motor_Top = false;
      Motor_Bottom = false;
      Motor_Left = false;
      Motor_Right = false;
      LED_Stop = true;
      Buzzer_Status = false;
      Control_Motor_Full_OFF();
    }
    if (DebugMODE_ST){
      Serial.print("[DebugMODE.ST]: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
}

/** Se foloseste pentru a opri masina automat daca sunt obstacole la mersul in spate. */
void Sensor_Bottom(){
  if (Motor_Bottom && Sensor_BOTTOM_STATUS){
    long duration, distance;
    digitalWrite(PIN_SB_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_SB_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_SB_trig, LOW);
    duration = pulseIn(PIN_SB_echo, HIGH);
    distance = (duration/2) / 29.1;
    // Check condition for stop car 
    if (distance <= 20){
      Serial.println("[DebugMODE]: Sensor_Bottom(): failsafe [<20].");
      Motor_Top = false;
      Motor_Bottom = false;
      Motor_Left = false;
      Motor_Right = false;
      LED_Stop = true;
      Buzzer_Status = false;
      Control_Motor_Full_OFF();
    }
    if (DebugMODE_SB){
      Serial.print("[DebugMODE.SB]: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
}


