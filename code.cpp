
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;


struct tree
{
    char data;
    int freq;
};

class Tree
{
public:
    char data;
    int freq;
    Tree* right, * left;
    Tree()
    {
        right = NULL;
        left = NULL;
    }
    Tree(char, int);

};

Tree::Tree(char data, int freq)
{
    left = NULL;
    right = NULL;
    this->data = data;
    this->freq = freq;
}

struct node
{
    char data;
    int count = 0;
    node* next;
    string code = "";
};

class list      //list is used to maintain all the characters in the file with their repetition count 
{
public:
    int size;
    node* head;

    list();
    void insertword(char);
    void display() const;
    void updatecount(char);
    void sort();
    bool check_data(char);
    void Delete_S();
    void insert_E(node*);
    void Huffman();
    Tree& huffman(Tree*);

};

class Queue
{
public:
    int front;
    int rear;
    int size;
    int nodeLeft;
    Tree** array;
    Queue(int);
    void enqueue(Tree*);
    Tree& dequeue();
    bool compare(Tree, Tree);
    void priority();
    bool isFull();
    bool isEmpty();

};

list::list()
{
    size = 0;
    head = NULL;
}

void list::insertword(char d) // this function only updates the words 
{
    if (head == NULL)
    {
        node* temp = new node;
        temp->data = d;
        temp->count++;
        temp->next = NULL;
        head = temp;
    }

    else
    {
        //this function is used to find the existence of data in a node if found only the count is incremented
        bool found = check_data(d);

        if (found == 0)
        {
            node* ptr = head;
            while (ptr->next != NULL)
                ptr = ptr->next;
            node* temp = new node;
            temp->data = d;
            temp->count++;
            temp->next = NULL;
            ptr->next = temp;
        }

    }
    size++;

}

bool list::check_data(char d)          //this function is used to find the existence of data in a node if found only the count is incremented 
{
    node* t = head;
    while (t != NULL)
    {
        if (t->data == d)
        {
            t->count++;
            return 1;
        }
        t = t->next;
    }
    return 0;
}

void list::display() const
{
    node* ptr = head;
    while (ptr != NULL)
    {
        cout << ptr->data << "\nNumber of time repeated : " << ptr->count << endl;
        ptr = ptr->next;
    }
}

void list::sort()
{
    node* ptr = head;
    if (ptr->next == NULL)
        return;


    else
    {
        node* ptr2 = new node, * temp = new node;

        while (ptr != NULL)
        {
            ptr2 = ptr->next;
            while (ptr2 != NULL)
            {
                if (ptr2->count < ptr->count)
                {
                    temp->data = ptr->data;
                    temp->count = ptr->count;

                    ptr->data = ptr2->data;
                    ptr->count = ptr2->count;

                    ptr2->data = temp->data;
                    ptr2->count = temp->count;
                }
                ptr2 = ptr2->next;
            }
            ptr = ptr->next;
        }
    }
}


void list::Delete_S()
{
    if (head == NULL)
        return;

    head = head->next;

    if (head == NULL)
        return;
    else
        head = head->next;    //removing the the 2 nodes which are already used.

}

void list::insert_E(node* l)
{
    node* ptr = head;
    while (ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = l;
}

void list::Huffman()
{
    node* orignal = head;
    node* ptr = head;

    tree array[100];
    int size = 0;
    int roots = 0;

    for (int i = 0; ptr != NULL; i++, ptr = ptr->next, size += 3)
    {
        ptr = head;


        array[2 * i + 1].data = ptr->data;
        array[2 * i + 1].freq = ptr->count;            //left child
       // size++;

        if (ptr->next == NULL)
            break;

        else
        {
            array[2 * i + 2].data = ptr->next->data;
            array[2 * i + 2].freq = ptr->next->count;      //right child added
         //   size++;


            array[i].data = '?';
            array[i].freq = array[2 * i + 2].freq + array[2 * i + 1].freq;  //parent node
           // size++;
            roots++;


            //temp node is created and added at the back
            node* temp = new node;
            temp->data = array[i].data;
            temp->count = array[i].freq;
            temp->next = NULL;
            insert_E(temp);


            Delete_S(); //2 nodes from start are deleted

            sort(); //the new list is sorted according to the new data


            cout << endl << endl;
            // cout << "\nValue of index : " << i;
            // cout << "\nData : " << array[2*i+1].data << "\nFreq : " << array[2*i+1].freq <<endl;
            display();

        }
    }
    //roots (0,1,2,3,4)
    //left (1,3,5,7,9)
    //right(2,4,6,8,10)

    //---------------------------------------------------------------------------------------testing for swapping-------------------------------------------------------------------//

/*
    for (int i = 0; i < roots; i++)         //to sort the root
    {
        for (int j = 1; j < roots; j++)
        {
            if (array[j].freq > array[i].freq)
            {
                swap (array[i].data , array[j].data);       //swapping root
                swap(array[i].freq, array[j].freq);

                swap (array[2 * i + 1].data, array[2 * i + 1].data);    //swapping left child
                swap(array[2 * i + 1].freq, array[2 * i + 1].freq);

                swap(array[2 * i + 2].data, array[2 * i + 2].data);     //swapping right child
                swap(array[2 * i + 2].freq, array[2 * i + 2].freq);
            }
        }
    }
*/


/* for (int i = 0; i < roots; i++)
 {
     cout << "\n--------------------Root Child " << i+1 << " --------------------\n";
     cout << "\nData : " << array[i].data << "\nFrequency : " << array[i].freq << endl;

     cout << "\n--------------------Left Child " << i+1 << " --------------------\n";
     cout << "\nData : " << array[2*i+1].data << "\nFrequency : " << array[2*i+1].freq << endl;

     cout << "\n--------------------Right Child " << i+1 << " --------------------\n";
     cout << "\nData : " << array[2 * i + 2].data << "\nFrequency : " << array[2 * i + 2].freq << endl;
 }
 */

}


void codeGenerator(Tree* root, string code)  //Generates code recurrsively 
{
    if (root != NULL)
    {
        if (root->data != '?')
        {
            cout << root->data << ":- " << code << endl;
            return;
        }
        codeGenerator(root->left, code + "0");
        codeGenerator(root->right, code + "1");
    }
}

void inorder(Tree*);

Tree& list::huffman(Tree* answer)
{
    int queuesize = 0;
    node* ptr = head;
    for (int i = 0; ptr != NULL; i++, ptr = ptr->next)       //for loop to update queue size to allocate to queue. 
    {
        queuesize++;
    }
    Queue treelist(queuesize * 2);

    ptr = head;
    Tree* t = new Tree;
    for (int i = 0; ptr != NULL; i++, ptr = ptr->next) //putting values in queue
    {
        treelist.enqueue(new Tree(ptr->data, ptr->count));
    }

    int lastFreq = 0;

    for (int i = 0; i < /*queuesize-2*/treelist.front != treelist.rear; i++)
    {
        //if(treelist.nodeLeft == 1) 
       // {
         // break;
        //}
        Tree left = treelist.dequeue();
        Tree right = treelist.dequeue();

        if (right.freq == 0 || left.freq == 0)
            break;

        Tree* parent = new Tree('?', left.freq + right.freq);
        parent->left = &left;
        parent->right = &right;

        treelist.enqueue(parent);

        answer = parent;

        //cout << "\nleft data : " << left.data << "\n left freq : " << left.freq << endl;
        //cout << "\nRight data : " << right.data << "\n right freq : " << right.freq << endl;
        //cout << "\nanswer data : " << answer->data << "\n answer freq : " << answer->freq << endl;


    //inorder(answer);
        treelist.priority();
        lastFreq = answer->freq;
    }
    //  codeGenerator(&treelist.dequeue(), "");

      //codeGenerator(answer, "");
      /*
      Tree* parent; int c = 6;
      for (int i = 0; i < 6; i++);
      {
          Tree left = treelist.dequeue();
          Tree right = treelist.dequeue();

          parent = new Tree('?', left.freq + right.freq);
          parent->left = &left;
          parent->right = &right;

          treelist.enqueue(parent);
          treelist.priority();
      }*/

      // answer = &treelist.dequeue();
       //cout << "\nanswer data : " << answer->data << "\n answer freq : " << answer->freq << endl;

    return *answer;
}
//  ------------------------------------------------------------------------------------------------------------------------------------------------------

Queue::Queue(int s)
{
    front = -1;
    rear = -1;
    size = s;
    array = new Tree * [size];
    nodeLeft = 0;
}

bool Queue::isFull()
{
    if (front == 0 && rear == size - 1)
        return 1;

    else if (front == rear + 1)
        return 1;

    else
        return 0;
}


bool Queue::isEmpty()
{
    if (front == rear + 1)
    {
        return true;
    }

    else return 0;
}

void Queue::enqueue(Tree* t)
{
    if (rear < 0)
    {
        rear++, front++;
        array[rear] = t;
    }

    else
    {
        if (rear == size - 1)
            return;

        else
        {
            rear++;
            array[rear] = t;
        }
    }
    nodeLeft++;
    priority();
}

Tree& Queue::dequeue()
{
    Tree* temp = new Tree;
    if (front == rear + 1)
        return *temp;

    else
    {
        Tree* temp = array[front];
        front++;
        return *temp;
    }
    nodeLeft--;
}

bool Queue::compare(Tree t1, Tree t2)
{
    bool check = 0;
    (t1.freq > t2.freq) ? check = 0 : check = 1;
    return check;
}

void Queue::priority()
{
    bool check = 0;
    for (int i = front; i < rear + 1; i++)
    {
        for (int j = front; j < rear + 1; j++)
        {
            check = compare(*array[i], *array[j]);
            if (check)
                swap(array[i], array[j]);
            else
                continue;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------


void inorder(Tree* root)
{
    /*Tree *curr = root;


    while (curr!=NULL)
    {
        curr.
    }*/
    if (root != NULL)
    {
        cout << "\n\nData : " << root->data << "\nFrequency : " << root->freq;

        inorder(root->left);
        inorder(root->right);

    }


}

//----------------------------------------------------------Task 2

void codeGenerator(Tree* root, char word, string code, int& size)  //Generates code recurrsively 
{
    if (root != NULL)
    {
        if (root->data == word)
        {
            size = code.length();
            return;
        }
        codeGenerator(root->left, word, code + "0", size);
        codeGenerator(root->right, word, code + "1", size);
    }
}


class check //returns true if 1st root has greater freq
{
public:
    bool operator()(Tree* leftChild, Tree* rightChild)
    {
        bool c;
        (leftChild->freq > rightChild->freq) ? c = 1 : c = 0;
        return c;
    }
};

float ratio(Tree* root, list wordlist)
{
    Tree* temp = root;
    node* ptr = wordlist.head;
    int size;
    float compression = 0;
    int totalfreq = root->freq;
    while (ptr != NULL)
    {
        temp = root;
        codeGenerator(root, ptr->data, "", size);
        compression += (ptr->count * size);

        ptr = ptr->next;
    }
    //ABT
    compression = compression / totalfreq;
    cout << "\nAverage Bit rate is : " << compression;
    //8 divided by ABT is compression ratio
    compression = 8 / compression;
    return compression;
}


Tree* HuffmanTask2(list wordlist)  //Generates Huffman for task 2
{
    Tree* leftChild, * rightChild, * parent;
    node* ptr = wordlist.head;

    priority_queue<Tree*, vector<Tree*>, check> treelist;   //priority_queue of type Tree
    for (int i = 0; ptr != NULL; i++, ptr = ptr->next)
    {
        treelist.push(new Tree(ptr->data, ptr->count));    //creates a new leaf and inserts in queue (parameterised constructor)
    }

    while (treelist.size() > 1) //The last tree inside the queue is the tree we want
    {

        leftChild = treelist.top(); //the minimum is stored on the left       
        treelist.pop();             //tree is deleted from queue

        rightChild = treelist.top();//the 2nd minimum is stored on the right
        treelist.pop();             //tree is deleted from queue

        parent = new Tree('?', leftChild->freq + rightChild->freq);  //parent node is created with the data ? and frequeny which is the sum of leftchild and right child

        parent->left = leftChild;
        parent->right = rightChild;

        treelist.push(parent);  //it is pushed back and the queue is sorted again
    }

    string code = "\0";
    Tree* answer = treelist.top();
    Tree* temp = answer;

    cout << "\nHuffman tree decoded Task 2 :\n";
    codeGenerator(temp, code); //code is printed using the last tree stored in queue
    return answer;
}


Tree* HuffmanTask1(list wordlist)
{
    Tree* left, * right, * parent, * answer = new Tree;

    node* ptr = wordlist.head;


    left = new Tree(ptr->data, ptr->count);         //making first tree which would be assigned to left
    if (ptr->next != NULL)
    {
        ptr = ptr->next;

        right = new Tree(ptr->data, ptr->count);
        parent = new Tree('?', ptr->count);
        parent->left = left;
        parent->right = right;
        left = parent;
        answer = parent;
    }

    if (ptr->next != NULL)
        ptr = ptr->next;

    else
        goto exit1;

    while (ptr != NULL)
    {
        right = new Tree(ptr->data, ptr->count);
        parent = new Tree('?', right->freq + left->freq);
        parent->left = left;
        parent->right = right;
        left = parent;
        answer = parent;
        ptr = ptr->next;
    }

exit1:
    Tree* temp = answer;


    cout << "\nHuffman tree decoded Task 1 :\n";
    codeGenerator(temp, "");

    return answer;
}


Tree* HuffmanTree3(list wordlist)
{

    Tree* left, * right, * parent, * answer = new Tree;

    node* ptr = wordlist.head;


    right = new Tree(ptr->data, ptr->count);         //making first tree which would be assigned to left
    if (ptr->next != NULL)
    {
        ptr = ptr->next;

        left = new Tree(ptr->data, ptr->count);
        parent = new Tree('?', ptr->count);
        parent->left = left;
        parent->right = right;
        right = parent;
        answer = parent;
    }
    
    if (ptr->next != NULL)
        ptr = ptr->next;

    else
        goto exit2;

    while (ptr != NULL)
    {
        left = new Tree(ptr->data, ptr->count);
        parent = new Tree('?', right->freq + left->freq);
        parent->left = left;
        parent->right = right;
        right = parent;
        answer = parent;
        ptr = ptr->next;
    }


exit2:
    Tree* temp = answer;

    cout << "\nHuffman tree decoded Tree 3 :\n";
    codeGenerator(temp, "");

    return answer;
}
//-----------------------------------------------------------------------------------------------------

int main()
{
    fstream file;
    string filename;
    list wordslist;
    int numOfChar = 0;
    Tree* answer = new Tree;
    Tree* answer2 = new Tree;
    Tree* answer3 = new Tree;

label1:
    cout << "\nEnter the File name you want to open : ";       //file name is taken input
    cin >> filename;



    file.open(filename, ios::in);
    //file.open("Project.txt", ios::in);
    if (!file)
    {
        cout << "\nFile not found : re-enter file name\n";
        goto label1;
    }

    else
    {
        cout << "\nFile created\n";
        int i = 0;
        char temp;
        while (!file.eof())     //to count total words and update words in list
        {
            temp = file.get();
            if ((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z'))   //to only read the characters
                wordslist.insertword(temp);
        }
        wordslist.sort();
        file.close();
        cout << "\n-----------------Data in file------------------------\n";
        wordslist.display();

    }
    int size = 0;



    //wordslist.Huffman();
   //*answer = wordslist.huffman(answer);


    float compression1, compression2,compression3;

    answer = HuffmanTask1(wordslist);
    compression1 = ratio(answer, wordslist);
    cout << "\nCompression Ratio of Tree 1 is : " << compression1 << endl;


    //Task 2---------------------------------------------------------------------------
    answer2 = HuffmanTask2(wordslist);
    compression2 = ratio(answer2, wordslist);
    cout << "\nCompression Ratio of Tree 2 is : " << compression2 << endl;



    //Tree 3
    answer3 = HuffmanTree3(wordslist);
    compression3 = ratio(answer3, wordslist);
    cout << "\nCompression Ratio of Tree 3 is : " << compression3 << endl;


    if (compression1 > compression2 && compression1 > compression3)
        cout << "\nUsing Huffman Tree 1 is better for compression due to its compression ratio of : " << compression1;

    else if (compression2 > compression1 && compression2 > compression3)
        cout << "\nUsing Huffman Tree 2 is better for compression due to its compression ratio of : " << compression2;

    else if (compression3 > compression1 && compression3 > compression2) 
        cout << "\nUsing Huffman Tree 3 is better for compression due to its compression ratio of : " << compression3;

    else if (compression1 == compression2 == compression3)
        cout << "\nAll trees are optimal";

    cout << endl << endl << endl;
    return 0;
}


