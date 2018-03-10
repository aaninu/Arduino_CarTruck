////////////////////////////////////////////////////////////////////////////
// Titlu proiect: Smart Car (Radio control)                               //
// Autor: Aninu                                                           //
// Versiune: V 2.0                                                        //
// URL: https://aninu.xyz/post/smart-car-v1/                              //
// GitHub: https://github.com/aaninu/Arduino_Car                          //
////////////////////////////////////////////////////////////////////////////
//  Note: Pentru anumite variabile se foloseste o valoare curenta si una  //
// veche pentru a nu se face SPAM de comenzi catre modulele folosite de   //
// masina. Codul Radio specific este trimis de telecomanda.               //
////////////////////////////////////////////////////////////////////////////

/** Include librariile necesare. */
#include "VirtualWire.h"
#include "TimedAction.h"

/** Variabilele folosite pentru Developer */
boolean DebugMode = true;         // Activeaza / dezactiveaza mesajele de debug din SERIAL
bool DebugMODE_ST = false;        // Activeaza / dezactiveaza informatiile despre senzorul din fata al masinii
bool DebugMODE_SB = false;        // Activeaza / dezactiveaza informatiile despre senzorul din spate al masinii
int DebugSerialValue = 0;         // Valoarea trimisa prin SERIAL catre masina

/** Initializarea setarilor pentru radio. */
int Radio_Speed = 4000;     // Valoarea Speed pentru radio
int PIN_tx = 10;            // PIN-ul folosit pentru modulul de transmitere
int PIN_rx = 12;            // PIN-ul folosit pentru modulul de receptie
int Radio_Test_Value = 0;

/** Reprezinta PINII folositi pentru LED-uri. */
int PIN_LED_PozitieFata = 27;       // LED pentru pozitie fata
int PIN_LED_FazaLunga = 29;         // LED pentru faza lunga
int PIN_LED_GoDown = 35;            // LED pentru mersul cu spatele
int PIN_LED_PozitieSpate = 33;      // LED pentru pozitie spate
int PIN_LED_Stop = 37;              // LED pentru stop
int PIN_LED_Stanga = 25;            // LED pentru semnalizare stanga
int PIN_LED_Dreapta = 23;           // LED pentru semnalizare dreapta

/** Se foloseste pentru activarea / oprirea ledurilor */
/** LED pentru pozitii */
bool LED_Pozitii = false;             // Valoare curenta
bool oLED_Pozitii = false;            // Valoare veche
/** LED pentru faza lunga */
bool LED_FazaLunga = false;           // Valoare curenta
bool oLED_FazaLunga = false;          // Valoare veche
/** LED pentru STOP */
bool LED_Stop = false;                // Valoare curenta
bool oLED_Stop = false;               // Valoare veche
/** LED pentru semnalizare stanga */
bool LED_Left = false;                // Valoare curenta
bool oLED_Left = false;               // Valoare veche
/** LED pentru semnalizare dreapta */
bool LED_Right = false;               // Valoare curenta
bool oLED_Right = false;              // Valoare veche
/** Sistemul de avarii */
bool LED_Avarii = false;              // Valoare curenta
bool oLED_Avarii = false;             // Valoare veche

/** Se foloseste pentru timpul alocat semnalizarilor.  */
int LED_Semnal_Timer = 0;

/** Lista de comenzi radio pentru leduri, specifice pentru aceasta versiune de masina. */
String COD_LED_Pozitii = "Av1_LED_Pos";       // Comanda pentru pozitii
String COD_LED_FazaLunga = "Av1_LED_Faz";     // Comanda pentru faza lunga
String COD_LED_Left = "Av1_LED_Lef";          // Comanda pentru semnalizare stanga
String COD_LED_Right = "Av1_LED_Rig";         // Comanda pentru semnalizare dreapta
String COD_LED_Avarii = "Av1_LED_LAR";        // Comanda pentru avarii

/** Reprezinta PINII folositi de motoare. */ 
int PIN_Motor_A_Top = 53;         // Motor Stanga Fata >> Deplasare inainte
int PIN_Motor_A_Bottom = 51;      // Motor Stanga Fata >> Deplasare inapoi
int PIN_Motor_B_Top = 49;         // Motor Dreapta Fata >> Deplasare inainte
int PIN_Motor_B_Bottom = 47;      // Motor Dreapta Fata >> Deplasare inapoi
int PIN_Motor_C_Top = 52;         // Motor Stanga Spate >> Deplasare inainte
int PIN_Motor_C_Bottom = 50;      // Motor Stanga Spate >> Deplasare inapoi
int PIN_Motor_D_Top = 48;         // Motor Dreapta Spate >> Deplasare inainte
int PIN_Motor_D_Bottom = 46;      // Motor Dreapta Spate >> Deplasare inapoi

/** Lista de comenzi radio pentru motoare, specifice pentru aceasta versiune de masina. */
String COD_Motor_Top = "Av1_MOT_TOP";         // Deplasarea inainte
String COD_Motor_Bottom = "Av1_MOT_BOT";      // Deplasarea in spate
String COD_Motor_Left = "Av1_MOT_Lef";        // Rotirea la stanga
String COD_Motor_Right = "Av1_MOT_Rig";       // Rotirea la dreapta
String COD_Motor_Servo = "Av1_Ser_Top";       // Valoarea primita de la potentiometru.

/** Se folosesc pentru activarea / oprirea motoarelor in functie de directia dorita. */
/** Deplasarea inainte. */
bool Motor_Top = false;             // Valoare curenta 
bool oMotor_Top = false;            // Valoare veche
/** Deplasarea in spate.  */
bool Motor_Bottom = false;          // Valare curenta
bool oMotor_Bottom = false;         // Valoare veche
/** Rotirea masinii la stanga. */
bool Motor_Left = false;            // Valoare curenta
bool oMotor_Left = false;           // Valoare veche
/** Rotirea masinii la dreapta. */
bool Motor_Right = false;           // Valoare curenta
bool oMotor_Right = false;          // Valoare veche

/** Reprezinta PIN-ul unde este conectat buzzer-ul. */
int PIN_Buzzer = 11;

/** Se foloseste pentru activarea / oprirea buzzer-ului. */
bool Buzzer_Status = false;

/** Se foloseste pentru timpul buzzer-ului. */
int Buzzer_Timer = 0;

/** Reprezinta cei 2 PINI folositi pentru senzorul din fata al masinii. */
int PIN_ST_echo = 26;             // PIN - echo
int PIN_ST_trig = 27;             // PIN - trig
bool Sensor_TOP_STATUS = false;

/** Reprezinta cei 2 PINI folositi pentru senzorul din spate al masinii. */
int PIN_SB_echo = 28;             // PIN - echo
int PIN_SB_trig = 29;             // PIN - trig
bool Sensor_BOTTOM_STATUS = false;

