# Arduino ile Akıllı LED Animasyon ve Karaşimşek Sistemi
Bu proje, Arduino platformu kullanılarak temel ve orta düzey gömülü sistem programlama mantığını, dizi (array) kullanımını ve döngü (for) kontrol mekanizmalarını öğretmek amacıyla geliştirilmiş eğitim odaklı bir uygulamadır.Sistem, donanım başlatıldığında bir senkronizasyon (başlangıç) algoritması çalıştırır ve ardından sürekli bir döngü halinde sıralı tarama (Karaşimşek efekti) algoritmasını yürütür.
### 🛠️ Donanım Gereksinimleri
<details>
  <summary>Projenin fiziksel olarak veya Proteus (ISIS) simülasyon ortamında test edilebilmesi için gerekli bileşenler</summary>
  <ol>
    <li><a href="https://store.arduino.cc/">1x Arduino Uno R3 (veya muadili mikrodenetleyici)</a></li>
    <li><a href="https://www.robotistan.com/5mm-kirmizi-led-paketi-10-adet">8x Standart LED (Örn: Kırmızı/Mavi)</a></li>
    <li><a href="https://www.direnc.net/220r-1w-direnc-paketi-50-adet">8x 220 $\Omega$ Direnç (Akım sınırlama amacıyla)</a></li>
    <li><a href="#usage">1x Breadboard ve Jumper Kablolar</a></li>
  </ol>
</details>

## 💻 Kod Yapısı ve Algoritma Analizi
Proje kodu iki ana bölümden (setup ve loop) oluşmakta olup, pin yönetimi dinamik bir dizi üzerinden gerçekleştirilmiştir.

### 1. Global Tanımlamalar ve Pin Matrisi
```sh
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
```
Analiz: LED'lerin bağlı olduğu dijital pinler ardışık olarak bir tamsayı dizisine (array) atanmıştır. Bu yaklaşım, kodun ölçeklenebilirliğini artırır; ilerleyen aşamalarda pin değişiklikleri sadece bu satırdan yönetilebilir.

### 2. Başlatma ve Karşılama Algoritması (void setup)
```sh
void setup() {
  for (int x = 0; x < 8; x++) {
    pinMode(ledPins[x], OUTPUT);
  }
  ```

Giriş/Çıkış Yapılandırması: for döngüsü kullanılarak dizideki 8 dijital pin de mikrodenetleyiciye OUTPUT (Çıkış) olarak deklare edilir.

```sh
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x <= 7; x++) {
      digitalWrite(ledPins[x], HIGH);
    }
    delay(1000);
    for (int x = 0; x < 8; x++) {
      digitalWrite(ledPins[x], LOW);
    }
    delay(1000);
  }
}
```
Sistem Kontrolü (Göz Kırpma): Enerji verildiğinde veya sistem resetlendiğinde, iç içe geçmiş döngüler vasıtasıyla tüm LED'ler aynı anda yüksek lojik seviyeye (HIGH) çekilir. 1000 ms (1 saniye) aktif, 1000 ms pasif (LOW) kalacak şekilde bu işlem 3 kez tekrarlanır. Amaç, donanımın kararlı çalıştığını ve tüm LED hatlarının sağlam olduğunu doğrulamaktır.

### 3. Sonsuz Döngü ve Tarama Algoritması (void loop)
Sistem setup aşamasını geçtikten sonra, ana döngü içerisinde iki aşamalı bir kaydırma algoritması çalıştırır.

#### A. Soldan Sağa Tarama (Artan İndis)
```sh
  for (int x = 0; x < 8; x++) {
    digitalWrite(ledPins[x], HIGH);
    delay(500);
    digitalWrite(ledPins[x], LOW);
  }
```
Mantık: Döngü, dizinin 0. indisinden (2 numaralı pin) başlar ve 7. indise (9 numaralı pin) kadar sırayla ilerler. Her bir LED 500 ms boyunca lojik 1 konumunda kalır, ardından lojik 0 konumuna çekilerek bir sonraki LED'e geçiş sağlanır.

#### B. Sağdan Sola Tarama (Azalan İndis)
```sh
  for (int x = 7; x >= 0; x--) {
    digitalWrite(ledPins[x], HIGH);
    delay(500);
    digitalWrite(ledPins[x], LOW);
  }
}
```
Mantık: Soldan sağa tarama bittiği an, bu kez döngü sayacı tersine çalıştırılır. 7. indisten (9 numaralı pin) başlayarak 0. indise doğru azalan bir sıra takip edilir. Böylece görsel olarak "git-gel" (Karaşimşek) efekti asenkron bir kesmeye uğramadan sonsuz döngüde devam eder.

## 🎯 Eğitimsel Kazanımlar
Bu projeyi inceleyen veya klonlayan bir öğrenci/geliştirici şu kavramları öğrenecektir:

* Mikrodenetleyicilerde Giriş/Çıkış (I/O) yönetimi.

* Bellek optimizasyonu için veri kümelerini Diziler (Arrays) ile yönetme.

* Tekrarlayan görevlerde işlemci yükünü ve kod kalabalığını azaltmak için For Döngüsü kullanımı.

* Zamanlama fonksiyonlarının (delay) yürütme önceliğine etkisi.

### 📄 Lisans
Bu proje MIT Lisansı altında açık kaynak olarak sunulmuştur. Eğitim ve ticari amaçlı projelerde kaynak gösterilerek serbestçe kullanılabilir, değiştirilebilir ve dağıtılabilir.
