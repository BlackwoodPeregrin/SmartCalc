#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using syze_type = size_t;

 private:
  class Node {
   public:
    Node *_pNext;
    Node *_pPrev;
    value_type _data;
    explicit Node(const_reference data = value_type(), Node *pNext = nullptr,
                  Node *pPrev = nullptr)
        : _pNext(pNext), _pPrev(pPrev), _data(data) {}
  };
  Node *_first;
  Node *_last;
  size_t _size;

 public:
  Stack() : _first(nullptr), _last(nullptr), _size(0) {}
  explicit Stack(std::initializer_list<value_type> const &items)
      : _first(nullptr), _last(nullptr), _size(0) {
    for (value_type value : items) {
      push(value);
    }
  }
  explicit Stack(const Stack<value_type> &s)
      : _first(nullptr), _last(nullptr), _size(0) {
    *this = s;
  }
  explicit Stack(Stack<value_type> &&s)
      : _first(nullptr), _last(nullptr), _size(0) {
    *this = std::move(s);
  }
  ~Stack() { clear(); }
  void operator=(Stack<value_type> &&s) {
    clear();
    swap(s);
  }
  Stack &operator=(const Stack<value_type> &s) {
    if (this == &s) {
      throw std::invalid_argument("ERROR u can't move of object youself\n");
    }
    clear();
    Node *current = s._first;
    while (current != nullptr) {
      push(current->_data);
      current = current->_pNext;
    }
    return *this;
  }

  const_reference top() {
    if (empty()) {
      throw std::out_of_range("ERROR in func top(), stack is EMPTY");
    }
    return _last->_data;
  }
  value_type get_top() {
    if (empty()) {
      throw std::out_of_range("ERROR in func get_top(), stack is EMPTY");
    }
    return _last->_data;
  }

  bool empty() { return _size == 0; }
  syze_type size() { return _size; }

  void push(const_reference value) {
    if (_last == nullptr) {
      _last = new Node(value);
      _first = _last;
    } else {
      if (_first == _last) {
        _last = new Node(value, nullptr, _first);
        _first->_pNext = _last;
      } else {
        Node *newNode = new Node(value, nullptr, _last);
        _last->_pNext = newNode;
        _last = newNode;
      }
    }
    ++_size;
  }
  value_type pop() {
    if (empty()) {
      throw std::out_of_range("ERROR in func pop(), stack is EMPTY");
    }
    Node *toDel = _last;
    value_type value = toDel->_data;
    _last = _last->_pPrev;
    delete toDel;
    toDel = nullptr;
    --_size;
    return value;
  }
  void swap(Stack &other) {
    if (this == &other) {
      throw std::invalid_argument(
          "ERROR in func swap(), can't swap yourself object\n");
    }
    std::swap(_last, other._last);
    std::swap(_first, other._first);
    std::swap(_size, other._size);
  }
  void clear() {
    while (_last != nullptr) {
      pop();
    }
    _first = nullptr;
    _size = 0;
  }
};
}  // namespace s21
