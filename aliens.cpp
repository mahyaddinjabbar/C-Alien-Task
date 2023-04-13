#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <unordered_set>


using namespace std;

void insertToLeftOfAlien(std::stack<int>& stack,std::unordered_set<int>& set,std::unordered_set<int>& left_parents, int parent_id, int child_id, std::ofstream& out) {
    std::stack<int> tempStack;

    while (!stack.empty()) {
        int alien = stack.top();
        stack.pop();
        tempStack.push(alien);

        if (alien == parent_id){
            stack.push(child_id);
            set.insert(child_id);
            left_parents.insert(parent_id);
            break;
        }
    }
    while (!tempStack.empty()) {
        stack.push(tempStack.top());
        tempStack.pop();
    }


}



void insertToRightOfAlien(std::stack<int>& stack,std::unordered_set<int>& set,std::unordered_set<int>& right_parents, int parent_id, int child_id, std::ofstream& out) {
    std::stack<int> tempStack;

    while (!stack.empty()) {
        int alien = stack.top();
        stack.pop();
        
        if (alien == parent_id) {
            stack.push(alien);
            stack.push(child_id);
            set.insert(child_id);
            right_parents.insert(parent_id);
            break;
        }
        tempStack.push(alien);
    }


    while (!tempStack.empty()) {
        stack.push(tempStack.top());
        tempStack.pop();
    }

}

void findFavRelatives(std::stack<int>& stack, int alien_id, std::ofstream& out) {
    std::stack<int> tempStack;
   

    int prev = -1;
    int next = -1;

    bool found_alien = false;

    while (!stack.empty()) {
        int alien = stack.top();
        stack.pop();
        if(alien == alien_id) {
            found_alien = true;
            if (!stack.empty()) {
                prev = stack.top();
            }
            if (!tempStack.empty()) {
                next = tempStack.top();
            }

            tempStack.push(alien);


            if (prev != -1 && next != -1) {
                out << prev << " " << next << endl;
            } else if (prev == -1 && next == -1) {
                out << "0" << " " << "0" << endl;
            } else if (prev == -1) {
                out << "0" << " " << next << endl;
            } else if (next == -1) {
                out << prev << " " << "0" << endl;
            }

            break;

        } else {
            tempStack.push(alien);
        }
    

    }


    while (!tempStack.empty()) {
        stack.push(tempStack.top());
        tempStack.pop();
    }

    if(!found_alien){
        out << "error0" << endl;
        return;
    }


}

int main() {
    std::stack<int> stack;
    std::unordered_set<int> set;
    std::unordered_set<int>left_parents;
    std::unordered_set<int>right_parents;
    ifstream in("aliens.in");
    ofstream out("aliens.out");

    int alien_id;
    int parent_id;
    int child_id;
    int root_id;
    string command;
    in >> root_id;
    stack.push(root_id);
    set.insert(root_id);

    while(in >> command){
        if(command == "L"){
            in >> parent_id >> child_id;
            if(parent_id == child_id){
                out << "error1"<<endl;
                continue;
            }
            if(set.count(parent_id)<=0){
                out<<"error2"<<endl;
                continue;
            }
            if(set.count(child_id)>0){
                out<<"error3"<<endl;
                continue;
            }
            if(left_parents.count(parent_id)>0){
                out<<"error4"<<endl;
                continue;
            }
            insertToLeftOfAlien(stack,set,left_parents, parent_id,child_id, out);
            
        }
        if(command == "R"){
            in >> parent_id >> child_id;
            if(parent_id == child_id){
                out << "error1" << endl;
                continue;
            }
            if(set.count(parent_id)<=0){
                out<<"error2"<<endl;
                continue;
            }
            if(set.count(child_id)>0){
                out<<"error3"<<endl;
                continue;
            }
            if(right_parents.count(parent_id)>0){
                out<<"error5"<<endl;
                continue;
            }

            insertToRightOfAlien(stack,set,right_parents, parent_id, child_id, out);
            
        }
        if(command == "?"){
            in >> alien_id;
            findFavRelatives(stack, alien_id, out);
        }        
    }
    in.close();
    out.close();

    return 0;
}