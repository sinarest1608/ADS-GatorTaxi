// KSHITIJ SINHA
// UFID: 1416-0481
// COP5536 - Spring23

using namespace std;

class RedBlackTreeNode
{
public:
    // Defining as per PDF
    int rideNumber, rideCost, tripDuration, nodeColor;

    // Left child, Right child and Parent for current RBT Node
    RedBlackTreeNode *l, *r, *parent;

    // Min heap pointer
    MinHeapNode *minHeapNode;

    // Modifying default constructor
    RedBlackTreeNode(int rideNumber, int rideCost, int tripDuration)
        : rideNumber(rideNumber), rideCost(rideCost), tripDuration(tripDuration),
          nodeColor(1), l(NULL), r(NULL), parent(NULL), minHeapNode(NULL) {}
        //   Color is coded using 1 and 0; 1 for RED, 0 for BLACK
};

class RedBlackTree
{
    // Defnining Root for RBT
    RedBlackTreeNode *root;

    //  Right rotation for RBT
    void rotateRight(RedBlackTreeNode *&node)
    {
        RedBlackTreeNode *tempNode = node->l;
        node->l = tempNode->r;
        if (node->l != NULL) // Check if left child NULL
        {
            node->l->parent = node; // switch parent pointers
        }
        tempNode->parent = node->parent; 
        if (node->parent == NULL) 
        {
            root = tempNode;
        }
        else if (node == node->parent->l)
        {
            node->parent->l = tempNode;
        }
        else
        {
            node->parent->r = tempNode;
        }
        // Final pointer changes
        tempNode->r = node;
        node->parent = tempNode;
    }

    // Left rotation for RBT
    void rotateLeft(RedBlackTreeNode *&node)
    {
        // Create temp node for switching.
        RedBlackTreeNode *tempNode = node->r;
        node->r = tempNode->l;
        if (node->r != NULL)
        {
            node->r->parent = node;
        }
        tempNode->parent = node->parent;
        if (node->parent == NULL)
        {
            root = tempNode;
        }
        else if (node == node->parent->l)
        {
            node->parent->l = tempNode;
        }
        else
        {
            node->parent->r = tempNode;
        }
        // Final pointer changes.
        tempNode->l = node;
        node->parent = tempNode;
    }

    // SINHA
    
    //  Restructure function for rebalancing the tree
    void restructure(RedBlackTreeNode *&node)
    {
        while (node != root && node->nodeColor != 0 && node->parent->nodeColor == 1)
        {
            // Get the parent and grandparent
            RedBlackTreeNode *parent = node->parent;
            RedBlackTreeNode *grandparent = parent->parent;

            if (parent == grandparent->l) // CASE A
            {
                // Get the uncle using grandparent
                RedBlackTreeNode *uncle = grandparent->r;

                if (uncle != NULL && uncle->nodeColor == 1) // CASE A.1
                {
                    grandparent->nodeColor = 1;
                    parent->nodeColor = uncle->nodeColor = 0;
                    node = grandparent;
                }
                else
                {
                    if (node == parent->r) // CASE A.2
                    {
                        rotateLeft(parent);
                        swap(parent, node);
                    }
                    rotateRight(grandparent);
                    swap(parent->nodeColor, grandparent->nodeColor);
                    node = parent;
                }
            }
            else // CASE B
            {
                RedBlackTreeNode *uncle = grandparent->l;

                if (uncle != NULL && uncle->nodeColor == 1) // CASE B.1
                {
                    grandparent->nodeColor = 1;
                    parent->nodeColor = uncle->nodeColor = 0;
                    node = grandparent;
                }
                else
                {
                    if (node == parent->l) // CASE B.2
                    {
                        rotateRight(parent);
                        swap(parent, node);
                    }
                    rotateLeft(grandparent);
                    swap(parent->nodeColor, grandparent->nodeColor);
                    node = parent;
                }
            }
        }
        root->nodeColor = 0;
    }

    // RBT Search Function
    RedBlackTreeNode* find(RedBlackTreeNode *node, int key)
    {
        if (node == NULL || key == node->rideNumber)
        {
            return node;
        }

        if (key < node->rideNumber)
        {
            return find(node->l, key); // Recursive call
        }
        else
        {
            return find(node->r, key); // Recursive call
        }
    }

    void transplant(RedBlackTreeNode *u, RedBlackTreeNode *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->l)
        {
            u->parent->l = v;
        }
        else
        {
            u->parent->r = v;
        }
        if (v != NULL)
        {
            v->parent = u->parent;
        }
    }

    // SINHA

    // RBT Delete Function
    void erase(RedBlackTreeNode *node, int key)
    {
        // Add temporary nodes to keep track for existing data.
        RedBlackTreeNode *temp1 = NULL;
        RedBlackTreeNode *temp2 = NULL, *temp3 = NULL;
        while (node != NULL)
        {
            if (node->rideNumber == key)
            {
                temp1 = node;
            }

            node = (node->rideNumber <= key) ? node->r : node->l;
        }

        //  If element not found in tree
        if (temp1 == NULL)
        {
            cout << "Couldn't find key in the tree" << endl;
            return;
        }

        temp3 = temp1;
        int temp3Color = temp3->nodeColor;
        if (temp1->l == NULL)
        {
            temp2 = temp1->r;
            transplant(temp1, temp1->r);
        }
        else if (temp1->r == NULL)
        {
            temp2 = temp1->l;
            transplant(temp1, temp1->l);
        }
        else
        {
            temp3 = temp1->r;
            temp3Color = temp3->nodeColor;
            temp2 = temp3->r;
            if (temp3->parent != temp1)
            {
                transplant(temp3, temp3->r);
                temp3->r = temp1->r;
                temp3->r->parent = temp3;
            }

            transplant(temp1, temp3);
            temp3->l = temp1->l;
            temp3->l->parent = temp3;
            temp3->nodeColor = temp1->nodeColor;
        }

        delete temp1;
        if (temp3Color == 0)
        {
            restructure(temp2);
        }
    }

    // Insert into RBT
    void insert(int key)
    {
        // Creating a new node and defining the children, parent and colors. 
        RedBlackTreeNode *node;
        node->parent = NULL;
        node->rideNumber = key;
        node->l = NULL;
        node->r = NULL;
        node->nodeColor = 1;

        RedBlackTreeNode *y = nullptr;
        RedBlackTreeNode *x = root;

        // while root not NULL
        while (x != NULL)
        {
            y = x;
            x = (node->rideNumber < x->rideNumber) ? x->l : x->r; // Finding the position to Insert using BST property
        }

        node->parent = y; // Insert and change the parent

        if (node->parent == NULL)
        {
            node->nodeColor = 0;
            return;
        }

        if (node->parent->parent == NULL)
        {
            return;
        }

        restructure(node); // Apply restructure to rebalance the tree

        // SINHA
    }
};