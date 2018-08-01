#define fadePin 5 //пин управления MOSFET транзистором

#define pirPin  2  //пин подключения управляющего сигнала PIR датчика

#include <Wire.h>

#include <BH1750.h>

BH1750 lightMeter;

int lig,i;       //переменная для хранения состояния света (вкл/выкл)

void setup(){
  Serial.begin(9600);
  
    lightMeter.begin();
 
  lig = 0;     //устанаваливаем переменную для первого включения света
  
}

void loop(){
  
  pinMode(pirPin, INPUT);           // назначить выводу порт ввода
digitalWrite(pirPin, LOW);       // включить подтягивающий резистор


 uint16_t lux = lightMeter.readLightLevel();
 Serial.print("l:");
  Serial.print(lux);
 Serial.print("_");
   if((digitalRead(pirPin) == HIGH)&&(lux<=50) )  //если сигнал с датчика высокого уровня(т.е. есть движение)
   {
    if (lig == 0)
      {
        for (int i=0; i<=75; i++)
          {
            analogWrite(fadePin,i);
            delay(10);
                   }
         
          lig=1;
      }

    if (lig == 1)
      {
        i=0;
        while(i<75)
          {
            if((digitalRead(pirPin) == HIGH)&&(lux<=50) ){  //если сигнал с датчика высокого уровня(т.е. есть движение)
                
                  analogWrite(fadePin,75);
                  i=0;
                }
                else{
                  i++;
                  }
                  delay(100);
                  Serial.print(i);
                  Serial.print("_");
          }
      }
      
     
   } 
  if(digitalRead(pirPin) == LOW )
   {
     if(lig == 1) //если свет включен
     {
      
       for(int i=75; i>=0; i--)//плавно гасим его
       {
       
        analogWrite(fadePin,i);
       delay(10);
       } 
       lig = 0; //и передаем значение переменной, что свет выключен
      //  Serial.print("Выкл");
        
     }
   }
}
