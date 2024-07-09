//Group 25
//Group Assignment 1


#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "ArgumentManager.h"

class node {
public:
  string val;
  node *next;
  int frequency;
  node(string val) {
    this->val = val;
    this->frequency = 0;
    next = nullptr;
  };
};

class Linkedlist {
private:
  node *head;
  node *tail;
  int size;
  bool isinnocent;

public:
  // Constructor and Distructor
  Linkedlist() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    isinnocent = false;
  };

  ~Linkedlist() {
    node *temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
  };

  // Get size and get head
  int getsize() { return size; };
  node *getHead() { return head; };

  // Add but at end
  void addNode(string val) {
    // cout <<"Add node has been called" << endl;
    node *newNode = new node(val);
    if (size == 0) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    size++;
  };

  // sorting
  void sort() {
    // cout <<"Sorting has been called" << endl;
    if (size == 0 || size == 1) {
      return;
    }
    bool sorted = false;
    node *current;
    while (!sorted) {
      sorted = true;
      current = head;
      while (current->next != nullptr) {
        if (stoi(current->val) > stoi(current->next->val)) {
          string temp = current->val;
          current->val = current->next->val;
          current->next->val = temp;
          sorted = false;
        }
        current = current->next;
      }
    }
  };

  // guilty or not
  void compare(ofstream &output) {
    // cout <<"compare has been called" << endl;
    if (size == 0 || size == 1) {
      return;
    } else {
      int count = 1;
      int guilty = 0;
      node *temp = head;
      while (temp->next != nullptr) {
        if (count == 2) {
          output << temp->val << endl;
        }
        if (temp->val == temp->next->val) {
          temp->frequency++;
          temp->next->frequency++;
          guilty += 2;
          count++;
        } else {
          count = 1;
        }
        temp = temp->next;
      }
      if (count == 2) {
        output << temp->val << endl;
      }
      if (guilty == size) {
        isinnocent = true;
      }
    }
  };

  void print(ofstream &output) {
    node *temp = head;
    output << "Guilty:" << endl;
    compare(output);
    if (size != 0 && !isinnocent) {
      output << "Innocent:" << endl;
      while (temp) {
        if (temp->frequency == 0) {
          output << temp->val << endl;
        }
        temp = temp->next;
      }
    }
  };
};

// Swapping and decoding
void decode(vector<string> &vec) {
  // cout <<"decode has been called" << endl;
  for (int i = 0; i < vec.size(); i++) {
    string phrase;
    string word = vec[i];

    while (word.find_last_of('(') != -1 && word.find_first_of(')') != -1) {

      int left = word.find_last_of('('), right = word.find_first_of(')');
      phrase = word.substr(left + 1, right - left - 1);
      reverse(phrase.begin(), phrase.end());

      word.replace(left + 1, right - left - 1, phrase);

      string neww;
      for (int i = 0; i < word.length(); i++) {
        if (i == left || i == right)
          continue;
        else
          neww += word[i];
      }

      word = neww;
    }
    vec[i] = word;
  }
}



int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  const string inputfile = am.get("input");
  const string outputfile = am.get("output");

  // ifstream input("ga1/input1.txt");
  // ofstream output("output22.txt");

  Linkedlist *letter = new Linkedlist();

  ifstream fin(inputfile);
  ofstream fout(outputfile);

  string sentence;
  vector<string> inputbar1;
  vector<string> inputbar2;
  bool bar1 = true;

  while (getline(fin, sentence)) {
    sentence.erase(remove(sentence.begin(), sentence.end(), '\n'),
                   sentence.end());
    sentence.erase(remove(sentence.begin(), sentence.end(), '\r'),
                   sentence.end());

    // Check if bar 1 or 2
    if (!sentence.empty()) {
      if (sentence == "Bar1" || sentence == "Bar2") {
        if (sentence == "Bar1") {
          // cout << "Test for bar 1" << endl;
          bar1 = true;
        } else {
          // cout << "Test for bar 2" << endl;
          bar1 = false;
        }
        continue;
      }

      if (bar1) {
        // cout << "Test for bar 1" << endl;
        inputbar1.push_back(sentence);
      } else if (!bar1) {
        // cout << "Test for bar 2" << endl;
        inputbar2.push_back(sentence);
      }
    }
  }

  decode(inputbar1);
  decode(inputbar2);

  for (int i = 0; i < inputbar1.size(); i++) {
    letter->addNode(inputbar1[i]);
  }

  for (int i = 0; i < inputbar2.size(); i++) {
    letter->addNode(inputbar2[i]);
  }

  letter->sort();
  letter->print(fout);

  fin.close();
  fout.close();

  delete letter;
  return 0;
}
