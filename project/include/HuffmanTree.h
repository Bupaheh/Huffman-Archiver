#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

namespace huffman {

    struct TreeNode {
        TreeNode(std::vector<uint8_t> data, unsigned long count,
                 TreeNode *left = nullptr, TreeNode *right = nullptr);

        unsigned long count;
        std::unique_ptr<TreeNode> left, right;
        std::vector<uint8_t> data;
    };

    typedef std::unique_ptr<TreeNode> NodePtr;

    class HuffmanTree {
    public:
        explicit HuffmanTree(TreeNode *node);

        std::vector<bool> code(uint8_t sequence) const;
        uint8_t decode(const std::vector<bool> &sequence) const;
        bool containsCode(const std::vector<bool> &sequence) const noexcept;


    private:
        void dfs(const NodePtr &node, std::vector<bool> &stack);

        std::unordered_map <uint8_t, std::vector<bool>> dataToCode;
        std::unordered_map <std::vector<bool>, uint8_t> codeToData;
    };


}
