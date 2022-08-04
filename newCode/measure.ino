void dcMeasure() {
  shuntvoltageA = ina219A.getShuntVoltage_mV();
  busvoltageA = ina219A.getBusVoltage_V();
  current_mAA = ina219A.getCurrent_mA();
  power_mWA = ina219A.getPower_mW();
  loadvoltageA = busvoltageA + (shuntvoltageA / 1000);

  shuntvoltageB = ina219B.getShuntVoltage_mV();
  busvoltageB = ina219B.getBusVoltage_V();
  current_mAB = ina219B.getCurrent_mA();
  power_mWB = ina219B.getPower_mW();
  loadvoltageB = busvoltageB + (shuntvoltageB / 1000);

  Serial.println("INA 219 A    :");
  Serial.print("Bus Voltage    : "); Serial.print(busvoltageA); Serial.println(" V");
  Serial.print("Shunt Voltage  : "); Serial.print(shuntvoltageA); Serial.println(" mV");
  Serial.print("Load Voltage   : "); Serial.print(loadvoltageA); Serial.println(" V");
  Serial.print("Current        : "); Serial.print(current_mAA); Serial.println(" mA");
  Serial.print("Power          : "); Serial.print(power_mWA); Serial.println(" mW");
  Serial.println("");

  Serial.println("INA 219 B    :");
  Serial.print("Bus Voltage    : "); Serial.print(busvoltageB); Serial.println(" V");
  Serial.print("Shunt Voltage  : "); Serial.print(shuntvoltageB); Serial.println(" mV");
  Serial.print("Load Voltage   : "); Serial.print(loadvoltageB); Serial.println(" V");
  Serial.print("Current        : "); Serial.print(current_mAB); Serial.println(" mA");
  Serial.print("Power:         : "); Serial.print(power_mWB); Serial.println(" mW");
  Serial.println();
}

void acMeasure() {
  Serial.print("Custom Address:");
  Serial.println(pzem.readAddress(), HEX);

  // Read the data from the sensor
  voltage = pzem.voltage();
  current = pzem.current();
  power = pzem.power();
  energy = pzem.energy();
  frequency = pzem.frequency();
  pf = pzem.pf();

  // Check if the data is valid
  if (isnan(voltage)) {
    Serial.println("Error reading voltage");
  } else if (isnan(current)) {
    Serial.println("Error reading current");
  } else if (isnan(power)) {
    Serial.println("Error reading power");
  } else if (isnan(energy)) {
    Serial.println("Error reading energy");
  } else if (isnan(frequency)) {
    Serial.println("Error reading frequency");
  } else if (isnan(pf)) {
    Serial.println("Error reading power factor");
  } else {
    // Print the values to the Serial console
    Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
    Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
    Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
    Serial.print("Energy: ");       Serial.print(energy, 3);     Serial.println("kWh");
    Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
    Serial.print("PF: ");           Serial.println(pf);
    Serial.println();
  }
}

void batSensing() {
  //Bat A
  busvoltageC = ina219C.getBusVoltage_V();

  //Bat B
  busvoltageD = ina219D.getBusVoltage_V();
  int batVolumeC = busvoltageC*100;
  int batVolumeD = busvoltageD*100;
  
  batAPercentage = map(batVolumeC, 1060, 1306, 0, 100);
  batBPercentage = map(batVolumeD, 1060, 1306, 0, 100);
  if (batAPercentage > 100){
    batAPercentage = 100;
  }
  if (batBPercentage > 100){
    batBPercentage = 100;
  }
  if (batAPercentage < 0){
    batAPercentage = 0;
  }
  if (batBPercentage < 0){
    batBPercentage = 0;
  }
  Serial.println("INA 219 C    :");
  Serial.print("Bus Voltage    : "); Serial.print(busvoltageC); Serial.println(" V");
  Serial.println();

  Serial.println("INA 219 D    :");
  Serial.print("Bus Voltage    : "); Serial.print(busvoltageD); Serial.println(" V");
  Serial.println();
}

//void batSensing() {
//  batAValue = (analogRead(batA) * 3)/900;
//  batBValue = (analogRead(batB) * 3)/900;
//
//  Serial.print("Bat A Analog : ");
//  Serial.println(analogRead(batA));
//  Serial.print("Bat B Analog : ");
//  Serial.println(analogRead(batB));
//  batAPercentage = map(batAValue, 11.5, 13.5, 0, 100);
//  batBPercentage = map(batBValue, 11.5, 13.5, 0, 100);
//
//  Serial.print("Bat A : ");
//  Serial.println(batAValue);
//  Serial.print("Bat B : ");
//  Serial.println(batBValue);
//  Serial.println();
//}
