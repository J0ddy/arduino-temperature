#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//TODO: Add Data for each month's avarage temperature (As Array)
//TODO: Add Method to check if the temperature is below or above avarage and update the second line to that information

int pinTemp = A1;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  lcd.clear();
  int temp = map(((analogRead(pinTemp) - 20) * 3.04), 0, 1023, -40, 125);
  lcd.print("Temperature: ");
  lcd.print(temp);
  lcd.print("C");
  delay(1000);
}
