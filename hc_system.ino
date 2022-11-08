#include "DHT.h"

#define DHT0PIN 8     // what pin we're connected to
#define DHT1PIN 9
#define DHT2PIN 4
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define cooler_low_level_PIN 2
#define cooler_high_level_PIN 3

#define heater_low_level_PIN 15
#define heater_high_level_PIN 16

#define humidity_low_level_PIN 17
#define humidity_high_level_PIN 18

DHT dht0(DHT0PIN, DHTTYPE,4);
DHT dht1(DHT1PIN, DHTTYPE,4);
DHT dht2(DHT2PIN, DHTTYPE,4);
void setup(void) {
  Serial.begin(9600);

  Serial.println("DHT SYSTEM");
  pinMode(cooler_low_level_PIN,OUTPUT);
  pinMode(cooler_high_level_PIN,OUTPUT);
  
  pinMode(heater_low_level_PIN,OUTPUT);
  pinMode(heater_high_level_PIN,OUTPUT);
  
  pinMode(humidity_low_level_PIN,OUTPUT);
  pinMode(humidity_high_level_PIN,OUTPUT);
  
  
  dht0.begin();
  dht1.begin();
  dht2.begin();
}
      
void loop(void) {

   int heater_state = 0;
   int cooler_state = 0;
   int humidity_state = 0;
   int HC_super_state  = 0;
   
   boolean coolerIsOn = false;
   boolean heaterIsOn = false;
   
   boolean humidifier_low = false;
   boolean humidifier_high = false;
   boolean cooler_low = false;
   boolean cooler_high = false;
   boolean heater_low = false;
   boolean heater_high = false;
   



	
	   
	      while(true){
		     float h0 = dht0.readHumidity();
	      // Read temperature as Celsius
	      float t0 = dht0.readTemperature();
	      
	      float h1 = dht1.readHumidity();
	      // Read temperature as Celsius
	      float t1 = dht1.readTemperature();
	      
	      float h2 = dht2.readHumidity();
	      // Read temperature as Celsius
	      float t2 = dht2.readTemperature();
	      
	        float avgT = (t0+t1+t2)/3;
	       float avgH = (h0+h1+h2)/3;
	      
	      
	      
	      
	    //check humidity 
	   if(avgH<80 && humidity_state ==0){
		  humidity_state = 1;
		  humidifier_low = 1;
		  humidifier_high = 0;
		   
	    }
	    
	    if(avgH<70 && humidity_state==1){
		  humidity_state = 2;
		  humidifier_low = 0;
		  humidifier_high = 1;
		  
	    }
	    
	    if(avgH>75 && humidity_state == 2){
		  humidity_state = 1;
		  humidifier_low = 1;
		  humidifier_high = 0;
		  
	    }
	    
	    if(avgH>85 && humidity_state == 1){
		  humidity_state = 0;
		  humidifier_low = 0;
		  humidifier_high = 0;
		  
	    }
	 
	 
	 //check cooler

	     
	      if(HC_super_state == 0 || coolerIsOn){
		     
		     
		    
		   
	         if(avgT > 32 && cooler_state==0){
		 
		 HC_super_state = 1;
		 coolerIsOn = true;
			cooler_state = 1;
			cooler_low = 1;
			cooler_high = 0;
			
			
		     }
		 if(avgT>38 && cooler_state==1){
		 HC_super_state = 1;
		 coolerIsOn = true;
			cooler_state = 2;
			cooler_low = 0;
			cooler_high = 1;
			
			
		     }
		  if(avgT<35 && cooler_state==2){
		  HC_super_state = 1;
		  coolerIsOn = true;
			cooler_state = 1;
			cooler_low = 1;
			cooler_high = 0;
			
			
			      }
		  if(avgT < 28 && cooler_state == 1){
			   coolerIsOn = false;
			   cooler_state = 0;
			   cooler_low = 0;
			   cooler_high = 0;
			   HC_super_state = 0;
			   
			   
		  }
		
		   }
	       
	
	       
	       //check heater
		    if(HC_super_state == 0 || heaterIsOn){
			
	
		    
			if(avgT<20 && heater_state == 0){
			HC_super_state = 2;
			heaterIsOn = true;
			heater_state = 1;
			      heater_low = 1;
			      heater_high = 0;
			
			      }
			if(avgT<15 && heater_state == 1){
			HC_super_state = 2;
			heaterIsOn = true;
			heater_state = 2;
			   heater_low = 0;
			   heater_high = 1;
			  
			   }
			if(avgT>17 && heater_state == 2){
			HC_super_state = 2;
			heaterIsOn = true;
			heater_state = 1;
			      heater_low = 1;
			      heater_high = 0;
			      
			     
			      }
			if(avgT > 23 && heater_state == 1){
			   heaterIsOn = false;
			heater_state = 0;
			      heater_low = 0;
			      heater_high = 0;
			      HC_super_state = 0;
			    
			    
			   }
				   
		  
		  }
	
			
	       
		  
		     
		digitalWrite(heater_low_level_PIN,heater_low);
		digitalWrite(heater_high_level_PIN,heater_high);
	       digitalWrite(cooler_low_level_PIN,cooler_low);
	       digitalWrite(cooler_high_level_PIN,cooler_high);
	       digitalWrite(humidity_low_level_PIN,humidifier_low);
	       digitalWrite(humidity_high_level_PIN,humidifier_high);
	
		 
 
   // Check if any reads failed and exit early (to try again).
  if (isnan(h0) || isnan(t0)) {
    Serial.println("Failed to read from DHT0 sensor!");
    return;
  }
  if (isnan(h1) || isnan(t1)) {
    Serial.println("Failed to read from DHT1 sensor!");
    return;
  }
  
  if (isnan(h2) || isnan(t2)) {
    Serial.println("Failed to read from DHT2 sensor!");
    return;
  }

  Serial.print("avgT             "); 
  Serial.print(avgT);
  Serial.println();
  Serial.print("avgH            ");
  Serial.print(avgH); 
    Serial.println();
 
  delay(1500);
	      }
  
  }

