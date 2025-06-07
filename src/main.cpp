// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

// Main program to demonstrate PMTree permutation generation
int main() {
  // Initialize input elements
  std::vector<char> elements = {'1', '2', '3'};
  
  // Create permutation tree
  PMTree tree(elements);

  // Retrieve and display all permutations
  std::cout << "All permutations:\n";
  auto allPerms = getAllPerms(tree);
  for (const auto& perm : allPerms) {
    for (char c : perm) {
      std::cout << c;
    }
    std::cout << "\n";
  }

  // Retrieve and display specific permutations
  std::cout << "\nSpecific permutations:\n";
  
  std::cout << "Permutation 1: ";
  auto perm1 = getPerm1(tree, 1);
  for (char c : perm1) {
    std::cout << c;
  }
  std::cout << "\n";

  std::cout << "Permutation 2: ";
  auto perm2 = getPerm2(tree, 2);
  for (char c : perm2) {
    std::cout << c;
  }
  std::cout << "\n";

  return 0;
}
