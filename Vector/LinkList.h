#pragma once

template<typename T>
class LinkList
{
private:
    typedef struct LNode {
        int data;
        struct LNode* next;
    }LNode;
    LNode header;
public:
    LinkList();
    ~LinkList();

private:

};

LinkList::LinkList()
{
}

LinkList::~LinkList()
{
}