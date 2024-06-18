# Práctica 1

## 1. Explicación codigo:

```c++

     #include <Arduino.h>
     #define LED_BUILTIN 23
     #define DELAY 50

     void setup() {
     Serial.begin(115200);
     pinMode(LED_BUILTIN, OUTPUT);
     }

    void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("ON");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("OFF");
    delay(500);
    }

```

La instrucción "#define LED_BUILTIN 23" define el pin en el que se va a conectar el led, este led es controlado por el codigo.

En la función **setup()**, se inciacliza la configuración y la comunicación serial.

En la función **loop()**, se crea un bucle en el que el led va a encenderse y apagarse en intervalos de 500 milisegundos y va a mostrar un el mensaje "on" si está encendido y el "off" si está apagado por el puerto serie.

## 2. Quitando el delay y el serial

### Sin delay:
Quitando el delay podemos observar que el LED cambia de estado rápidamente, con con un intervalo de tiempo que es el que corresponde con las instrucciones que se llevan a cabo en el apartado loop(). El microcontrolador puede ejecutar tareas en paralelo, como otras partes del código, mientras el LED está parpadeando, ya que no estará bloqueado con un tiempo de espera.

### Sin serial ni sin delay:
Quitando el serial junto el delay hace que el LED cambie de estado tan rápido que no se pueda percibir visualmente ya que no hay ningún retraso en las instrucciones. Al eliminar la funcón serial hace que no se envien datos por el puerto serial, lo que puede ser útil para em monitoreo del programa. Como el microcontrolador ejectuta las instrucciones loop() lo más rápido posible supone un mayor consumo de energía.



## 3.Diagrama de flujos:

### Con delay:

```mermaid

graph LR
    Inicio --> setup
    setup --> loop
    loop --> Cambiar_LED_ON
    Cambiar_LED_ON --> Encender_LED
    Encender_LED --> Imprimir_ON
    Imprimir_ON --> Esperar
    Esperar --> Cambiar_LED_OFF
    Cambiar_LED_OFF --> Apagar_LED
    Apagar_LED --> Imprimir_OFF
    Imprimir_OFF --> Esperar
    Esperar --> loop
```

En este diagrama de flujos se puede observar todas las acciones que lleva a cabo el codigo, primero se incializa con el setup y luego entra en el loop y entra en el bucle de encender e imprimir es y una vez terminado hay un tiempo de **espera** y vuelve al bucle.

### Sin delay:

```mermaid
graph LR
    Inicio((Inicio))
    Inicio --> setup
    setup --> loop
    loop --> Encender_LED
    Encender_LED --> Imprimir_ON
    Imprimir_ON --> Apagar_LED
    Apagar_LED --> Imprimir_OF
    Imprimir_OF --> loop
```

En este diagrama de flujos se puede observar todas las acciones que lleva a cabo el codigo, primero se incializa con el setup y luego entra en el loop y entra en el bucle de encender e imprimir, sin **ningún tiempo de espera** adicional.

## 4. Diagrama de tiempos



```mermaid

sequenceDiagram
participant LED
participant sistema
sistema->>LED: Encender
LED-->sistema: ON
sistema->>LED: Apagar
LED-->>sistema: OFF

```

Aquí se muestra el diagrama de tiempos, que va de encendido a apagado en intervalos de 500 ms, es decir hay un cambio de estado cada 500ms.

## 5. Medir la frecuencia con el osciloscopio:

Hemos quitado el delay y en nuestro caso hemos modificado el pin y ahora el pin de salida es el 2.

### 5.1. Con el envio por el puerto série del mensaje i utilizando las funciones de Arduino

```c++
#include <Arduino.h>
 
  int led = 2;

  void setup() {
    pinMode(led,OUUTPUT);
    Serial.begin(115200);
  }

  void loop(){
    Serial.println("ON");
    digitalWrite(led,HIGH);
    Serial.println("OFF");
    digitalWrite(led,LOW);
  }

```
La frecuencia que nos da el osciloscopio es 29,52 KHz

### 5.2. Con el envio por el puerto série y accedirendo directamente a los registros

```c++
#include <Arduino.h>
  
  int led = 2;
  uint32_t *gpio_out = (uint32_t*) GPIO_OUT_REG;

  void setup(){
    pinMode(led,OUTPUT);
    Serial.begin(115200);
  }

  void loop(){
    Serial.println("ON");
    *gpio_out |=(1 << led);
    Serial.println("OFF");
    *gpio_out ^= (1 << led);
  }

```

La frecuencia que nos da el osciloscopio es 29,6 KHz

### 5.3. Sin el envio por el puerto série del mensaje i utilizando las funciones de Arduino

```c++
#include <Arduino.h>

   int led= 2;

   void setup(){
    pinMode(led,OUTPUT);
   }

   void loop(){
    digitalWrite(led, HIGH);
    digitalWrite(led, LOW);
   }

```
La frecuencia que nos da el osciloscopio es de 1,74 MHz

### 5.4. Sin el envio por el puerto série y accedirendo directamente a los registros

```c++
#include <Arduino.h>
   
   int led= 2;
   uint32_t*gpio_out = (uint32_t*)GPIO_OUT_REG;

   void setuo(){
    pinMode(led,OUTPUT);
   }

   void loop(){
    *gpio_out |= (1 << led);
    *gpio_out ^= (1 << led);
   }

   ```
La frecuencia que nos da el osciloscopio es de 4,7 MHz
 
## Cual es el tiempo libre que tiene el procesador ?

El tiempo libre del procesador en este caso se ve afectado por las instrucciones dentro del loop() y la duración total de los retrasos. Como este codigo está compuesto de retrasos, el procesador tiene mucho tiempo libre entre cada iteración, concretamente un tiempo de 500 milisegundos que es el que tarde entre encender y apagar el LED.

## Conclusión

En conlusción, este codigo diseñado para la placa Arduino controla un LED con intervalos regulares de cambio de estado. Podemos observar que el procesador tiene un tiempo libre significativo por lo que podría estar haciendo otras tareas mientras está esperando.

