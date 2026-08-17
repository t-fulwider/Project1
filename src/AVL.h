#pragma once
#include <string>
#include <utility>
#include <vector>

using namespace std;

// template given by Prof. Kapoor and DsA class
class AVL {

    struct Node {
        string _ufid;
        string _name;
        int _height;
        Node *_left, *_right;

        Node(string ufid, string name) : _ufid(ufid), _name(std::move(name)), _height(1), _left(nullptr), _right(nullptr) {
        };
    };

    Node *_root;

    // Height
    // Returns 1-based height of tree. In other words, if it is empty, the height is 0, otherwise this returns the length
    //  of the longest path in nodes.
    int Height(Node* root);

    //Rotations
    Node* RotateLeft(Node* node);
    Node* RotateRight(Node* node);

    //Helper functions

    Node* InsertHelper(Node* root, const string& ufid, const string& name);
    void DeleteHelper(Node* root);
    Node* RemoveIDHelper(Node* root, const string& ufid, bool& removed);

    // find the inorder SUCCESSOR for given node, used for deletion
    Node* InorderSuccessor(Node* root);

    void PostorderHelper(Node* node, vector<string>& result, string& variable);
    void PreorderHelper(Node* node, vector<string>& result, string& variable);
    void InorderHelper(Node* node, vector<string>& result, string& variable);


public:
    // constructor and destructor
    AVL();

    ~AVL();

    // Class Methods

    // checks if ufid is valid under constraints
    bool IsUfidValid(const string& ufid);

    // checks if name is valid under constraints
    bool IsNameValid(const string& name);

    // Inserts into BST. If successful, returns true, otherwise false.
    // Will fail if UFID already exists in the tree.
    bool Insert(const string& name, const string& ufid);

    // Searches for node with given UFID. Returns an string - if not found, returns empty string
    string SearchID(const string& ufid);

    // Searches for name. Since multiple UFID's can share the same name, returns a vector with all matching ID's in preorder traversal order.
    // If none are found, the returned vector will be empty.
    vector<string> SearchName(const string &name);

    // Deletes node with provided UFID. If found (and removed), return true. If node was not present, return false.
    // If there are two children, replaces with inorder SUCCESSOR.
    bool RemoveID(const string& ufid);

    // remove the node at index if tree was an ascending list
    bool RemoveInorder(int index);

    // Performs a preorder traversal and returns list of strings if there were nodes in the tree.
    vector<string> TraversePreorder(string variable);

    // Performs an inorder traversal and returns list of strings if there were nodes in the tree.
    vector<string> TraverseInorder(string variable);

    // Performs a postorder traversal and returns list of strings if there were nodes in the tree.
    vector<string> TraversePostorder(string variable);

    // print all nodes in inorder traversal
    void PrintInorder();

    // print all nodes in preorder traversal
    void PrintPreorder();

    // print all nodes in postorder traversal
    void PrintPostorder();

    // print the number of levels in tree if any, return that number for testing
    int PrintLevelCount();
};