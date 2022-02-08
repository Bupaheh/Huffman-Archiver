#include "HuffmanTree.h"

#include <utility>

namespace huffman {

    TreeNode::TreeNode(std::vector<uint8_t> data, unsigned long count, TreeNode *left, TreeNode *right):
                        data(std::move(data)), count(count), left(left), right(right) {}

    HuffmanTree::HuffmanTree(TreeNode *node) {
        if (node != nullptr) {
            NodePtr root(node);
            std::vector<bool> stack;
            if (node->left == nullptr)
                stack.push_back(false);
            dfs(root, stack);
        }
    }

    void HuffmanTree::dfs(const NodePtr &node, std::vector<bool> &stack) {
        if (node->left == nullptr) {
            dataToCode[node->data.front()] = stack;
            codeToData[stack] = node->data.front();
            return;
        }
        stack.push_back(false);
        dfs(node->left, stack);
        stack.pop_back();
        stack.push_back(true);
        dfs(node->right, stack);
        stack.pop_back();
    }

    std::vector<bool> HuffmanTree::code(uint8_t sequence) const {
        return dataToCode.at(sequence);
    }

    uint8_t HuffmanTree::decode(const std::vector<bool> &sequence) const {
        return codeToData.at(sequence);
    }

    bool HuffmanTree::containsCode(const std::vector<bool> &sequence) const noexcept {
        return codeToData.find(sequence) != codeToData.end();
    }

}