#include <PinChangeInt.h>
#include <eHealth.h>

//Include always this code when using the pulsioximeter sensor
//=========================================================================
uint8_t cont = 0;
void readPulsioximeter(){

  cont ++;

  if (cont == 50) { //Get only one of 50 measures to reduce the latency
    eHealth.readPulsioximeter();
    cont = 0;
  }
}

void setup() {
  Serial.begin(115200);
  
  // put your setup code here, to run once:
  eHealth.initPulsioximeter();
  eHealth.initPositionSensor();
//  eHealth.readBloodPressureSensor();

  //Attach the interruptions for using the pulsioximeter.
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  delay(1000);
}

// append a new key-value pair to the json string
template <typename T> 
void append(String &str, const char *key, T value, bool comma=true){
  if(comma) str += String(", ");
  str += String("\"");
  str += String(key);
  str += String("\": ");
  str += String(value);  
}

void loop() {
   char ch;
   
   // are we getting triggered?
//   if (Serial.available())    {
     // read-out trigger signal and ignore
//     ch = Serial.read();
  
     // read all sensor values
     int airFlow = eHealth.getAirFlow();
     float temperature = eHealth.getTemperature();
     float conductance = eHealth.getSkinConductance();
     float resistance = eHealth.getSkinResistance();
     int BPM = eHealth.getBPM();
     int SPO2 = eHealth.getOxygenSaturation();
     uint8_t pos = eHealth.getBodyPosition();
     float EMG = eHealth.getEMG();
//     uint8_t bp_nof_data = eHealth.getBloodPressureLength();
//     int bp_systolic = eHealth.getSystolicPressure(1);
//     int bp_diastolic = eHealth.getDiastolicPressure(1);

     // create json string
     String str = "{";
     append(str, "airflow", airFlow, false);
     append(str, "temperature", temperature);
     append(str, "skin-conductance", conductance);
     append(str, "skin-resistance", resistance);
     append(str, "BPM", BPM);
     append(str, "SPO2", SPO2);
     append(str, "body-position", pos);
     append(str, "EMG", EMG);
//     append(str, "bp-nof-data", bp_nof_data);
//     append(str, "bp-systolic", bp_systolic);
//     append(str, "bp-diastolic", bp_diastolic);
     str += "}";

     // communicate
     Serial.println(str);
     delay(50);
//   }
}
