#include "HuffmanBuilder.h"

#include <queue>
#include <stdexcept>
#include <HuffmanTree.h>

namespace huffman {

    void HuffmanBuilder::update(uint8_t seq, unsigned long count) {
        if (count != 0)
            data[seq] += count;
    }

    namespace {
        struct cmp {
            bool operator()(const TreeNode *a, const TreeNode *b) const {
                if (a->count != b->count)
                    return a->count > b->count;
                return a->data > b->data;
            }
        };
    }

    HuffmanTree HuffmanBuilder::build() const {
        std::priority_queue <TreeNode *, std::vector<TreeNode *>, cmp> q;
        try {
            for (auto &i : data)
                q.push(new TreeNode(std::vector<uint8_t>{i.first}, i.second));
            while (q.size() > 1) {
                TreeNode *first = q.top();
                q.pop();
                TreeNode *second = q.top();
                q.pop();
                std::vector<uint8_t> newData = first->data;
                newData.insert(newData.end(), second->data.begin(), second->data.end());
                q.push(new TreeNode(newData, first->count + second->count, first, second));
            }
        } catch (std::bad_alloc &e) {
            while (!q.empty()) {
                delete q.top();
                q.pop();
            }
            throw std::bad_alloc();
        }
        return HuffmanTree(!q.empty() ? q.top() : nullptr);
    }

    unsigned long HuffmanBuilder::getCount(uint8_t seq) const noexcept {
        try {
            return data.at(seq);
        } catch (std::out_of_range &e) {
            return 0;
        }
    }

    unsigned long HuffmanBuilder::getMaxCount() const noexcept {
        unsigned long res = 0;
        for (auto &i : data)
            res = std::max(res, i.second);
        return res;
    }
}
