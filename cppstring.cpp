// Copyright (c) 2024 Irina Selyakh
//
// Данное программное обеспечение распространяется на условиях лицензии MIT.
// Подробности смотрите в файле LICENSE

#include "cppstring.h"
#include <utility>
#include <iostream>

String::String(const String& other) {
  if (other.str_ == nullptr) {
    str_ = nullptr;
    size_ = capacity_ = 0;
  } else {
    str_ = new char[other.size_ + 1];
    size_ = other.size_;
    capacity_ = other.capacity_;
    std::copy(other.str_, other.str_ + size_, str_);
    str_[size_] = '\0';
  }
}

String::String(size_t count, const char symbol) {  // NOLINT
  if (count == 0) {
    str_ = nullptr;
    size_ = capacity_ = 0;
  } else {
    str_ = new char[count + 1];
    size_ = count;
    capacity_ = count;
    for (size_t i = 0; i < count; ++i) {
      str_[i] = symbol;
    }
    str_[size_] = '\0';
  }
}

String& String::operator+=(const String& other) {
  if (size_ + other.size_ > capacity_) {
    capacity_ = std::max(2 * capacity_, size_ + other.size_);
    const auto new_str = new char[capacity_ + 1];
    std::copy(str_, str_ + size_, new_str);
    delete[] std::exchange(str_, new_str);
  }
  std::copy(other.str_, other.str_ + other.size_, str_ + size_);
  size_ += other.size_;
  str_[size_] = '\0';
  return *this;
}

String& String::operator=(const String& other) {
  if (str_ == nullptr && other.str_ == nullptr) {
    return *this;
  }
  if (other.str_ != nullptr) {
    auto new_str = new char[other.size_ + 1];
    std::copy(other.str_, other.str_ + other.size_ + 1, new_str);
    delete[] std::exchange(str_, new_str);
    size_ = other.size_;
    capacity_ = other.capacity_;
  } else {
    delete[] str_;
    str_ = new char[1];
    size_ = 0;
    str_[size_] = '\0';
  }
  return *this;
}

String& String::operator=(const char& symbol) {
  if (str_ == nullptr && symbol == '\0') {
    return *this;
  }
  auto new_str = new char[2];
  *new_str = symbol;
  delete[] str_;
  str_ = new_str;
  size_ = capacity_ = 1;
  new_str[size_] = '\0';
  return *this;
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

void String::PushBack(const char& symbol) {
  if (size_ + 1 > capacity_) {
    capacity_ = std::max(2 * capacity_, size_ + 1);
    auto new_str = new char[capacity_ + 1];
    std::copy(str_, str_ + size_, new_str);
    delete[] std::exchange(str_, new_str);
  }
  str_[size_] = symbol;
  str_[++size_] = '\0';
}

void String::Resize(const size_t new_size, const char& symbol) {
  if (Size() > new_size) {
    size_ = new_size;
    str_[size_] = '\0';
  } else {
    const auto new_str = new char[new_size + 1];
    std::copy(str_, str_ + size_, new_str);
    auto copy_new_size = new_size;
    while (size_ != copy_new_size) {
      new_str[copy_new_size - 1] = symbol;
      --copy_new_size;
    }
    delete[] std::exchange(str_, new_str);
    size_ = new_size;
    str_[size_] = '\0';
  }
  if (capacity_ < new_size) {
    capacity_ = 2 * new_size;
  }
}

void String::Reserve(const size_t new_capacity) {
  if (new_capacity > capacity_) {
    capacity_ = new_capacity;
    const auto new_str = new char[capacity_ + 1];
    std::copy(str_, str_ + size_, new_str);
    delete[] std::exchange(str_, new_str);
  }
}

void String::ShrinkToFit() {
  capacity_ = std::min(capacity_, size_);
}

void String::Clear() {
  delete[] str_;
  str_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
  if (!str.Empty()) {
    os << str.Data();
    return os;
  }
  return os;
}