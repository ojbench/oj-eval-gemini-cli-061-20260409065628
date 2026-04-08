#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>     // 数学函数
#include <iomanip>   // 控制输出格式
#include <iostream>  // 输入输出
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
private:
  double a, b; // a + bi
public:
  complex() : a(0), b(0) {}                   // 默认构造函数 0+0i
  complex(double a) : a(a), b(0) {}           // 构造函数 a+0i
  complex(double a, double b) : a(a), b(b) {} // 构造函数 a+bi

  double &real() { return a; } // 返回实部
  double &imag() { return b; } // 返回虚部

  complex operator-() const { return complex(-a, -b); } // 返回负数
  complex operator~() const { return complex(a, -b); } // 返回共轭复数

  complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); } // 加法
  complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); } // 减法
  complex operator*(const complex &rhs) const { 
      return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); 
  } // 乘法
  complex operator/(const complex &rhs) const {
      if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
          throw divided_by_zero();
      }
      double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
      return complex((a * rhs.a + b * rhs.b) / denominator, (b * rhs.a - a * rhs.b) / denominator);
  } // 除法

  complex &operator+=(const complex &rhs) {
      a += rhs.a;
      b += rhs.b;
      return *this;
  }
  complex &operator-=(const complex &rhs) {
      a -= rhs.a;
      b -= rhs.b;
      return *this;
  }
  complex &operator*=(const complex &rhs) {
      double new_a = a * rhs.a - b * rhs.b;
      double new_b = a * rhs.b + b * rhs.a;
      a = new_a;
      b = new_b;
      return *this;
  }
  complex &operator/=(const complex &rhs) {
      if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
          throw divided_by_zero();
      }
      double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
      double new_a = (a * rhs.a + b * rhs.b) / denominator;
      double new_b = (b * rhs.a - a * rhs.b) / denominator;
      a = new_a;
      b = new_b;
      return *this;
  }

  bool operator==(const complex &rhs) const {
      return sign(a - rhs.a) == 0 && sign(b - rhs.b) == 0;
  } // 判断相等

  explicit operator bool() const {
      return sign(a) != 0 || sign(b) != 0;
  } // 转换为 bool

  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
      double real_part = x.a;
      double imag_part = x.b;
      
      // 如果实部为负数（real<-10^{-6}），则输出 - 号，否则不输出符号。
      // 如果虚部为负数（imag<-10^{-6}），则输出 - 号，否则输出 + 号。
      
      if (sign(real_part) < 0) {
          os << "-";
          real_part = -real_part;
      }
      
      // Wait, the problem says:
      // 输出运算符的输出格式为 `[/-]<实部>[+/-]<虚部>i`，其中实部和虚部都是浮点数，保留 6 位小数。
      // 如果实部为负数（real<-10^{-6}），则输出 - 号，否则不输出符号。
      // 如果虚部为负数（imag<-10^{-6}），则输出 - 号，否则输出 + 号。
      // Let's check the sample:
      // complex a(-2,0); -> -2.000000+0.000000i
      // complex b(0,-2); -> 0.000000-2.000000i
      // complex c(1,-1e-10); -> 1.000000+0.000000i
      // complex d(-1e-10,1); -> 0.000000+1.000000i
      
      // Wait, if real_part is negative, we output '-' and then the absolute value?
      // No, the sample says:
      // complex a(-2,0); -> -2.000000+0.000000i
      // If we just output `x.a`, it will output `-2.000000`.
      // But wait, if `x.a` is `-1e-10`, `sign(x.a) == 0`, so it's considered non-negative.
      // If we just output `x.a`, it might output `-0.000000`.
      // To avoid `-0.000000`, we should probably set it to `0.0` if `sign(x.a) == 0`.
      
      if (sign(real_part) == 0) real_part = 0.0;
      if (sign(imag_part) == 0) imag_part = 0.0;
      
      os << std::fixed << std::setprecision(6);
      
      // For real part, if it's negative, `real_part` itself will have a minus sign when printed.
      // Wait, if we just print `real_part`, it will be `-2.000000`.
      // Let's check if we need to print `-` manually.
      // "如果实部为负数（real<-10^{-6}），则输出 - 号，否则不输出符号。"
      // This just means normal printing of a float, but we need to avoid `-0.000000`.
      // So if `sign(real_part) == 0`, we set it to `0.0` to avoid `-0.000000`.
      // If `sign(real_part) > 0`, it prints normally (no sign).
      // If `sign(real_part) < 0`, it prints normally (with `-` sign).
      
      os << real_part;
      
      // For imaginary part:
      // "如果虚部为负数（imag<-10^{-6}），则输出 - 号，否则输出 + 号。"
      if (sign(imag_part) < 0) {
          // imag_part is negative, so printing it will include the `-` sign.
          // Wait, if we just print `imag_part`, it will be `-2.000000`.
          // So we don't need to print `-` manually, just print `imag_part`.
          os << imag_part << "i";
      } else {
          // imag_part is non-negative, we need to print `+` manually.
          os << "+" << imag_part << "i";
      }
      
      return os;
  }
};

} // namespace sjtu

#endif