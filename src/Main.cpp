#include <iostream>
#include <fstream>
#include <memory>
#include <string>

class TreeNode{
public:
    int data;
    int count;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(int x){
        data = x;
        count = 1;
        left = NULL;
        right = NULL;
    }
};

class Tree{
private:
    std::shared_ptr<TreeNode> root;
    int* array;
    int index;
    int ComparisonCount;
    int NumberOfNodes;

    void inOrder(std::shared_ptr<TreeNode> node){
        if(node->left != NULL){
            ComparisonCount++;
            inOrder(node->left);
        }
        array[index] = node->data;
        index++;
        if(node->right != NULL){
            ComparisonCount++;
            inOrder(node->right);
        }
    }

public:
    Tree(){
        root = NULL;
        ComparisonCount = 0;
        NumberOfNodes = 0;
        array = new int[0];
    }

    void add(int* x, int size){
        for(int i = 0; i < size; i++){
            add(*x);
            x++;
        }
    }

    void add(int num){
        if(root == NULL){
            root = std::make_shared<TreeNode>(num);
            NumberOfNodes++;
        }
        bool searching = true;
        std::shared_ptr curr = root;
        while(searching){
            ComparisonCount++;
            if(num == curr->data){
                curr->count++;
                searching = false;
            }
            else if(num < curr->data){
                if(curr->left == NULL){
                    curr->left = std::make_shared<TreeNode>(num);
                    searching = false;
                    NumberOfNodes++;
                }
                else{
                    curr = curr->left;
                }
            }
            else if(num > curr->data){
                if(curr->right == NULL){
                    curr->right = std::make_shared<TreeNode>(num);
                    searching = false;
                    NumberOfNodes++;
                }
                else{
                    curr = curr->right;
                }
            }
        }
    }

    int* toSortedArray(){
        delete[] array;
        array = new int[NumberOfNodes];
        index = 0;
        inOrder(root);
        return array;
    }

    int getSize(){
        return NumberOfNodes;
    }

    int getComparisonCount(){
        return ComparisonCount;
    }

    ~Tree(){
        delete[] array;
    }
};

class BubbleSort{// I know this looks dumb but its easier to get the comparison count this way under any other circumstance this would not be a class
private:
    int ComparisonCount;
public:
    BubbleSort(){
        ComparisonCount = 0;
    }

    int* sort(int* x, int size){
        int* array = new int[size];
        int temp;
        for(int i = 0; i < size; i++){
            array[i] = x[i];
        }
        bool swapping = true;
        while(swapping){
            swapping = false;
            for(int i = 1; i < size; i++){
                ComparisonCount++;
                if(array[i - 1] > array[i]){
                    temp = array[i-1];
                    array[i-1] = array[i];
                    array[i] = temp;
                    swapping = true;
                }
            }
        }
        return array;
    }

    int getComparisonCount(){
        return ComparisonCount;
    }
};

int main(){
    Tree tree = Tree();
    BubbleSort bubble = BubbleSort();

    std::string path;
    std::cout << "Enter file path\n>>> ";
    std::getline(std::cin, path);
    std::ifstream file;
    file.open(path.c_str());
    if(file.is_open() == 0){
        std::cout << "Invalid filepath";
        return 1;
    }

    int num;
    int lines;
    while(file >> num){
        lines++;
    }
    file.close();
    int* array = new int[lines];
    int i = 0;
    file.open(path.c_str());
    while(file >> num){
        array[i] = num;
        i++;
    }
    file.close();
    
    tree.add(array, lines);
    int* BubbleSorted = bubble.sort(array, lines);
    int* TreeSorted = tree.toSortedArray();

    std::cout << "\nlist sorted with a tree:\n";
    for(i = 0; i < tree.getSize(); i++){
        std::cout << TreeSorted[i] << " ";
    }
    std::cout << "\nComparisons " << tree.getComparisonCount() << '\n';

    std::cout << "\nlist sorted with bubbles:\n";
    for(i = 0; i < lines; i++){
        std::cout << BubbleSorted[i] << " ";
    }
    std::cout << "\nComparisons " << bubble.getComparisonCount() << '\n';
}