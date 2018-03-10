////////////////////////////////////////////////////////////////////////////
// Titlu proiect: Smart Car (Radio control)                               //
// Autor: Aninu                                                           //
// Versiune: V 2.0                                                        //
// URL: https://aninu.xyz/post/smart-car-v1/                              //
// GitHub: https://github.com/aaninu/Arduino_Car                          //
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
void DebugMode_Msg(String text);
void DebugMode_Msg(String text, int valoare);
void DebugMode_Msg(String text, bool valoare);
void DebugMode_Msg(String text, char* valoare);
void DebugMode_Msg(String text, String valoare);
void Radio_Setup();
void Radio_Receiver();
void Radio_Parsing(char Value[], int Len);
void Radio_Decode_Variable(String Variabila, bool Value);
void Radio_DecodeInt_Value(String sVariabila, int iValoare);
//////////////////////////////////////////////////////////////////////

/** Se foloseste pentru a initializa setarile Radio. */
void Radio_Setup(){
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(PIN_rx);
  vw_setup(Radio_Speed);
  vw_rx_start();
  DebugMode_Msg("Radio_Setup() ...");
}

/** Se foloseste pentru a afisa comenzile radio receptionate. */
void Radio_Receiver(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)){
    char Radio_Receive[buflen];
    for (int i = 0; i < buflen; i++){
      Radio_Receive[i] = char(buf[i]);
    }
    Radio_Parsing(Radio_Receive, buflen);
  }
}

/** Se foloseste pentru a parsa comenzile radio primite. */
void Radio_Parsing(char Value[], int Len){
  char vType[11];
  for (int i = 0; i < 11; i++){
    vType[i] = Value[i];
  }
  String Variabila = (String)vType;
  Variabila = Variabila.substring(0,11);
  int iStart = 0, iStop = 0;
  for (int i = 11; i < Len; i++){
    if (Value[i] == '{' && iStart == 0) iStart = i;
    if (Value[i] == '}' && iStart != 0) iStop = i;
    if (iStart != 0 && iStop != 0) break;
  }
  char vValue[6] = " ";
  int j = 0;
  for (int i = iStart + 1; i < iStop; i++){
    vValue[j] = Value[i];
    j++;
  }
  String Valoare = (String) vValue;
 
  //Serial.print(Variabila);
  //Serial.print(" = ");
  //Serial.print(Valoare);
  //Serial.print(", ");
  
  if (Valoare == "True"){
    //Serial.println("Este true");
    Radio_Decode_Variable(Variabila, true);

  }else if (Valoare == "False"){
    //Serial.println("Este false");
    Radio_Decode_Variable(Variabila, false);

  }else{
    int iValoare = atoi(Valoare.c_str());
    Radio_DecodeInt_Value(Variabila, iValoare);
    
    //Serial.print("Trebuie sa fie INT ");
    //Serial.print(iValoare);
    //Serial.println(" END HH");
  }
}

