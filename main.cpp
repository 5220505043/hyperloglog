//
//  main.cpp
//  HyperLogLog Implementasyonu
//  Mavlyuda Almazova ogr no:5220505043
//  Created by mavlyuda almazova on 13.03.2026.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdint.h>

class HyperLogLog {
private:
    int p;          // Hassasiyet (Precision)
    int m;          // Kova sayısı (2^p)
    double alpha;   // Düzeltme katsayısı
    std::vector<uint8_t> registers;

    // 64-bit Karıştırma (Hash) Fonksiyonu
    uint64_t hash(std::string key) {
        uint64_t h = 0x84222325;
        for (char c : key) {
            h ^= (uint64_t)c;
            h *= 0x100000001b3;
        }
        return h;
    }

    // İlk 1 bitine kadar olan sıfır sayısını bulur (rho)
    uint8_t get_leading_zeros(uint64_t x) {
        if (x == 0) return 64 - p;
        uint8_t count = 1;
        // p bit kova için ayrıldığı için kalan bitlerde arıyoruz
        uint64_t remaining_bits = x << p;
        return __builtin_clzll(remaining_bits | 1) + 1;
    }

public:
    HyperLogLog(int precision = 12) : p(precision) {
        m = 1 << p;
        registers.assign(m, 0);
        
        // Standart Alpha_m değerleri
        if (m == 16) alpha = 0.673;
        else if (m == 32) alpha = 0.697;
        else if (m == 64) alpha = 0.709;
        else alpha = 0.7213 / (1.0 + 1.079 / m);
    }

    void add(std::string item) {
        uint64_t x = hash(item);
        uint32_t idx = x >> (64 - p); // İlk p bit kova indeksi
        uint8_t rho = get_leading_zeros(x);
        registers[idx] = std::max(registers[idx], rho);
    }

    // İki HLL yapısını birleştirme (Mergeability)
    void merge(const HyperLogLog& other) {
        for (int i = 0; i < m; ++i) {
            registers[i] = std::max(registers[i], other.registers[i]);
        }
    }

    double estimate() {
        double sum = 0;
        int empty_buckets = 0;
        for (uint8_t val : registers) {
            sum += std::pow(2.0, -val);
            if (val == 0) empty_buckets++;
        }

        // Harmonik Ortalama Formülü
        double E = alpha * m * m * (1.0 / sum);

        // Küçük veri düzeltmesi (Linear Counting)
        if (E <= 2.5 * m) {
            if (empty_buckets > 0) {
                E = m * std::log((double)m / empty_buckets);
            }
        }
        return E;
    }
};

int main() {
    HyperLogLog hll(12); // m = 4096 kovalar

    // Örnek veri ekleme
    for(int i=0; i<10000; ++i) {
        hll.add("user_" + std::to_string(i));
    }

    std::cout << "Tahmini Benzersiz Sayi: " << hll.estimate() << std::endl;
    return 0;
}
