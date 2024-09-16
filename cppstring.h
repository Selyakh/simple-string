// Copyright (c) 2024 Irina Selyakh
//
// Данное программное обеспечение распространяется на условиях лицензии MIT.
// Подробности смотрите в файле LICENSE

#ifndef MY_STRING_H
#define MY_STRING_H
#include <stdexcept>
#include <cstring>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
  char* str_;
  size_t size_;
  size_t capacity_;

 public:
  String() : str_(nullptr), size_(0), capacity_(0) {
  }

  String(const char* other, size_t size) : str_(new char[size + 1]), size_(size), capacity_(size) {
    std::copy(other, other + size, str_);
    str_[size] = '\0';
  }

  String(const String& other);

  String(const char* other) : String(other, std::strlen(other)) {  // NOLINT
  }

  String(const char symbol) : str_(new char[2]) {  // NOLINT
    *str_ = symbol;
    size_ = capacity_ = 1;
    str_[size_] = '\0';
  }

  String(size_t count, const char symbol);

  String& operator+=(const String& other);

  String& operator=(const String& other);  // копируюзее присваивание

  String& operator=(const char& symbol);

  void Swap(String& other);

  [[nodiscard]] const char* Data() const {
    return str_;
  }

  [[nodiscard]] const char* Data() {
    return str_;
  }

  [[nodiscard]] const char* CStr() const {
    return str_;
  }
  [[nodiscard]] char* CStr() {
    return str_;
  }

  [[nodiscard]] size_t Size() {
    return size_;
  }

  [[nodiscard]] size_t Size() const {
    return size_;
  }

  [[nodiscard]] size_t Length() {
    return size_;
  }

  [[nodiscard]] size_t Length() const {
    return size_;
  }

  [[nodiscard]] size_t Capacity() {
    return capacity_;
  }

  [[nodiscard]] size_t Capacity() const {
    return capacity_;
  }

  char& operator[](size_t idx) {
    return str_[idx];
  }

  const char& operator[](size_t idx) const {
    return str_[idx];
  }

  char& At(size_t idx) {  // возвращает ссылку на символ строки по индексу idx
    if (idx < size_) {
      return str_[idx];
    }
    throw StringOutOfRange{};
  }

  const char& At(size_t idx) const {
    if (idx < size_) {
      return str_[idx];
    }
    throw StringOutOfRange{};
  }

  [[nodiscard]] char& Front() {
    return *str_;
  }

  [[nodiscard]] char& Front() const {
    return *str_;
  }

  [[nodiscard]] char& Back() {
    return str_[size_ - 1];
  }
  [[nodiscard]] char& Back() const {
    return str_[size_ - 1];
  }

  [[nodiscard]] bool Empty() const {
    return Size() == 0;
  }

  void PopBack() {
    if (size_ > 0) {
      str_[--size_] = '\0';
    }
  }

  void PushBack(const char& symbol);

  void Resize(const size_t new_size, const char& symbol);  // изменяет размер строки на новый размер new_size, заполняя
                                                           // новые элементы символом symbol, если строка увеличивается

  void Reserve(const size_t new_capacity);  // резерв памяти под строку

  void ShrinkToFit();  // уменьшает ёмкость строки

  void Clear();

  ~String() {
    delete[] str_;
  }

  friend std::ostream& operator<<(std::ostream& os, const String& str);
};

inline String operator+(const String& lhs, const String& rhs) {
  String result(lhs.Size() + rhs.Size(), '\0');
  std::copy(lhs.Data(), lhs.Data() + lhs.Size(), result.CStr());
  std::copy(rhs.Data(), rhs.Data() + rhs.Size(), result.CStr() + lhs.Size());
  return result;
}

[[nodiscard]] inline bool operator<(const String& lhs, const String& rhs) {
  for (size_t i = 0; i < lhs.Size() && i < rhs.Size(); ++i) {
    if (lhs[i] < rhs[i]) {
      return true;
    }
    if (lhs[i] > rhs[i]) {
      return false;
    }
  }
  return (lhs.Size() < rhs.Size());
  return false;
}

[[nodiscard]] inline bool operator>(const String& lhs, const String& rhs) {
  return rhs < lhs;
}

[[nodiscard]] inline bool operator<=(const String& lhs, const String& rhs) {
  return !(rhs < lhs);
}

[[nodiscard]] inline bool operator>=(const String& lhs, const String& rhs) {
  return !(lhs < rhs);
}

[[nodiscard]] inline bool operator==(const String& lhs, const String& rhs) {
  if (lhs.Size() != rhs.Size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.Size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

[[nodiscard]] inline bool operator!=(const String& lhs, const String& rhs) {
  return !(lhs == rhs);
}

#endif