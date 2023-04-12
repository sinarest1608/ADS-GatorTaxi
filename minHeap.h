// KSHITIJ SINHA
// UFID: 1416-0481
// COP5536 - Spring23


using namespace std;


// Defining Min heap node
class MinHeapNode
{
public:
    // Variables as per definition given in PDF
    int rideNumber, rideCost, tripDuration;
    struct RedBlackTreeNode *rbtNode;

// Default constructor
    MinHeapNode(int rideNumber, int rideCost, int tripDuration)
        : rideNumber(rideNumber), rideCost(rideCost), tripDuration(tripDuration), rbtNode(NULL) {}
};


// Custom Heap implementation
template <typename T>
class MinHeap
{
public:

    // Custom comparator function that compares two nodes based on ride cost; 
    // To be used in heapify and tie breaking
    bool cmp(MinHeapNode &lhs,  MinHeapNode &rhs) 
    {
        if (lhs.rideCost == rhs.rideCost) // Tie 
        {
            return lhs.tripDuration < rhs.tripDuration;
        }
        return lhs.rideCost < rhs.rideCost;
    }

    // Heap Insert
    void insert(T item)
    {
        items.push_back(item);
        heapifyUp(size() - 1); // Calling heapify after each insert
    }

    // Heap Delete 
    T heapDelete()
    {
        T item = items.front(); 
        // swap nodes
        swap(items.front(), items.back());
        // insert from end
        items.pop_back();
        // call heapify again
        heapifyDown(0);
        return item;
    }
    // SINHA
    T getRoot() const
    {
        // get the top most i.e root
        return items.front();
    }

    int size() const
    {
        return items.size();
    }

    bool clear() const
    {
        return items.empty();
    }


    vector<T> items;
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (cmp(items[index], items[parent]))
            {
                swap(items[index], items[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    // Heapify Down function
    void heapifyDown(int index)
    {
        // Left child 2*Current + 1, Right child 2*Current +2
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int min_index = index;
        if (left_child < size() && cmp(items[left_child], items[min_index]))
        {
            min_index = left_child;
        }
        if (right_child < size() && cmp(items[right_child], items[min_index]))
        {
            min_index = right_child;
        }
        if (min_index != index)
        {
            swap(items[index], items[min_index]);
            heapifyDown(min_index);
        }
    }
};