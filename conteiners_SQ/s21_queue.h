#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using syze_type = size_t;

 private:
  class Node {
   public:
    Node *_pNext;
    value_type _data;
    explicit Node(const_reference data = value_type(), Node *pNext = nullptr)
        : _pNext(pNext), _data(data) {}
  };
  syze_type _size;
  Node *_head;
  Node *_tail;

 public:
  Queue() : _size(0), _head(nullptr), _tail(nullptr) {}
  explicit Queue(std::initializer_list<value_type> const &items)
      : _size(0), _head(nullptr), _tail(nullptr) {
    for (value_type value : items) {
      push(value);
    }
  }
  explicit Queue(const Queue<value_type> &q)
      : _size(0), _head(nullptr), _tail(nullptr) {
    *this = q;
  }
  explicit Queue(Queue &&q) : _size(0), _head(nullptr), _tail(nullptr) {
    *this = std::move(q);
  }
  ~Queue() { clear(); }
  void operator=(Queue &&q) {
    clear();
    swap(q);
  }
  Queue &operator=(const Queue &q) {
    if (this == &q) {
      throw std::invalid_argument("ERROR u can't copy of object youself\n");
    }
    clear();
    Node *current = q._head;
    while (current != nullptr) {
      push(current->_data);
      current = current->_pNext;
    }
    return *this;
  }

  const_reference front() {
    if (empty()) {
      throw std::out_of_range("Error in func front(), list is EMPTY\n");
    }
    return _head->_data;
  }
  const_reference back() {
    if (empty()) {
      throw std::out_of_range("Error in func back(), list is EMPTY\n");
    }
    return _tail->_data;
  }

  bool empty() { return (_size == 0); }
  syze_type size() { return _size; }

  void push(const_reference value) {
    if (_head == nullptr) {
      _head = new Node(value);
      _tail = _head;
    } else {
      if (_head == _tail) {
        _tail = new Node(value);
        _head->_pNext = _tail;
      } else {
        Node *newElement = new Node(value);
        _tail->_pNext = newElement;
        _tail = newElement;
      }
    }
    ++_size;
  }
  value_type pop() {
    if (empty()) {
      throw std::out_of_range("ERROR in func pop(), queue is EMPTY");
    }
    Node *toDel = _head;
    value_type value = toDel->_data;
    _head = _head->_pNext;
    delete toDel;
    toDel = nullptr;
    --_size;
    return value;
  }
  void swap(Queue &q) {
    if (this == &q) {
      throw std::invalid_argument(
          "ERROR in func swap(), can't swap yourself object\n");
    }
    std::swap(_head, q._head);
    std::swap(_tail, q._tail);
    std::swap(_size, q._size);
  }
  void clear() {
    while (_head != nullptr) {
      pop();
    }
    _tail = nullptr;
    _size = 0;
  }
};
}  // namespace s21
