void getBuffer() // Get weather status data
{
  
  int index;
  for (index = 0; index < 35; index++)
  {
    if (df.available())
    {
      databuffer[index] = df.read();
      if (databuffer[0] != 'c')
      {
        index = -1;
      }
    }
    else
    {
      index--;
    }
  }
}
int transCharToInt(char *_buffer, int _start, int _stop) // char to int）
{
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start; _index <= _stop; _index++)
  {
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10 * result + _temp[_index - _start];
  }
  return result;
}

int WindDirection() // Wind Direction
{
  return transCharToInt(databuffer, 1, 3);
}

float WindSpeedAverage() // air Speed (1 minute)
{
  temp = 0.44704 * transCharToInt(databuffer, 5, 7);
  return temp;
}

float WindSpeedMax() // Max air speed (5 minutes)
{
  temp = 0.44704 * transCharToInt(databuffer, 9, 11);
  return temp;
}

float Temperature() // Temperature ("C")
{
  temp = (transCharToInt(databuffer, 13, 15) - 32.00) * 5.00 / 9.00;
  return temp;
}

float RainfallOneHour() // Rainfall (1 hour)
{
  temp = transCharToInt(databuffer, 17, 19) * 25.40 * 0.01;
  return temp;
}

float RainfallOneDay() // Rainfall (24 hours)
{
  temp = transCharToInt(databuffer, 21, 23) * 25.40 * 0.01;
  return temp;
}

int Humidity() // Humidity
{
  return transCharToInt(databuffer, 25, 26);
}

float BarPressure() // Barometric Pressure
{
  temp = transCharToInt(databuffer, 28, 32);
  return temp / 10.00;
}

void loop_dfrobot(){
  Serial2.println("Start DF Robot");
  //getBuffer(); // Begin
  StaticJsonDocument<200> doc;
  doc["windDirection"] = WindDirection();
  doc["averageWindSpeed"] = WindSpeedAverage();
  doc["maxWindSpeed"] = WindSpeedMax();
  doc["rainFallOneHour"] = RainfallOneHour();
  doc["rainFallOneHour"] = RainfallOneDay();

  doc["temprature"] = Temperature();
  doc["humidity"] = Humidity();
  doc["barometricPressure"] = BarPressure();
  doc["buoy"] = "";
  doc["rx"] = "";
  serializeJsonPretty(doc, Serial2);
  Serial2.println("");
}
