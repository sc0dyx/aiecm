#ifndef FACTOR_HPP
#define FACTOR_HPP

#include <cmath>
#include <gmpxx.h>
#include <iostream>

class UltraFactor {
private:
  /// функция которая автоматически уже подставляет гладкую B в lcm(1, 2, ..., B
  /// - 1, B)
  struct Point {
    mpz_class x;
    mpz_class y;
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}
  };
  mpz_class lcmB_gmp(int B) {
    mpz_class result = 1;

    for (int i = 2; i <= B; i++) {
      mpz_class temp = i;
      mpz_lcm(result.get_mpz_t(), result.get_mpz_t(), temp.get_mpz_t());
    }

    return result;
  } // функция которая возвращает обратный элемент (алгоритм Евклида)
  mpz_class inverse(mpz_class a, mpz_class n) {
    mpz_class s = 0, old_s = 1;
    mpz_class t = 1, old_t = 0;
    mpz_class r = n, old_r = a;

    while (r != 0) {
      mpz_class q = old_r / r;

      mpz_class temp = r;
      r = old_r - q * r;
      old_r = temp;

      temp = s;
      s = old_s - q * s;
      old_s = temp;

      temp = t;
      t = old_t - q * t;
      old_t = temp;
    }

    if (old_s < 0)
      old_s += n;
    return old_s;
  }
  void ecm(mpz_class x, mpz_class y, mpz_class a, mpz_class n, int B) {
    // выбираю кривую
    mpz_class b = (y * y - x * x * x - a * x) % n;
    // для удобства присваиваем точки новым переменным
    mpz_class x_1 = x;
    mpz_class y_1 = y;
    Point P(x_1, y_1)
        // находим гладкую B
        mpz_class Blcm = lcmB_gmp(B);
    // удваиваем точку 2P
    mpz_class lambda =
        ((3 * x_1 * x_1 + a) * inverse(2 * y_1, n)) % n; // находим лямбду
    mpz_class x_2 =
        (lambda * lambda - 2 * x_1) % n; // находим x_2 удвоенной точки
    mpz_class y_2 =
        (lambda * (x_1 - x_2) - y_1) % n; // находим y_2 удвоенной точки
    Point Q(x_2, y_2)
  }
};

#endif // !
