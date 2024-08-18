#include <cstdlib>
#include <iostream>

#include "bst.cpp"

using namespace std;

int main() {

  int TreeKeys[5] = {50, 76, 21, 4, 32};
  int input = 0;

  BST myTree;

  cout << "Print new tree: ";

  myTree.PrintInOrder();

  for (int i = 0; i < 5; i++) {
    myTree.AddLeaf(TreeKeys[i]);
  }

  myTree.PrintInOrder();

  cout << "\nDone\n";

  myTree.PrintChildren(myTree.ReturnRootKey());

  cout << "Smallet value:" << myTree.FindSmallest() << endl;

  cout << "Enter value to delete. Enter -1 to exit.\n";

  while (input != -1) {
    cout << "\nDelete Node:";
    cin >> input;
    if (input == -1) {
      cout << "exit\n";
      return 0;
    }
    myTree.RemoveNode(input);
    cout << "\nTree:\n";
    myTree.PrintInOrder();
  }

  return 0;
}
