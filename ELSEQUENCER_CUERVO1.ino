/******************************************************
 *                                                    *
 *    CÓDIGO PARA CONTROLAR EL WIRES A TRAVÉS DE      *
 *     DE "EL SEQUENCER" DE SPARKFUN Y USANDO         *
 *     UN VUMETRO A PARTIR DEL "SOUND DETECTOR"       *
 *        TAMBIÉN DE SPARKFUN, CON UN GUANTE          *        
 *        INTERRUPTOR DE TELA CONDUCTIVA              *
 *                                                    *
 ******************************************************/



// Se declaran los pines para el guante interruptor
// Se declaran los pines que se usaran para el EL wire (o leds) (2 - 9 / A - H) en EL sequencer.
int PIN_BOTON = A2;
int LED1 = 2;
int LED2 = 3;

//Variable que se usará para determinar si se ha presionado el guante interruptor para iniciar el código del vumetro
//(Una sola vez)
int botonpresionado = 0;

//Se declaran valores que se usaran para el silencio.
int Valor;
int Valor1;
int Valor2;
int Valor3;
int Valor4;




void setup()
{
  //Se inicia la conexión serial
  Serial.begin(9600);
  //Se definen los tipos de pines para los leds y el interruptor
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(PIN_BOTON,INPUT);
  //Se conecta el interruptor a la resistencia "pull-up" interna para evitar el ruido en la lectura
  //Explicación más detallada de esto y del funcionamiento de los interruptores: http://www.instructables.com/id/Arduino-Button-Tutorial/?ALLSTEPS
  digitalWrite(PIN_BOTON,HIGH);
}


//Se define una función que lee el pin del guante interruptor y returna su estado (HIGH o LOW)
//Si el valor es LOW, el botón ha sido presionado.
boolean handle_button()
{
  int button_pressed = !digitalRead(PIN_BOTON); // pin low -> pressed
  return button_pressed;
}



void loop()
{

  //Para revisar si el interruptor funciona, descomentar la línea siguiente y comentar la lectura del "Valor"
  //Serial.print(button_pressed ? "^" : ".");

  //Se lee el valor del pin A5 en este caso la salida de audio del "Sound detector"
  Valor = analogRead(A5);
  
 //Transferimos los valores para saber cual era el estado anterior

 Valor4 = Valor3;

 Valor3 = Valor2;

 Valor2 = Valor1;

 Valor1 = Valor;



//Visualizamos los valores en el monitor serial (Útil para determinar los valores máximos y mínimos del sensor), una vez calibrado puede comentarse

 Serial.print("Valor: ");

 Serial.print(Valor);

 Serial.print("\t Valor1: ");

 Serial.print(Valor1);

 Serial.print("\t Valor2: ");

 Serial.print(Valor2);

 Serial.print("\t Valor3: "); 

 Serial.print(Valor3);

 Serial.print("\t Valor4: ");

 Serial.println(Valor4);

 
  // Llamamos la función que lee el estado del guante interruptor
  boolean button_pressed = handle_button();

  //Si el guante interruptor fue presionado, cambiar el estado de la variable estática que da inicio al código del vumetro.
  if (button_pressed)
  {
    botonpresionado = 1;
  }

  if (botonpresionado == 1){

//Condicionamos que si el programa lee 4 veces seguidas 0 que se apagen los leds, si no ponemos esto los leds parpadearan mucho

if (Valor1+Valor2+Valor3+Valor4==0){

  digitalWrite(LED1,LOW);

  digitalWrite(LED2,LOW);
}


//Encendemos los leds segun el valor de entrada.
//Si el valor de lectura del sensor es mayor a determinado valor, encender led, si no, apagarlo. Esto es lo que usamos para calibrar el vumetro
//Para usar una escala paralela para encender un número n de leds:

//Valor máximo sensor -  Valor mínimo sensor / número de leds = incremento entre el valor asignado a cada led.

else{

 if (Valor>600){

   digitalWrite(LED1, HIGH);

 }

 else{

   digitalWrite(LED1, LOW);

 }



 if (Valor>624){

   digitalWrite(LED2, HIGH);

 }

 else{

   digitalWrite(LED2, LOW);

 }
}

}
   
}

