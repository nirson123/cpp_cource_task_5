//
// Created by nir son on 25/05/2021.
//

#ifndef CPP_TASK_5_BINARYTREE_HPP
#define CPP_TASK_5_BINARYTREE_HPP

#include <vector>
#include <string>
#include <exception>
#include <iostream>

namespace ariel {

    // node of a binary tree
    template<typename T>
    struct Node {
        T value;
        Node *left;
        Node *right;
        Node(T val)
                : value(val), right(nullptr), left(nullptr){}
    };

    template<typename T>
    class BinaryTree {

    private:
        Node<T>* root;      // root of the tree

        // an iterator for pre-order traversal of the tree
        class preorder_iterator {
        private:
            std::vector<Node<T>*> vec;          // keep a vector of pointers to the nodes
            typename std::vector<Node<T>*>::iterator it;
            Node<T>* bt;

            void traverse(Node<T> *current_node) {  // fill the vector
                if (current_node == nullptr) { return; }
                vec.push_back(current_node);
                traverse(current_node->left);
                traverse(current_node->right);
            }

        public:
            explicit preorder_iterator(BinaryTree<T>& bt, bool end = false) : bt(bt.root){
                traverse(this->bt);
                vec.push_back(nullptr); // to indicate the end
                if (!end) { it = vec.begin(); }
                else { it = --vec.end(); }  // move to the nullptr
            }

            preorder_iterator(const preorder_iterator& other) : vec(other.vec), bt(other.bt){
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
            }

            preorder_iterator& operator=(const preorder_iterator& other){
                if(this == &other){return *this;}
                this->vec = other.vec;
                this->bt = other.bt;
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
                return *this;
            }

            preorder_iterator(const preorder_iterator&& other)  noexcept : vec(other.vec), bt(other.bt){
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
            }

            preorder_iterator& operator=(preorder_iterator&& other) noexcept {
                this->vec = other.vec;
                this->bt = other.bt;
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
                return *this;
            }

            ~preorder_iterator() = default;



            // iterator operators
            T &operator*() const { return (*it)->value; }
            T *operator->() const { return &((*it)->value); }
            preorder_iterator &operator++() {++it; return *this;}
            preorder_iterator operator++(int) {preorder_iterator temp = *this; it++; return temp;}
            bool operator==(const preorder_iterator &other) const { return (*(this->it) == *(other.it)); }
            bool operator!=(const preorder_iterator &other) const { return !(*this == other); }
        }; // end of preorder iterator

        // an iterator for in-order traversal of the tree
        class inorder_iterator {
        private:
            std::vector<Node<T>*> vec;  // keep a vector of pointers to the nodes
            typename std::vector<Node<T>*>::iterator it;
            Node<T>* bt;

            void traverse(Node<T>* current_node) { // fill the vector
                if (current_node == nullptr) { return; }
                traverse(current_node->left);
                vec.push_back(current_node);
                traverse(current_node->right);
            }

        public:
            explicit inorder_iterator(BinaryTree<T>& bt, bool end = false) : bt(bt.root){
                traverse(this->bt);
                vec.push_back(nullptr); // to indicate the end
                if (!end) { it = vec.begin(); }
                else { it = --vec.end(); }    // move to the nullptr
            }


            inorder_iterator(const inorder_iterator& other) : vec(other.vec), bt(other.bt){
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
            }

            inorder_iterator& operator=(const inorder_iterator& other){
                if(this == &other){return *this;}
                this->vec = other.vec;
                this->bt = other.bt;
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
                return *this;
            }

            inorder_iterator(const inorder_iterator&& other)  noexcept : vec(other.vec), bt(other.bt){
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
            }

            inorder_iterator& operator=(inorder_iterator&& other) noexcept {
                this->vec = other.vec;
                this->bt = other.bt;
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
                return *this;
            }

            ~inorder_iterator() = default;

            // iterator operators
            T &operator*() const { return (*it)->value; }
            T *operator->() const { return &((*it)->value); }
            inorder_iterator &operator++() {++it; return *this;}
            inorder_iterator operator++(int) {inorder_iterator temp = *this; it++; return temp;}
            bool operator==(const inorder_iterator &other) const { return (*(this->it) == *(other.it)); }
            bool operator!=(const inorder_iterator &other) const { return !(*this == other); }

            friend BinaryTree<T>& BinaryTree<T>::add_left(const T &father, T val);
            friend BinaryTree<T>& BinaryTree<T>::add_right(const T &father, T val);
        };// end of inorder iterator

        // an iterator for post-order traversal of the tree
        class postorder_iterator {
        private:
            std::vector<Node<T>*> vec;  // keep a vector of pointers to the nodes
            typename std::vector<Node<T>*>::iterator it;
            Node<T>* bt;

            void traverse(Node<T>* current_node) {  // fill the vector
                if (current_node == nullptr) { return; }
                traverse(current_node->left);
                traverse(current_node->right);
                vec.push_back(current_node);
            }

        public:
            explicit postorder_iterator(BinaryTree<T>& bt, bool end = false) : bt(bt.root){
                traverse(this->bt);
                vec.push_back(nullptr); // to indicate the end
                if (!end) { it = vec.begin(); }
                else { it = --vec.end(); }  // move to the nullptr
            }


            postorder_iterator(const postorder_iterator& other) : vec(other.vec), bt(other.bt){
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
            }

            postorder_iterator& operator=(const postorder_iterator& other){
                if(this == &other){return *this;}
                this->vec = other.vec;
                this->bt = other.bt;
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
                return *this;
            }

            postorder_iterator(const postorder_iterator&& other)  noexcept : vec(other.vec), bt(other.bt){
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
            }

            postorder_iterator& operator=(postorder_iterator&& other) noexcept {
                this->vec = other.vec;
                this->bt = other.bt;
                this->it = this->vec.begin();
                int n_moves = other.it - other.vec.begin();
                for(int i = 0; i < n_moves; i++){++(this->it);}
                return *this;
            }

            ~postorder_iterator() = default;


            // iterator operators
            T &operator*() const { return (*it)->value; }
            T *operator->() const { return &((*it)->value); }
            postorder_iterator &operator++() {++it; return *this;}
            postorder_iterator operator++(int) {postorder_iterator temp = *this; it++; return temp;}
            bool operator==(const postorder_iterator &other) const { return (*(this->it) == *(other.it)); }
            bool operator!=(const postorder_iterator &other) const { return !(*this == other); }
        };// end of postorder iterator

        // release all the node's pointers
        void releaseNodes(Node<T>* current_node) {
            if (current_node == nullptr) { return; }
            releaseNodes(current_node->left);
            releaseNodes(current_node->right);
            delete current_node;
        }

        void copy_by_value(const Node<T>* other, Node<T>*& in_this){
            in_this = new Node<T>(other->value);
            if(other->left != nullptr){copy_by_value(other->left, in_this->left);}
            if(other->right != nullptr){copy_by_value(other->right, in_this->right);}
        }

    public:
        BinaryTree() : root(nullptr) {} // simple constructor
        BinaryTree(const BinaryTree<T>& other){copy_by_value(other.root, this->root);}    // copy constructor
        BinaryTree(BinaryTree<T>&& other)  noexcept : root(other.root){other.root = nullptr;}      // moving constructor
        ~BinaryTree() { releaseNodes(root); }
        
        // assignment operator
        BinaryTree<T>& operator=(const BinaryTree<T>& other){
            if(this == &other){return *this;}
            releaseNodes(this->root);
            copy_by_value(other.root, this->root);
            return *this;
        }

        // moving operator
        BinaryTree<T>& operator=(BinaryTree<T>&& other) noexcept {
            releaseNodes(this->root);
            this->root = other.root;
            other.root = nullptr;
        }

        // add (or change the data) root to the tree
        BinaryTree& add_root(T val) {
            if (root == nullptr) { root = new Node<T>(val); }
            else { root->value = val; }
            return *this;
        }

        //add or change nodes in the graph (out-line implementation)
        BinaryTree& add_right(const T &father, T val);
        BinaryTree& add_left(const T &father, T val);

        // iterators
        preorder_iterator begin_preorder() { return preorder_iterator(*this); }
        preorder_iterator end_preorder() { return preorder_iterator(*this, true); }
        inorder_iterator begin_inorder() { return inorder_iterator(*this); }
        inorder_iterator end_inorder() { return inorder_iterator(*this, true); }
        postorder_iterator begin_postorder() { return postorder_iterator(*this); }
        postorder_iterator end_postorder() { return postorder_iterator(*this, true); }
        inorder_iterator begin() { return begin_inorder(); }
        inorder_iterator end() { return end_inorder(); }

        //output operator
        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree<U>& bt);
        template <typename V>
        friend std::ostream &print_tree(std::ostream& os, const Node<V>* current_node, int space); //helper for printing
    };


    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_right(const T &father, T val) {
        // find the father node
        auto it1 = begin_inorder();
        while (it1 != end_inorder() && !(*it1 == father)) { ++it1; }

        // if not found, throw exception
        if (it1 == end_inorder()) { throw std::invalid_argument("the value not found in the tree!"); }


        Node<T>* fatherNode = *(it1.it);    // get the node object
        if (fatherNode->right == nullptr) { fatherNode->right = new Node<T>(val); } // add
        else { fatherNode->right->value = val; }    // change
        return *this;
    }

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_left(const T &father, T val) {
        // find the father node
        auto it1 = begin_inorder();
        while (it1 != end_inorder() && !(*it1 == father)) { ++it1; }

        // if not found, throw exception
        if (it1 == end_inorder()) { throw std::invalid_argument("the value not found in the tree!"); }

        Node<T>* fatherNode = *(it1.it);    // get the node object
        if (fatherNode->left == nullptr) { fatherNode->left = new Node<T>(val); } // add
        else { fatherNode->left->value = val; } // change
        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& bt) {return print_tree(os, bt.root, 0);}

    template<typename T>
    std::ostream& print_tree(std::ostream& os, const Node<T>* current_node, int space) {
        static const int SPACES = 10;   // difference between lines

        if(current_node == nullptr){return os;}

        space += SPACES;
        print_tree(os, current_node->right, space); // recursively print right child
        os << std::endl;

        for(int i = SPACES; i < space; i++){os << " ";} // print spaces

        os << current_node->value << std::endl; // print value

        print_tree(os, current_node->left, space);  // recursively print left child
        return os;
    }
}
#endif //CPP_TASK_5_BINARYTREE_HPP
