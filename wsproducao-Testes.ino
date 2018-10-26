#include <SPI.h>
#include <LiquidCrystal.h>
#include <MUX74HC4067.h>
#include <SoftwareSerial.h>


LiquidCrystal lcd(9);
MUX74HC4067 mux(3, 4, 5, 6, 7);

//Serial da Balança
SoftwareSerial mySerial(8, 10); // RX, TX

SoftwareSerial SerialDebug(16, 17); // RX, TX

const int led_verde =  A0;      //Led
const int  led_vermelho =  A1; //Buzina

int conta1, botao;
int apertou = 0;
int envia = 0;
int SC = 0;
int volume = 0;
int x = 0; //Usada na leitura de botões
String inputString = "";
String aux;
String ope;
String peso;
char ultimoestab, estab;
boolean stringComplete1 = false;

signed long displayMillis = 0;
signed long displayinterval = 100;

//String Entrada;

String strlida = "";





void setup() {
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);

  Serial.begin(9600);
  SerialDebug.begin(9600);
  //mySerial.begin(9600);

  mux.signalPin(2, INPUT, DIGITAL);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Working Software");
  lcd.setCursor(0,1);
  lcd.print("Producao 1.0");
  delay(3000);

  lcd.clear();
  lcd.print("Config. balanca");
  lcd.setCursor(0,1);
  lcd.print("Aguarde...");
  


while(!Serial.available()){  

                          //Aguarda Comunicação com a Serial
                          lcd.setCursor(7,1);
                            lcd.print("       ");
                            delay(200);
                            lcd.setCursor(8,1);
                            lcd.print(".");
                            delay(200);
                            lcd.setCursor(9,1);
                            lcd.print(".");
                            delay(200);
                            lcd.setCursor(10,1);
                            lcd.print(".");
                            delay(300);

                      }

    if(Serial.available()){

                    //Entrada = leSerial();
					leSerial();

                      SerialDebug.println(strlida);
                    
                    ope = strlida.substring(11,12);

                    if (ope == "e"){

                                       RetornaOK("SETUP");

                                       while(!Serial.available()){
                                                                  //Espera
                                                                }
                                                      if(Serial.available()){

                                                        strlida = "";
                                                        leSerial();

                                                        int h = strlida.indexOf("=");
                                                        strlida = strlida.substring(h+1);
                                                        h = strlida.indexOf(" ");
                                                        strlida = strlida.substring(0,h);

                                                        mySerial.begin(strlida.toInt());
                                                        RetornaOK("OK");
                                                        
                                                      }
                                        
                      
                                   
                       
                                    }
                      
                    }
    

 
  lcd.clear();
  lcd.print("Balanca");
  lcd.setCursor(0,1);
  lcd.print("Configurada");
  delay(1000);
  lcd.clear();
  lcd.print("Volume:");
  lcd.setCursor(10,0);
  lcd.print(volume);
   

}

void loop() {
  lebalanca();
  botao = leiturabotoes ();
  delay(1);

    if(Serial.available()){

     leSerial();
	   
	   SerialDebug.println("1");
       SerialDebug.println(strlida);


      ope = strlida.substring(11,12);

      if ( (ope == "e") & (envia == 1)){

                
              
               RetornaOK(aux);

                      lcd.setCursor(0,0);
                      lcd.print("                ");
                      lcd.setCursor(0,0);
                      lcd.print("Validando..");
                      //delay(500);

                while(!Serial.available()){

                      
                  }

                   if(Serial.available()){

                    strlida = "";
					SerialDebug.println("2");
					SerialDebug.println(strlida);
                    leSerial();
					SerialDebug.println("3");
					SerialDebug.println(strlida);

                    

                    int h = strlida.indexOf("=");
                     strlida = strlida.substring(h+1);
                     h = strlida.indexOf(" ");
                     strlida = strlida.substring(0,h);
					 SerialDebug.println("4");
					SerialDebug.println(strlida);

                          if (strlida == "Erro"){

                                   lcd.setCursor(0,0);
                                   lcd.print("                ");
                                   lcd.setCursor(0,0);
                                   lcd.print("FORA DA FAIXA");
                                   digitalWrite(led_vermelho, HIGH);
                                   delay(500);
                                   digitalWrite(led_vermelho, LOW);
                                   RetornaOK("OK");
                                   lcd.setCursor(0,0);
                                   lcd.print("                ");
                                   lcd.setCursor(0,0);
                                   lcd.print("Volume:");
                                   lcd.setCursor(10,0);
                                   lcd.print(volume); 
                                   strlida = "";                   
                                   envia = 0;
                          
                          }
                          else if (strlida == "Estoque"){

                                   lcd.setCursor(0,0);
                                   lcd.print("                ");
                                   lcd.setCursor(0,0);
                                   lcd.print("SEM ESTOQUE");
                                   digitalWrite(led_vermelho, HIGH);
                                   delay(500);
                                   digitalWrite(led_vermelho, LOW);
                                   RetornaOK("OK");
                                   lcd.setCursor(0,0);
                                   lcd.print("                ");
                                   lcd.setCursor(0,0);
                                   lcd.print("Volume:");
                                   lcd.setCursor(10,0);
                                   lcd.print(volume); 
                                   strlida = "";                   
                                   envia = 0;
                          
                          }
                          else{          
                                   volume = volume +1;           
                                   lcd.setCursor(0,0);
                                   lcd.print("                ");
                                   lcd.setCursor(0,0);
                                   lcd.print(strlida);
                                   digitalWrite(led_verde, HIGH);
                                   delay(500);
                                   digitalWrite(led_verde, LOW);
                                   delay(1000);
                                   RetornaOK("OK");
                                   lcd.setCursor(0,0);
                                   lcd.print("                ");
                                   lcd.setCursor(0,0);
                                   lcd.print("VolumeD:");
                                   lcd.setCursor(10,0);
                                   lcd.print(volume);
                                   envia = 0;
                                   
                                   
                          }
                       }
             
                                 
         }
         else{
                if (SC == 1){
                  RetornaOK("*SC*");
                }
                else{
                
                RetornaOK("ZERO");
                }
             }


      

      
    }


    
if ((botao != 0) && (apertou == 0) ){

    aux = "";                                               
    aux = botao;
    aux += ";";
    aux += peso;
    apertou = 1;
    envia = 1;
  
}
    
  
  

}// fim Loop


//Funções

void lebalanca () {
  int comunica1 = 0;

  while (mySerial.available()) {
    comunica1 = 1;
    conta1 = 0;
    char inChar = (char)mySerial.read();
    //byte g = inChar;

    if ((inChar != 2) && (inChar != 1) && (inChar != 32)) {
      if ((inChar != 69) && (inChar != 73)) {
        inputString += inChar;
        // peso1[o] = inChar;
        //    Serial.print(inChar);
        //Serial.println(inputString);
      }
      else {
        if ((inChar == 69) || (inChar == 73)) {
          ultimoestab = estab;
          estab = inChar;
        }
      }
    }
    if (inChar == 1) {
      stringComplete1 = true;
      break;
    }
    delay(5);
  }

  if (stringComplete1) {
    comunica1 = 1;
    
    peso = inputString;
    //delay(50);

    //Serial.println(inputString);
    //Serial.println(peso);
    
    if (millis() - displayMillis > displayinterval) {
      displayMillis = millis();
      lcd.setCursor(7,0);
      lcd.print("        ");
      lcd.setCursor(0,0);
      lcd.print("Volume:");
      lcd.setCursor(10,0);
      lcd.print(volume);
      lcd.setCursor(0, 1);
      lcd.print("Peso:                      ");
      int i;
      int w = peso.toFloat();
      //int w = inputString.toFloat();
      if ((w >= 0) && (w < 10)) {
        i = 7;
      }
      if ((w >= 10) && (w < 100)) {
        i = 6;
      }
      if ((w >= 100) && (w < 1000)) {
        i = 5;
      }
      lcd.setCursor(i, 1);
      lcd.print(peso.toFloat());
      //lcd.print(inputString.toFloat());
      lcd.setCursor(12, 1);
      lcd.print("kg");
      lcd.setCursor(15, 1);
      lcd.print(estab);
     }

    /* 
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Volume:");
    lcd.setCursor(10,0);
    lcd.print(volume);
    */
    
    inputString = "";
    stringComplete1 = false;
    delay(1);
    apertou = 0;
    SC = 0;
    
  } 

  conta1++;
  if ((comunica1 == 0) && (conta1 > 10000)) {

     SC = 1; 
     apertou = 1;
     conta1++;     
     
    lcd.setCursor(0, 0);
    lcd.print("SEM COMUNICACAO      ");
    lcd.setCursor(0, 1);
    lcd.print("COM A BALANCA        ");    

    inputString = "";
    conta1 = 0;
  }
}//Fim LeBalanca

int leiturabotoes () {
  x = 0;
  //int btreset = -1;
  byte data;
  
  for (byte i = 0; i < 10; ++i) {
    data = mux.read(i);
    
    if ( data == LOW ) {
      x = i;
      return x + 1;
      break;
    }
    else {
      x = 0;
    }
  }
  
  return x;
}//Fim leiturabotoes

void RetornaOK(String strValImp) {
  //Responde com OK    
  String strDadImp = "";

  //Serial.println("ENTROU NO OK");
  Serial.println("HTTP/1.1 200 OK");
  Serial.println("Content-Type: text/html");
  Serial.println("Connection: close");

  strDadImp = "<!DOCTYPE HTML>";
  strDadImp += "<html>";
  strDadImp += strValImp;
  strDadImp += "</html>";

  Serial.print("Content-Length: ");
  Serial.print(strDadImp.length());
  Serial.print("\r\n\r\n");
  Serial.println(strDadImp);
  //apertou = 0;
  botao =0;
}


void leSerial(){

    strlida = "";
  
  
  while(Serial.available()){
            char bp = (char)(Serial.read());
									
						strlida += bp;
						
                 if (bp == '\n'){
					 
					 while(Serial.available()){
					 Serial.read();
					 delay(3);
					 }
				 } 
        
            
       delay(3);  //Somente pra estabillizar a leitura da serial
  }

  //return strlida;
}// Fim leSerial









