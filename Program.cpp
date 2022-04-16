#include <LiquidCrystal.h>
#include <time.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int avarageTemps[12] = {0,3,7,12,15,21,23,23,19,13,7,2};

bool isTempHigherThanAvarage(int temp) {
  time_t theTime = time(NULL);
  struct tm *aTime = localtime(&theTime);
  int currentMonth = aTime->tm_mon + 1;
  return temp>avarageTemps[currentMonth-1];
}

int pinTemp = A1;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  lcd.clear();
  int temp = map(((analogRead(pinTemp) - 20) * 3.04), 0, 1023, -40, 125);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");
  if(isTempHigherThanAvarage(temp)) lcd.print(" Higher");
  else lcd.print(" Lower");
  delay(1000);
}
