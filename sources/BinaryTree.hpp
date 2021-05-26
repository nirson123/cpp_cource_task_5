//
// Created by nir son on 25/05/2021.
//

#ifndef CPP_TASK_5_BINARYTREE_HPP
#define CPP_TASK_5_BINARYTREE_HPP

#include <vector>
#include <string>

namespace ariel {

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
        Node<T>* root;

        class preorder_iterator {
        private:
            std::vector<Node<T>*> vec;
            typename std::vector<Node<T>*>::iterator it;
            BinaryTree<T>& bt;

            void traverse(Node<T> *current_node) {
                if (current_node == nullptr) { return; }
                vec.push_back(current_node);
                traverse(current_node->left);
                traverse(current_node->right);
            }

        public:
            explicit preorder_iterator(BinaryTree<T>& bt, bool end = false) : bt(bt){
                traverse(bt.root);
                vec.push_back(nullptr);
                if (!end) { it = vec.begin(); }
                else { it = --vec.end(); }
            }

            // iterator operators
            T &operator*() const { return (*it)->value; }
            T *operator->() const { return &((*it)->value); }
            preorder_iterator &operator++() {++it; return *this;}
            const preorder_iterator operator++(int) {preorder_iterator temp = *this; it++; return temp;}
            bool operator==(const preorder_iterator &other) const { return (*(this->it) == *(other.it)); }
            bool operator!=(const preorder_iterator &other) const { return !(*this == other); }
        }; // end of preorder iterator

        class inorder_iterator {
        private:
            std::vector<Node<T>*> vec;
            typename std::vector<Node<T>*>::iterator it;
            BinaryTree<T>& bt;

            void traverse(Node<T>* current_node) {
                if (current_node == nullptr) { return; }
                traverse(current_node->left);
                vec.push_back(current_node);
                traverse(current_node->right);
            }

        public:
            explicit inorder_iterator(BinaryTree<T>& bt, bool end = false) : bt(bt){
                traverse(bt.root);
                vec.push_back(nullptr);
                if (!end) { it = vec.begin(); }
                else { it = --vec.end(); }
            }

            // iterator operators
            T &operator*() const { return (*it)->value; }
            T *operator->() const { return &((*it)->value); }
            inorder_iterator &operator++() {++it; return *this;}
            const inorder_iterator operator++(int) {inorder_iterator temp = *this; it++; return temp;}
            bool operator==(const inorder_iterator &other) const { return (*(this->it) == *(other.it)); }
            bool operator!=(const inorder_iterator &other) const { return !(*this == other); }

            friend BinaryTree<T>& BinaryTree<T>::add_left(const T &father, T val);
            friend BinaryTree<T>& BinaryTree<T>::add_right(const T &father, T val);
        };// end of inorder iterator

        class postorder_iterator {
        private:
            std::vector<Node<T>*> vec;
            typename std::vector<Node<T>*>::iterator it;
            BinaryTree<T>& bt;

            void traverse(Node<T>* current_node) {
                if (current_node == nullptr) { return; }
                traverse(current_node->left);
                traverse(current_node->right);
                vec.push_back(current_node);
            }

        public:
            explicit postorder_iterator(BinaryTree<T>& bt, bool end = false) : bt(bt){
                traverse(bt.root);
                vec.push_back(nullptr);
                if (!end) { it = vec.begin(); }
                else { it = --vec.end(); }
            }

            // iterator operators
            T &operator*() const { return (*it)->value; }
            T *operator->() const { return &((*it)->value); }
            postorder_iterator &operator++() {++it; return *this;}
            const postorder_iterator operator++(int) {postorder_iterator temp = *this; it++; return temp;}
            bool operator==(const postorder_iterator &other) const { return (*(this->it) == *(other.it)); }
            bool operator!=(const postorder_iterator &other) const { return !(*this == other); }
        };// end of postorder iterator

        void releaseNodes(Node<T>* current_node) {
            if (current_node == nullptr) { return; }
            releaseNodes(current_node->left);
            releaseNodes(current_node->right);
            delete current_node;
        }

    public:
        BinaryTree() : root(nullptr) {}
        ~BinaryTree() { releaseNodes(root); }

        // add to the tree
        BinaryTree& add_root(T val) {
            if (root == nullptr) { root = new Node<T>(val); }
            else { root->value = val; }
            return *this;
        }
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
        auto it1 = begin_inorder();
        while (it1 != end_inorder() && *it1 != father) { ++it1; }
        if (it1 == end_inorder()) { throw std::invalid_argument("the value not found in the tree!"); }

        Node<T>* fatherNode = *(it1.it);
        if (fatherNode->right == nullptr) { fatherNode->right = new Node<T>(val); }
        else { fatherNode->right->value = val; }
        return *this;
    }

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_left(const T &father, T val) {
        auto it1 = begin_inorder();
        while (it1 != end_inorder() && *it1 != father) { ++it1; }
        if (it1 == end_inorder()) { throw std::invalid_argument("the value not found in the tree!"); }

        Node<T>* fatherNode = *(it1.it);
        if (fatherNode->left == nullptr) { fatherNode->left = new Node<T>(val); }
        else { fatherNode->left->value = val; }
        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& bt) {return print_tree(os, bt.root, 0);}

    template<typename T>
    std::ostream& print_tree(std::ostream &os, const Node<T>* current_node, int space) {
        if(current_node == nullptr){return os;}
        space += 10;
        print_tree(os, current_node->right, space);
        os << std::endl;
        for(int i = 10; i < space; i++){os << " ";}
        os << current_node->value << std::endl;
        print_tree(os, current_node->left, space);
        return os;
    }
}
#endif //CPP_TASK_5_BINARYTREE_HPP
