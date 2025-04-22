#pragma once

#include <sstream>
#include <string>
#include <iomanip> 

class HeapHelper {

public:
    void printHeap() const {
        if (isEmpty()) {
            std::cout << "Heap is empty." << std::endl;
            return;
        }

        std::cout << "Heap Size: " << size() << std::endl;
        printTreeStructure();
    }

private:
    void printTreeStructure() const {
        const int MAX_LEVEL = 6;  // 控制最大打印层级（防止溢出）
        int max_level = calculateTreeDepth();
        if (max_level > MAX_LEVEL) {
            std::cout << "Tree too deep to print (max allowed depth: "
                << MAX_LEVEL << ")" << std::endl;
            return;
        }

        // 动态计算节点宽度（适应不同数据类型）
        int node_width = calculateNodeWidth();
        int last_level_nodes = 1 << (max_level - 1);
        int total_width = last_level_nodes * node_width;

        for (int level = 0; level < max_level; ++level) {
            int nodes = 1 << level;
            //将剩余空间进行均分，例如leve=1，第二层，有2个node，空白部分应该分成均匀3份
            int spacing = (total_width - node_width * nodes) / (nodes + 1);

            // 打印当前层节点
            for (int i = 0; i < (1 << level); ++i) {
                int index = (1 << level) - 1 + i;
                if (index >= count) break;

                std::cout << std::string(spacing, ' ');
                printNode(data[index], node_width);
            }
            std::cout << std::endl;

            // 打印树枝（非最后一层）
            if (level < max_level - 1) {
                printBranches(level, total_width, node_width);
            }
        }
    }

    int calculateTreeDepth() const {
        int depth = 0;
        int nodes = 0;
        while (nodes < count) {
            depth++;
            nodes += (1 << (depth - 1));
        }
        return depth;
    }

    int calculateNodeWidth() const {
        int max_width = 0;
        std::stringstream ss;
        for (int i = 0; i < count; ++i) {
            ss.str("");
            ss << data[i];
            int len = ss.str().length();
            if (len > max_width) max_width = len;
        }
        return max_width + 2;  // 左右各留一个空格
    }

    void printNode(const Item& item, int width) const {
        std::stringstream ss;
        ss << item;
        std::string str = ss.str();
        int padding = (width - str.length()) / 2;
        std::cout << std::setw(width)
            << std::string(padding, ' ') + str + std::string(padding, ' ');
    }

    void printBranches(int level, int total_width, int node_width) const {
        int nodes = 1 << level;             // 当前层节点数
        int next_nodes = nodes << 1;        // 下层节点数
        int spacing = (total_width - node_width * nodes) / (nodes + 1);
        int next_spacing = (total_width - node_width * next_nodes) / (next_nodes + 1);

        // 计算树枝符号位置
        int branch_line_len = total_width;
        std::string branch_line(branch_line_len, ' ');

        for (int i = 0; i < nodes; ++i) {
            // 当前节点中心坐标
            int node_start = spacing + i * (node_width + spacing);
            int node_center = node_start + node_width / 2;

            // 左子节点中心坐标
            int left_child_start = next_spacing + (2 * i) * (node_width + next_spacing);
            int left_child_center = left_child_start + node_width / 2;

            // 右子节点中心坐标
            int right_child_start = next_spacing + (2 * i + 1) * (node_width + next_spacing);
            int right_child_center = right_child_start + node_width / 2;

            // 绘制树枝（从父节点中心到子节点中心）
            if (left_child_center < branch_line_len) {
                int slash_pos = (node_center + left_child_center) / 2;
                if (slash_pos >= 0 && slash_pos < branch_line_len) {
                    branch_line[slash_pos] = '/';
                }
            }

            if (right_child_center < branch_line_len) {
                int backslash_pos = (node_center + right_child_center) / 2;
                if (backslash_pos >= 0 && backslash_pos < branch_line_len) {
                    branch_line[backslash_pos] = '\\';
                }
            }
        }

        std::cout << branch_line << std::endl;
    }
};