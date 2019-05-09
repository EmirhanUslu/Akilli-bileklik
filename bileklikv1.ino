#define echoPin 7
#define trigPin 6
#define buzzerPin 3
#define potpin A0 //Potansiyometreyi A0 pinine tanımlıyoruz
//yukarıda pinlerimi tanımladım ve artık pin numarası yerine direk adını yazabilirim.

//aşağıda  ölçüm için aralığımı tanımladım  varsayılan olarak maksimum aralığı 20cm yaptım
int maximumRange = 20; 
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
  // Echo pin ultrasonik sensöre dönen ses dalgalarını okumaya yarıyor  giriş pini
  pinMode(echoPin, INPUT);
  // Buzzer pini çıkış pini alarm verdireceğimiz zaman kullanacağız
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  // loop kontrol kartımızın döngüsü   belirlediğimiz senaryoya göre tüm işlemler döngü halinde burda gerçekleşecek.
  
  //"Değer" değişkeni potansiyometrenin değerini okuyup buna göre değişir
  deger  = analogRead(potpin); 
  // Burda okuduğumuz analog değeri 0 ile 100 arasında skala ettim.
  sondeger=deger/10.2;    
  //Okunan değer seri monitörde mesaj olarak gönderilir    
  Serial.println(sondeger); 
  // okuyup skala ettiğim değeri maksimum aralık olarak tanımladım.
  maximumRange=sondeger;
  //Bu işlem 100 milisaniye aralıklarla yapılır
  delay(100); 
  // Ölçüm adında bir değişken tanımladık mesafe fonksiyonumuzdan değerler buraya döndürülecek.
  int olcum = mesafe(maximumRange, minimumRange);
  //Melodi fonksiyonumuzu çağırdık ve melodi fonksiyonumuzu bekletmek istediğimiz değeri gönderdik ben 5, 10 ,15 gibi değerleri denedikten sonra en verimli süre olarak 20 yi kullandım.
  melodi(olcum * 20);
}
//Mesafe fonksiyonumuzu tanımladım
int mesafe(int maxrange, int minrange)
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
  delay(50);
// Eğer mesafe istediğimiz aralıkta değilse 
  if (distance >= maxrange || distance <= minrange)
    return 0;
//Değilse  mesafeyi döndür
  return distance;
}
//melodi fonksiyonumuzu tanımladık fonksiyon parametresi olan dly ölçüm*20 olarak loop fonksiyonun içinde tanımlanan  parametreden geliyor.
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
