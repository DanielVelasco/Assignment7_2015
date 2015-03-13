#include <iostream>
#include <sstream>
#include <string.h>
#include "MovieTree.h"

using namespace std;

MovieTree::~MovieTree()
{

}


MovieTree::MovieTree()
{

    nil = new MovieNode();
	root = nil;

}





void MovieTree::InitOutputJsonObject()
{

     Assignment6Output = json_object_new_object();


}


void MovieTree::AddToJson(std::string type,std::string parameter,MovieNode *node) //the json factory. Helps me remain organized while committing to json output
{
opCount++;

string title = node->title;

json_object *jOperation = json_object_new_object();
stringstream sOperations;
sOperations << opCount;
string stringjOperationTitle = sOperations.str();
const char * charOperationsTitle = stringjOperationTitle.c_str();

    if(type == "rent")
    {


        stringstream sMovieQuantity;
        sMovieQuantity << node->quantity;
        string stringjMovieQuantity = sMovieQuantity.str();
        const char * charMovieQuantity = stringjMovieQuantity.c_str();


        json_object *jParam = json_object_new_string(parameter.c_str());
        json_object *jType = json_object_new_string(type.c_str());
        json_object *jMovieQuantity = json_object_new_string(charMovieQuantity);

        json_object_object_add(jOperation, "operation", jType);
        json_object_object_add(jOperation, "parameter", jParam);
        json_object_object_add(jOperation, "output", jMovieQuantity);

    }
    if(type == "count")
    {

        stringstream sMovieCount;
        sMovieCount << MovieCount;
        string stringjMovieCount = sMovieCount.str();
        const char * charMovieCount = stringjMovieCount.c_str();


        json_object *jType = json_object_new_string(type.c_str());
        json_object *jMovieCount = json_object_new_string(charMovieCount);

        json_object_object_add(jOperation, "operation", jType);
        json_object_object_add(jOperation, "output", jMovieCount);


    }
    if(type == "traverse")
    {


        json_object *jType = json_object_new_string(type.c_str());


        json_object_object_add(jOperation, "operation", jType);
        json_object_object_add(jOperation, "output", jArray);



    }
    if(type =="height")
    {





        stringstream sHeightTree;
        sHeightTree << HeightTree;
        string stringjHeightTree = sHeightTree.str();
        const char * charHeightTree = stringjHeightTree.c_str();



        json_object *jType = json_object_new_string(type.c_str());
        json_object *jHeight = json_object_new_string(charHeightTree);

        json_object_object_add(jOperation, "operation", jType);
        json_object_object_add(jOperation, "output", jHeight);



    } if(type =="add" || type == "delete")
    {


        json_object *jParam = json_object_new_string(parameter.c_str());
        json_object *jType = json_object_new_string(type.c_str());


        json_object_object_add(jOperation, "operation", jType);
        json_object_object_add(jOperation, "parameter", jParam);
        json_object_object_add(jOperation, "output", jArray);
    }

json_object_object_add(Assignment6Output, charOperationsTitle  , jOperation);

}



int MovieTree::countLongestPath(MovieNode* node) {
  if (node==nil) {
    return 0;
  }
  else {
    // compute the depth of each subtree
    int lDepth = countLongestPath(node->leftChild);
    int rDepth = countLongestPath(node->rightChild);
    // use the larger one subtree
    if (lDepth > rDepth) return(lDepth+1);
    else return(rDepth+1);
  }
}




void MovieTree::rightRotate(MovieNode * y)
{
   MovieNode *x;
   x = y->leftChild;
   /* x's right subtree becomes y's left subtree */
   y->leftChild = x->rightChild;
   if ( x->rightChild != nil )
       x->rightChild->parent = y;
   /* x's new parent was y's parent */
   x->parent = y->parent;
   /* Set the parent to point to x instead of y */
   /* First see whether we're at the root */
   if ( y->parent == nil )
        root = x;
  else{
       if ( y == (y->parent)->leftChild ){
           /* y was on the left of its parent */
           y->parent->leftChild  = x;
       }else{
           /* y must have been on the right */
           y->parent->rightChild  = x;
       }
   }
   /* Finally, put y on x's right */
   x->rightChild  = y;
   y->parent = x;
}


void MovieTree::leftRotate(MovieNode *x )
{
   MovieNode *y;
   y = x->rightChild;
   /* y's left subtree becomes x's right subtree */
   x->rightChild = y->leftChild ;
   if ( y->leftChild  != nil )
       y->leftChild ->parent = x;
   /* y's new parent was x's parent */
   y->parent = x->parent;
   /* Set the parent to point to y instead of x */
   /* First see whether we're at the root */
   if ( x->parent == nil )
        root = y;
  else
  {
       if ( x == (x->parent)->leftChild  )
       {
           /* x was on the left of its parent */
           x->parent->leftChild  = y;
       }else
       {
           /* x must have been on the right */
           x->parent->rightChild  = y;
       }
   }
   /* Finally, put x on y's left */
   y->leftChild  = x;
   x->parent = y;
}

MovieNode* MovieTree::addMovieNode(int rating, std::string title, int year, int quantity)
{

MovieNode *temp = new MovieNode(rating,title,year,quantity);
jArray = json_object_new_array();

    if(root == nil)
    {

        root = temp;
        root->parent = nil;
        root->rightChild = nil;
        root->leftChild = nil;

        AddToJson("add",root->title,root);

        return root;
    } else
    {


     MovieNode *y = nil;
     MovieNode *x = root;
     MovieNode *z = temp;

   //assume we don't have an empty tree, which means that root isn't NULL

    const char * charTitle = title.c_str();



    while(x != nil)
    {
        y = x;
        string titleX = x->title;



        const char * charTitleX = titleX.c_str();

        json_object *jsonTitle = json_object_new_string(titleX.c_str());

        json_object_array_add(jArray,jsonTitle);

        if(strcmp(charTitleX,charTitle) > 0)
        {

            x = x->leftChild;
        }if(strcmp(charTitleX,charTitle) < 0)
        {

            x = x->rightChild;
        }
    }

    AddToJson("add",title,x);

    z->parent = y;
    string titleY = y->title;

    const char * charTitleY = titleY.c_str();
    if(strcmp(charTitleY,charTitle) > 0)
    {

        y->leftChild = z;
        z->leftChild = nil;
       z->rightChild = nil;
    }else
    {

        y->rightChild = z;
       z->leftChild = nil;
       z->rightChild = nil;
    }


    return z;

    }
}

void MovieTree::rbDeleteFixup(MovieNode * x)
{
MovieNode *w = nil;

   while (x != root and x->isRed == false)
   {
     if (x == x->parent->leftChild)
     {
            w = x->parent->rightChild;
            if (w->isRed == true)
            {
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->rightChild;
            }
             if (w->leftChild->isRed == false and w->rightChild->isRed == false)
             {

               w->isRed = true;
               x = x->parent;
            }
           else{
               if (w->rightChild->isRed == false)
               {
                  w->leftChild->isRed = false;
                  w->isRed = true;
                  rightRotate(w);
                 w = x->parent->rightChild;
                }
               w->isRed = x->parent->isRed;
               x->parent->isRed = false;
               w->rightChild->isRed = false;
               leftRotate(x->parent);
               x = root;
        }
     }
     else
     {

            w = x->parent->leftChild;
            if (w->isRed == true)
            {
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->leftChild;
            }
             if (w->rightChild->isRed == false and w->leftChild->isRed == false)
             {

               w->isRed = true;
               x = x->parent;
            }
           else
           {
               if (w->leftChild->isRed == false)
               {
                  w->rightChild->isRed = false;
                  w->isRed = true;
                  leftRotate(w);
                 w = x->parent->leftChild;
                }
               w->isRed = x->parent->isRed;
               x->parent->isRed = false;
               w->leftChild->isRed = false;
               rightRotate(x->parent);
               x = root;
            }

     }
  x->isRed = false;
}

}
MovieNode* MovieTree::findMinimum(MovieNode *root)
{

MovieNode *node = root;

// loop down to find leftmost leaf of supplied node
while (node->leftChild != nil)
{
    node = node->leftChild;
}

  return node;
}
//u is the OG node, v is the replacement
void MovieTree::rbTransplant(MovieNode * u, MovieNode * v)
{

  if (u->parent == nil)
  {
     root = v;
   }
  else if (u == u->parent->leftChild)
  {
     u->parent->leftChild = v;
  }
  else
  {
     u->parent->rightChild = v;
  }
  v->parent = u->parent;
}

void MovieTree::removeMovieNode(MovieNode * NodetoRemove)
{

  MovieNode *y = NodetoRemove;
  bool yOG = y->isRed;
  MovieNode *x = nil;

  if (NodetoRemove->leftChild == nil)
    {
       x = NodetoRemove->rightChild;
       rbTransplant(NodetoRemove, NodetoRemove->rightChild);
    }

    else if (NodetoRemove->rightChild == nil)
    {
        x = NodetoRemove->leftChild;
        rbTransplant(NodetoRemove, NodetoRemove->leftChild);

    }
  else
  {

     y  = findMinimum(NodetoRemove->rightChild);
     yOG = y->isRed;
     x = y->rightChild;
     if (y->parent == NodetoRemove)
        {
            x->parent = y;
        }
        else{
            rbTransplant(y, y->rightChild);
            y->rightChild = NodetoRemove->rightChild;
            y->rightChild->parent = y;
        }
     rbTransplant(NodetoRemove, y);
     y->leftChild = NodetoRemove->leftChild;
     y->leftChild->parent = y;
     y->isRed = NodetoRemove->isRed;
    }
if (yOG == false)
 {

    rbDeleteFixup(x);

 }


}


void MovieTree::IsMovieInTree(string title,MovieNode *root)
{
    if(root != nil)
    {
        if(root->title == title)
            {

                MovieFound = 1;

            }if(MovieFound!=1)
            {

                IsMovieInTree(title,root->leftChild);
                IsMovieInTree(title,root->rightChild);

            }

    }
}

void MovieTree::deleteMovieNode(std::string title){

   if(root == nil)
    {

    } else {

    MovieNode *x = root;

    //assume we don't have an empty tree, which means that root isn't NULL

    const char * charTitle = title.c_str();

    while(x->title != title)
    {

        string titleX = x->title;

        const char * charTitleX = titleX.c_str();

        json_object *jsonTitle = json_object_new_string(titleX.c_str());

        json_object_array_add(jArray,jsonTitle);


        if(strcmp(charTitleX,charTitle) > 0){

            x = x->leftChild;
        }if(strcmp(charTitleX,charTitle) < 0){

            x = x->rightChild;
        }


    } if(x->title == title) {

        json_object *jsonTitle = json_object_new_string(title.c_str());
        json_object_array_add(jArray,jsonTitle);
        removeMovieNode(x);


    }



}

}



// Returns 0 if the tree is invalid, otherwise returns the black node height.
int MovieTree::rbValid(MovieNode * node)
{

    int lh = 0;
    int rh = 0;

    if (node == nil)
        return 1;

    else
    {

        if (node->isRed)
        {
            if(node->leftChild->isRed || node->rightChild->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }

        // Check for valid binary search tree.
        if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Deteremine the height of let and right children.
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }

        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }

        else
            return 0;

    }
}

void MovieTree::rbAddFixup(MovieNode *xt)
 {

    MovieNode *x = addMovieNode(xt->ranking,xt->title,xt->year,xt->quantity);

    MovieNode *y = nil;

    x->isRed = true;

    while ((x != root) &&(x->parent->isRed == true) ) {

        if ( x->parent == x->parent->parent->leftChild ) {

           y = x->parent->parent->rightChild;
          if ( y->isRed == true ) {

              x->parent->isRed = false;
             y->isRed = false;
              x->parent->parent->isRed = true;

              x = x->parent->parent;
          }
         else {

              if ( x == x->parent->rightChild ) {

                 x = x->parent;
                  leftRotate(x);
             }

              x->parent->isRed = false;
              x->parent->parent->isRed = true;
             rightRotate(x->parent->parent );
          }

      }
     else {

          y = x->parent->parent->leftChild;
          if ( y->isRed == true ) {

              x->parent->isRed = false;
             y->isRed = false;
              x->parent->parent->isRed = true;

              x = x->parent->parent;
          }
         else {

              if ( x == x->parent->leftChild ) {

                 x = x->parent;
                  rightRotate(x);
             }

              x->parent->isRed = false;
              x->parent->parent->isRed = true;
             leftRotate(x->parent->parent );
          }

    }

}
root->isRed = false;


int height = rbValid(x);

//cout << "height of black node " << height << endl; // height of black node

}
void MovieTree::countMovieNodes(MovieNode *node)
 {


  if(node->leftChild != nil)
    {

        countMovieNodes(node->leftChild);
        MovieCount++;

    }

    if(node->rightChild != nil)
    {

        countMovieNodes(node->rightChild);
        MovieCount++;

    }

 }

void MovieTree::searchMovieTree(MovieNode * root, std::string title, json_object * traverseLog)
{

  if(root != nil)
    {
    if(root->title == title)
        {

                if(root->quantity > 0)
                {

                    root->quantity = (root->quantity-1);

                    cout <<	"Movie Info:"	<<	endl;
                    cout <<	"==========="	<<	endl;
                    cout << "Ranking:" << root->ranking <<endl;
                    cout << "Title:" << root->title <<endl;
                    cout << "Year:" << root->year <<endl;
                    cout << "Quantity:" << root->quantity <<endl;



                }if(root->quantity == 0)
                {

                    cout << "Movie out of stock" << endl;
                    jArray = json_object_new_array();
                    deleteMovieNode(root->title);


                }

                    MovieFound = 1;

                    MovieSearchFound = root;

        }if(MovieFound!=1)
        {

            searchMovieTree(root->leftChild,title,traverseLog);
            searchMovieTree(root->rightChild,title,traverseLog);

        }

}

}

void MovieTree::printMovieInventory(MovieNode * root, json_object * traverseLog)
{

    if(root->leftChild != nil)
    {

        printMovieInventory(root->leftChild,traverseLog);

    }

      string title = root->title;

      json_object *jsonTitle = json_object_new_string(title.c_str());

      json_object_array_add(jArray,jsonTitle);

    if(root->rightChild != nil)
    {

        printMovieInventory(root->rightChild,traverseLog);

    }
}
