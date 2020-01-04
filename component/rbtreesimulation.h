#ifndef RBTREESIMULATION_H
#define RBTREESIMULATION_H
#include "simulator.h"
#include<QHash>
#include<QQueue>
class QPainter;

//红黑树算法取自算法导论第三版
class RBtreeSimulation :public Simulator
{
    Q_OBJECT
public:
    RBtreeSimulation();

    // Simulator interface
public:
    virtual void produceSimulateData() override;
    virtual void clearSimulateData() override;
    virtual QWidget *getUi() override;
    virtual QString getName() const override;
    virtual void setPixmap(QPixmap *) override;
    virtual void currentSnapshot(int n_) const override;
    virtual int frameAllNumber() const override;
    virtual void nextFrame(int n_) override;
    virtual QSize calculationMinPixSize() override;
    virtual void makeElementsBig(int factor) override;
private:
    QVector<int> elementProperties{40//节点直径
                                  };

    int _diameter =40;   //节点直径
    int _radius = _diameter / 2;    //半径
    int _nodeLineHeight = 3 * _diameter / 2;     //垂直距离
    int _fontSize=_radius;      //字体大小

    //红黑树节点类
    template<typename T>
    class Node;
    Node<int> *root;        //红黑树根节点
    Node<int> *NIL;     //红黑树的哨兵节点

    //用于绘图的红黑树节点类
    struct FakeNode;
    FakeNode * fakeRoot;     //绘图红黑树的根节点
    FakeNode * fakeNIL;     //绘图红黑树的哨兵节点
    FakeNode * fakeSentinelNode;     //绘图节点形成的序链接链表的哨兵节点
    QHash<int, FakeNode *> fakeNodeContainer;    //持有绘图树节点
    QQueue<FakeNode *> fakeNodeQueue;       //用来进行层序遍历,然后设置每个绘图节点的y轴坐标

    //树节点数量
    int _nodeSize=0;

    QVector<int> _qvectorForData;       //插入节点值保留的副本
    int _indexForQvector=0;     //以上副本的索引

    FakeNode * _searchNodeItem=nullptr;

    struct Action;
    QVector<Action> _arrayForOrder;     //保存的一系列操作
    //红黑树颜色
    enum Color { Red, Black };
    //红黑树节点
    template <typename T>
    class Node {
    public:
        // for rbtree
        T item;
        Node<T> *parent;
        Node<T> *left;
        Node<T> *right;
        Color color;

        Node(const T &_item, Node<T> *_parent = nullptr, Node<T> *_left = nullptr,
             Node<T> *_right = nullptr, Color _Color = Red)
            : item(_item),
              parent(_parent),
              left(_left),
              right(_right),
              color(_Color) {}
    };

    struct FakeNode {
        int _value;

        FakeNode *_left;
        FakeNode *_right;
        FakeNode *_parent;

        FakeNode *_next = nullptr;
        FakeNode *_prev = nullptr;

        int x = 0, y = -1;               // current coordinate
        int xParent = -1, yParent = -1;  // parent link coordinate
        Color color = Red;

        FakeNode(int value, FakeNode *left = nullptr, FakeNode *right = nullptr,
                 FakeNode *parent = nullptr)
            : _value(value), _left(left), _right(right), _parent(parent) {}
    };

    //绘图操作
    enum Operator {
        Search,
        Add,
        Rotate,
        ChangeColor,
        NextValue,
        Substitute,
        Done
    };
    //步骤
    struct Action {
        Operator _ope;
        int array[6];
    };
        /* 下面是规则的说明
         * 1.增加节点( Add)
         *      索引0:新节点值
         *      索引1:父节点值
         * 2.旋转(Rotate)
         *      索引0:父节点值
         *      索引1:值为0与左孩子旋转,值为1与右孩子旋转
         * 3.变色(ChangeColor)
         *      0是红色,值1是黑色.索引5的值大于1表示不存在当前节点
         *      索引0:当前节点值,索引1:当前节点值颜色
         *      索引2:当前节点值,索引3:当前节点值颜色
         *      索引4:当前节点值,索引5:当前节点值颜色
         *      三个键值对组成
         * 4.查找过程(Search)
         *      索引0:当前节点值
         * 5.下一个值(NextValue)
         *      索引0值固定为0
         * 6.插入或删除完成(Done)
         *      索引0值:当成功时为1,失败时0
         * 7.替换某个节点(Substitute),并且删除那个节点
         *      索引0:被替换的节点,y
         *      索引1:将要用来替换的新节点,x
         *      索引2:被替换节点的原始节点,开始赋值的y
         *  注意:这种方式的作用不好说清,是不是换一种麻烦的代码但可读性较高的算法呢?
         */
    struct SomeNodeItem{FakeNode * a[3];};
private:
    void initialTree();
    void rotationWithLeftChild(Node<int> *&root);
    void rotationWithRightChild(Node<int> *&root);
    Node<int> *&getParentReference(Node<int> *child) {
        if (child->parent == NIL) return this->root;
        return child == child->parent->left ? child->parent->left
                                            : child->parent->right;
    }
    bool insert(int );
    void insertionFixUpOfDoubleRed(Node<int> *root);
    void replace(Node<int> *y, Node<int> *x);
    Node<int> * findMinValueNode(const Node<int> * root);
    void remove(int );
    void removeFixUpOfLostOfBlack(Node<int> *root);

    //绘图
    void dispatchActionAndDraw(Action &action);
    void drawAllElement(QPainter &_painter, FakeNode *_nodeItem)const;
    void drawAllElement()const;
    void drawCurrentNodeItem(FakeNode * _nodeItem)const;
    void paintColor(FakeNode *root,QPainter & pp,int dx=0)const;
    template<typename T>
    void recolorNodeItem(std::initializer_list<T> lists)const;

    FakeNode *search(Action &action);
    void add(Action &action);
    void rotate(Action &action);
    SomeNodeItem  changeColor(Action &action);
    void showNextValue();
    void substitute(Action &action);
    void done(Action &action);

    void fillPropertyInInsert(FakeNode *_nodeItem);
    void insertNodeItemIntoLinkedList(FakeNode *_nodeItem);
    void deleteNodeItemFromLinkedList(FakeNode * _nodeItem);
    void setY();

    void rotationWithLeftChildForNodeItem(FakeNode *&root);
    void rotationWithRightChildForNodeItem(FakeNode *&root);
    void replaceForNodeItem(FakeNode *y, FakeNode *x);
    FakeNode *&getParentReferenceForNodeItem(FakeNode *child) {
        if (child->_parent == fakeNIL) return this->fakeRoot;
        return child == child->_parent->_left ? child->_parent->_left
                                              : child->_parent->_right;
    }
};

#endif // RBTREESIMULATION_H