#pragma once

template <typename T> class Tree;

template <typename T> class Node {
  friend class Tree<T>;

public:
  Node(const T value);
  ~Node();

private:
  Node<T> *parent = nullptr;
  Node<T> *left = nullptr;
  Node<T> *right = nullptr;
  T value;
  int deep = 0;
};

template <typename T> Node<T>::Node(const T value) : value(value) {
  // std::cout << "constructor\n";
}

template <typename T> Node<T>::~Node() {
  // std::cout << "destructor\n";
}
