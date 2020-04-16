#include "rbtreesimulation.h"
#include<initializer_list>
#include<QPainter>
#include<QWidget>

RBtreeSimulation::RBtreeSimulation():Simulator()
{
    initialTree();
}

RBtreeSimulation::~RBtreeSimulation()
{
    qDeleteAll(fakeNodeContainer);
    emptyTree(root);
    delete NIL;
    delete fakeSentinelNode;
}

void RBtreeSimulation::produceActionData()
{
    _qvectorForData.clear();
    for(int i=0;i<100;i++){
        auto x=i;/*rand() % 200;*/
        if(insert(x))
            _qvectorForData<<x;
    }
    currentActionNumber=_arrayForOrder.size();
}

void RBtreeSimulation::clearActionData()
{
    _arrayForOrder.clear();
    emptyTree(root);
    root=NIL;
    fakeSentinelNode->_prev=fakeSentinelNode->_next=fakeSentinelNode;
    fakeRoot=fakeNIL;
    fakeNIL->_parent=fakeNIL->_left=fakeNIL->_right=fakeNIL;
    fakeNodeContainer.remove(-9998);
    qDeleteAll(fakeNodeContainer);
    fakeNodeContainer.clear();
    fakeNodeContainer.insert(fakeNIL->_value,fakeNIL);

    currentAction=0;
    currentAnmIndex=0;
    currentAnmNumber=0;
}

QWidget *RBtreeSimulation::getUi()
{
    return new QWidget;
}

QString RBtreeSimulation::getName() const
{
    return "红黑树";
}

void RBtreeSimulation::setPixmap(QPixmap *p)
{
    pix=p;
    pix->fill();
}

void RBtreeSimulation::currentSnapshot() const
{
    QPainter pp(pix);
    pix->fill();
    pp.translate(0,_diameter/2);
    QFont font = pp.font();
    font.setPixelSize(_fontSize);
    pp.setFont(font);
    drawAllElement(pp,fakeRoot);
    pp.end();
    auto x=currentAction-1;
    if(_arrayForOrder[x]._ope==Operator::Search)
        drawCurrentNodeItem(_searchNodeItem);
}

int RBtreeSimulation::actionNumber() const
{
    return _arrayForOrder.size();
}

void RBtreeSimulation::nextAction()
{
    dispatchActionAndDraw();
//    currentAction++;
}

QSize RBtreeSimulation::calculationMinPixSize()
{
    auto w_=_qvectorForData.size()*_radius+_radius;
    return {w_,0};
}

void RBtreeSimulation::makeElementsBig(int factor)
{

    _diameter +=factor;
    _radius = _diameter / 2;
    _nodeLineHeight = 3 * _diameter / 2;
    _fontSize=_radius;
}

void RBtreeSimulation::prepareReplay()
{
    fakeRoot=fakeNIL;

    fakeSentinelNode->_prev=fakeSentinelNode->_next=fakeSentinelNode;

    currentAction=0;
    currentAnmIndex=0;
}

void RBtreeSimulation::nextFrame()
{
    if(!hasAnimation){
        nextAction();
//        hasAnimation=true;
    }else{
        auto & action=_arrayForOrder[currentAction];
        switch (action._ope) {
        case Operator::Search:{
            if(currentAnmIndex>=currentAnmNumber){
                drawCurrentNodeItem(_searchNodeItem);
                hasAnimation=false;
                currentAction++;
            }
            QPainter pp(pix);
            pp.translate(0,_diameter/2);
            QFont font = pp.font();
            font.setPixelSize(_fontSize);
            pp.setFont(font);
            auto & _nodeItem=_searchNodeItem->_parent;
            pp.setPen(QPen(Qt::blue,30));
            pp.drawLine(_nodeItem->x*_diameter/2,_nodeItem->y*_nodeLineHeight,(_nodeItem->x+xLine)*_diameter/2,(_nodeItem->y+yLine)*_nodeLineHeight);
            pp.setPen(Qt::black);
            pp.setBrush(_nodeItem->color==Red?Qt::red:Qt::black);
            pp.drawEllipse(QPoint(_nodeItem->x*_diameter/2,_nodeItem->y*_nodeLineHeight),_radius+5,_radius+5);
            pp.setBrush(_searchNodeItem->color==Red?Qt::red:Qt::black);
            pp.drawEllipse(QPoint(_searchNodeItem->x*_diameter/2,_searchNodeItem->y*_nodeLineHeight),_radius,_radius);
            pp.setPen(Qt::white);
            pp.drawText(QRect(_nodeItem->x*_diameter/2-_radius,_nodeItem->y*_nodeLineHeight-_radius,_diameter,_diameter),Qt::AlignCenter,QString::number(_nodeItem->_value));
            pp.drawText(QRect(_searchNodeItem->x*_diameter/2-_radius,_searchNodeItem->y*_nodeLineHeight-_radius,_diameter,_diameter),Qt::AlignCenter,QString::number(_searchNodeItem->_value));
            currentAnmIndex++;
        }
            break;
        default:
            break;
        }
    }
}

void RBtreeSimulation::animationStart()
{

}

bool RBtreeSimulation::isOver() const
{
    return currentAction>=currentActionNumber;
}

void RBtreeSimulation::searchANM()
{
    _searchNodeItem->_parent;
}

void RBtreeSimulation::initialTree()
{
    root=NIL=new Node<int>(-9998);
    NIL->color=Black;
    NIL->parent=NIL->left=NIL->right=NIL;

    fakeSentinelNode=new FakeNode(-9999);
    fakeSentinelNode->_prev=fakeSentinelNode->_next=fakeSentinelNode;

    fakeRoot=fakeNIL=new FakeNode(-9998);
    fakeNIL->color=Black;
    fakeNIL->_parent=fakeNIL->_left=fakeNIL->_right=fakeNIL;

    fakeNodeContainer.insert(fakeNIL->_value,fakeNIL);
}

void RBtreeSimulation::emptyTree(Node<int> *&root)
{
    if(root!=NIL)
    {
        emptyTree(root->left);
        emptyTree(root->right);
        delete root;
        root=nullptr;
    }
}

void RBtreeSimulation::rotationWithLeftChild(Node<int> *&root)
{
    Node<int> *left_child = root->left;

    root->left = left_child->right;
    left_child->right->parent = root;

    left_child->right = root;
    left_child->parent = root->parent;

    root->parent = left_child;
    root = left_child;
}

void RBtreeSimulation::rotationWithRightChild(Node<int> *&root)
{
    Node<int> *right_child = root->right;

    root->right = right_child->left;
    right_child->left->parent = root;

    right_child->left = root;
    right_child->parent = root->parent;

    root->parent = right_child;
    root = right_child;
}

bool RBtreeSimulation::insert(int x)
{
    _arrayForOrder.append({Operator::NextValue,{0}});
    auto temp=root;
    //红黑树在调整时,其哨兵节点NIL的父节点在旋转过程中会改变,因此,在树进行一轮清空后,
    //此时root=NIL,即root.parent不再是NIL.所以这里不可以写成root->parent
    auto tempParent=NIL;
    while (temp!=NIL) {
        tempParent=temp;
        _arrayForOrder.append({Operator::Search,{temp->item}});  //Search
        if(temp->item>x){
            temp=temp->left;
        }
        else if(temp->item<x){
            temp=temp->right;
        }
        else
            break;
    }
    if(temp!=NIL){
        _arrayForOrder.append({Operator::Done,{0}});
        return false;
    }
    auto newNode=new Node<int>(x,tempParent,NIL,NIL);
    _nodeSize++;
    if(tempParent==NIL){
        root=newNode;
        _arrayForOrder.append({Operator::Add,{x,tempParent->item}});
    }
    else {
        if(x<tempParent->item){
            tempParent->left=newNode;
        }
        else{
            tempParent->right=newNode;
        }
        _arrayForOrder.append({Operator::Add,{x,tempParent->item}});
    }
    insertionFixUpOfDoubleRed(newNode);
    _arrayForOrder.append({Operator::Done,{1}});
    return true;
}

void RBtreeSimulation::insertionFixUpOfDoubleRed(Node<int> *root)
{
    while (root->parent->color == Red) {
        if (root->parent == root->parent->parent->left) {
            if (root->parent->parent->right->color == Red) {  //case 1
                root->parent->color = Black;
                root->parent->parent->right->color = Black;
                root->parent->parent->color = Red;
                _arrayForOrder.append({Operator::ChangeColor,{root->parent->item,1,
                                                              root->parent->parent->right->item,1,
                                                              root->parent->parent->item,0}});  //record
                root = root->parent->parent;
                _arrayForOrder.append({Operator::Search,{root->item}}); //record
            } else {
                Node<int> *&gp = getParentReference(root->parent->parent);
                if (root == root->parent->right) {   //case 2
                    root = root->parent;
                    _arrayForOrder.append({Operator::Rotate,{getParentReference(root)->item,1}});
                    rotationWithRightChild(getParentReference(root));
                }
                _arrayForOrder.append({Operator::Rotate,{gp->item,0}});
                rotationWithLeftChild(gp);    //case 3
                gp->color = Black;
                gp->right->color = Red;
                _arrayForOrder.append({Operator::ChangeColor,{gp->item,1,gp->right->item,0,-1,2}});
                break;
            }
        } else {
            if (root->parent->parent->left->color == Red) {
                root->parent->color = Black;
                root->parent->parent->left->color = Black;
                root->parent->parent->color = Red;
                _arrayForOrder.append({Operator::ChangeColor,{root->parent->item,1,
                                                              root->parent->parent->left->item,1,
                                                              root->parent->parent->item,0}});
                root = root->parent->parent;
                _arrayForOrder.append({Search,{root->item}});
            } else {
                Node<int> *&gp = getParentReference(root->parent->parent);
                if (root == root->parent->left) {
                    root = root->parent;
                    _arrayForOrder.append({Rotate,{getParentReference(root)->item,0}});
                    rotationWithLeftChild(getParentReference(root));
                }
                _arrayForOrder.append({Rotate,{gp->item,1}});
                rotationWithRightChild(gp);
                gp->color = Black;
                gp->left->color = Red;
                _arrayForOrder.append({ChangeColor,{gp->item,1,gp->left->item,0,-1,2}});
                break;
            }
        }
    }
    this->root->color = Black;
    _arrayForOrder.append({Operator::ChangeColor,{this->root->item,1,-1,2,-1,2}});
}

void RBtreeSimulation::replace(Node<int> *y, Node<int> *x)
{
    if(y==root)
        root=x;
    else if(y==y->parent->left)
        y->parent->left=x;
    else
        y->parent->right=x;
    x->parent=y->parent;
}

RBtreeSimulation::Node<int> *RBtreeSimulation::findMinValueNode(const Node<int> *root)
{
    auto temp=root;
    while (temp->left!=NIL) {
        _arrayForOrder.append({Operator::Search,{temp->item}});
        temp=temp->left;
    }
    return const_cast<Node<int> *>(temp);
}

void RBtreeSimulation::remove(int v)
{
    auto temp=root;
    while (temp!=NIL) {
        _arrayForOrder.append({Operator::Search,{temp->item}});  //Search
        if(temp->item>v){
            temp=temp->left;
        }
        else if(temp->item<v){
            temp=temp->right;
        }
        else
            break;
    }
    if(temp==NIL){
        _arrayForOrder.append({Operator::Done,{0}});
        return ;
    }
    auto y=temp;
    auto temp1=v;
    auto yOriginalColor=y->color;
    Node<int> * x=nullptr;
    if(temp->left==NIL){
        x=temp->right;
        replace(y,x);

    }else if(temp->right==NIL){
        x=temp->left;
        replace(y,y->left);
    }else{
        auto minNode=findMinValueNode(temp->right);
        //这里使用一种简单的方式,保留源节点,仅仅替换值的方式间接删除找到的节点
        y->item=minNode->item;
        y=minNode;
        x=y->right;
        yOriginalColor=y->color;
        if(y->parent==temp)
            x->parent=y;//算法导论中这几行没看明白,暂时把形式保存在这里好了.
        //喔,调试源码偶然发现了,这一步当x为哨兵节点是很重要,因为哨兵节点也参与之后调整过程
        //向上回溯时,需要赋值root=root.parent.哨兵节点父节点每次都会变化,所以这里必须强制更新
        //这里虽然采用删除方式不同,但还是保留了算法导论中的结构
        else {
            ;
        }
        replace(y,y->right);
    }
    _arrayForOrder.append({Operator::Substitute,{y->item,x->item,temp1}});
    delete y;
    y=nullptr;
    if(yOriginalColor==Black)
        removeFixUpOfLostOfBlack(x);
    _arrayForOrder.append({Operator::Done,{1}});
}

void RBtreeSimulation::removeFixUpOfLostOfBlack(Node<int> *root)
{
    while (root->color == Black && root != this->root) {
        Node<int> *root_brother = nullptr;
        if (root == root->parent->left) {
            root_brother = root->parent->right;
            if (root_brother->color == Red) {	//case 1
                Node<int> *&gp = getParentReference(root->parent);
                _arrayForOrder.append({Operator::Rotate,{gp->item,1}});
                rotationWithRightChild(gp);
                gp->color = Black;
                gp->left->color = Red;
                root_brother = root->parent->right;
                _arrayForOrder.append({Operator::ChangeColor,{gp->item,1,gp->left->item,0,-1,2}});
            }
            if (root_brother->left->color == Black
                    && root_brother->right->color == Black) {	//case 2
                root_brother->color = Red;
                _arrayForOrder.append({Operator::ChangeColor,{root_brother->item,0,-1,2,-1,2}});
                root = root->parent;
                _arrayForOrder.append({Operator::Search,{root->item}});
            } else {
                Node<int> * &root_parent = getParentReference(root->parent);
                if (root_brother->right->color == Black) {	//case 3
                    _arrayForOrder.append({Operator::Rotate,{root_brother->item,0}});
                    rotationWithLeftChild(root_parent->right);
                    root_parent->right->color = Black;
                    root_parent->right->right->color = Red;
                    root_brother=root_parent->right;
                    _arrayForOrder.append({Operator::ChangeColor,{root_parent->right->item,1,root_parent->right->right->item,0,-1,2}});
                }
                _arrayForOrder.append({Operator::Rotate,{root_parent->item,1}});
                rotationWithRightChild(root_parent);	//case 4
                root_parent->color = root_parent->left->color;
                root_parent->left->color = Black;
                root_parent->right->color = Black;
                //利用枚举默认值也是和我们的规定值相等,否则下面要判断
                _arrayForOrder.append({Operator::ChangeColor,{root_parent->item,root_parent->color,root_parent->left->item,1,root_parent->right->item,1}});
                root = this->root;
                _arrayForOrder.append({Operator::Search,{root->item}});
            }
        } else {
            root_brother = root->parent->left;
            if (root_brother->color == Red) {	//case 1
                Node<int> *&gp = getParentReference(root->parent);
                _arrayForOrder.append({Operator::Rotate,{gp->item,0}});
                rotationWithLeftChild(gp);
                gp->color = Black;
                gp->right->color = Red;
                root_brother = root->parent->left;
                _arrayForOrder.append({Operator::ChangeColor,{gp->item,1,gp->right->item,0,-1,2}});
            }
            if (root_brother->left->color == Black
                    && root_brother->right->color == Black) {	//case 2
                root_brother->color = Red;
                _arrayForOrder.append({Operator::ChangeColor,{root_brother->item,0,-1,2,-1,2}});
                root = root->parent;
                _arrayForOrder.append({Operator::Search,{root->item}});
            } else {
                Node<int> * &root_parent = getParentReference(root->parent);
                if (root_brother->left->color == Black) {	//case 3
                    _arrayForOrder.append({Operator::Rotate,{getParentReference(root_brother)->item,1}});
                    rotationWithRightChild(root_parent->left);
                    root_parent->left->color = Black;
                    root_parent->left->left->color = Red;
                    _arrayForOrder.append({Operator::ChangeColor,{root_parent->left->item,1,root_parent->left->left->item,0,-1,2}});
                }
                _arrayForOrder.append({Operator::Rotate,{root_parent->item,0}});
                rotationWithLeftChild(root_parent);	//case 4
                root_parent->color = root_parent->right->color;
                root_parent->left->color = Black;
                root_parent->right->color = Black;
                _arrayForOrder.append({Operator::ChangeColor,{root_parent->item,root_parent->color,root_parent->left->item,1,root_parent->right->item,1}});
                root = this->root;
                _arrayForOrder.append({Operator::Search,{root->item}});
            }
        }
    }
    root->color = Black;
    _arrayForOrder.append({Operator::ChangeColor,{root->item,1,-1,2,-1,2}});
}

void RBtreeSimulation::dispatchActionAndDraw()
{
    auto & action=_arrayForOrder[currentAction];
    switch (action._ope) {
        case Operator::Search:{
                auto x=search(action);
//                drawCurrentNodeItem(x);
                currentAnmNumber=10;
                xLine=(_searchNodeItem->x-_searchNodeItem->xParent)/currentAnmNumber;
                yLine=(_searchNodeItem->y-_searchNodeItem->yParent)/currentAnmNumber;
                currentAnmIndex=0;
                hasAnimation=true;
            }
            break;
        case Operator::Add:
            add(action);
            drawAllElement();
            currentAction++;
            break;
        case Operator::Rotate:
            rotate(action);
            drawAllElement();
            currentAction++;
            break;
        case Operator::Substitute:
            substitute(action);
            drawAllElement();
            currentAction++;
            break;
        case Operator::ChangeColor:{
                recolorNodeItem(changeColor(action));
            }
        currentAction++;
            break;
        case Operator::NextValue:
            showNextValue();
            currentAction++;
            break;
        case Operator::Done:
            done(action);
            drawAllElement();
            currentAction++;
            break;
    }
}

//深度优先
void RBtreeSimulation::drawAllElement(QPainter &_painter, RBtreeSimulation::FakeNode *_nodeItem) const
{
    if(_nodeItem!=fakeNIL){
        drawAllElement(_painter,_nodeItem->_left);
        drawAllElement(_painter,_nodeItem->_right);
        //draw line
        if(_nodeItem->xParent>0)
            _painter.drawLine(_nodeItem->x*_diameter/2,_nodeItem->y*_nodeLineHeight,_nodeItem->xParent*_diameter/2,_nodeItem->yParent*_nodeLineHeight);
        //draw cycle
        QPainterPath myPath;
        myPath.addEllipse(QPoint(_nodeItem->x*_diameter/2,_nodeItem->y*_nodeLineHeight),_radius,_radius);
        _painter.drawPath(myPath);
        _painter.fillPath(myPath,_nodeItem->color==Red?Qt::red:Qt::black);
        //draw text
        _painter.setPen(Qt::white);
        _painter.drawText(QRect(_nodeItem->x*_diameter/2-_radius,_nodeItem->y*_nodeLineHeight-_radius,_diameter,_diameter),Qt::AlignCenter,QString::number(_nodeItem->_value));
        _painter.setPen(Qt::black);
    }
}

void RBtreeSimulation::drawAllElement() const
{
    pix->fill();
    QPainter pp(pix);
    pp.translate(0,_diameter/2);
    QFont font = pp.font();
    font.setPixelSize(_fontSize);
    pp.setFont(font);
    drawAllElement(pp,fakeRoot);
}

void RBtreeSimulation::drawCurrentNodeItem(RBtreeSimulation::FakeNode *_nodeItem) const
{
    pix->fill();
    QPainter pp(pix);
    pp.translate(0,_diameter/2);
    QFont font = pp.font();
    font.setPixelSize(_fontSize);
    pp.setFont(font);
    drawAllElement(pp,fakeRoot);

    QPainterPath myPath;
    myPath.addEllipse(QPoint(_nodeItem->x*_diameter/2,_nodeItem->y*_nodeLineHeight),_radius+5,_radius+5);
    pp.drawPath(myPath);
    pp.fillPath(myPath,_nodeItem->color==Red?Qt::red:Qt::black);
    pp.setPen(Qt::white);
    pp.drawText(QRect(_nodeItem->x*_diameter/2-_radius,_nodeItem->y*_nodeLineHeight-_radius,_diameter,_diameter),Qt::AlignCenter,QString::number(_nodeItem->_value));
    pp.setPen(Qt::black);
}

void RBtreeSimulation::paintColor(RBtreeSimulation::FakeNode *root, QPainter &pp, int dx) const
{
    if(root==nullptr)
        return;
    QPainterPath myPath;
    if(_searchNodeItem==root)
        dx=5;
    myPath.addEllipse(QPoint(root->x*_diameter/2,root->y*_nodeLineHeight),_radius+dx,_radius+dx);
    pp.drawPath(myPath);
    pp.fillPath(myPath,root->color==Red?Qt::red:Qt::black);
    pp.setPen(Qt::white);
    pp.drawText(QRect(root->x*_diameter/2-_radius,root->y*_nodeLineHeight-_radius,_diameter,_diameter),Qt::AlignCenter,QString::number(root->_value));
    pp.setPen(Qt::black);
}

void RBtreeSimulation::animation()
{

}

RBtreeSimulation::FakeNode *RBtreeSimulation::search(RBtreeSimulation::Action &action)
{
    //保存当前正在查找的节点,在染色时会考虑相应变大一点
    _searchNodeItem=fakeNodeContainer.value(action.array[0]);
    return _searchNodeItem;
}

void RBtreeSimulation::add(RBtreeSimulation::Action &action)
{
    auto _parentNode=fakeNodeContainer.value(action.array[1]);
    FakeNode * _newNode=nullptr;
    if(fakeNodeContainer.contains(action.array[0])){
        _newNode=fakeNodeContainer.value((action.array[0]));
        _newNode->_left=fakeNIL;
        _newNode->_right=fakeNIL;
        _newNode->_parent=_parentNode;
        _newNode->init();
    }else{
        _newNode=new FakeNode(action.array[0],fakeNIL,fakeNIL,_parentNode);
        fakeNodeContainer.insert(_newNode->_value,_newNode);
    }
    if(_parentNode==fakeNIL)
        fakeRoot=_newNode;
    else if(_parentNode->_value>_newNode->_value)
        _parentNode->_left=_newNode;
    else
        _parentNode->_right=_newNode;

    fillPropertyInInsert(_newNode);
}

void RBtreeSimulation::rotate(RBtreeSimulation::Action &action)
{
    auto _currentNodeItem=fakeNodeContainer.value(action.array[0]);
    if(action.array[1]==0)
        rotationWithLeftChildForNodeItem(getParentReferenceForNodeItem(_currentNodeItem));
    else
        rotationWithRightChildForNodeItem(getParentReferenceForNodeItem(_currentNodeItem));
    setY();
}

Util::TupleWrapArray<RBtreeSimulation::FakeNode*,3> RBtreeSimulation::changeColor(RBtreeSimulation::Action &action)
{
    int i=0;
    FakeNode * a[3]={};
    while(i<3){
        auto colorValue=action.array[2*i+1];
        if(colorValue>1)
            break;
        a[i]=fakeNodeContainer.value(action.array[2*i]);
        a[i]->color=colorValue==0?Red:Black;
        i++;
    }
    // 等价于return std::make_tuple(a[0],a[1],a[2]);
    return Util::make_TupleForArray(a);
}

void RBtreeSimulation::showNextValue()
{

}

void RBtreeSimulation::substitute(RBtreeSimulation::Action &action)
{
    auto y=fakeNodeContainer.value(action.array[0]);
    deleteNodeItemFromLinkedList(y);
    fakeNodeContainer.remove(y->_value);
    auto x=fakeNodeContainer.value(action.array[1]);
    if(action.array[0]!=action.array[2]){
        auto yOriginal=fakeNodeContainer.value(action.array[2]);
        fakeNodeContainer.remove(yOriginal->_value);
        yOriginal->_value=y->_value;
        fakeNodeContainer.insert(y->_value,yOriginal);
    }
    if(y==fakeRoot)
        fakeRoot=x;
    else if(y==y->_parent->_left)
        y->_parent->_left=x;
    else
        y->_parent->_right=x;
    x->_parent=y->_parent;
    setY();
    delete y;
}

void RBtreeSimulation::done(RBtreeSimulation::Action &action)
{
    Q_UNUSED(action)
}

void RBtreeSimulation::fillPropertyInInsert(RBtreeSimulation::FakeNode *_nodeItem)
{
    //insert value into linkedlist-ordered and update x coordinate
    insertNodeItemIntoLinkedList(_nodeItem);
    //set right infomation left without x by level-order
    setY();
}

void RBtreeSimulation::insertNodeItemIntoLinkedList(RBtreeSimulation::FakeNode *_nodeItem)
{
    FakeNode * _pCurrent=fakeSentinelNode->_prev;
    while (_pCurrent!=fakeSentinelNode&&_nodeItem->_value<_pCurrent->_value) {
        _pCurrent->x++;
        _pCurrent=_pCurrent->_prev;
    }
    _nodeItem->x=_pCurrent->x+1;
    _nodeItem->_next=_pCurrent->_next;
    _pCurrent->_next->_prev=_nodeItem;
    _nodeItem->_prev=_pCurrent;
    _pCurrent->_next=_nodeItem;
}

void RBtreeSimulation::deleteNodeItemFromLinkedList(RBtreeSimulation::FakeNode *_nodeItem)
{
    if(_nodeItem==fakeNIL)
        return ;
    auto brokenPoint=_nodeItem->_prev;
    brokenPoint->_next=_nodeItem->_next;
    _nodeItem->_next->_prev=brokenPoint;
    brokenPoint=brokenPoint->_next;
    while(brokenPoint!=fakeSentinelNode){
        brokenPoint->x--;
        brokenPoint=brokenPoint->_next;
    }
}

void RBtreeSimulation::setY()
{
    FakeNode * temp=nullptr;
    fakeRoot->color=Black;
    fakeSentinelNode->y=-1;
    fakeNIL->y=-1;
    fakeNodeQueue.enqueue(fakeRoot);
    int level=0;
    int column=fakeNodeQueue.size();
    while (fakeNodeQueue.size()>0) {
        temp=fakeNodeQueue.dequeue();
        column--;
        temp->y=level;
        temp->xParent=temp->_parent->x;
        temp->yParent=temp->_parent->y;
        if(temp->_left!=fakeNIL)
            fakeNodeQueue.enqueue(temp->_left);
        if(temp->_right!=fakeNIL)
            fakeNodeQueue.enqueue(temp->_right);
        if(column==0){
            level++;
            column=fakeNodeQueue.size();
        }
    }
}

void RBtreeSimulation::rotationWithLeftChildForNodeItem(RBtreeSimulation::FakeNode *&root)
{
    auto left_child = root->_left;

    root->_left = left_child->_right;
    left_child->_right->_parent = root;

    left_child->_right = root;
    left_child->_parent = root->_parent;

    root->_parent = left_child;
    root = left_child;
}

void RBtreeSimulation::rotationWithRightChildForNodeItem(RBtreeSimulation::FakeNode *&root)
{
    auto right_child = root->_right;

    root->_right = right_child->_left;
    right_child->_left->_parent = root;

    right_child->_left = root;
    right_child->_parent = root->_parent;

    root->_parent = right_child;
    root = right_child;
}

void RBtreeSimulation::recolorNodeItem(Util::TupleWrapArray<FakeNode *, 3> tuple_) const
{
    QPainter pp(pix);
    pp.translate(0,_diameter/2);
    QFont font = pp.font();
    font.setPixelSize(_fontSize);
    pp.setFont(font);
    auto [a,b,c]=tuple_;
    paintColor(a,pp);
    paintColor(b,pp);
    paintColor(c,pp);
}
