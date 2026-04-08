# Problem 061 - 复数

**ACMOJ Problem ID**: 2686

## Table of Contents

- [Problem 061 - 复数](#problem-061-复数)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

Implement complex number class with operations, exceptions, header file structure.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **2686. 复数** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/061/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

请你实现一个简单的复数类。

我们使用代数表示法来表示复数，即 $a+b\mathrm{i}$，其中 $a$ 为实部，$b$ 为虚部。

你需要完成一个基本的复数类，其需要满足以下的功能。

#### 构造函数

对于复数类，我们有以下几个最基本的要求:

1. 默认构造函数，默认复数值为 $0$ 。

   ```cpp
complex z; // z = 0;
```

2. 可以用一个数值构造一个复数类。此时虚部为 $0$ ，实部为传入的值。

   ```cpp
complex z1 = 1;        // z = 1;
complex z2 = 2.22;     // z = 2.22;
complex z3(114.514);   // z = 114.514;
```

3. 可以使用两个数值构造一个复数类。此时第一个数值为实部，第二个数值为虚部。

   ```cpp
complex z1(1, 2);       // z = 1 + 2i;
complex z2(2.22, 3.33); // z = 2.22 + 3.33i;
```

4. 拷贝构造和拷贝赋值函数，可以从其他类拷贝构造或拷贝赋值。

   ```C++
complex x;     // x = 0;
complex y = x; // y = x = 0;
x = y = 2; // x = y = 2;
```

#### 访问实部和虚部

我们需要实现两个函数 `real(),imag()`，分别返回复数的实部和虚部的引用。

```C++
complex z(1, 2);
std::cout << z.real() << "," << z.imag() << std::endl; // 输出 1,2
z.real() = 3;
z.imag() = 4; // z = 3+4i
```

#### 比较函数

我们要求实现比较运算符 `==` 用于判断两个复数是否相等。**由于浮点数有精度问题，我们要求两个复数的实部和虚部的差的绝对值都小于 $10^{-6}$ 时，认为两个复数相等。**

$$
z_1 =a+b\mathrm{i},z_2=c+d\mathrm{i}
$$

$$
z_1=z_2 \iff |a-c|<10^{-6} \;\mathrm{and}\; |b-d|<10^{-6}
$$

```C++
complex a = 1, b = 2, c = 2;
std::cout << int(a == b) << std::endl; // 输出 0
std::cout << int(b == c) << std::endl; // 输出 1
```

#### 四则运算

加减乘除的表现和正常的数学运算一致。还包含一个取负数的运算符 `-`，和一个取共轭复数（虚部相反）的运算符 `~`。

特别地，对于除法，如果除数为 $0$（$|a|<10^{-6} \text{ }\mathrm{and}\text{ } |b|<10^{-6}$），你需要抛出异常 `divided_by_zero`。**其定义在下发模板中给出**。

```C++
complex a = 1, b = 0;
try {
    a /= b;
} catch(const std::exception &err) {
    // 此处应该输出(不包含引号) "complex divided by zero!"
    std::cout << err.what(); 
}
```

#### 输出函数

输出运算符的输出格式为 `[/-]<实部>[+/-]<虚部>i`，其中实部和虚部都是浮点数，保留 $6$ 位小数。

- 如果实部为负数（$real<-10^{-6}$），则输出 `-` 号，否则不输出符号。
- 如果虚部为负数（$imag<-10^{-6}$），则输出 `-` 号，否则输出 `+` 号。

```C++
complex a(-2,0);
complex b(0,-2);
complex c(1,-1e-10);
complex d(-1e-10,1);
std::cout << a << std::endl; // 输出 -2.000000+0.000000i
std::cout << b << std::endl; // 输出 0.000000-2.000000i
std::cout << c << std::endl; // 输出 1.000000+0.000000i  用加号，因为它的虚部绝对值在 10^-6 以内，认为是 0。 属于非负数
std::cout << d << std::endl; // 输出 0.000000+1.000000i  实部无符号，因为它的绝对值在 10^-6 以内，认为是 0。 属于非负数
```

#### 类型转换

我们的复数类要支持转化为 `bool` 类型，当且仅当复数的值为 $0$（$|a|<10^{-6} \text{ }\mathrm{and}\text{ } |b|<10^{-6}$）时，转化为 `false` ，否则转化为 `true` 。

```cpp
complex a; // 默认初始化为 0
if (a) {
    std::cout << "a is not zero!" << std::endl;
} else {
    std::cout << "a is zero!" << std::endl; // 输出 a is zero!
}
```

<!-- ## 模长辐角

我们要求实现 `abs(),arg()` 两个函数，分别返回复数的模长和辐角（弧度制，(-pi, pi]）。

```cpp
complex z(3, 4);
std::cout << z.abs() << std::endl; // 输出 5
std::cout << z.arg() << std::endl; // 输出 0.927295
complex x(-3, -4);
std::cout << x.abs() << std::endl; // 输出 5
std::cout << x.arg() << std::endl; // 输出 -2.214297
```

你需要用到 `cmath` 中的函数，见 [提示](#提示)

## 开 $n$ 次根

实现 `std::vector<complex> root(int n)` 开根函数，返回一个 `std::vector` ，其中包含了复数的 $n$ 次根。（我们确保 $n\ge 1$）

给定复数 $z = a+bi$，$r$ 为其模长，$\theta$ 为其辐角，其 $n$ 次根的公式为：

$$
w_k = \sqrt[n]{r} \left( \cos \frac{\theta + 2k\pi}{n} + i \sin \frac{\theta + 2k\pi}{n} \right)
$$

其中，$w_k$ 为 $z$ 的第 $k$ 个 $n$ 次根，$k=0,1,2,\dots,n-1$

```cpp
complex z(1, 0);
std::vector<complex> res = z.root(2);
for (auto &i : res) {
    std::cout << i << std::endl;
}
/*
1.000000+0.000000i
-1.000000+0.000000i
*/
```

你需要用到 `cmath` 中的函数，见 [提示](#提示) -->

#### 其他说明

需要特别注意的是，**即使你没有实现 `complex` 的部分函数，你也依然需要保留这些函数的声明，否则将无法通过编译**，即使这个测试点没有用到这些函数。

如果你提交的代码中全部 `CE` ，并且具体报错信息里面提示 `undefined reference to 'Some_of_your_member_functions_are_missing()'` ，说明你提交的代码里缺少了某些成员函数的声明。请与下发模板文件进行比对，补全缺少的成员函数的声明，再次提交即可。

如果你正确地保留了声明，但是没有实现部分功能，那么你只会在对应的测试点出现 `CE` (报错信息是 `undefined reference to xxx(具体函数)`) ，其他没有用到这些功能的测试点不会受到影响。

#### 提示

你可能需要用到 `<cmath>` 库中的一些函数：

```cpp
double fabs(double x); // 返回 x 的绝对值
```

对于输出的控制，你可以使用 `<iomanip>` 中的 `std::fixed` 和 `std::setprecision` 来控制输出的精度。

在下发文件 `complex.hpp` 中，我们提供了一个函数 `sign` 用于判断一个浮点数的符号，你可以直接使用：

```cpp
// 判断 x 的符号，返回 1 表示 x > 0, 返回 0 表示 x = 0, 返回 -1 表示 x < 0
const double eps = 1e-6;
inline int sign(double x) {
    return (x > eps) - (x < -eps);
}
```


#### 下发模板

**你需要完善并提交下方模板即可。**

```cpp
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
  complex();                   // 默认构造函数 0+0i
  complex(double a);           // 构造函数 a+0i
  complex(double a, double b); // 构造函数 a+bi

  double &real(); // 返回实部
  double &imag(); // 返回虚部

  complex operator-() const; // 返回负数
  complex operator~() const; // 返回共轭复数

  complex operator+(const complex &rhs) const; // 加法
  complex operator-(const complex &rhs) const; // 减法
  complex operator*(const complex &rhs) const; // 乘法
  complex operator/(const complex &rhs) const; // 除法

  complex &operator+=(const complex &rhs);
  complex &operator-=(const complex &rhs);
  complex &operator*=(const complex &rhs);
  complex &operator/=(const complex &rhs);

  bool operator==(const complex &rhs) const; // 判断相等

  explicit operator bool() const; // 转换为 bool

  friend std::ostream &operator<<(std::ostream &os, const complex &x); // 输出
};

} // namespace sjtu

#endif
```

### Input Format

See the problem description above.

### Output Format

See the problem description above.

### Samples

No sample data provided for this problem.

### Data Constraints

|  Testcases No.  | 前置 Test  | 额外考察的内容                                  | 分数   |
|  -------------- | ------------ | ----------------------------------------------- | ------ |
| $1$         | **无** | 考察所有构造函数、赋值操作、访问实部和虚部         | $10$ |
| $2$         | $1$        | 考察单目运算符 `~` (取共轭) 和 `-` (取负数) | $10$ |
| $3$         | $1$        | 考察加法和减法 `+,-,+=,-=`               | $10$ |
| $4$         | $1$        | 考察乘法和除法 `*,/,*=,/=` （无异常处理）          | $10$ |
| $5$         | $1$        | 考察类型转换运算符 `bool`       | $10$ |
| $6$         | $1$        | 考察比较运算符 `==`            | $10$ |
| $7$         | $1$        | 考察输出函数（不要求小数位数，只要你的输出与答案误差在 $10^{-4}$ 内即被认为正确）  | $10$ |
| $8$         | $7$        | 考察输出函数（你必须严格按照我们的要求）  | $10$ |
| $9$         | $2,3,4$    | 无 (四则运算测试，含异常处理)     | $10$ |
| $10$        | $5,6,7,9$  | 无 (综合压力测试，含异常处理)      | $10$ |

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 128 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/061/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
