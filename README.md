# Класс String: Реализация и Тестирование

## Описание проекта
Этот проект представляет реализацию пользовательского класса String, который служит альтернативой стандартному классу std::string. Класс поддерживает основные операции над строками, такие как копирование, присваивание, объединение, доступ по индексу, сравнение и пр. Проект разработан для изучения базовых принципов работы с памятью и строками на языке C++.

## Основные функции класса String:
1. **Конструкторы:**

   - Конструктор по умолчанию.
   - Конструктор от C-строки.
   - Конструктор копирования.
   - Конструктор от символа.

2. **Методы для работы с данными:**
   - Data() — возвращает указатель на строку.
   - CStr() — возвращает C-строку (завершается нулевым символом).

3. **Операции с длиной строки:**
   - Size() — возвращает размер строки.
   - Length() — возвращает длину строки (аналогично Size()).
   - Capacity() — возвращает текущую вместимость строки.

4. **Методы для работы с символами:**
   - Front() — возвращает первый символ строки.
   - Back() — возвращает последний символ строки.
   - At() — доступ к символу по индексу с проверкой границ.

5. **Операции изменения строки:**
   - PushBack() — добавляет символ в конец строки.
   - Resize() — изменяет размер строки, при необходимости заполняет строку указанным символом.
   - Reserve() — увеличивает выделенную память под строку.
   - ShrinkToFit() — уменьшает емкость до текущего размера строки.
   - Clear() — очищает строку.
   - Swap() — обменивает содержимое двух строк.

6. **Операторы:**
   - Оператор присваивания.
   - Операторы сравнения строк (<, >, <=, >=, ==, !=).
   - Оператор сложения строк.

## Структура проекта
+ cppstring.h — заголовочный файл, содержащий объявление класса String и его методов.
+ cppstring.cpp — файл с реализацией методов класса String.
+ string_public_test.cpp — файл с тестами для проверки функциональности класса.
+ CMakeLists.txt — Файл конфигурации сборки для CMake.

## Зависимости
+ C++17 или новее.
+ Catch2 — Фреймворк для модульного тестирования.

## Установка и сборка
Шаг 1: Клонирование репозитория
```bash
git clone <ссылка на репозиторий>
cd <название проекта>
```
Шаг 2: Сборка проекта
1. Создайте директорию для сборки:
```bash
mkdir build
cd build
```
2. Сборка с использованием CMake:
```bash
cmake ..
make
```
Шаг 3: Запуск тестов

После успешной сборки вы можете запустить тесты:
```bash
./string_public_test
```

## Пример использования
```cpp
#include <iostream>
#include "cppstring.h"

int main() {
  String str("Hello");
  String str2("World");
  String str3 = str + ", " + str2 + "!";
  std::cout << str3 << '\n';  // Hello, World!

  String str4 = str3;
  std::cout << str4 << '\n';  // Hello, World!

  char first_char = str[0];
  char last_char = str[str.Size() - 1];

  std::cout << "Первый символ: " << first_char << '\n';    // Первый символ: H
  std::cout << "Последний символ: " << last_char << '\n';  // Последний символ: o

  String str5("Hello");
  if (str == str5) {
    std::cout << "Строки равны" << '\n';  // Строки равны
  } else {
    std::cout << "Строки не равны" << '\n';
  }

  String str6;
  str6 = str2;
  std::cout << str6 << '\n';  // World

  const char* c_style_str = str3.CStr();
  std::cout << "C-style строка: " << c_style_str << '\n';  // C-style строка: Hello, World!
  return 0;
}
```

## Лицензия
Проект распространяется под лицензией MIT. Подробнее см. файл LICENSE.

## Авторство
+ Реализация класса String — Ирина Селях.
+ Тесты, используемые в данном проекте, были взяты из внешних источников для проверки корректности работы кода.
