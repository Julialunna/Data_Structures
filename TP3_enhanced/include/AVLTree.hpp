#ifndef AVLTREE_HPP
#define AVLTREE_HPP
class ClientsStorage;   
class PackageStorage;

template <typename T>
struct Node{
    T value;
    Node *leftChild;
    Node *rightChild;
    int height;
    Node(const T &k)
        : value(k), leftChild(nullptr), rightChild(nullptr), height(1) {}
};
template <typename T>
class AVLTree{
    friend class ClientsStorage;
    friend class PackageStorage;
private:
    Node<T> *root;
    int height(Node<T> *node);
    int balanceFactor(Node<T> *node);
    Node<T> *rotateLeft(Node<T> *x);
    Node<T> *rotateRight(Node<T> *y);
    Node<T> *insertNode(Node<T> *node, const T &value);
    Node<T> *deleteNode(Node<T> *node, const T &key);
    int max(int v1, int v2);
    void destroy(Node<T> *node);

public:
    void insert(const T &key);
    void remove(const T &key);
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    int getHeight();
    T *find(int id) const;
    T *find(const std::string &sku) const;
};


template <typename T>
int AVLTree<T>::getHeight()
{
    return this->height(this->root);
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    this->destroy(this->root);
}
//returns the max value
template <typename T>
int AVLTree<T>::max(int v1, int v2)
{
    if (v1 > v2)
        return v1;
    return v2;
}
//calculates tree height recursively
template <typename T>
int AVLTree<T>::height(Node<T> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int left_height = this->height(node->leftChild);
    int right_height = this->height(node->rightChild);
    return 1 + this->max(left_height, right_height);
}

// calculates Tree balance based on heights
template <typename T>
int AVLTree<T>::balanceFactor(Node<T> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int balance = this->height(node->rightChild) - this->height(node->leftChild);
    return balance;
}

template <typename T>
Node<T> *AVLTree<T>::rotateLeft(Node<T> *x)
{
    Node<T> *y = x->rightChild;
    Node<T> *z = y->leftChild;

    y->leftChild = x;
    x->rightChild = z;

    // Update heights
    x->height = this->max(this->height(x->leftChild), this->height(x->rightChild)) + 1;
    y->height = this->max(this->height(y->leftChild), this->height(y->rightChild)) + 1;

    // Return new root
    return y;
}

template <typename T>
Node<T> *AVLTree<T>::rotateRight(Node<T> *y)
{
    Node<T> *x = y->leftChild;
    Node<T> *z = x->rightChild;

    x->rightChild = y;
    y->leftChild = z;

    // Update heights
    y->height = this->max(this->height(y->leftChild), this->height(y->rightChild)) + 1;
    x->height = this->max(this->height(x->leftChild), this->height(x->rightChild)) + 1;

    // Return new root
    return x;
}
//insert node encapsulation
template <typename T>
void AVLTree<T>::insert(const T &key)
{
    this->root = this->insertNode(this->root, key);
}

//balanced avl insertion has a cost of O(log(n))
//insert node and guarantees that tree is balanced
template <typename T>
Node<T> *AVLTree<T>::insertNode(Node<T> *node, const T &value)
{
    if (node == nullptr)
        return new Node<T>(value);

    if (value < node->value)
        node->leftChild = this->insertNode(node->leftChild, value);
    else if (value > node->value)
        node->rightChild = this->insertNode(node->rightChild, value);
    else{
        std::cerr<<"Registro Duplicado, insercao cancelada\n";
        return node;}

    // updates height
    node->height = 1 + this->max(this->height(node->leftChild),
                                 this->height(node->rightChild));

    // check balance
    int balance = this->balanceFactor(node);

    // case Left Left
    if (balance < -1 && value < node->leftChild->value)
        return this->rotateRight(node);

    // case Right Right
    if (balance > 1 && value > node->rightChild->value)
        return this->rotateLeft(node);

    // case Left Right
    if (balance < -1 && value > node->leftChild->value)
    {
        node->leftChild = this->rotateLeft(node->leftChild);
        return this->rotateRight(node);
    }

    // case Right Left
    if (balance > 1 && value < node->rightChild->value)
    {
        node->rightChild = this->rotateRight(node->rightChild);
        return this->rotateLeft(node);
    }

    // node already balanced
    return node;
}

//
template <typename T>
void AVLTree<T>::remove(const T &key)
{
    this->root = this->deleteNode(this->root, key);
}

//deletes node keeping the tree balanced
template <typename T>
Node<T> *AVLTree<T>::deleteNode(Node<T> *node, const T &key)
{
    if (!node)
        return nullptr;

    if (key < node->value)
    {
        node->leftChild = this->deleteNode(node->leftChild, key);
    }
    else if (key > node->value)
    {
        node->rightChild = this->deleteNode(node->rightChild, key);
    }
    else
    {

        if (!node->leftChild || !node->rightChild)
        {
            // 0 or 1 child
            Node<T> *tmp = node->leftChild
                               ? node->leftChild
                               : node->rightChild;
            if (!tmp)
            {
                tmp = node;
                node = nullptr;
            }
            else
            {
                *node = *tmp;
            }
            delete tmp;
        }
        else
        {
            // 2 children: chooses successor in-order
            Node<T> *succ = node->rightChild;
            while (succ->leftChild)
                succ = succ->leftChild;
            node->value = succ->value;
            node->rightChild = this->deleteNode(node->rightChild, succ->value);
        }
    }

    if (!node)
        return node;

    // updates height
    node->height = 1 + this->max(this->height(node->leftChild),
                                 this->height(node->rightChild));
    // re-balance
    int bf = this->balanceFactor(node);
    // rotate right
    if (bf < -1 && this->balanceFactor(node->leftChild) <= 0)
        return this->rotateRight(node);
    // rotate left right
    if (bf < -1 && this->balanceFactor(node->leftChild) > 0)
    {
        node->leftChild = this->rotateLeft(node->leftChild);
        return this->rotateRight(node);
    }
    // rotate left
    if (bf > 1 && this->balanceFactor(node->rightChild) >= 0)
        return this->rotateLeft(node);
    // rotate right left
    if (bf > 1 && this->balanceFactor(node->rightChild) < 0)
    {
        node->rightChild = this->rotateRight(node->rightChild);
        return this->rotateLeft(node);
    }
    return node;
}

// free memory using pos-order traversal
template <typename T>
void AVLTree<T>::destroy(Node<T> *node)
{
    if (!node)
        return;
    destroy(node->leftChild);
    destroy(node->rightChild);
    delete node;
}

//finds register based on an int key
//tree is always balanced, the cost is : O(log(n))
template <typename T>
T *AVLTree<T>::find(int packageId) const
{
    Node<T> *currentNode = root;
    while (currentNode)
    {
        if (packageId == currentNode->value.packageId)
        return &currentNode->value;
        else if (packageId < currentNode->value.packageId)
        currentNode = currentNode->leftChild;
        else
        currentNode = currentNode->rightChild;
    }
    return nullptr;
}
//finds register based on string key
//tree is always balanced, the cost is : O(log(n))
template <typename T>
T *AVLTree<T>::find(const std::string &name) const
{
    Node<T>* currentNode = root;
    while (currentNode) {
        if (name == currentNode->value.name)
        return &currentNode->value;
        else if (name < currentNode->value.name)
        currentNode = currentNode->leftChild;
        else
        currentNode = currentNode->rightChild;
    }
    return nullptr;
}

#endif