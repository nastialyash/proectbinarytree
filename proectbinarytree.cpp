
#include <iostream>

using namespace std;


struct TreeNode {
    string carNumber;  
    string violationDes[10];  
    double fineAmount[10];  
    int violationCount;  
    TreeNode* left;
    TreeNode* right;

    TreeNode(string num) : carNumber(num), violationCount(0), left(nullptr), right(nullptr) {}
};


class Database {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, string carNumber, const string& violationDesc, double fineAmount) {
        if (node == nullptr) {
            node = new TreeNode(carNumber);
            node->violationDes[node->violationCount] = violationDesc;
            node->fineAmount[node->violationCount] = fineAmount;
            node->violationCount++;
        }
        else if (carNumber < node->carNumber) {
            node->left = insert(node->left, carNumber, violationDesc, fineAmount);
        }
        else if (carNumber > node->carNumber) {
            node->right = insert(node->right, carNumber, violationDesc, fineAmount);
        }
        else {
         
            if (node->violationCount < 10) {  
                node->violationDes[node->violationCount] = violationDesc;
                node->fineAmount[node->violationCount] = fineAmount;
                node->violationCount++;
            }
        }
        return node;
    }

  
    TreeNode* search(TreeNode* node, const string& carNumber) {
        if (node == nullptr || node->carNumber == carNumber) {
            return node;
        }
        else if (carNumber < node->carNumber) {
            return search(node->left, carNumber);
        }
        else {
            return search(node->right, carNumber);
        }
    }

    
    void printDatabase(TreeNode* node) {
        if (node != nullptr) {
            printDatabase(node->left);
            cout << "Car Number: " << node->carNumber << "\nViolations:\n";
            for (int i = 0; i < node->violationCount; i++) {
                cout << "  - " << node->violationDes[i] << ", Fine: " << node->fineAmount[i] << "\n";
            }
          
            printDatabase(node->right);
        }
    }

  
    void printRange(TreeNode* node, const string& start, const string& end) {
        if (node != nullptr) {
            if (node->carNumber >= start) {
                printRange(node->left, start, end);
            }
            if (node->carNumber >= start && node->carNumber <= end) {
                cout << "Car Number: " << node->carNumber << "\nViolations:\n";
                for (int i = 0; i < node->violationCount; i++) {
                    cout << node->violationDes[i] << "Fine: " << node->fineAmount[i] << "\n";
                }
               
            }
            if (node->carNumber <= end) {
                printRange(node->right, start, end);
            }
        }
    }

public:
    Database() : root(nullptr) {}

    void addTicket(const string& carNumber, const string& violationDesc, double fineAmount) {
        root = insert(root, carNumber, violationDesc, fineAmount);
    }

    
    void printDatabase() {
        printDatabase(root);
    }

    
    void printByCarNumber(const string& carNumber) {
        TreeNode* node = search(root, carNumber);
        if (node != nullptr) {
            cout << "Car Number: " << node->carNumber << "\nViolations:\n";
            for (int i = 0; i < node->violationCount; i++) {
                cout << "  - " << node->violationDes[i] << ", Fine: " << node->fineAmount[i] << "\n";
            }
          
        }
        else {
            cout << "Car with number " << carNumber;
        }
    }

   
    void printByRange(const string& start, const string& end) {
        printRange(root, start, end);
    }
};

int main() {
    Database db;

   
    db.addTicket("AB1234CD", "Speeding", 100);
    db.addTicket("AB1234CD", "Parking violation", 50);
    db.addTicket("XY5678ZT", "Running a red light", 150);
  
   
    

    cout << "\nDetails for car number 128jji4i:\n";
    db.printByCarNumber("AB1234CD");

  
   
}