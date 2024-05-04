#include <bits/stdc++.h>
using namespace std;


class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName(){
        return studentName;
    }     
    void set_studentName(string Name){
        studentName=Name;
    }

    string get_rollNumber(){
        return rollNumber;
    }
    void set_rollNumber(string rollnum){
        rollNumber=rollnum;
    }
};

class Node{
private:
	Node* next;
	StudentRecord* element;
public:
    Node* get_next(){
        return next;
    }
    StudentRecord* get_element(){
        return element;
    }

    void set_next(Node* value){
        next =value;
    }
    void set_element(StudentRecord* student){
        element =student;
    }

};

class Entity {
private:
    string name;
    Node* iterator;

public:
    string get_name(){
        return name;
    }
    void set_name(string Name){
        name=Name;
    }
    Node* get_iterator(){
        return iterator;
    }
    void set_iterator(Node* iter){
        iterator=iter;
    }
};




class LinkedList : public Entity {
    // Implement LinkedList members here

public:
    void add_student(StudentRecord &student){
        
        Node *obj=new Node();
        obj->set_element(&student);
        obj->set_next(nullptr); 
        if(get_iterator()==nullptr)
        {
            set_iterator(obj);

        }
        else{
            Node* it=get_iterator();
            while(it->get_next()!=nullptr)
            {
                it=it->get_next();
            }
            it->set_next(obj);
        }
    }
    void delete_student(string studentName){
        Node* crnt = get_iterator();

            if (crnt && crnt->get_element()->get_studentName() == studentName) {
            this -> set_iterator(crnt->get_next());
            delete crnt;
            return;
        }

                Node* prev = nullptr;
        while (crnt && crnt->get_element()->get_studentName() != studentName) {
            prev = crnt;
            crnt = crnt->get_next();
        }

        
        if (crnt == nullptr) {
            return;
        }

        
        prev->set_next(crnt -> get_next());
        delete crnt;
    }
};
vector<StudentRecord> students;
vector<LinkedList> EntityArray;

void read_input_file(string file_path){
    ifstream file;
    file.open(file_path);
    if(!file.is_open())
    {
        cerr<<"Cant OPen File"<<endl;
        return ;
    }
    string lin;
    
    vector<vector<string>> info;
    set<string> entities;
    while(getline(file,lin)){
        vector<string> row;
        lin=lin+",";
        string word="";
        int i=0;
        while(i<lin.length())
        {
            if(lin[i]=='[')
            {
             string t;
             while(lin[i-1]!=']')
             {
                t=t+lin[i];
                i++;
             }
             row.push_back(t);
             i++;
            }
            else if(lin[i]==',')
            {
                row.push_back(word);
                word="";
                i++;

            }
            else{
                word=word+lin[i];
                i++;
            }
            
        }
        info.push_back(row);

    }
    file.close();
    for(int i=0;i<info.size();i++)
    {
        StudentRecord object;
        for(int j=0;j<2;j++)
        {
            if(j==0)
            object.set_studentName(info[i][j]);
            else{
                object.set_rollNumber(info[i][j]);
            }
        } 
        students.push_back(object);
    }
     for(int i  = 0;i<info.size();i++){
        for(int j = 2;j<info[0].size();j++){
            
            if(info[i][j][0] == '['){
               string s = info[i][j];
               s.erase(s.begin());
               s.erase(s.end() - 1);
               s = s + ',';
               string word = "";
               for(int k = 0;k<s.size();k++){
                  if(s[k] == ','){
                    entities.insert(word);
                    word = "";
                  }
                  else{
                    word = word + s[k];
                  }
               }
            }
            else{
                entities.insert(info[i][j]);
            }
        }
    }

    for(auto it = entities.begin();it != entities.end();it++){
        if(*it == "\n" || *it == "" || *it == " ")
         entities.erase(it);
    }


        
        for(const string &t:entities)
    {
             LinkedList obj;
             obj.set_name(t);
             obj.set_iterator(nullptr);
             EntityArray.push_back(obj);

    }
       int stp=0;
       

      for(int i  = 0;i<info.size();i++){
      
        for(int j = 2;j<info[0].size();j++){
            
            if(info[i][j][0] == '['){
               string str = info[i][j];
               str.erase(str.begin());
               str.erase(str.end() - 1);
               str = str + ',';
               string word = "";
               for(int k = 0;k<str.size();k++){
                  if(str[k] == ','){
                    string name = word;
                    for (LinkedList  &entity : EntityArray) {
                                if (entity.get_name() == name) {
                                    entity.add_student(students[stp]);
                                }
                            }
                    word = "";
                  }
                  else{
                    word = word + str[k];
                  }
               }
            }
            else{
                for (LinkedList &entity : EntityArray) {
                                string name = info[i][j];
                                if (entity.get_name() == name) {
                                    entity.add_student(students[stp]);
                                }
                            }
                 
            }
        }

        stp = stp + 1;
    }


    


     
    





}
