/*
 * Author: Ivan Sanchez <sanivi08@gmail.com>
 * 
 * English:
 * 
 *    Title: Ardismótica.
 *    Description: house designed for people with disability (deaf, wheelchair and blind).
 * 
 * Spanish:
 * 
 *    Titulo: Ardismotica.
 *    Descripción: Casa diseñada para personas con discapacidad(sordo, silla de ruedas y ciegos).
 * 
 */






// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo puerta

Servo servoMotor;


//Servo cama

Servo servoCama;  // create servo object to control a servo

int potpin = A4;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin



//Luces

int luces_1=22;       //salon
int luces_2=24;      //Luz baño
int luces_3=26;        //Luz Habitacion1
int luces_4=28;        //Luz Habitacion2

//Barreras infrarrojas

int contador=0;
int contador2=0;

int periodo = 10000;
int periodo2 = 10000;  
int periodo3=10000;
int periodo4=10000;
int periodo5= 10000;
int periodo6= 250;
 byte temp=0;                  //estado del temporizador despertador
                                 // tiempo que esta el LED en alto y bajo
unsigned long tiempoAnterior = 0;      //guarda tiempo de referencia para comparar
unsigned long tiempoAnterior2 = 0;
unsigned long tiempoAnterior3 = 0;
unsigned long tiempoAnterior4 = 0;
unsigned long tiempoAnterior5 = 0;
unsigned long tiempoAnterior6 = 0;

const int barrera_infrarroja_1 = A0;      // lectura del Fototransistor de la primera barrera
const int barrera_infrarroja_2 = A1;      // lectura del Fototransistor de la segunda barrera

const int barrera_infrarroja_3 = A2;      // lectura del Fototransistor de la primera barrera
const int barrera_infrarroja_4 = A3;      // lectura del Fototransistor de la segunda barrera



int Medida_infrarrojo_1 = 0;                 // Inicializamos el valor del sensor de salon
int Medida_infrarrojo_2 = 0;                // Inicializamos el valor del sensor de baño

int Medida_infrarrojo_3 = 0;                 // Inicializamos el valor del sensor de H1
int Medida_infrarrojo_4 = 0;                // Inicializamos el valor del sensor de H2

// PULSADORES

int value=0;
int value4=0;
int value2=0;
int value3=0;
int estado=1;

bool flanco = LOW;
bool flancoAnterior = LOW;
bool flancoAnterior2 = LOW;
int botonCuenta;

//PULSaDORES

int Pul_emer =50;
int Pul_timbre =48;
int Pul_telef =46;
int Pul_desperta =52;

//indicadores luminosos

int Luz_Emer =36;
int Luz_Timbre =30;
int Luz_desperta =32;
int Luz_presencia =34;


//ACTUADORES


int zumba=12;
int zumba2=13;
int vibra=42;
int estadovibra;

 //SENSOR AGUA

const int sensorPin = A6;          


//PIR detector de presencia
 
int pirEntrada = 40;               
int estadoPir = 0;
int botonCuenta2;
 int alarmaPir=LOW;
int alarmaPirAnterior=LOW;


void setup()                 // CONFIGURACIONES DE PINES
{
  Serial.begin(9600);            // Inicializa el puerto serie

// SERVO PUERTA

  servoMotor.attach(9);

  
// SERVO CAMA

 servoCama.attach(8);

 

 //ILUMINACION CASA
  
  pinMode(luces_1, OUTPUT);
  pinMode(luces_2, OUTPUT);

  pinMode(luces_3, OUTPUT);
  pinMode(luces_4, OUTPUT);

  pinMode(sensorPin, INPUT);
  
  
// pulsadores

  pinMode(Pul_emer, INPUT);
  pinMode(Pul_timbre, INPUT);

  pinMode(Pul_telef, INPUT);
  pinMode(Pul_desperta, INPUT);
  
// indicadores luminosos

  pinMode(Luz_Emer, OUTPUT);
  pinMode(Luz_Timbre, OUTPUT);

  pinMode(Luz_desperta, OUTPUT);
  pinMode(Luz_presencia, OUTPUT);
  pinMode(zumba, OUTPUT);
  pinMode(vibra, OUTPUT);
 


//Alarma presencia PIR


 pinMode(pirEntrada, INPUT);
}






void loop()                   //CICLO


{
  //ALARMA DE FUGA DE AGUA.

   int humedad = analogRead(sensorPin);
   
   if(humedad < 500){



   digitalWrite(Luz_Emer, HIGH);
   digitalWrite(zumba,HIGH);
   
   



  
   }

             //LUCES AUTOMATICAS y PUERTA PRINCIPAL
                                                      

  Medida_infrarrojo_1 =analogRead(barrera_infrarroja_1);
  Medida_infrarrojo_2 =analogRead(barrera_infrarroja_2);
  Medida_infrarrojo_3 =analogRead(barrera_infrarroja_3);
  Medida_infrarrojo_4 =analogRead(barrera_infrarroja_4);




//-LUCES SALON Y APERTURA PUERTA
  
  if(Medida_infrarrojo_1<200){

    
   
   
    if(millis()-tiempoAnterior>=periodo){  //si ha transcurrido el periodo programado
      
     servoMotor.write(80);     // Desplazamos a la posición 90º        //PUERTA PRINCIPAL
    
    //encendemos luz salon
    digitalWrite(luces_1,LOW);
    tiempoAnterior=millis();  //guarda el tiempo actual como referencia
    }
   }
  else{
    
    
     // Desplazamos a la posición 0º
  servoMotor.write(0);
  
  
  
     //apagamos luces salon
    digitalWrite(luces_1,HIGH);
    
  }

  
  
//-BAño

  if(Medida_infrarrojo_2<200){
   if(millis()-tiempoAnterior2>=periodo2){  //si ha transcurrido el periodo programado
    
    digitalWrite(luces_2,LOW);
    tiempoAnterior2=millis();  //guarda el tiempo actual como referencia
    }
   }
  else{
    digitalWrite(luces_2,HIGH);
    
  }

//-Habitacion1


  if(Medida_infrarrojo_3<200){
    if(millis()-tiempoAnterior3>=periodo3){  //si ha transcurrido el periodo programado
    
    digitalWrite(luces_3,LOW);
    tiempoAnterior3=millis();  //guarda el tiempo actual como referencia
    }
   }
  else{
    digitalWrite(luces_3,HIGH);
  }


//-Habitacion2


 if(Medida_infrarrojo_4<200){
 if(millis()-tiempoAnterior4>=periodo4){  //si ha transcurrido el periodo programado
    
    digitalWrite(luces_4,LOW);
    tiempoAnterior4=millis();  //guarda el tiempo actual como referencia
    }
   }
  else{
    digitalWrite(luces_4,HIGH);
  }


  

 //SERVO CAMA


  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  servoCama.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there

    

  
                              //LUCES INDICADORAS.

 //emergencia

value = digitalRead(Pul_emer);

if (value == HIGH) {
    // ENTONCES ENCENDEMOS EL LED
    digitalWrite(Luz_Emer, HIGH);
    digitalWrite(zumba,HIGH);
   }

if (value == LOW) {

  
    
    
    digitalWrite(Luz_Emer, LOW);
    digitalWrite(zumba, LOW);
  }

  //ALARMA DE PRESENCIA

  //DESpertador
 
alarmaPir= digitalRead(Pul_telef);

 if (alarmaPir!= alarmaPirAnterior) {
    
    if (alarmaPir == HIGH) {
      botonCuenta2++;             //Cuenta flancos (ascendente y descendente)

      
      } 
  
    delay(50);
  }
  
 alarmaPirAnterior=alarmaPir;


  if (botonCuenta2 % 2 == 0) {

//Con flanco de subida y bajada se activa la alarmas de presencia y queda activada
    
    digitalWrite(Luz_presencia, LOW);           //desactiva alarma presencia
   
  } else {


  //SE ACTIVA LA ALARMA DE PRESENCIA

    
   estadoPir = digitalRead(pirEntrada);            
  
if(estadoPir == HIGH){

 
    digitalWrite(Luz_presencia,HIGH);
    
   
   
  }
  else
  {
    digitalWrite(Luz_presencia,LOW);
    }
  }









 //Timbre


  value3 = digitalRead(Pul_timbre);
  
if (value3 == HIGH) {
    // ENTONCES ENCENDEMOS EL LED
    digitalWrite(Luz_Timbre, HIGH);

    //Melodia
    
   tone(zumba2, 600); // tone (PIN DEL ZUMBADOR, FREQÜÉNCIA);
  delay (100);  // TIEMPO DE MANTENER EL TONO.
  tone(zumba2, 294); 
  delay (100);  
  tone(zumba2, 494); 
  delay (100);  
  }


  
  // SE OPRIMIO EL BOTON DE APAGADO?
  
  if (value3 == LOW) {
    // ENTONCES APAGAMOS EL LED
    digitalWrite(Luz_Timbre, LOW);
    noTone(zumba2);
    
  }


//DESpertador
 
flanco= digitalRead(Pul_desperta);
 if (flanco != flancoAnterior) {
    
    if (flanco == HIGH) {
      botonCuenta++;

      
      } 
  
    delay(50);
  }
  
 flancoAnterior=flanco;


  if (botonCuenta % 2 == 0) {
    digitalWrite(Luz_desperta, LOW);
    digitalWrite(vibra, LOW);
  } else {
    digitalWrite(Luz_desperta, HIGH);
    digitalWrite(vibra, HIGH);
    delay(250);
    digitalWrite(vibra,LOW);
    delay(250);
  }


}

   
 
