void setup() {
    Serial.begin(115200);
  // put your setup code here, to run once:

}

void writeValues(const String& type, const String& index, const String& value)
{
     Serial.write(("{\"type\":\"" + type + "\",\"index\":" + index + ",\"value\":" + value + "}").c_str());
}

long update_time = 0;
void loop() {
  long current_time = millis();
  long elapsed_time = current_time - update_time;
  if(elapsed_time > 5000)
  {
    update_time = current_time;
    writeValues("temperature", "0", "21.0");
    writeValues("temperature", "1", "11.0");
    writeValues("sound", "0", "33.333" );
    writeValues( "weight", "0", "500.0" );
    writeValues("humidity", "0", "95.0" );
    writeValues("pressure", "0", "1001055" );
    writeValues("light-intensity", "0", "80" );
  }
}
