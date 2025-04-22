#ifndef MAXHEAP_H_INCLUDED
#define MAXHEAP_H_INCLUDED

#include <algorithm>
#include <cassert>

/**
* 最大二叉堆：
* 1、必须是一棵完全二叉树。
* 2、根节点的值必须大于叶子节点
*/
template<typename Item>
class MaxHeap {
private:
    Item* data;
    int count;     //大小
    int capacity;  //容量

    void shiftUp(int k) {
        while (k > 0) {
            int p = (k - 1) / 2;  //父节点索引
            if (data[p] >= data[k]) {
                break;
            }
            std::swap(data[p], data[k]);
            k = p;
        }
    }

    void shiftDown(int k) {
        Item e = data[k];
        while (k < count) {
            int j = 2 * k + 1; //获得k的左子节点索引
            if (j >= count) { //左子节点不存在，表示k已经是叶子节点
                break;
            }
            if (j + 1 < count && data[j] < data[j + 1]) { //判断是否有右孩子，并比较左右孩子的大小
                j++;
            }
            if (e >= data[j]) {
                break;
            }
            data[k] = data[j];
            k = j;
        }
        data[k] = e;
    }

public:
    // 构造函数, 构造一个空堆, 可容纳capacity个元素
    MaxHeap(int capacity) {
        data = new Item[capacity];
        this->capacity = capacity;
        count = 0;
    }

    // 构造函数, 通过一个给定数组创建一个最大堆
    // 该构造堆的过程, 时间复杂度为O(n)
    MaxHeap(Item arr[], int n) {
        data = new Item[n];
        capacity = n;
        std::copy(arr, arr + n, data);
        count = n;

        //从最后一个非叶子节点开始调整
        for (int i = count / 2 - 1; i >= 0; i--) {
            shiftDown(i);
        }
    }

    ~MaxHeap() {
        delete[] data;
    }

    // 返回堆中的元素个数
    int size() const {
        return count;
    }

    // 返回一个布尔值, 表示堆中是否为空
    bool isEmpty() const {
        return count == 0;
    }

    // 向最大堆中插入一个新的元素 item
    void insert(Item item) {
        assert(count + 1 <= capacity);
        int k = count;
        data[count++] = item;
        shiftUp(k);
    }

    // 从最大堆中取出堆顶元素, 即堆中所存储的最大数据
    Item extractMax() {
        assert(count > 0);

        Item ret = data[0]; //取出第一个元素
        data[0] = data[count - 1]; //将最后一个元素放到第一位
        count--;

        shiftDown(0); //对第一个元素执行shiftDown操作
        return ret;
    }

    // 获取最大堆中的堆顶元素
    Item getMax() const {
        assert(count > 0);
        return data[0];
    }
};

#endif // MAXHEAP_H_INCLUDED

