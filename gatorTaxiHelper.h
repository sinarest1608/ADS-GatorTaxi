// KSHITIJ SINHA
// UFID: 1416-0481
// COP5536 - Spring23

// Importing basic libraries for I/O, File Handling and the gatorTaxiHelper file
// that has the GatorTaxi class and the required functions along with "minHeap.h" and
// "rbt.h" header files which have the custom implemented MinHeap and the RedBlackTree
#include <iostream>
#include <vector>
#include <map>
#include "minHeap.h"
#include "rbt.h"

using namespace std;

//  Gator Taxi class
class GatorTaxi
{
    // Create Min Heap Object
    MinHeap<MinHeapNode> min_heap;

    // Create Red Black Tree
    map<int, RedBlackTreeNode *> redBlackTree;

public:
    void Print(int rideNumber)
    {
        // create stream for output file
        ofstream outfile;
        string file_output = "";
        outfile.open("output_file.txt", ios_base::app);

        if (redBlackTree.find(rideNumber) != redBlackTree.end())
        {
            RedBlackTreeNode *node = redBlackTree[rideNumber];
            file_output = "(" + to_string(node->rideNumber) + "," + to_string(node->rideCost) + "," + to_string(node->tripDuration) + ")" + "\n";

            // Adding the file_output variable which has th calculated output for the particular command to the output file.
            outfile << file_output;
        }
        else
        {

            file_output = "(0,0,0)";
            file_output += "\n";
            outfile << file_output;
        }
    }

    void Print(int rideNumber1, int rideNumber2)
    {
        // create stream for output file
        ofstream outfile;

        outfile.open("output_file.txt", ios_base::app);
        auto iterator = redBlackTree.lower_bound(rideNumber1);
        string file_output = "";
        while (iterator != redBlackTree.end() and iterator->first <= rideNumber2)
        {
            RedBlackTreeNode *node = iterator->second;
            file_output += "(" + to_string(node->rideNumber) + "," + to_string(node->rideCost) + "," + to_string(node->tripDuration) + "),";
            ++iterator;
        }
        file_output = file_output.substr(0, file_output.size() - 1);
        if (file_output == "")
        {
            file_output = "(0,0,0)";
        }
        file_output += "\n";

        // Adding the file_output variable which has th calculated output for the particular command to the output file.
        outfile << file_output;
    }

    void Insert(int rideNumber, int rideCost, int tripDuration)
    {

        // If already present i.e duplicate entry,exit program
        if (redBlackTree.find(rideNumber) != redBlackTree.end())
        {
            // create stream for output file
            ofstream outfile;
            outfile.open("output_file.txt", ios_base::app);
            string file_output = "Duplicate RideNumber";
            outfile << file_output;
            outfile.close(); // Close output file
            exit(0);         // Exit the program
        }

        // If unique entry, insert intro the data structures.
        MinHeapNode minHeapNode(rideNumber, rideCost, tripDuration);

        RedBlackTreeNode *redBlackTreeNode = new RedBlackTreeNode(rideNumber, rideCost, tripDuration);
        redBlackTree[rideNumber] = redBlackTreeNode;
        minHeapNode.rbtNode = redBlackTreeNode;

        min_heap.insert(minHeapNode);

        MinHeapNode top_node = min_heap.getRoot();
        redBlackTreeNode->minHeapNode = &top_node;
    }

    void GetNextRide()
    {
        // create stream for output file
        ofstream outfile;
        outfile.open("output_file.txt", ios_base::app);

        string file_output = "";

        // If heap empty, no active ride requests for next ride.
        if (min_heap.clear())
        {
            file_output = "No active ride requests\n";
            outfile << file_output;
            return;
        }
        MinHeapNode selected = min_heap.getRoot();
        min_heap.heapDelete();
        redBlackTree.erase(selected.rideNumber);
        delete selected.rbtNode;
        file_output = "(" + to_string(selected.rideNumber) + "," + to_string(selected.rideCost) + "," + to_string(selected.tripDuration) + ")" + "\n";

        // Adding the file_output variable which has th calculated output for the particular command to the output file.
        outfile << file_output;
        return;
    }

    void CancelRide(int rideNumber)
    {
        // Entry not in tree,return
        if (redBlackTree.find(rideNumber) == redBlackTree.end())
        {
            return;
        }
        // If present, erase as usual
        RedBlackTreeNode *redBlackTreeNode = redBlackTree[rideNumber];
        MinHeapNode temp = *redBlackTreeNode->minHeapNode;
        redBlackTree.erase(rideNumber);

        MinHeap<MinHeapNode> temp_min_heap;

        while (!min_heap.clear())
        {
            MinHeapNode elem = min_heap.getRoot();
            min_heap.heapDelete();
            if (elem.rideNumber != rideNumber)
            {
                temp_min_heap.insert(elem);
            }
            else
            {
                break;
            }
        }

        while (!min_heap.clear())
        {
            temp_min_heap.insert(min_heap.getRoot());
            min_heap.heapDelete();
        }

        swap(min_heap, temp_min_heap);

        delete redBlackTreeNode;
    }

    void UpdateTrip(int rideNumber, int new_tripDuration)
    {
        // create stream for output file
        ofstream outfile;
        outfile.open("output_file.txt", ios_base::app);

        // Search in tree, if not found!
        if (redBlackTree.find(rideNumber) == redBlackTree.end())
        {
            string file_output = "Ride not found\n";
            outfile << file_output;
            return;
        }

        //  Else update the trip according to trip duration.
        RedBlackTreeNode *redBlackTreeNode = redBlackTree[rideNumber];
        int old_trip_cost = redBlackTreeNode->rideCost;
        int old_tripDuration = redBlackTreeNode->tripDuration;

        if (new_tripDuration <= old_tripDuration)
        {
            CancelRide(rideNumber);
            Insert(rideNumber, old_trip_cost, new_tripDuration);
        }
        // when current trip duration is twice old duration
        else if (old_tripDuration < new_tripDuration and new_tripDuration <= 2 * old_tripDuration)
        {
            CancelRide(rideNumber);
            Insert(rideNumber, old_trip_cost + 10, new_tripDuration);
        }
        else
        {
            CancelRide(rideNumber);
        }
    }
};