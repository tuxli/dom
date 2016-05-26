#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#include <Servo.h>
DHT dht(DHTPIN, DHTTYPE);

//sensores
#define RELAY1  7   // bomba de agua
int moistureSensor = 2;
int moisture_val;
int seguridad = 3;

//luces
int led1 = 22;
int led2 = 23;
int led3 = 24;
int led4 = 25;
int led5 = 26;
int led6 = 27;
int led7 = 28;
int led8 = 29;

//servo

Servo servo;
int ledred = 30;
int ledgreen = 31;

//motor cortinas
int motor = A14;
int motor2 = A15;



void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  
  //servoporton
  
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  servo.attach(9); 

//motor cortinas

pinMode(motor, OUTPUT);
 pinMode(motor2, OUTPUT);
  
  pinMode(RELAY1, OUTPUT);   
  pinMode(seguridad, INPUT);        // switchPin is an input
 digitalWrite(seguridad, HIGH);    // Activate internal pullup resistor
 dht.begin();
 
 Serial.begin(9600); //inicializado el puerto en 9600 baudio

 //COMANDOS PARA OBTENER DATOS
 // h -- humedad relativa
 // t -- Temperatura ambiental
 // g -- Gas 
 // p -- humedad terrestre
 // s -- Estado seguridad (Ventana)
 
}

void loop() {
int datos = Serial.read();
int h = dht.readHumidity();// Lee la humedad
int t= dht.readTemperature();//Lee la temperatura
int gas = analogRead(0);  // Lee Gas
int temp_suelo = analogRead(5); // Lee humedad Ambiental
//delay (1000);


// ******************* programacion luces *******

 if (Serial.available() > 0) { 
    
String datos = Serial.readString(); //guardamos lo que se lee en una variable
Serial.print (datos);
   //led1
    if (datos== "1") { 
      digitalWrite(led1, HIGH);
      //delay(1);
      Serial.print("\n");
    }
    else if (datos== "2") { 
      digitalWrite(led1, LOW);
      //delay(100);
      Serial.print("\n");
    }
    //led2
     if (datos== "3") { 
      digitalWrite(led2, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "4") { 
      digitalWrite(led2, LOW);
      //delay(100);
      Serial.print("\n");
    } 
    //led3
    if (datos== "5") { //si es H enciende led
      digitalWrite(led3, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "6") { //si es L apago led
      digitalWrite(led3, LOW);
      //delay(100);
      Serial.print("\n");
    } 
    //led4
    if (datos== "7") { //si es H enciende led
      digitalWrite(led4, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "8") { //si es L apago led
      digitalWrite(led4, LOW);
      //delay(100);
      Serial.print("\n");
    } 
    //led5
    if (datos== "9") { //si es H enciende led
      digitalWrite(led5, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "10") { //si es L apago led
      digitalWrite(led5, LOW);
      //delay(100);
      Serial.print("\n");
    } 
    //led6
    if (datos== "11") { //si es H enciende led
      digitalWrite(led6, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "12") { //si es L apago led
      digitalWrite(led6, LOW);
      //delay(100);
      Serial.print("\n");
    } 
    
    //led7
    if (datos== "13") { //si es H enciende led
      digitalWrite(led7, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "14") { //si es L apago led
      digitalWrite(led7, LOW);
      //delay(100);
      Serial.print("\n");
    }
    
    //led8
    if (datos== "15") { //si es H enciende led
      digitalWrite(led8, HIGH);
      //delay(100);
      Serial.print("\n");
    }
    else if (datos== "16") { //si es L apago led
      digitalWrite(led8, LOW);
      //delay(100);
      Serial.print("\n");
    } 

//************** motores cortina ********* //


int onTime = 2500;
int offTime = 1000;

if (datos== "30"){
digitalWrite(motor, HIGH);
delay (onTime);
digitalWrite(motor, LOW);
delay (offTime);

}

if (datos== "31"){
  digitalWrite(motor2, HIGH);
  delay (onTime);
  digitalWrite(motor2, LOW);
  delay(offTime);
}



    
//************** servo motor porton ********* //  
   
   if (datos== "21" ){
      servo.write(5);
      digitalWrite(ledgreen,HIGH);
      digitalWrite(ledred,LOW);
    }
    
  if (datos== "20"){
    servo.write(175);
    digitalWrite(ledgreen,LOW);
    digitalWrite(ledred,HIGH);
  }

//**************** Humedad ********* //
if(datos== "h"){
Serial.print("Humedad Relativa: ");                 
Serial.print(h);//Escribe la humedad
Serial.println(" %");
}                     

//************* Temperatura ********** //              

if(datos== "t")
{
Serial.print("Temperatura: ");                  
Serial.print(t);//Escribe la temperatura
Serial.println(" C"); 
}                 

//********************Gas ************************* // 
if(datos== "g")
{
Serial.print("Sensor de Gas: ");                   
Serial.println(gas);
}

//***************** Temperatura Terrestre *************** //

if(datos== "p")
{
Serial.print("Humedad Terrestre: ");                   
Serial.println(temp_suelo);

if(analogRead(5) < 500)
{
digitalWrite(RELAY1,0); // Turns ON Relays 1
Serial.println("Motor Agua Encender");
delay(1000); // Wait 2 seconds
}else{
if(analogRead(5) > 500)
{
digitalWrite(RELAY1,1);
Serial.println("Motor Agua Apagar");
}
}
}

//********* sensores seguridad puerta*************** //
if(datos== "s")
{
if(digitalRead(seguridad) == 1){
Serial.println("Ventana Abierta");
}
if(digitalRead(seguridad) == 0){
Serial.println("Ventana Cerrada");
}
}
//delay(1000);

Serial.println("********no leo nada**********");

 }
}
