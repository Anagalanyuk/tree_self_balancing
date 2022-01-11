#pragma once
#include "Node.h"
#include <cassert>

#include "Tree.h"

class UnitTest {
public:
  void RunTest();
};

void UnitTest::RunTest() {

  Tree<int> tree;
  std::cout << "\033[1;33mTest Add\033[0m" << std::endl;
  tree.Add(20);
  std::cout << "Add: 20" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  assert(tree.GetSize() == 1);
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Remove\033[0m" << std::endl;
  tree.Add(30);
  tree.Add(10);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "Remove: 10" << std::endl;
  tree.Remove(10);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  assert(!tree.Search(10));
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Remove root\033[0m" << std::endl;
  tree.Remove(20);
  assert(tree.GetValue(tree.GetRoot()) != 20);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Remove node\033[0m" << std::endl;
  tree.Add(20);
  tree.Add(30);
  tree.Add(40);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "Remove: 40" << std::endl;
  tree.Remove(40);
  tree.ShowItems(tree.GetRoot());
  assert(tree.GetSize() == 2);
  std::cout << "\033[1;32m\nTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Balance\033[0m" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "Root: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "Add(10)";
  tree.Add(10);
  std::cout << std::endl;
  assert(tree.GetValue(tree.GetRoot()) == 20);
  assert(tree.GetDeepLeftBranch() == tree.GetDeepRightBranch());
  tree.ShowItems(tree.GetRoot());
  std::cout << "\nRoot: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest min turn left\033[0m" << std::endl;
  std::cout << "tree.add(40)" << std::endl;
  std::cout << "tree.add(50)" << std::endl;
  tree.Add(40);
  tree.Add(50);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  assert(tree.GetDeepRightBranch() == 2);
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest min turn right\033[0m" << std::endl;
  std::cout << "tree.add(7)" << std::endl;
  std::cout << "tree.add(5)" << std::endl;
  tree.Add(7);
  tree.Add(5);
  assert(tree.GetDeepLeftBranch() == 2);
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest search\033[0m" << std::endl;
  std::cout << "Search: 20" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  assert(tree.Search(20));
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest min value: \033[0m" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "min value: " << tree.GetValue(tree.Minimum(tree.GetRoot()))
            << std::endl;
  assert(tree.GetValue(tree.Minimum(tree.GetRoot())) == 5);
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest max value: \033[0m" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "max value: " << tree.GetValue(tree.Maximum(tree.GetRoot()))
            << std::endl;
  assert(tree.GetValue(tree.Maximum(tree.GetRoot())) == 50);
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Get root\033[0m" << std::endl;
  assert(tree.GetValue(tree.GetRoot()) == 20);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "root: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Next\033[0m" << std::endl;
  assert(tree.GetValue(tree.Next(tree.GetRoot())) == 30);
  std::cout << "Next: " << tree.GetValue(tree.Next(tree.GetRoot()))
            << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest Previous\033[0m" << std::endl;
  assert(tree.GetValue(tree.Previous(tree.GetRoot())) == 10);
  std::cout << "Previous: " << tree.GetValue(tree.Previous(tree.GetRoot()))
            << std::endl;
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest turn left\033[0m" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "root: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  std::cout << "Add : 9, 15, 16" << std::endl;
  tree.Add(9);
  tree.Add(15);
  tree.Add(16);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "root: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  assert(tree.GetDeepLeftBranch() == 3 && tree.GetDeepRightBranch() == 3);
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;

  std::cout << "\033[1;33mTest turn right\033[0m" << std::endl;
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "root: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  std::cout << "Add : 45, 55, 60" << std::endl;
  tree.Add(45);
  tree.Add(55);
  tree.Add(18);
  tree.Add(60);
  tree.ShowItems(tree.GetRoot());
  std::cout << std::endl;
  std::cout << "root: " << tree.GetValue(tree.GetRoot()) << std::endl;
  std::cout << "Left branch depth: " << tree.GetDeepLeftBranch() << std::endl;
  std::cout << "Right branch depth: " << tree.GetDeepRightBranch() << std::endl;
  assert(tree.GetDeepLeftBranch() == 4 && tree.GetDeepRightBranch() == 5);
  std::cout << "\033[1;32mTest successful\033[0m" << std::endl;
}
