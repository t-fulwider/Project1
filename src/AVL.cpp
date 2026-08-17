#include <iostream>
#include <cctype>
#include <regex>
#include "AVL.h"
// == Constructor and Destructor == //
AVL::AVL()
{
	_root = nullptr;
}
AVL::~AVL()
{
	DeleteHelper(_root);
}

int AVL::Height(Node* root)
{
	// check if root is nullptr (height would be 0)
	// else, return the roots height value (should be 1-based tree height)
	return 1 + max(root->_left? root->_left->_height: 0,root->_right?  root->_right->_height: 0);
}

// == Rotations == //
AVL::Node* AVL::RotateLeft(Node *node)
{
	// given by Prof. Kapoor
	if (!node || !node->_right)
		return node;
	Node* grandchild = node->_right->_left;
	Node* newParent = node->_right;
	newParent->_left = node;
	node->_right = grandchild;
	node->_height = Height(node);
	newParent->_height = Height(newParent);
	return newParent;
}
AVL::Node* AVL::RotateRight(Node *node)
{
	// given by Prof. Kapoor
	if (!node || !node->_left)
		return node;
	Node* grandchild = node->_left->_right;
	Node* newParent = node->_left;
	newParent->_right = node;
	node->_left = grandchild;
	node->_height = Height(node);
	newParent->_height = Height(newParent);
	return newParent;
}

// == Helper Functions == //
void AVL::DeleteHelper(Node *root)
{
	// if root is nullptr, nothing to delete
	if (root == nullptr)
		return;
	// Postorder traverse and delete nodes (hit all children before parent)
	DeleteHelper(root->_left);
	DeleteHelper(root->_right);
	delete root;
}
AVL::Node* AVL::InsertHelper(Node* root, const string& ufid, const string &name)
{

	// if current node is nullptr, insert the new node here
	if (root == nullptr)
	{
		root = new Node(ufid, name);
		return root;
	}
	// search tree
	// if given ufid is less than current, go to the left
	if (ufid < root->_ufid)
		root->_left = InsertHelper(root->_left, ufid, name);
	else
		// if given ufid is more than current, go to the right
		root->_right = InsertHelper(root->_right, ufid, name);

	// update height of each node called in recursive path
	root->_height = Height(root);
	// ROTATIONS!!!!
	// compute balance factor if children exist (to avoid segv)
	int balanceFactor = (root->_left? root->_left->_height: 0) - (root->_right? root->_right->_height: 0);
	// subtree/tree is right heavy
	if (balanceFactor == -2)
	{
		// if this is a right-left case
		if ((root->_right->_left? root->_right->_left->_height: 0) - (root->_right->_right? root->_right->_right->_height: 0) == 1)
		{
			root->_right = RotateRight(root->_right);
			root = RotateLeft(root);
		}
		// right - right case
		else
			root = RotateLeft(root);
	}
	// tree is left heavy
	else if (balanceFactor == 2)
	{
		// tree is a left-right case
		if ((root->_left->_left? root->_left->_left->_height: 0) - (root->_left->_right? root->_left->_right->_height: 0) == -1)
		{
			root->_left = RotateLeft(root->_left);
			root = RotateRight(root);
		}
		// left - left case
		else
			root = RotateRight(root);
	}
	return root;
}
AVL::Node* AVL::RemoveIDHelper(Node* root, const string& ufid, bool& removed)
{
	// check if node exists
	if (root == nullptr)
		return root;
	// traverse through list to find matching ufid
	if (ufid < root->_ufid)
	{
		root->_left = RemoveIDHelper(root->_left, ufid, removed);
	}
	else if (ufid > root->_ufid)
	{
		root->_right = RemoveIDHelper(root->_right, ufid, removed);
	}
	else
	{
		removed = true;
		// no children
		if (root->_right == nullptr && root->_left == nullptr)
		{
			delete root;
			// avoid dangling pointer
			return nullptr;
		}
		// one child (has left child)
		else if (root->_right == nullptr)
		{
			Node* temp = root->_left;
			delete root;
			return temp;
		}
		// one child (has right child)
		else if (root->_left == nullptr)
		{
			Node* temp = root->_right;
			delete root;
			return temp;
		}
		// two children
		else
		{
			// find inorder successor
			Node* newRoot = InorderSuccessor(root);
			// swap the values between the two
			root->_ufid = newRoot->_ufid;
			root->_name = newRoot->_name;
			// remove the node that was where inorder successor used to be
			root->_right = RemoveIDHelper(root->_right, newRoot->_ufid, removed);
			return root;
		}
	}
	// update the height
	root->_height = Height(root);
	return root;
}
AVL::Node* AVL::InorderSuccessor(Node* root)
{
	// if node doesn't exist or has no right child, there is no inorder successor
	if (root == nullptr || root->_right == nullptr)
		return nullptr;
	Node* current = root->_right;
	// find the leftmost leaf of the root's right child
	while (current->_left != nullptr)
		current = current->_left;
	return current;
}
void AVL::PreorderHelper(Node* node, vector<string>& result, string& variable)
{
	if (node == nullptr)
		return;
	// NLR (operate root, then go left, then go right)
	// determine if we're looking for the names or ufids (for printing)
	if (variable == "name")
		result.push_back(node->_name);
	else
		result.push_back(node->_ufid);
	PreorderHelper(node->_left, result, variable);
	PreorderHelper(node->_right, result, variable);
}
void AVL::PostorderHelper(Node* node, vector<string>& result, string& variable)
{
	if (node == nullptr)
		return;
	// LRN (go left, go right, operate on current node)
	PostorderHelper(node->_left, result, variable);
	PostorderHelper(node->_right, result, variable);
	if (variable == "name")
		result.push_back(node->_name);
	else
		result.push_back(node->_ufid);
}
void AVL::InorderHelper(Node* node, vector<string>& result, string& variable)
{
	if (node == nullptr)
		return;
	// LNR (go left, operate on current, then go right)
	InorderHelper(node->_left, result, variable);
	if (variable == "name")
		result.push_back(node->_name);
	else
		result.push_back(node->_ufid);
	InorderHelper(node->_right, result,variable);
}

// == Class Methods == //
bool AVL::IsUfidValid(const string &ufid)
{
	// ufid must contain solely 8 digits (characters '0-9')
	if (ufid.length() != 8)
		return false;
	regex constraint = regex("[0-9]{8}");
	// checks ufid to see if 8 digits in a row
	return regex_match(ufid, constraint);
}
bool AVL::IsNameValid(const string &name)
{
	// name can be any length; only contain 'A-Z', 'a-z' or spaces
	// CANNOT be empty
	regex constraint = regex("^[A-Za-z\\s]+$");
	return regex_match(name, constraint);
}
bool AVL::Insert(const string& name, const string& ufid)
{
	// add check to see if ufid already exists
	if (!IsNameValid(name) || !IsUfidValid(ufid) || !SearchID(ufid).empty())
	{
		cout << "unsuccessful";
		return false;
	}

	_root = InsertHelper(_root, ufid, name);
	cout << "successful";
	return true;
}
string AVL::SearchID(const string& ufid)
{
	// temporary node to traverse tree
	Node* tempNode = _root;
	// search tree until reaching a leaf's child (nullptr)
	while (tempNode != nullptr)
	{
		// tree node / student found
		if (ufid == tempNode->_ufid)
			return tempNode->_name;
		// ufid greater than current, go right
		if (ufid > tempNode->_ufid)
			tempNode = tempNode->_right;
		else
			// ufid less than current, go right
			tempNode = tempNode->_left;
	}
	// matching ufid never found, return empty string
	return "";
}
vector<string> AVL::SearchName(const string& name)
{
	//traverse list to hit every node
	// if names match, push node into a vector
	if (!IsNameValid(name))
	{
		// quick check for valid name
		cout << "unsuccessful";
		return {};
	}
	// create two vectors, one for name, one for id's
	vector<string> nameVec = TraversePreorder("name");
	vector<string> idVec = TraversePreorder("ufid");
	vector<string> result;
	for (int i = 0; i < nameVec.size(); i++)
	{
		// if names match, push the corresponding ID into result
		if (nameVec[i] == name)
			result.push_back(idVec[i]);
	}
	if (result.empty())
		cout << "unsuccessful";
	else
	{
		// simple print loop
		for (int i = 0; i < result.size() - 1; i++)
			cout << result[i] << endl;
		cout << result.back();
	}
	return result;
}
bool AVL::RemoveID(const string& ufid)
{
	// initialize whether node was removed or not
	bool removed = false;
	_root = RemoveIDHelper(_root, ufid, removed);
	if (!removed)
	{
		cout << "unsuccessful";
		return false;
	}
	cout << "successful";
	return true;
}
bool AVL::RemoveInorder(int index)
{
	// turn tree into linear, ascending list
	vector<string> inOrderVec = TraverseInorder("ufid");
	// make sure index is in range
	if (index < 0 || index >= inOrderVec.size())
	{
		cout << "unsuccessful";
		return false;
	}
	// remove the node at index
	bool result = RemoveID(inOrderVec[index]);
	return result;
}
vector<string> AVL::TraversePreorder(string variable)
{
	vector<string> result;
	PreorderHelper(_root, result, variable);
	return result;
}
vector<string> AVL::TraverseInorder(string variable)
{
	vector<string> result;
	InorderHelper(_root, result, variable);
	return result;
}
vector<string> AVL::TraversePostorder(string variable)
{
	vector<string> result;
	PostorderHelper(_root, result, variable);
	return result;
}
void AVL::PrintInorder()
{
	vector<string> printStr = TraverseInorder("name");
	// make sure tree is not empty
	if (printStr.empty())
		return;
	for (int i = 0; i < printStr.size() - 1; i++)
		cout << printStr[i] << ", ";
	// avoid extra comma at end
	cout << printStr.back();
}
void AVL::PrintPreorder()
{
	vector<string> printStr = TraversePreorder("name");
	// make sure tree is not empty
	if (printStr.empty())
		return;
	for (int i = 0; i < printStr.size() - 1; i++)
		cout << printStr[i] << ", ";
	// avoid extra comma at end
	cout << printStr.back();
}
void AVL::PrintPostorder()
{
	vector<string> printStr = TraversePostorder("name");
	// make sure tree is not empty
	if (printStr.empty())
		return;
	for (int i = 0; i < printStr.size() - 1; i++)
		cout << printStr[i] << ", ";
	// avoid extra comma at end
	cout << printStr.back();
}
int AVL::PrintLevelCount()
{
	// if tree empty, level is 0
	if (_root == nullptr)
	{
		cout << 0;
		return 0;
	}
	// else, level count is the height of tree
	cout << _root->_height;
	return _root->_height;
}