void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // -1 bar to 1 bar
  // 0 to 1023 
  
  // output 1v to 5v;
  // starting value 1023/5 = 205// -1bar
  //3v zero pressure 614;
  // 0-101kpa 2v range;
  //(value - 614)/(101kpa - 0)*2 =
  double value = (analogRead(A0));
//  Serial.println(value);
  double cal = 1.17;
  double pres = (value - ((1023.0/5)*3));
  double pres_converted = pres*(250.0/1023) + cal;
  Serial.print(pres_converted);
  Serial.print("\n");
}
