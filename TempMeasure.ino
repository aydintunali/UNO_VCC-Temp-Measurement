
#define GAIN  250/256   // Gain
#define OFFS  340       // Offset (may change on different chips)

void setup() {
  Serial.begin(115200);
  Serial.println("-- Internal Temperature Measurement --");
}

void loop() {
  Serial.print("Temp: ");
  Serial.println(readTemp());
  delay(1000);
}

// This function measures the internal temperature voltage of Atmega328
// and calculates the temperature value in degrees.
// Returns 25 for 25 degrees. (1C precision)
int readTemp(void){
// Reference=1.1V, Measure:Temp channel
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delayMicroseconds(400);           // wait for MUX change and bandgap reference 
  bitSet(ADCSRA,ADSC);              // start measure
  while (bit_is_set(ADCSRA,ADSC));  // wait until finish
  int result = ADCL;                // get the result low and
  result |= ADCH<<8;                // high bytes
  result -= OFFS;
  result *= GAIN;                   // calculate the temperature
  return result;
}

