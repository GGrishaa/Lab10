#include <iostream>
#include <string>
using namespace std;

int pow(int a, int b){
    int c = 1;
    for(int i = 0; i < b; i++){
        c = c * a;
    }
    return c;
}

int get_lena(int a){
    int ccc = 0;
    int aa;
    if(a < 0){
        ccc++;
        aa = -a;
    }
    else if (a == 0){
        return 1;
    }
    else{
        aa = a;
    }
    while (aa != 0){
        ccc++;
        aa = aa / 10;
    }
    return ccc;
}

template <typename T>
T maxim(T a, T b, T c){
    if(a >= b){
        if (a >= c){
            return a;
        }
        else{
            return c;
        }
    }
    else{
        if (b >= c){
            return b;
        }
        else{
            return c;
        }
    }
}

template <typename T>
T maxim(T a, T b){
    if(a >= b){
        return a;
    }
    return b;
}

class element{
  private:
    int data;
    element* right;
    element* left;

  public:
    element(int new_data = 0, element* new_right = nullptr, element* new_left = nullptr){
        data = new_data;
        right = new_right;
        left = new_left;
    }
    element(const element & other){
        this->data = other.data;
        this->right = other.right;
        this->left = other.left;
    }
    ~element(){
        right = nullptr;
        left = nullptr;
    }

    element* get_right_element(){
        return right;
    }
    element* get_left_element(){
        return left;
    }
    int get_data(){
        return data;
    }
    bool right_is_null(){
        return (right == nullptr);
    }
    bool left_is_null(){
        return (left == nullptr);
    }
    void set_right_element(element& new_right_element){
        right = &new_right_element;
    }
    void set_left_element(element& new_left_element){
        left = &new_left_element;
    }
    void set_right_element(element* new_right_element){
        right = new_right_element;
    }
    void set_left_element(element* new_left_element){
        left = new_left_element;
    }
    void set_data(int new_data){
        data = new_data;
    }
    void print(){
        cout << data;
    }
    string kaspfks(){
        string result = to_string(this->data);
        int f = this->left_is_null() + this->right_is_null();
        if (f == 2) {
            return result;
        } else if (f == 1) {
            return result + "[" + (this->left_is_null() ? "r:" + this->right->kaspfks() : "l:" + this->left->kaspfks()) + "]";
        } else {
            return result + "[l:" + this->left->kaspfks() + ",r:" + this->right->kaspfks() + "]";
        }
    }
};

class MyBinaryTree{
  private:
    element* base;
    int count;
  public:
    MyBinaryTree(element* new_base = nullptr, int new_count = 0){
        base = new_base;
        count = new_count;
    }
    MyBinaryTree(const MyBinaryTree & other){
        this->base = other.base;
        this->count = other.count;
    }
    ~MyBinaryTree(){
        element* current = base;
        element* previous;
        bool flag;
        while(count != 0){
            while(current->get_right_element() != nullptr || current->get_left_element() != nullptr){
                if(current->get_right_element() != nullptr){
                    previous = current;
                    flag = 1;
                    current = current->get_right_element();
                }
                else{
                    previous = current;
                    flag = 0;
                    current = current->get_left_element();
                }
            }
            //cout << "элемент " << current->get_data() << " удален" << endl;
            if(flag == 0){
                previous->set_left_element(nullptr);
            }
            else{
                previous->set_right_element(nullptr);
            }
            delete current;
            current = base;
            count--;
        }
    }
    void push(element & new_element){
        if(base == nullptr){
            base = &new_element;
            count++;
        }
        else{
            element* current = base;
            while(current != nullptr){
                if(current->get_data() < new_element.get_data()){
                    if(current->get_right_element() == nullptr){
                        current->set_right_element(new_element);
                        count++;
                        break;
                    }
                    else{
                        current = current->get_right_element();
                    }
                }
                else if(current->get_data() > new_element.get_data()){
                    if(current->get_left_element() == nullptr){
                        current->set_left_element(new_element);
                        count++;
                        break;
                    }
                    else{
                        current = current->get_left_element();
                    }
                }
                else{
                    break;
                }
            }
        }
    }
    int get_count(){
        return count;
    }
    void set_base(element & new_base){
        base = &new_base;
    }
    void push(int new_data){
        if(base == nullptr){
            base = new element(new_data);
            count++;
        }
        else{
            element* current = base;
            element* new_one = new element(new_data);
            while(current != nullptr){
                if(current->get_data() < new_one->get_data()){
                    if(current->get_right_element() == nullptr){
                        current->set_right_element(*new_one);
                        count++;
                        break;
                    }
                    else{
                        current = current->get_right_element();
                    }
                }
                else if(current->get_data() > new_one->get_data()){
                    if(current->get_left_element() == nullptr){
                        current->set_left_element(*new_one);
                        count++;
                        break;
                    }
                    else{
                        current = current->get_left_element();
                    }
                }
                else{
                    delete new_one;
                    break;
                }
            }
        }
    }
    int max_len(element* current){
        if (current == nullptr){
            return 0;
        }
        int m0 = get_lena(current->get_data()), m1 = 0, m2 = 0;
        if (current->get_left_element() != nullptr){
            m1 = max_len(current->get_left_element());
        }
        if(current->get_right_element() != nullptr){
            m2 = max_len(current->get_right_element());
        }
        return maxim(m0, m1, m2);

    }
    int max_len(){
        return max_len(this->base);
    }
    element* get_base(){
        return base;
    }
    int count_elements(element* current){
        int counter = 1;
        if(current == nullptr){
            return 0;
        }
        if(current->get_left_element() != nullptr){
            counter += count_elements(current->get_left_element());
        }
        if(current->get_right_element() != nullptr){
            counter += count_elements(current->get_right_element());
        }
        return counter;
    }
    int count_elements(){
        return count_elements(this->base);
    }
    int count_right_elements(element* current){
        if(current == nullptr){
            return 0;
        }
        return count_elements(current->get_right_element());
    }
    int count_right_elements(){
        return count_right_elements(this->base);
    }
    int count_left_elements(element* current){
        if(current == nullptr){
            return 0;
        }
        return count_elements(current->get_left_element());
    }
    int count_left_elements(){
        return count_left_elements(this->base);
    }
    int count_str(element* current){
        if (current == nullptr){
            return 0;
        }
        int c1 = 0, c2 = 0;
        if(current->get_left_element() != nullptr){
            c1 = count_str(current->get_left_element());
        }
        if(current->get_right_element() != nullptr){
            c2 = count_str(current->get_right_element());
        }
        return (maxim(c1, c2) + 1);
    }
    int count_str(){
        return count_str(this->base);
    }

    void print(){
        if(count == 1){
            cout << base->get_data() << endl;
        }
        else if (count == 0){
            cout << endl;
        }
        else{
            element** ARR = new element*[1];
            ARR[0] = base;
            int* SPACES = new int[2];
            int left_strok = this->count_str();
            SPACES[0] = SPACES[1] = (pow(2, left_strok - 1) - 1) * (this->max_len() + 1);
            int COUNT_SPACES = 2;
            int COUNT_ELEMENTS = 1;
            for(int i = 0; i < this->count_str(); i++){
                COUNT_ELEMENTS = pow(2, i);
                COUNT_SPACES = COUNT_ELEMENTS + 1;
                element** arr = new element*[COUNT_ELEMENTS];
                int* spaces = new int[COUNT_SPACES];
                left_strok--;


                if(i == 0){
                    arr[0] = base;
                    spaces[0] = spaces[1] = SPACES[0];
                }
                else{
                    for(int j = 0; j < COUNT_ELEMENTS/2; j++){
                        if(ARR[j] == nullptr){
                            arr[j * 2] = nullptr;
                            arr[j * 2 + 1] = nullptr;
                        }
                        else{
                            arr[j * 2] = ARR[j]->get_left_element();
                            arr[j * 2 + 1] = ARR[j]->get_right_element();
                        }
                    }
                    spaces[0] = spaces[COUNT_SPACES - 1] = (pow(2, left_strok) - 1) * (this->max_len() + 1);
                    for(int ii = 1; ii < COUNT_SPACES - 1; ii++){
                        spaces[ii] = SPACES[0] + 1;
                    }
                }
                for(int ii = 0; ii < COUNT_ELEMENTS; ii++){
                    ARR[ii] = arr[ii];
                }
                for(int ii = 0; ii < COUNT_SPACES; ii++){
                    SPACES[ii] = spaces[ii];
                }


                for(int iii = 0; iii < COUNT_ELEMENTS; iii++){
                    for(int ii = 0; ii < spaces[iii]; ii++){
                        cout << ' ';
                    }
                    if(arr[iii] == nullptr){
                        for(int k = 0; k < this->max_len(); k++){
                            cout << ' ';
                        }
                    }
                    else{
                        if(get_lena(arr[iii]->get_data()) == this->max_len()){
                            cout << arr[iii]->get_data();
                        }
                        else{
                            int tututu = this->max_len() - get_lena(arr[iii]->get_data());
                            for(int kk = 0; kk < tututu; kk++){
                                cout << ' ';
                            }
                            cout << arr[iii]->get_data();
                        }
                    }
                }
                for(int ii = 0; ii < spaces[COUNT_SPACES - 1]; ii++){
                    cout << ' ';
                }
                cout << endl;


                delete[] arr;
                delete[] spaces;
            }
            delete[] SPACES;
            delete[] ARR;
        }
    }
    string kaspfks(){
        if(this->base == nullptr){
            return "[]";
        }
        else{
            return this->base->kaspfks();
        }
    }

};

int main(){
    MyBinaryTree tree;
    tree.push(100);
    tree.push(0);
    tree.push(-3);
    //tree.push(105);
    //tree.push(1800);
    //tree.push(10);
    //tree.push(101);
    //tree.push(1801);
    //tree.push(0);
    //tree.push(-1);
    //tree.push(-2);
    //tree.push(-3);
    tree.push(-5);
    tree.print();
    return 0;
}
