#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct node
{
    int data;
    node *left;
    node *right;
};


node *root = nullptr;                 // root node of the list


// -----------------------------------------------------------------------------
// @brief        - Create a node object
// 
// @param value  - Value to be stored into node object
// 
// @return node* - Returns pointer to the address of the created node
// -----------------------------------------------------------------------------
node *create_node(int value = -1)
{
    node *new_node  = new node;
    new_node->data  = value;
    new_node->left  = nullptr;
    new_node->right = nullptr;

    return (new_node);

} // END of create_node function

// -----------------------------------------------------------------------------
// @brief       - Inserts a new node into a b-tree
// 
// @param root  - Accepts a pointer to the address of the root in b-tree 
//        num   - Value to be inserted into b-tree
// 
// @return root - returns a pointer to the address of the root node in b-tree
// -----------------------------------------------------------------------------
node *insert_node(node *root, int num = -1)
{
    node *my_node = create_node(num);

    // -------------------------------------------------------------------------
    // checks if current node is empty
    // -------------------------------------------------------------------------
    if (root == nullptr)
    {
        root = my_node;
        return root;
    }

    // -------------------------------------------------------------------------
    // Traverses to the right of the current node
    // -------------------------------------------------------------------------
    else if (my_node->data >= root->data)
    {
        root->right = insert_node(root->right, num);
    }

    // -------------------------------------------------------------------------
    // Traverses to the left of the current node
    // -------------------------------------------------------------------------
    else
    {
        root->left = insert_node(root->left, num);
    }

    return root;

} // END of insert function

// -----------------------------------------------------------------------------
// Implement own stack to recursively call through the tree
//  without having to worry about a stack overflow
// -----------------------------------------------------------------------------
#define MAX_STACK_ITEMS 10          // length of the stack
node *myStack [MAX_STACK_ITEMS];    // create the stack
node *current = nullptr;            // current node is instantiated to null
int top_node  = -1;                 // top_node tracks the top of the stack

// -----------------------------------------------------------------------------
// @brief - returns a pointer to the top_node in myStack
// -----------------------------------------------------------------------------
node *top()
{
  return myStack[top_node];
} // END of top

// -----------------------------------------------------------------------------
// @brief - Pushes new node to the stack
// 
// @param - head_node stores the node that will be pushed to stack
// -----------------------------------------------------------------------------
void push_node(node *head_node)
{
  top_node += 1;
  myStack[top_node] = head_node;
} // END of push_node

/**
 * @brief pops the node from top of stack
 */
void pop_node()
{
  top_node -= 1;
} // END of pop_node

// -----------------------------------------------------------------------------
// END of stack implementation
// -----------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// @brief      walks as far left as possible from any node in btree
/// @param root is of type node and contains information about current node
/// ----------------------------------------------------------------------------
void walk_left(node *root)
{
  while (current != nullptr)
      {
        push_node(current);
        current = current->left;
      }
} // END of walk_left

// ----------------------------------------------------------------------------
// @brief - Walks the tree and prints the values in order from L->G
//           Uses stack implementation instead of recursion
//
// @param - root is of type node and contains information about current node
// ----------------------------------------------------------------------------
void walk(node *root)
{
  node *popped_node = nullptr;
  current           = root;
  bool finished     = 0;

  while (!finished)
  {
    // walk far left of current node
    walk_left(current);

    // -------------------------------------------------------------------------
    // if the stack is not empty then:
    //  pop node, print popped node, go to subtree to the right of popped node
    // -------------------------------------------------------------------------
    if (top_node != -1)
    {
      popped_node = myStack[ top_node ];
      pop_node();
      printf("%d ", popped_node->data);
      current = popped_node->right;
    }

    // else the stack is empty return to caller
    else return;
  }
}

// -----------------------------------------------------------------------------
// @brief - Walks and deletes elements in a b-tree
// 
// @param root - accepts a pointer to the address of the root in b-tree
// -----------------------------------------------------------------------------
void delete_nodes(node *root)
{
    if (root != nullptr)
    {
        
        // walks to the left of current node
        delete_nodes(root->left);

        // after return pops nullptr off stack delete the current node
        delete root;

        // checks if there are any nodes to the right of the current node
        if (root->right != nullptr)
        {
            delete_nodes(root->right);
        }
    }
    
    // when root is = null return to most recent node that is not null
    return;

} // END of delete_nodes function

int main()
{
    // instantiate gcp_root to null to create empty list
    root       = nullptr;
    int nums[] = {12, 49, 2, 1, 6, 50, 36};
    int len    = sizeof(nums) / sizeof(nums[0]);

    // create and insert nodes from nums arr
    for (int i = 0; i < len; ++i)
    {
        root = insert_node(root, nums[i] );
    }

    // walks and prints the b-tree
    walk(root);


    // walk and delete the items in the b-tree
    delete_nodes(root);

    return 0;
}