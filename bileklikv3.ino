#define echoPin 7   // ort ult. sen.
#define trigPin 6   // ort ult. sen.
#define saechoPin 5 // sag ult. sen.
#define satrigPin 4 // sag ult. sen.
#define soechoPin 9 // sol ult. sen.
#define sotrigPin 8 // sol ult. sen.
#define buzzerPin 3 // buzzer
#define potpin A0 //Potansiyometreyi A0 pinine tanımlıyoruz
#define motorPin 10 // orta titreşim mot.
#define samotorPin 11 //sağ motor
#define somotorPin 12 //sol motor
#define buton 13
//yukarıda pinlerimi tanımladım ve artık pin numarası yerine direk adını yazabilirim.

//aşağıda  ölçüm için aralığımı tanımladım  varsayılan olarak maksimum aralığı 20cm yaptım
int maximumRange = 0; 
int minimumRange = 0;
int deger=0; 
int sondeger=0;
void setup()
{
  //9600 Baund bir seri haberleşme başlatıyoruz
  Serial.begin(9600); 
  //Seri monitörde bir kez gönderilen bir mesaj tanımlıyoruz  
  Serial.println("Pot Deger Okuma"); 
  //Trig pin  ultrasonik sensörü tetiklemeye yarıyor  çıkış pini
  pinMode(trigPin, OUTPUT);
  pinMode(satrigPin, OUTPUT);
  pinMode(sotrigPin, OUTPUT);
  // Echo pin ultrasonik sensöre dönen ses dalgalarını okumaya yarıyor  giriş pini
  pinMode(echoPin, INPUT);
  pinMode(saechoPin, INPUT);
  pinMode(soechoPin, INPUT);
  
  // Buzzer pini çıkış pini alarm verdireceğimiz zaman kullanacağız
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin , OUTPUT);
  pinMode(samotorPin , OUTPUT);
  pinMode(somotorPin , OUTPUT);
  pinMode(buton , INPUT);
  digitalWrite(motorPin,HIGH);
}

void loop()
{
  // loop kontrol kartımızın döngüsü   belirlediğimiz senaryoya göre tüm işlemler döngü halinde burda gerçekleşecek.
  
  //"Değer" değişkeni potansiyometrenin değerini okuyup buna göre değişir
  deger  = analogRead(potpin); 
  // Burda okuduğumuz analog değeri 0 ile 100 arasında skala ettim.
  sondeger=deger/10.2;    
  //Okunan değer seri monitörde mesaj olarak gönderilir    
  Serial.println("Max Range");
  Serial.println(sondeger); 
  
  // okuyup skala ettiğim değeri maksimum aralık olarak tanımladım.
  maximumRange=sondeger;
  //Bu işlem 100 milisaniye aralıklarla yapılır
  delay(100); 
  // Ölçüm adında bir değişken tanımladık mesafe fonksiyonumuzdan değerler buraya döndürülecek.
  int ortOlcum= ortMesafe(maximumRange, minimumRange);
  int sagOlcum= sagMesafe(maximumRange, minimumRange);
  int solOlcum= solMesafe(maximumRange, minimumRange);
  //Melodi fonksiyonumuzu çağırdık ve melodi fonksiyonumuzu bekletmek istediğimiz değeri gönderdik ben 5, 10 ,15 gibi değerleri denedikten sonra en verimli süre olarak 20 yi kullandım.
 if (digitalRead(buton) == 1)
 {
  if(ortOlcum>sagOlcum and ortOlcum>solOlcum)
  melodi(ortOlcum * 20);
  else if(sagOlcum>ortOlcum and sagOlcum>solOlcum)
  sagmelodi(sagOlcum * 20);
  else
  solmelodi(solOlcum * 20);
 }
  int skalaa=skala(ortOlcum);
  ortUyari(skalaa*5);
  int skalaaa=skala(sagOlcum);
  sagUyari(skalaaa*5);
  int skalaaaa=skala(solOlcum);
  solUyari(skalaaaa*5);    
}

// Titreşim motoru için ölçümü ters çevirme fonks.
int skala(int dly)
{
  int dly2=dly;
  if(dly2==100)
  {
    return 0;
  }
  else if(dly2==0)
  {
  return 0;
  }
  else
  {
   dly=100-dly2;  
  }
  return dly;
}



// oRTA SENSÖR İÇİN Mesafe fonksiyonumuzu tanımladım
int ortMesafe(int maxrange, int minrange)
{
//Burda long tipinde değişken kullandım çünkü sensörden okuyacağımız değer  int maksimum değerini aşabilir  
  long duration, distance;
//Sensörü tetiklemeyi durdurduk.
  digitalWrite(trigPin, LOW);
//2mikro saniye bekledik.
  delayMicroseconds(2);
// Sensörü tekrar tetikledik
  digitalWrite(trigPin, HIGH);
// 10 mikro saniye bekledik.
  delayMicroseconds(10);
// sensörü tetiklemeyi durdurduk 
  digitalWrite(trigPin, LOW);
// Burda  pulseIn fonksiyonu ile sensörü dinledik  sensör burda gönderilen ses dalgasının  kendine ne kadar sürede geri döndüğünü döndürüyor.PulseIn fonksiyonu arduino 'nun kendi
// fonksiyonudur.
  duration = pulseIn(echoPin, HIGH);
// Burda zamanı 58.2 değerine bölerek  mesafeyi elde ediyoruz.
  distance = duration / 58.2;
// 50 mili saniye bekliyoruz
delayMicroseconds(50);
// Eğer mesafe istediğimiz aralıkta değilse 
  if (distance >= maxrange || distance <= minrange)
    return 0;
//Değilse  mesafeyi döndür
  return distance;
}

// Sağ SENSÖR İÇİN Mesafe fonksiyonumuzu tanımladım
int sagMesafe(int maxrange, int minrange)
{
//Burda long tipinde değişken kullandım çünkü sensörden okuyacağımız değer  int maksimum değerini aşabilir  
  long duration, distance;
//Sensörü tetiklemeyi durdurduk.
  digitalWrite(satrigPin, LOW);
//2mikro saniye bekledik.
  delayMicroseconds(2);
// Sensörü tekrar tetikledik
  digitalWrite(satrigPin, HIGH);
// 10 mikro saniye bekledik.
  delayMicroseconds(10);
// sensörü tetiklemeyi durdurduk 
  digitalWrite(satrigPin, LOW);
// Burda  pulseIn fonksiyonu ile sensörü dinledik  sensör burda gönderilen ses dalgasının  kendine ne kadar sürede geri döndüğünü döndürüyor.PulseIn fonksiyonu arduino 'nun kendi
// fonksiyonudur.
  duration = pulseIn(saechoPin, HIGH);
// Burda zamanı 58.2 değerine bölerek  mesafeyi elde ediyoruz.
  distance = duration / 58.2;
// 50 mili saniye bekliyoruz
delayMicroseconds(50);
// Eğer mesafe istediğimiz aralıkta değilse 
  if (distance >= maxrange || distance <= minrange)
    return 0;
//Değilse  mesafeyi döndür
  return distance;
}


// Sol SENSÖR İÇİN Mesafe fonksiyonumuzu tanımladım
int solMesafe(int maxrange, int minrange)
{
//Burda long tipinde değişken kullandım çünkü sensörden okuyacağımız değer  int maksimum değerini aşabilir  
  long duration, distance;
//Sensörü tetiklemeyi durdurduk.
  digitalWrite(sotrigPin, LOW);
//2mikro saniye bekledik.
  delayMicroseconds(2);
// Sensörü tekrar tetikledik
  digitalWrite(sotrigPin, HIGH);
// 10 mikro saniye bekledik.
  delayMicroseconds(10);
// sensörü tetiklemeyi durdurduk 
  digitalWrite(sotrigPin, LOW);
// Burda  pulseIn fonksiyonu ile sensörü dinledik  sensör burda gönderilen ses dalgasının  kendine ne kadar sürede geri döndüğünü döndürüyor.PulseIn fonksiyonu arduino 'nun kendi
// fonksiyonudur.
  duration = pulseIn(soechoPin, HIGH);
// Burda zamanı 58.2 değerine bölerek  mesafeyi elde ediyoruz.
  distance = duration / 58.2;
// 50 mili saniye bekliyoruz
  delayMicroseconds(50);
// Eğer mesafe istediğimiz aralıkta değilse 
  if (distance >= maxrange || distance <= minrange)
    return 0;
//Değilse  mesafeyi döndür
  return distance;
}


//uyarı fonksiyonumuzu tanımladık fonksiyon parametresi olan dly ölçüm*20 olarak loop fonksiyonun içinde tanımlanan  parametreden geliyor.
int melodi(int dly)
{
// tone fonksiyonu arduino'nun kendi fonksiyonudur ve burdaki 210 değeride  buzzer tonlarından biri   
  tone(buzzerPin, 440);
//burda parametreden gelen değer kadar bekliyoruz     
  delay(dly);
// notone fonksiyonu arduino'nun kendi fonksiyonudur ve buzzer'ı susturmaya yarar.
  noTone(buzzerPin);
// burda yine parametreden gelen değer kadar bekliyoruz.
  delay(dly);
}

//uyarı fonksiyonumuzu tanımladık fonksiyon parametresi olan dly ölçüm*20 olarak loop fonksiyonun içinde tanımlanan  parametreden geliyor.
int sagmelodi(int dly)
{
// tone fonksiyonu arduino'nun kendi fonksiyonudur ve burdaki 210 değeride  buzzer tonlarından biri   
  tone(buzzerPin, 210);
//burda parametreden gelen değer kadar bekliyoruz     
  delay(dly);
// notone fonksiyonu arduino'nun kendi fonksiyonudur ve buzzer'ı susturmaya yarar.
  noTone(buzzerPin);
// burda yine parametreden gelen değer kadar bekliyoruz.
  delay(dly);
}

//uyarı fonksiyonumuzu tanımladık fonksiyon parametresi olan dly ölçüm*20 olarak loop fonksiyonun içinde tanımlanan  parametreden geliyor.
int solmelodi(int dly)
{
// tone fonksiyonu arduino'nun kendi fonksiyonudur ve burdaki 210 değeride  buzzer tonlarından biri   
  tone(buzzerPin, 320);
//burda parametreden gelen değer kadar bekliyoruz     
  delay(dly);
// notone fonksiyonu arduino'nun kendi fonksiyonudur ve buzzer'ı susturmaya yarar.
  noTone(buzzerPin);
// burda yine parametreden gelen değer kadar bekliyoruz.
  delay(dly);
}

// Titreşim Motoru için fonks.
int ortUyari(int dly)
{
  digitalWrite(motorPin,LOW);
  delay(dly);
  digitalWrite(motorPin,HIGH);
  delay(dly);  
}
// Titreşim Motoru için fonks.
int sagUyari(int dly)
{
  digitalWrite(samotorPin,LOW);
  delay(dly);
  digitalWrite(samotorPin,HIGH);
  delay(dly);  
}
// Titreşim Motoru için fonks.
int solUyari(int dly)
{
  digitalWrite(somotorPin,LOW);
  delay(dly);
  digitalWrite(somotorPin,HIGH);
  delay(dly);  
}
