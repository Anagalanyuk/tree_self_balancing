#include <Tree.h>
#include <iostream>

template <typename T> Tree<T>::Tree() {
  // std::cout << "constructor" << endl;
}

template <typename T> Tree<T>::Tree(const Tree &source) {
  this->Copy(source.GetRoot());
}

template <typename T>
Tree<T>::Tree(Tree &&source) : root(source.root), size(source.size) {
  source.root = nullptr;
  source.size = 0;
  //	std::cout << "move" << endl;
}

template <typename T> Tree<T>::~Tree() { Clear(); }

template <typename T> Tree<T> &Tree<T>::operator=(const Tree &right) {

  this->Clear();
  this->Copy(right.GetRoot());
  return *this;
}

template <typename T> Tree<T> &Tree<T>::operator=(Tree &&right) {
  // std::cout << "move";
  this->Clear();

  root = right.root;
  size = right.size;
  right.root = nullptr;
  right.size = 0;
  return *this;
}

template <typename T> void Tree<T>::Add(const T item) {
  Node<T> *newNode = new Node<T>(item);
  Node<T> *perent = nullptr;
  bool result = false;

  if (root == nullptr) {
    root = newNode;
    result = true;
  } else {
    Node<T> *node = root;

    while (node->value != item) {
      perent = node;

      if (node->value < item) {
        if (node->right != nullptr) {
          node = node->right;
        } else {
          newNode->perent = perent;
          perent->right = newNode;
          result = true;
          break;
        }
      } else {
        if (node->left != nullptr) {
          node = node->left;
        } else {
          newNode->perent = perent;
          perent->left = newNode;
          result = true;
          break;
        }
      }
    }
  }
  if (result == false) {
    // std::cout << "delete";
    delete newNode;
  } else {
    size += 1;
  }
}

template <typename T> void Tree<T>::Clear() {
  Clear(this->GetRoot());
  root = nullptr;
  size = 0;
}

template <typename T> const Node<T> *Tree<T>::GetRoot() const { return root; }

template <typename T> void Tree<T>::ShowRootValue() const {
  std::cout << root->value << std::endl;
}

template <typename T> unsigned int Tree<T>::GetSize() const { return size; }

template <typename T>
const Node<T> *Tree<T>::Maximum(const Node<T> *const node) const {
  const Node<T> *max = node;
  while (max->right != nullptr) {
    max = max->right;
  }
  return max;
}

template <typename T>
const Node<T> *Tree<T>::Minimum(const Node<T> *const node) const {
  const Node<T> *min = node;

  while (min->left != nullptr) {
    min = min->left;
  }
  std::cout << "\nmin:" << min->value;
  return min;
}

template <typename T>
const Node<T> *Tree<T>::Next(const Node<T> *const node) const {
  const Node<T> *result = nullptr;

  if (node != nullptr) {
    const Node<T> *temp = node;
    if (temp->right != nullptr) {
      if (temp->right->left != nullptr) {
        temp = temp->right;
        while (temp->left != nullptr) {
          temp = temp->left;
        }
        result = temp;
      } else {
        result = temp->right;
      }
    } else {
      while (temp->perent->value < node->value) {
        temp = temp->perent;
        if (temp->perent == nullptr) {
          break;
          result = nullptr;
        }
      }
      if (temp->perent != nullptr) {
        result = temp->perent;
      } else if (node->left == nullptr && node->right == nullptr) {
        result = temp->perent;
      }
    }
  }
  std::cout << result->value;
  return result;
}

template <typename T>
const Node<T> *Tree<T>::Previous(const Node<T> *const node) const {
  const Node<T> *result = node;
  if (node != nullptr) {
    const Node<T> *temp = node;
    if (temp->left != nullptr) {
      if (temp->left->right != nullptr) {
        temp = temp->left->right;
        while (temp->right != nullptr) {
          temp = temp->right;
        }
        result = temp;
      } else {
        result = temp->left;
      }
    } else {

      while (temp->perent->value > node->value) {
        temp = temp->perent;
        if (temp->perent == nullptr) {
          break;
          result = nullptr;
        }
      }
      if (temp->perent != nullptr) {
        result = temp->perent;
      } else if (node->left == nullptr && node->right == nullptr) {
        result = temp->perent;
      }
    }
  }
  std::cout << "\nprevios:" << result->value;
  // std::cout << "\nnode:   " << node->value;
  return result;
}

template <typename T> void Tree<T>::Print(const Node<T> *const node) const {
  if (node != nullptr) {
    Print(node->left);
    std::cout << node->value << " ";
    Print(node->right);
  }
}

template <typename T> bool Tree<T>::Remove(const T item) {
  bool result = false;

  const Node<T> *temp = this->Search(item);
  if (temp != nullptr) {
    // std::cout << "\nresult:" << temp->value;

    if (temp->perent == nullptr) {
      if (temp->left != nullptr && temp->right == nullptr) {
        root = temp->left;
        size -= 1;
        result = true;
        delete temp;
      } else {
        root = temp->right;
        temp->right->perent = nullptr;
        Node<T> *sfree = temp->right;
        if (sfree != nullptr) {
          while (sfree->left != nullptr) {
            sfree = sfree->left;
          }
        }
        sfree->left = temp->left;
        temp->left->perent = sfree;
        size -= 1;
        result = true;
        delete temp;
      }
    } else {
      if (temp->right != nullptr) {
        temp->right->perent = temp->perent;
        if (temp->right->value > temp->perent->value) {
          temp->perent->right = temp->right;
        } else {
          temp->perent->left = temp->right;
        }
        if (temp->left != nullptr) {
          Node<T> *sfree = temp->right;
          while (sfree->left != nullptr) {
            sfree = sfree->left;
          }
          sfree->left = temp->left;
          temp->left->perent = sfree;
        }
        size -= 1;
        result = true;
        delete temp;
      } else if (temp->left != nullptr) {
        temp->left->perent = temp->perent;
        temp->perent->left = temp->left;
        size -= 1;
        result = true;
        delete temp;
      } else {
        if (temp->perent->left != nullptr &&
            temp->perent->left->value == temp->value) {
          temp->perent->left = nullptr;
          size -= 1;
          result = true;
          delete temp;
        } else {
          temp->perent->right = nullptr;
          size -= 1;
          result = true;
          delete temp;
        }
      }
    }
  }

  return result;
}

template <typename T> const Node<T> *Tree<T>::Search(const T item) const {
  const Node<T> *temp = root;
  const Node<T> *result = nullptr;
  while (temp != nullptr) {
    if (temp->value == item) {

      result = temp;
      // std::cout << "\nSearch:" << result->value;
      break;
    } else if (temp->value < item) {
      temp = temp->right;
    } else if (temp->value > item) {
      temp = temp->left;
    }
  }
  return result;
}
