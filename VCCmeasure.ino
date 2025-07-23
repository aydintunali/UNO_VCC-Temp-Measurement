
#define iREF  1100   // internal reference voltage [mV]

void setup() {
  Serial.begin(115200);
  Serial.println("-- Vcc Voltage measurement --");
}

void loop() {
  uint16_t vcc=readVcc();
  Serial.print("Vcc: ");
  Serial.print(vcc);
  Serial.println(" mV");
  delay(1000);
}

// This function measures and calculates the voltage at the AVCC pin
// using the Atmega328 internal reference (~1.1V).
// Returns 5000 for 5,000 volts. (1mV sensitivity)
int readVcc(void)
{
// Reference=VCCA, Measure:1.1V bandgap reference channel
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delayMicroseconds(200);           // wait for MUX change and bandgap reference
  bitSet(ADCSRA,ADSC);              // start measure
  while (bit_is_set(ADCSRA,ADSC));  // wait until finish
  int result = ADCL;                // get the result low and
  result |= ADCH<<8;                // and high bytes
  result = iREF * 1024L / result;   // Calculate Vcc value from the measurement
  return result;
}
