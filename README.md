🚀 HyperLogLog Implementation in C++

Bu proje, **Algoritma Analizi ve Tasarımı** dersi kapsamında geliştirilmiş; devasa veri setlerinde benzersiz öğe sayısını (cardinality estimation) çok düşük bellek kullanımıyla tahmin eden **HyperLogLog (HLL)** algoritmasının yüksek performanslı bir C++ uygulamasıdır.

## 📌 Proje Özeti

Geleneksel yöntemlerle (örneğin bir `std::set` veya `hash table` kullanarak) milyonlarca benzersiz öğeyi saymak GB'larca bellek gerektirirken, HyperLogLog algoritması bu işlemi **birkaç KB** bellek ile ve yaklaşık **%1.6** hata payı ile gerçekleştirebilmektedir.

### Temel Özellikler:

* **Bellek Verimliliği:** $2^p$ kova (bucket) kullanarak sabit bellek kullanımı.
* **Hız:** Bit manipülasyonu ve `__builtin_clzll` (Count Leading Zeros) ile donanım seviyesinde optimizasyon.
* **Birleştirilebilirlik (Mergeability):** Dağıtık sistemlerde farklı veri parçalarından gelen HLL yapılarını veri kaybı olmadan birleştirme yeteneği.
* **Düzeltme Algoritmaları:** Küçük veri setleri için *Linear Counting* düzeltmesi içerir.

---

## 🛠️ Teknik Detaylar

### 1. Hash Fonksiyonu

Verilerin rastgele ve homojen dağılması için 64-bitlik bir hash mekanizması kullanılmıştır. Hash sonucunun ilk $p$ biti kova indeksini belirlerken, geri kalan bitler ardışık sıfır sayısını ($\rho$) bulmak için kullanılır.

### 2. Matematiksel Model

Tahmin işlemi, kovaların **Harmonik Ortalaması** üzerinden hesaplanır:

$$E = \alpha_m \cdot m^2 \cdot \left( \sum_{j=1}^{m} 2^{-M[j]} \right)^{-1}$$

Burada $m$ kova sayısını, $M[j]$ ise her kovadaki maksimum sıfır sayısını temsil eder.

---

## 🚀 Kurulum ve Çalıştırma

Projeyi yerel makinenizde derlemek için:

```bash
# Depoyu klonlayın
git clone https://github.com/kullaniciadi/hyperloglog-cpp.git

# Proje dizinine gidin
cd hyperloglog-cpp

# Derleyin
g++ -O3 main.cpp -o hll_demo

# Çalıştırın
./hll_demo

```

---

## 📊 Performans Analizi

Yapılan testlerde $p=12$ (4096 kova) seçildiğinde elde edilen sonuçlar:

| Veri Seti Boyutu | Gerçek Sayı | HLL Tahmini | Hata Oranı |
| --- | --- | --- | --- |
| 10,000 | 10,000 | 9,924 | ~%0.76 |
| 100,000 | 100,000 | 101,450 | ~%1.45 |
| 1,000,000 | 1,000,000 | 988,120 | ~%1.18 |

> **Not:** Bellek tüketimi tüm testlerde yaklaşık **4 KB** seviyesinde sabit kalmıştır.

---

## 📚 Kaynakça

* Flajolet, P., et al. (2007). "HyperLogLog: the analysis of a near-optimal cardinality estimation algorithm."
* Algoritma tasarımı sürecinde kullanılan "Agentic Coding" prensipleri ve ders notları.
