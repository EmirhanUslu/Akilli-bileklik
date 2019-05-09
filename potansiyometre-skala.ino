#define potpin A0 //Potansiyometreyi A0 pinine tanımlıyoruz
int deger=0; 
int sondeger=0;
void setup() 
{
  Serial.begin(9600); //9600 Baund bir seri haberleşme başlatıyoruz
  Serial.println("Pot Deger Okuma"); //Seri monitörde bir kez gönderilen bir mesaj tanımlıyoruz
}
void loop() 
{
  deger  = analogRead(potpin); //"Değer" değişkeni potansiyometrenin değerini okuyup buna göre değişir
  sondeger=deger/10.2;        // Burda okuduğumuz analog değeri 0 ile 100 arasında skala ettim.
  Serial.println(sondeger); //Okunan değer seri monitörde mesaj olarak gönderilir
  delay(100); //Bu işlem 100 milisaniye aralıklarla yapılır
}
