// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

// Permutation Tree class for generating and accessing permutations
class PMTree {
 public:
  // Node structure for the permutation tree
  struct Node {
    char value;
    std::vector<std::unique_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };

  // Public interface
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() = default;

  std::vector<std::vector<char>> getAllPerms() const;
  std::vector<char> getPerm1(int num) const;
  std::vector<char> getPerm2(int num) const;

 private:
  // Member variables
  std::unique_ptr<Node> root;
  int totalPermutations;

  // Private helper functions
  void buildTree(Node* parent, const std::vector<char>& remaining);
  void collectPerms(const Node* node, std::vector<char>& current,
                    std::vector<std::vector<char>>& result) const;
  bool getPermByTraversal(const Node* node, int& remaining,
                          std::vector<char>& result) const;
  bool getPermByNavigation(const Node* node, int remaining,
                           std::vector<char>& result) const;
  int factorial(int n) const;
};

// Free functions for permutation access
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
