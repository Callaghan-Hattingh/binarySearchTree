#include <iostream>
#include <cstdlib>

#include "bst.h"

using namespace std;

BST::BST()
{
    root = NULL;
}

BST::node* BST::CreateLeaf(int key)
{
    node* n = new node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}


void BST::AddLeaf(int key)
{
    AddLeafPrivate(key, root);
}


void BST::AddLeafPrivate(int key, node* Ptr)
{
    if (root == NULL)
    {
        root = CreateLeaf(key);
    }
    else if (key < Ptr->key)
    {
        if (Ptr->left != NULL)
        {
            AddLeafPrivate(key, Ptr->left);
        }
        else
        {
            Ptr->left = CreateLeaf(key);
        }
    }
    else if (key > Ptr->key)
    {
        if (Ptr->right != NULL)
        {
            AddLeafPrivate(key, Ptr->right);
        }
        else
        {
            Ptr->right = CreateLeaf(key);
        }
    }
    else
    {
        cout << "The key " << key << "has already been added to the tree.\n";
    }
}


void BST::PrintInOrder()
{
    PrintInOrderPrivate(root);
}

void BST::PrintInOrderPrivate(node* Ptr)
{
    if (root == NULL)
    {
        cout << "the bst is empty.\n";
    }
    else
    {
        if (Ptr->left != NULL)
        {
            PrintInOrderPrivate(Ptr->left);
        }
        cout << Ptr->key << " ";
        if (Ptr->right != NULL)
        {
            PrintInOrderPrivate(Ptr->right);
        }
    }
    
}

BST::node* BST::ReturnNode(int key)
{
    return ReturnNodePrivate(key, root);
}

BST::node* BST::ReturnNodePrivate(int key, node* Ptr)
{
    if (Ptr != NULL)
    {
        if(Ptr->key == key)
        {
            return Ptr;
        }
        else
        {
            if(key < Ptr->key)
            {
                return ReturnNodePrivate(key, Ptr->left);
            }
            else
            {
                return ReturnNodePrivate(key, Ptr->right);
            }
        }
    }
    else
    {
        return NULL;
    }

}

int BST::ReturnRootKey()
{
    if(root == NULL)
    {
        return -1;
    }
    else
    {
        return root->key;
    }
}

void BST::PrintChildren(int key)
{
    node* Ptr = ReturnNode(key);

    if(Ptr != NULL)
    {
        cout << "Parent Node = " << Ptr->key << endl;

        Ptr->left == NULL ?
        cout << "Left Child = NULL\n": 
        cout << "Left Child = " << Ptr->left->key << endl;

        Ptr->right == NULL ?
        cout << "Right Child = NULL\n": 
        cout << "Right Child = " << Ptr->right->key << endl;
        
    }
    else
    {
        cout << "Key " << key << " does not exist.\n";
    }
}

int BST::FindSmallest()
{
    return FindSmallestPrivate(root);
}

int BST::FindSmallestPrivate(node* Ptr)
{
    if(root == NULL)
    {
        cout << "The tree is empty.\n";
        return -1;
    }
    else
    {
        if(Ptr->left != NULL)
        {
            return FindSmallestPrivate(Ptr->left);
        }
        else
        {
            return Ptr->key;
        }
    }
}

void BST::RemoveNode(int key)
{
    RemoveNodePrivate(key, root);
}

void BST::RemoveNodePrivate(int key, node* parent)
{
    if(root == NULL)
    {
        cout << "Tree is empty.\n";
    }
    else
    {
        if(root->key == key)
        {
            RemoveRootMatch();
        }
        else if(key < parent->key && parent->left != NULL)
        {
            parent->left->key == key?
            RemoveMatch(parent, parent->left, true) :
            RemoveNodePrivate(key, parent->left);
        }
        else if (key > parent->key && parent->right != NULL)
        {
            parent->right->key == key?
            RemoveMatch(parent, parent->right, false) :
            RemoveNodePrivate(key, parent->right);

        }
        else
        {
            cout << "Key: " << key << " not found in tree.";
        }
    }
}

void BST::RemoveRootMatch()
{
    if(root == NULL)
    {
        cout << "Tree is empty.\n";
    }
    else
    {
        node* delPtr = root;
        int rootKey = root->key;
        int smallestInRightSubtree;

        // case 0 - 0 children
        if(root->left == NULL && root->right == NULL)
        {
            root = NULL;
            delete delPtr;
            cout << "Removed root: " << rootKey << endl;
        }
        // case 1 - 1 child
        else if (root->left == NULL && root->right != NULL)
        {
            root = root->right;
            delPtr->right == NULL;
            delete delPtr;
            cout << "Removed root: " << rootKey << endl;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            root = root->left;
            delPtr->left == NULL;
            delete delPtr;
            cout << "Removed root: " << rootKey << endl;
        }
        // case 2 - 2 children
        else
        {
            smallestInRightSubtree = FindSmallestPrivate(root->right);
            RemoveNodePrivate(smallestInRightSubtree, root);
            root->key = smallestInRightSubtree;
            cout << "Removed root: " << rootKey << endl;
            
        }
        

    }
}

void BST::RemoveMatch(node* parent, node* match, bool leftSideParent)
{
    int smallestInRightSubtree;

    if(root == NULL)
    {
        cout << "Can not remove match, tree empty.";
    }
    else
    {
        // case 0 - 0 children
        if(match->left == NULL && match->right == NULL)
        {
            if(leftSideParent == true)
            {
                parent->left = NULL;
                delete match;
            }
            else
            {
                parent->right = NULL;
                delete match;
            }
            
        }
        // case 1 - 1 child
        else if (match->left == NULL && match->right != NULL)
        {
            if(leftSideParent == true)
            {
                parent->left = match->right;
                match->right = NULL;
                delete match;
            }
            else
            {
                parent->right = match->right;
                match->right = NULL;
                delete match;
            }
        }
        else if (match->left != NULL && match->right == NULL)
        {
            if(leftSideParent == true)
            {
                parent->left = match->left;
                match->left = NULL;
                delete match;
            }
            else
            {
                parent->right = match->left;
                match->left = NULL;
                delete match;
            }
        }
        // case 2 - 2 children
        else
        {
            smallestInRightSubtree = FindSmallestPrivate(match->right);
            RemoveNodePrivate(smallestInRightSubtree, match);
            match->key = smallestInRightSubtree;

        }
    }
}

BST::~BST(){
    RemoveSubtree(root);
}

void BST::RemoveSubtree(node* Ptr)
{
    if(Ptr != NULL)
    {
        if(Ptr->left != NULL)
        {
            RemoveSubtree(Ptr->left);
        }
        if(Ptr->right != NULL)
        {
            RemoveSubtree(Ptr->right);
        }
        cout << "Deleting Node with key: " << Ptr->key << endl;
        delete Ptr;
    }
}