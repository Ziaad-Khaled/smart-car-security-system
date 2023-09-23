const int led = 6;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  Serial.print(led);
  Serial.println("zzz");
}
