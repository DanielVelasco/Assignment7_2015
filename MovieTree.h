#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <json/json.h>

struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        // Now that we are using nil these NULL's should be overwritten in addMovieNode.
    	leftChild = NULL;
    	rightChild = NULL;
        parent = NULL;
        isRed = true;
    }

};

class MovieTree
{
        int opCount;

    public:
        MovieTree();
        virtual ~MovieTree();
        void InitOutputJsonObject();
        int rbValid(MovieNode * node);
        int MovieFound;
        int MovieCount;
        int HeightTree;
        json_object * Assignment6Output;
        json_object * jArray;
        MovieNode *root;
        MovieNode *MovieSearchFound;

        //   void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void deleteMovieNode(std::string title);
        void searchMovieTree(MovieNode *node, std::string title, json_object * traverseLog);
        void AddToJson(std::string type,std::string parameter, MovieNode *node);
        void IsMovieInTree(std::string title,MovieNode *node);
        void printMovieInventory(MovieNode * node, json_object * traverseLog);
        void countMovieNodes(MovieNode *node);
        void rbAddFixup(MovieNode * node); // called after insert to fix tree
        int countLongestPath(MovieNode *node);
        MovieNode* addMovieNode(int ranking, std::string title, int releaseYear, int quantity);

    protected:

    private:

      void leftRotate(MovieNode * x);
      void rightRotate(MovieNode * y);
      void rbDeleteFixup(MovieNode * node);
      void rbTransplant(MovieNode * u, MovieNode * v);
      void removeMovieNode(MovieNode * NodetoRemove);
      MovieNode* findMinimum(MovieNode *root);
      MovieNode *nil;

};

#endif // MOVIETREE_H
