// Copyright 2022 NNTU-CS
#include <algorithm>
#include <memory>
#include <vector>
#include "tree.h"

// Constructor for PMTree
PMTree::PMTree(const std::vector<char>& elements) {
  // Handle empty input
  if (elements.empty()) {
    root = nullptr;
    totalPermutations = 0;
    return;
  }

  // Initialize tree and calculate total permutations
  totalPermutations = factorial(elements.size());
  root = std::make_unique<Node>('\0');

  // Create root's children with input elements
  for (char elem : elements) {
    root->children.push_back(std::make_unique<Node>(elem));
  }

  // Build subtree for each child
  for (auto& child : root->children) {
    std::vector<char> remaining;
    for (char elem : elements) {
      if (elem != child->value) {
        remaining.push_back(elem);
      }
    }
    buildTree(child.get(), remaining);
  }
}

// Builds the permutation tree recursively
void PMTree::buildTree(Node* parent, const std::vector<char>& remaining) {
  if (remaining.empty()) return;

  // Add children for each remaining element
  for (char elem : remaining) {
    parent->children.push_back(std::make_unique<Node>(elem));
    std::vector<char> newRemaining;
    for (char e : remaining) {
      if (e != elem) newRemaining.push_back(e);
    }
    buildTree(parent->children.back().get(), newRemaining);
  }
}

// Retrieves all permutations from the tree
std::vector<std::vector<char>> PMTree::getAllPerms() const {
  std::vector<std::vector<char>> result;
  if (!root) return result;

  std::vector<char> current;
  for (const auto& child : root->children) {
    collectPerms(child.get(), current, result);
  }
  return result;
}

// Helper function to collect permutations recursively
void PMTree::collectPerms(const Node* node, std::vector<char>& current,
                          std::vector<std::vector<char>>& result) const {
  current.push_back(node->value);
  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const auto& child : node->children) {
      collectPerms(child.get(), current, result);
    }
  }
  current.pop_back();
}

// Retrieves the num-th permutation using traversal
std::vector<char> PMTree::getPerm1(int num) const {
  if (num < 1 || num > totalPermutations || !root) return {};

  std::vector<char> result;
  int remaining = num;
  for (const auto& child : root->children) {
    if (getPermByTraversal(child.get(), remaining, result)) {
      return result;
    }
  }
  return {};
}

// Helper function for getPerm1 to traverse tree
bool PMTree::getPermByTraversal(const Node* node, int& remaining,
                                std::vector<char>& result) const {
  result.push_back(node->value);
  if (node->children.empty()) {
    if (--remaining == 0) return true;
  } else {
    for (const auto& child : node->children) {
      if (getPermByTraversal(child.get(), remaining, result)) return true;
    }
  }
  result.pop_back();
  return false;
}

// Retrieves the num-th permutation using navigation
std::vector<char> PMTree::getPerm2(int num) const {
  if (num < 1 || num > totalPermutations || !root) return {};

  std::vector<char> result;
  int remaining = num - 1;
  for (const auto& child : root->children) {
    int childPerms = factorial(root->children.size() - 1);
    if (remaining < childPerms) {
      result.push_back(child->value);
      if (getPermByNavigation(child.get(), remaining, result)) return result;
      break;
    }
    remaining -= childPerms;
  }
  return {};
}

// Helper function for getPerm2 to navigate tree
bool PMTree::getPermByNavigation(const Node* node, int remaining,
                                 std::vector<char>& result) const {
  if (node->children.empty()) return true;

  int childPerms = factorial(node->children.size() - 1);
  for (const auto& child : node->children) {
    if (remaining < childPerms) {
      result.push_back(child->value);
      return getPermByNavigation(child.get(), remaining, result);
    }
    remaining -= childPerms;
  }
  return false;
}

// Calculates factorial for permutation count
int PMTree::factorial(int n) const {
  return (n <= 1) ? 1 : factorial(n - 1) * n;
}

// Free functions for permutation access
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  return tree.getPerm1(num);
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  return tree.getPerm2(num);
}
