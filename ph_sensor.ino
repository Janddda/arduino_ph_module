// Arduino Modul pro měření pH

// nastavení čísel propojovacích pinů
const int pinPo = A0;

void setup() {
  // komunikace po sériové lince rychlostí 9600 baud
  Serial.begin(9600);
}

void loop() {
  // vytvoření pomocných proměnných
  int pole[10];
  int zaloha;
  unsigned long int prumerVysl = 0;
  // načtení deseti vzorků po 10 ms do pole
  for (int i = 0; i < 10; i++) {
    pole[i] = analogRead(pinPo);
    delay(10);
  }
  // seřazení členů pole naměřených výsledků podle velikosti
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (pole[i] > pole[j]) {
        zaloha = pole[i];
        pole[i] = pole[j];
        pole[j] = zaloha;
      }
    }
  }
  // uložení 2. až 8. výsledku do
  // proměnné, z které se vypočte průměr
  // (vynechání dvou členů pole na začátku
  // a konci pro lepší přesnost)
  for (int i = 2; i < 8; i++) {
    prumerVysl += pole[i];
  }
  // výpočet hodnoty pH z průměru
  // měření a přepočet na rozsah 0-14 pH
  float prumerPH = (float)prumerVysl * 5.0 / 1024 / 6;
  float vyslednePH = -5.70 * prumerPH + 21.34;
  // vytištění výsledků po sériové lince
  Serial.print("Namerene pH: ");
  Serial.println(vyslednePH);
  // pauza 900 ms před novým měřením, celkem tedy 1s
  delay(900);
}
