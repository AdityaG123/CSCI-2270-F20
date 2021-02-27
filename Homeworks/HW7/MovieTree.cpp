#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void deleteNode(TreeNode *node){
    if (node == NULL){
       return;
    }
    deleteNode(node->leftChild);
    deleteNode(node->rightChild);
    LLMovieNode * head = node->head;
    while(head != NULL){
       LLMovieNode* temp = head;
       head = head->next;
       delete temp;
   }
   delete node;
}

MovieTree::~MovieTree()
{
   if(root != NULL){
        deleteNode(root);
   }
}

/* ------------------------------------------------------ */

void _grader_inorderTraversal(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		_grader_inorderTraversal(root->leftChild);
		cout << root->titleChar << " ";
		_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

void displayInOrder(TreeNode *current){
	if(current->leftChild != nullptr){
		displayInOrder(current->leftChild);
	}
	cout << "Movies starting with letter: " << current->titleChar << endl;
	LLMovieNode *temp = current->head;
	while(temp != NULL){
		cout << " >> " << temp->title << " " << temp->rating << endl;
		temp = temp->next;
	}
	if(current->rightChild != nullptr){
		displayInOrder(current->rightChild);
	}
}

void MovieTree::showMovieCollection(){
	if(root != NULL){
	    displayInOrder(root);
	}
}

TreeNode *searchTree(TreeNode *current, char move){
	if(current != NULL){
		if(current->titleChar == move){
			return current;
		}
		else if(current->titleChar > move){
			return searchTree(current->leftChild, move);
		}
		else{
			return searchTree(current->rightChild, move);
		}
	}
	else{
		return NULL;
	}
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating){
	TreeNode *current = searchTree(root, title[0]);
	if(current != NULL){
		LLMovieNode *temp = new LLMovieNode;
		temp->title = title;
		temp->ranking = ranking;
		temp->year = year;
		temp->rating = rating;
		if(current->head == NULL || current->head->title >= temp->title){
			temp->next = current->head;
			current->head = temp;
		}
		else{
			LLMovieNode *find = current->head;
			while(find->next != NULL && find->next->title < temp->title){
				find = find->next;
			}
			temp->next = find->next;
			find->next = temp;
		}
	}
	else{
		TreeNode *previous = NULL;
		TreeNode *temp1 = root;
		TreeNode *current = new TreeNode;

		current->parent = NULL;
		current->head = NULL;
		current->leftChild = NULL;
		current->rightChild = NULL;
		current->titleChar = title[0];

		while(temp1 != NULL){
			previous = temp1;
			if(current->titleChar < temp1->titleChar){
				temp1 = temp1->leftChild;
			}
			else{
				temp1 = temp1->rightChild;
			}
		}
		if(previous == NULL){
			root = current;
		}
		else if(current->titleChar < previous->titleChar){
			previous->leftChild = current;
			current->parent = previous;
		}
		else{
			previous->rightChild = current;
			current->parent = previous;
		}
		LLMovieNode *temp = new LLMovieNode;
		temp->title = title;
		temp->ranking = ranking;
		temp->year = year;
		temp->rating = rating;
		temp->next = current->head;
		current->head = temp;
		current->head->next = NULL;
	}
}

TreeNode* removeMovieRecordHelper(TreeNode* t, std::string title){
   // base case
   if (t == NULL){
       std::cout << "Movie not found." << std::endl;
       return t;
   }
   if (title.at(0) < t->titleChar){
       t->leftChild = removeMovieRecordHelper(t->leftChild, title);
   }
   else if (title.at(0) > t->titleChar){
       t->rightChild = removeMovieRecordHelper(t->rightChild, title);
   }
   else if (title.at(0) == t->titleChar){
       LLMovieNode* currNode = t->head;
       LLMovieNode* prevNode = NULL;
       while (currNode != NULL && currNode->title.compare(title) != 0){
           prevNode = currNode;
           currNode = currNode->next;
       }
       if (currNode == NULL){
           std::cout << "Movie: " << title << " not found, cannot delete." << std::endl;
           return t;
       }
       if (prevNode == NULL && t->head->next != NULL){
           t->head = t->head->next;          
           return t;
       }
       if (prevNode != NULL && currNode != NULL){
           prevNode->next = currNode->next;          
           return t;
       }
       if (t->leftChild == NULL && t->rightChild == NULL){
           delete t;
           t = NULL;
       }
       else if (t->leftChild == NULL){
           TreeNode *tempNode = t;
           t->rightChild->parent = t->parent;
           t = t->rightChild;          
           delete tempNode;
       }
       else if (t->rightChild == NULL){
           TreeNode *tempNode = t;
           t->leftChild->parent = t->parent;
           t = t->leftChild;          
           delete tempNode;
       }
       else{
           TreeNode* minValueNode = t->rightChild;
           while (minValueNode->leftChild != NULL)
           {
               minValueNode = minValueNode->leftChild;
           }
           t->head = minValueNode->head;
           t->titleChar = minValueNode->titleChar;
           t->rightChild = removeMovieRecordHelper(t->rightChild, minValueNode->head->title);
       }
   }
   return t;
} 

void MovieTree::removeMovieRecord(std::string title){
   root = removeMovieRecordHelper(root, title);
}

void MovieTree::leftRotation(TreeNode* curr){
   TreeNode* right = curr->rightChild;
   if (curr->titleChar == root->titleChar){
       curr->rightChild = right->leftChild;
       right->leftChild = curr;
       right->parent = NULL;
       curr->parent = right;
       if (curr->rightChild != NULL){
           curr->rightChild->parent = curr;
       }
       root = right;
       return;
   }
   if (curr->parent->rightChild->titleChar == curr->titleChar){
       curr->parent->rightChild = right;
   }
   else{
       curr->parent->leftChild = right;
   }
   right->parent = curr->parent;
   curr->parent = right;
   curr->rightChild = right->leftChild;
   if (right->leftChild != NULL){
       right->leftChild->parent = curr;
   }
   right->leftChild = curr;
}