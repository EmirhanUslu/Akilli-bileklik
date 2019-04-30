# Buzzer Kullanımı 

#define buzzerPin 3 // buzzer'ın bağlı olduğu pini belirledim
void setup() {

  pinMode(buzzerPin , OUTPUT); // buzzer pinini çıkış olarak belirledim

}

void loop() {

  tone(buzzerPin, 440); //buzzer'ı 440 frekans kodu ile aktif ettim
  delay(5000); //5 saniye beklettim 
  noTone(buzzerPin);  // buzzerı durdurdum
  delay(5000); //5 saniye beklettim 

  
  
}
// bu işlemleri loop da yaptığım için  buzzer 5 saniye çalışcak 5 saniye durucak
