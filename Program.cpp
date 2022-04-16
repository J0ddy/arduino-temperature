#include <LiquidCrystal.h>
#include <time.h>
#include <math.h>

int pinTemp = A1;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int avarageTemps[12] = {0,3,7,12,15,21,23,23,19,13,7,2};
int currentDay, currentMonth, currentYear;

void updateDateTime() {
  time_t theTime = time(NULL);
  struct tm *aTime = localtime(&theTime);
  currentDay = aTime->tm_mday+16;
  currentMonth = aTime->tm_mon+4;
  currentYear = aTime->tm_year+1922;
}
bool isTempHigherThanAvarage(int temp) {
  updateDateTime();
  return temp>avarageTemps[currentMonth-1];
}
void setup() {
  pinMode(2, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}
void PrintTemp() {
  int temp = map(((analogRead(pinTemp) - 20) * 3.04), 0, 1023, -40, 125);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");
  if(isTempHigherThanAvarage(temp)) lcd.print(" Higher");
  else lcd.print(" Lower");
}
void PrintTime() {
  lcd.print("Date: ");
  lcd.print(currentDay);
  lcd.print("/");
  lcd.print(currentMonth);
  lcd.print("/");
  lcd.print(currentYear);
}
void ActivateLED() {
  int temp = map(((analogRead(pinTemp) - 20) * 3.04), 0, 1023, -40, 125);
  int x = temp-avarageTemps[currentMonth-1];
  if(abs(x)>=15) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
}
void loop(){
  lcd.setCursor(0,0);
  lcd.clear();
  PrintTemp();
  lcd.setCursor(0,1);
  PrintTime();
  ActivateLED();
  delay(1000);
}
