////////////////////////////////////////////////////////////////////////////
// Titlu proiect: Smart Car (Radio control)                               //
// Autor: Aninu                                                           //
// Versiune: V 2.0                                                        //
// URL: https://aninu.xyz/post/smart-car-v1/                              //
// GitHub: https://github.com/aaninu/Arduino_Car                          //
////////////////////////////////////////////////////////////////////////////

/** Include librariile necesare. */
#include "Functions.h"

/** Initializarea setarilor generale si a pinilor. */
void setup(){
  // Init Serial / Debug Mode
  DebugMode_Setup();

  // Init LEDs PIN Setup
  LEDs_Setup();

  // Init Motors PIN Setup
  Motor_Setup();

  // Init Buzzer PIN Setup
  Buzzer_Setup();

  // Init Sensor PIN Top/Bottom
  Setup_SensorTop();
  Setup_SensorBottom();

  // Init Radio PIN Setup
  Radio_Setup();
}

/** Pregatirea functiilor care trebuie executate in acelasi timp. */
TimedAction Timed_DebugMode_Serial = TimedAction(1, DebugMode_Serial);
TimedAction Timed_Radio_Receiver = TimedAction(1, Radio_Receiver);
TimedAction Timed_Control_LED_Pozitii = TimedAction(1, Control_LED_Pozitii);
TimedAction Timed_Control_LED_FazaLunga = TimedAction(1, Control_LED_FazaLunga);
TimedAction Timed_Control_LED_Stop = TimedAction(1, Control_LED_Stop);
TimedAction Timed_Control_LED_Left = TimedAction(1, Control_LED_Left);
TimedAction Timed_Control_LED_Right = TimedAction(1, Control_LED_Right);
TimedAction Timed_Control_LED_Avarii = TimedAction(1, Control_LED_Avarii);
TimedAction Timed_System_LED_LeftRight = TimedAction(1, System_LED_LeftRight);
TimedAction Timed_Control_Motor_Top = TimedAction(1, Control_Motor_Top);
TimedAction Timed_Control_Motor_Bottom = TimedAction(1, Control_Motor_Bottom);
TimedAction Timed_Control_Buzzer = TimedAction(1, Control_Buzzer);
TimedAction timed_S_T = TimedAction(1, Sensor_Top);
TimedAction timed_S_B = TimedAction(1, Sensor_Bottom);

/** Se pornesc toate functiile in acelasi timp. */
void loop(){
  Timed_DebugMode_Serial.check();
  Timed_Radio_Receiver.check();
  Timed_Control_LED_Pozitii.check();
  Timed_Control_LED_FazaLunga.check();
  Timed_Control_LED_Stop.check();
  Timed_Control_LED_Left.check();
  Timed_Control_LED_Right.check();
  Timed_Control_LED_Avarii.check();
  Timed_System_LED_LeftRight.check();
  Timed_Control_Motor_Top.check();
  Timed_Control_Motor_Bottom.check();
  Timed_Control_Buzzer.check();
  timed_S_T.check();
  timed_S_B.check();
}

