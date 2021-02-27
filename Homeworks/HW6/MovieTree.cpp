#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  //write your code
  root = NULL;
}

MovieTree::~MovieTree() {
  //write your code
}

void printBST(MovieNode* parent) {
  if (parent->left != NULL) {
    printBST(parent->left);
  }
  cout << "Movie: " << parent->title << " " << parent->rating << endl;
  if (parent->right != NULL) {
    printBST(parent->right);
  }
}

void MovieTree::printMovieInventory() {
  //write your code
  if (root != NULL) {
    printBST(root);
  } else {
    cout << "Tree is Empty. Cannot print" << endl;
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //write your code
  MovieNode *leaf = new MovieNode;
  leaf->ranking = ranking;
  leaf->rating = rating;
  leaf->title = title;
  leaf->year = year;

  if(root == NULL){
    root = leaf;
    return;
  }

  MovieNode *temp = root;
  while(1){
    if(temp->title.compare(0,temp->title.size(),leaf->title) > 0){
      if(temp->left == NULL){
        temp->left = leaf;
        return;
      }
      else{
        temp = temp->left;
      }
    }
    else if(temp->title.compare(0,temp->title.size(),leaf->title) < 0){
      if(temp->right == NULL){
        temp->right = leaf;
        return;
      }
      else{
        temp = temp->right;
      } 
    }
  }
}

MovieNode* findNode(MovieNode* root, string title) {
  bool found = false;
  MovieNode* parent = root;
  while (!found) {
    if (title == parent->title) {
      found = true;
      return parent;
    }
    if (parent->left == NULL && parent->right == NULL) {
      found = true;
      return NULL;
    }
    if (parent->title >= title) {
      parent = parent->left;
    } else if (parent->title <= title) {
      parent = parent->right;
    }
  }
  return NULL;
}

void MovieTree::findMovie(string title)
{
    // Your code here
      MovieNode* found = findNode(root, title);
  if (found != NULL) {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << found->ranking << endl;
    cout << "Title  :" << found->title << endl;
    cout << "Year   :" << found->year << endl;
    cout << "rating :" << found->rating << endl;
  } else {
    cout << "Movie not found." << endl;
  }
}

void queryBST(MovieNode* parent, float rating, int year) {
  if (parent->rating >= rating && parent->year >= year) {
    cout << parent->title << "(" << parent->year << ") " << parent->rating << endl;
  }
  if (parent->left != NULL) {
    queryBST(parent->left, rating, year);
  }
  if (parent->right != NULL) {
    queryBST(parent->right, rating, year);
  }
}

void MovieTree::queryMovies(float rating, int year)
{
    // Your code here
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    queryBST(root, rating, year);
}

float add(MovieNode* root) 
{ 
  if (root == NULL) 
    return 0; 
  return (root->rating + add(root->left) + add(root->right)); 
} 

int countNodes(MovieNode* root){
  if(root == NULL){
    return 0;
  }
  return (1 + countNodes(root->left) + countNodes(root->right));
}

void MovieTree::averageRating() {
  //write your code
  if(root == NULL){
    cout << "Average rating:0.0" << endl;
    return;
  }

  float sum = add(root);
  int count = countNodes(root);
  float avg = sum/(count);
  cout << "Average rating:" << avg << endl;
  return;
}


// helper function to printLevelNodes()
void getLevel(MovieNode* node, int level) {
  if (node != NULL) {
    if (level == 0) {
      cout << "Movie: " << node -> title << " " << node -> rating << endl;
    }
    else if (level != 0) {
      getLevel(node -> left, level - 1);
      getLevel(node -> right, level - 1);
    }
  }

}

// helper function to printLevelNodes()
int maxLevel(MovieNode* node) {
  if (node == NULL) {
    return 0;
  }
  else {
    int leftD = maxLevel(node -> left);
    int rightD = maxLevel(node -> right);

    if (leftD > rightD) {
      return (leftD + 1);
    }
    else {
      return (rightD + 1);
    }
  }
}

void MovieTree::printLevelNodes(int level) {
  int max = maxLevel(root);

  if (level <= max) {
    getLevel(root, level);
  }
}
