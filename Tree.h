#pragma once
#include "Node.h"
#include <iostream>

template <typename T> class Tree {

public:
  Tree();
  Tree(const Tree &source);
  Tree(Tree &&source);
  ~Tree();

  //// Uncoment for tests
  int GetDeepLeftBranch() const;
  int GetDeepRightBranch() const;

  Tree &operator=(const Tree &right);
  Tree &operator=(Tree &&right);

  void Add(const T item);
  void Clear();
  const Node<T> *GetRoot() const;

  unsigned int GetSize() const;
  const Node<T> *Maximum(const Node<T> *const node) const;
  const Node<T> *Minimum(const Node<T> *const node) const;
  const Node<T> *Next(const Node<T> *const node) const;
  const Node<T> *Previous(const Node<T> *const node) const;
  void ShowItems(const Node<T> *const node) const;
  T GetValue(const Node<T> *const node) const;
  bool Remove(const T item);
  const Node<T> *Search(const T item) const;

private:
  Node<T> *root = nullptr;
  unsigned int size = 0;
  int deepLeftBranch = 0;
  int deepRightBranch = 0;
  int deep = 0;

  int GetBalance() const { return deepLeftBranch - deepRightBranch; }

  void TurnMimLeft(Node<T> *node) {
    node->left = node->parent;
    node->parent = node->left->parent;
    node->left->right = nullptr;
    node->parent->right = node;
    node->left->parent = node;
  };

  void TurnLeft() {
    Node<T> *temp = root->right;
    while (temp->left != nullptr) {
      temp = temp->left;
    }
    temp->left = root;

    if (temp->right != nullptr && temp->parent != root) {
      temp->parent->left = temp->right;
      temp->right->parent = temp->parent;
    }

    if (temp->parent == root) {
      root->parent = temp;
      root->right = nullptr;
      root = temp;
      root->parent = nullptr;
      root->deep = 0;
    } else {
      temp->right = root->right;
      root->right->parent = temp;
      temp->left = root;
      root->parent = temp;
      root->right = nullptr;
      root = temp;
      root->right->left = nullptr;
      root->parent = nullptr;
      root->deep = 0;
    }

    if (root->left != nullptr) {
      root->left->deep = 1;
      CorrectDeep(root->left);
    }

    if (root->right != nullptr) {
      root->right->deep = 1;
      CorrectDeep(root->right);
    }

    CorrectBranchesDeep();
  };

  void TurnMinRight(Node<T> *node) {
    node->right = node->parent;
    node->parent = node->right->parent;
    node->right->left = nullptr;
    node->parent->left = node;
    node->right->parent = node;
  }

  void TurnRight() {
    Node<T> *temp = root->left;
    while (temp->right != nullptr) {
      temp = temp->right;
    }
    temp->right = root;
    root->parent = temp;

    if (temp->left != nullptr && temp->parent != root) {
      temp->left->parent = temp->parent->right;
      temp->parent->right = temp->left;
    }

    if (temp->parent == root) {
      root->parent = temp;
      root->left = nullptr;
      root = temp;
      root->parent = nullptr;
      root->deep = 0;
    } else {
      temp->left = root->left;
      temp->parent->right = nullptr;
      root->left->parent = temp;
      root->left->parent = temp;
      root->left = nullptr;
      root = temp;
      root->parent = nullptr;
      root->deep = 0;
    }

    if (root->left != nullptr) {
      root->left->deep = 1;
      CorrectDeep(root->left);
    }

    if (root->right != nullptr) {
      root->right->deep = 1;
      CorrectDeep(root->right);
    }
    CorrectBranchesDeep();
  };

  void CorrectDeep(Node<T> *node) {
    if (node != nullptr) {
      CorrectDeep(node->left);
      node->deep = node->parent->deep + 1;
      CorrectDeep(node->right);
    }
  }

  void MaxDeep(Node<T> *node) {
    if (node != nullptr) {
      MaxDeep(node->left);
      if (deep < node->deep) {
        deep = node->deep;
      }
      MaxDeep(node->right);
    }
  }

  void CorrectBranchesDeep() {
    deep = 0;
    if (root->left != nullptr) {
      MaxDeep(root->left);
    }
    deepLeftBranch = deep;
    deep = 0;
    if (root->right != nullptr) {
      MaxDeep(root->right);
    }
    deepRightBranch = deep;
    deep = 0;
  }

  void Copy(const Node<T> *node) {
    if (node != nullptr) {
      Copy(node->left);
      this->Add(node->value);
      Copy(node->right);
    }
  }

  void Clear(const Node<T> *node) {
    if (node != nullptr) {
      Clear(node->left);
      Clear(node->right);
      size -= 1;
      delete node;
    }
  }
};

//// Uncoment for tests
template <typename T> int Tree<T>::GetDeepLeftBranch() const {
  return deepLeftBranch;
}

//// Uncoment for tests
template <typename T> int Tree<T>::GetDeepRightBranch() const {
  return deepRightBranch;
}

template <typename T> Tree<T>::Tree() {}

template <typename T> Tree<T>::Tree(const Tree &source) {
  this->Copy(source.GetRoot());
}

template <typename T>
Tree<T>::Tree(Tree &&source) : root(source.root), size(source.size) {
  source.root = nullptr;
  source.size = 0;
}

template <typename T> Tree<T> &Tree<T>::operator=(const Tree &right) {

  this->Clear();
  this->Copy(right.GetRoot());
  return *this;
}

template <typename T> Tree<T> &Tree<T>::operator=(Tree &&right) {
  this->Clear();

  root = right.root;
  size = right.size;
  right.root = nullptr;
  right.size = 0;
  return *this;
}

template <typename T> const Node<T> *Tree<T>::GetRoot() const { return root; }

template <typename T> T Tree<T>::GetValue(const Node<T> *const node) const {
  return node->value;
}

template <typename T> unsigned int Tree<T>::GetSize() const { return size; }

template <typename T> void Tree<T>::Add(const T item) {
  if (Search(item)) {
    return;
  }

  Node<T> *newNode = new Node<T>(item);
  Node<T> *searchNode = nullptr;

  if (root == nullptr) {
    root = newNode;
  } else {
    Node<T> *node = root;
    while (node->value != item) {
      searchNode = node;
      if (node->value < item) {
        if (node->right != nullptr) {
          node = node->right;
        } else {
          newNode->parent = searchNode;
          searchNode->right = newNode;

          if (searchNode->parent != nullptr &&
              searchNode->parent->left == nullptr &&
              searchNode->parent->parent != nullptr &&
              searchNode->parent->left == nullptr) {
            TurnMimLeft(searchNode);
            searchNode->deep -= 1;
            deepRightBranch -= 1;
          }

          break;
        }
      } else {
        if (node->left != nullptr) {
          node = node->left;
        } else {
          newNode->parent = searchNode;
          searchNode->left = newNode;

          if (searchNode->parent != nullptr &&
              searchNode->parent->right == nullptr &&
              searchNode->parent->parent != nullptr &&
              searchNode->parent->right == nullptr) {
            TurnMinRight(searchNode);
            deepLeftBranch -= 1;
          }
          break;
        }
      }
    }
  }
  size += 1;
  deep = 0;
  if (root->left != nullptr) {
    root->left->deep = 1;
    CorrectDeep(root->left);
  };
  if (root->right != nullptr) {
    root->right->deep = 1;
    CorrectDeep(root->right);
  };

  if (root != nullptr) {
    CorrectBranchesDeep();
  }
  deep = 0;
  if (GetBalance() < -1) {
    TurnLeft();
  } else if (GetBalance() > 1) {
    TurnRight();
  }
}

template <typename T> const Node<T> *Tree<T>::Search(const T item) const {
  const Node<T> *temp = root;
  const Node<T> *result = nullptr;
  while (temp != nullptr) {
    if (temp->value == item) {
      result = temp;
      break;
    } else if (temp->value < item) {
      temp = temp->right;
    } else if (temp->value > item) {
      temp = temp->left;
    }
  }
  return result;
}

template <typename T>
const Node<T> *Tree<T>::Minimum(const Node<T> *const node) const {
  const Node<T> *min = node;

  while (min->left != nullptr) {
    min = min->left;
  }
  return min;
}

template <typename T>
const Node<T> *Tree<T>::Maximum(const Node<T> *const node) const {
  const Node<T> *max = node;
  while (max->right != nullptr) {
    max = max->right;
  }
  return max;
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
      while (temp->parent->value < node->value) {
        temp = temp->parent;
        if (temp->parent == nullptr) {
          break;
          result = nullptr;
        }
      }
      if (temp->parent != nullptr) {
        result = temp->parent;
      } else if (node->left == nullptr && node->right == nullptr) {
        result = temp->parent;
      }
    }
  }
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
      while (temp->parent->value > node->value) {
        temp = temp->parent;
        if (temp->parent == nullptr) {
          break;
          result = nullptr;
        }
      }
      if (temp->parent != nullptr) {
        result = temp->parent;
      } else if (node->left == nullptr && node->right == nullptr) {
        result = temp->parent;
      }
    }
  }
  return result;
}

template <typename T> void Tree<T>::ShowItems(const Node<T> *const node) const {
  if (node != nullptr) {
    ShowItems(node->left);
    std::cout << node->value << " ";
    ShowItems(node->right);
  }
}

template <typename T> bool Tree<T>::Remove(const T item) {

  bool result = false;
  const Node<T> *deleteNode = this->Search(item);

  if (deleteNode->parent == nullptr) {
    if (deleteNode->left != nullptr && deleteNode->right == nullptr) {
      root = deleteNode->left;
      size -= 1;
      result = true;
      delete deleteNode;
      deepLeftBranch -= 1;
    } else if (deleteNode->left == nullptr && deleteNode->right != nullptr) {
      root = deleteNode->right;
      deleteNode->right->parent = nullptr;
      Node<T> *sfree = deleteNode->right;
      if (sfree != nullptr) {
        while (sfree->left != nullptr) {
          sfree = sfree->left;
        }
      }
      if (sfree->left != nullptr) {
        sfree->left = deleteNode->left;
        deleteNode->left->parent = sfree;
      }
      size -= 1;
      result = true;
      delete deleteNode;
      deepRightBranch -= 1;
      root->deep = 0;
    } else if (deleteNode->left == nullptr && deleteNode->right == nullptr) {
      Clear();
      result = true;
    } else {

      if (GetBalance() < 0) {
        Node<T> *searchNode = root->right;
        while (searchNode->left != nullptr) {
          searchNode = searchNode->left;
        }

        if (searchNode->parent == root) {
          searchNode->left = deleteNode->left;
          deleteNode->left->parent = searchNode;
          searchNode->parent = nullptr;
          searchNode->deep = 0;
          root = searchNode;
        } else {

          if (searchNode->right != nullptr) {
            searchNode->parent->left = searchNode->right;
            searchNode->right->parent = searchNode->parent;
          } else {
            searchNode->parent->left = nullptr;
          }
          searchNode->right = deleteNode->right;
          deleteNode->right->parent = searchNode;
          searchNode->left = deleteNode->left;
          deleteNode->left->parent = searchNode;
          root = searchNode;
          root->parent = nullptr;
          root->deep = 0;
        }
        delete deleteNode;
        size -= 1;
      } else {
        Node<T> *searchNode = root->left;
        while (searchNode->right != nullptr) {
          searchNode = searchNode->right;
        }

        if (searchNode->parent == root) {
          searchNode->right = deleteNode->right;
          deleteNode->right->parent = searchNode;
          searchNode->parent = nullptr;
          searchNode->deep = 0;
          root = searchNode;
        } else {

          if (searchNode->left != nullptr) {
            searchNode->left->parent = searchNode->parent;
            searchNode->parent->right = searchNode->left;
          } else {
            searchNode->parent->right = nullptr;
          }
          searchNode->right = deleteNode->right;
          deleteNode->right->parent = searchNode;
          searchNode->left = deleteNode->left;
          deleteNode->left->parent = searchNode;
          root = searchNode;
          root->parent = nullptr;
          root->deep = 0;
        }

        delete deleteNode;
        size -= 1;
      }
    }
  } else {
    if (deleteNode->right != nullptr) {
      deleteNode->right->parent = deleteNode->parent;
      if (deleteNode->right->value > deleteNode->parent->value) {
        deleteNode->parent->right = deleteNode->right;
      } else {
        deleteNode->parent->left = deleteNode->right;
      }
      if (deleteNode->left != nullptr) {
        Node<T> *sfree = deleteNode->right;
        while (sfree->left != nullptr) {
          sfree = sfree->left;
        }
        sfree->left = deleteNode->left;
        deleteNode->left->parent = sfree;
      }
      size -= 1;
      result = true;
      delete deleteNode;
    } else if (deleteNode->left != nullptr) {
      deleteNode->left->parent = deleteNode->parent;
      deleteNode->parent->left = deleteNode->left;
      size -= 1;
      result = true;
      delete deleteNode;
    } else {
      if (deleteNode->parent->left != nullptr &&
          deleteNode->parent->left->value == deleteNode->value) {
        deleteNode->parent->left = nullptr;
        size -= 1;
        result = true;
        delete deleteNode;
      } else {
        deleteNode->parent->right = nullptr;
        size -= 1;
        result = true;
        delete deleteNode;
      }
    }
  }

  if (root->left != nullptr) {
    root->left->deep = 1;
    CorrectDeep(root->left);
  }

  if (root->right != nullptr) {
    root->right->deep = 1;
    CorrectDeep(root->right);
  }

  CorrectBranchesDeep();
  deep = 0;

  if (GetBalance() < -1) {
    TurnLeft();
  } else if (GetBalance() > 1) {
    TurnRight();
  }
  return result;
}

template <typename T> void Tree<T>::Clear() {
  Clear(this->GetRoot());
  root = nullptr;
  size = 0;
}

template <typename T> Tree<T>::~Tree() { Clear(); }
