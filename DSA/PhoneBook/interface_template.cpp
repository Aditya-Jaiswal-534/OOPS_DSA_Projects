#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include<cmath>
#include<unordered_map>

using namespace std;
long long int mod(int i,long long int p){
    int long long ans=1;

    while(i--){
        ans=((ans%p)*(263))%p;
    }
    return ans;
    
}

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};
vector<string> separate(const string & record)
{
    string str="";
    string name=record;
    vector<string> wordsi;
    name=name+' ';
    for(int i=0;i<name.size();i++)
    {
         if(name[i]==' ')
            {
                wordsi.push_back(str);
                str="";   
            }
        else{
                str=str+name[i];
            }
    }
        return wordsi;
}

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string& str){
        long long int p=1000000007;
       long long int hashindex=0;
        for(int i=0;i<str.length();i++)
        { 
            hashindex =hashindex +((int)(str[i]))*(mod(i,p));
        }
        hashindex=hashindex % HASH_TABLE_SIZE;
        return hashindex;
    }

    // Add your own implementation for adding a contact
    void addContact( PhoneRecord* record){
        string k = record->getName();
        vector<string> mn= separate(k);
       
        for(int i=0;i<mn.size();i++)
        {
                int key = computeHash(mn[i]);
                HashTableRecord *obj = new HashTableRecord(key,record);
                if(hashTable[key]==nullptr){
                    hashTable[key] = obj;
                   
                }
               
                else{
                    HashTableRecord* temp = hashTable[key];
                    while(temp -> getNext() != nullptr){
                        temp = temp->getNext();
                    }
                    temp -> setNext(obj);
                   
                    
                }
            
        }
       
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName){
       
        string name = *searchName;
        vector<PhoneRecord*> v = fetchContacts(&name);
        name = *searchName;
        if(v.empty())
        return false;
        else{
            PhoneRecord* tempr=v[0];
            vector<string> mainname = separate(v[0]->getName());
            vector<string> srching=separate(name); 
            for(int i=0;i<mainname.size();i++)
            {
                int key=computeHash(mainname[i]);
                HashTableRecord* d1=hashTable[key];
                HashTableRecord*prev=d1;
               while(d1!=nullptr||(d1==hashTable[key]&& d1->getRecord()==tempr))
               {
                
                     HashTableRecord*temp=d1;   
                    if(d1->getRecord()==tempr)
                    {
                         if(d1->getRecord()->getName()!=name&& srching.size()>1)
                         {
                           return false;
                         }
                        
                        if(d1==hashTable[key])
                        {
                            hashTable[key]=temp->getNext();
                            temp->setNext(nullptr);
                            delete temp;
                            break;
                        }
                        else{
                            prev->setNext(temp->getNext());
                            temp->setNext(nullptr);
                            delete temp;
                            break;
                        }
                    }
                            
                    
                    prev=d1;
                    d1=d1->getNext();
               }   
            }
            
            return true;   
        }
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query){
        vector<PhoneRecord*> result;
        string s=*query;
        string tname=s;
        vector<string> words=separate(s);
        multimap<int,PhoneRecord*> mpp;
       unordered_map <PhoneRecord*,int> mmp;
        for(int i=0;i<words.size();i++)
        {
          int k=computeHash(words[i]);
          HashTableRecord* temp=hashTable[k];
            
            while(temp!=nullptr)
            {
                vector<string> mainname= separate(temp->getRecord()->getName());
                    if(count(mainname.begin(),mainname.end(),words[i])>0)
                    {
                        mmp[temp->getRecord()]++;
                        if(temp->getRecord()->getName()==tname)
                        mmp[temp->getRecord()]+=5;
                    
                    }
                    temp=temp->getNext();
            }

        }
        for(auto it=mmp.begin();it!=mmp.end();it++)
            {
               mpp.insert({it->second,it->first});
            }
            for(auto it=mpp.begin();it!=mpp.end();it++)
            {
                result.insert(result.begin(),it->second);
            }
       
       
            return result;
    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const{
       
       string s=record->getName();
       vector<string> v=separate(s);
       return v.size();


    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename){
        ifstream inputFile(filename);
        string line;
        string word="";
        while(getline(inputFile,line))
        {
            vector<string> wording;
            line=line+',';
            for(int i=0;i<line.length();i++)
            {
                if(line[i]==',')
                {
                    wording.push_back(word);
                    word="";
                }
                else
                word=word+line[i];

            }
             vector<string> numbers(wording.begin()+1,wording.end()-1);
            PhoneRecord *obj = new PhoneRecord(wording[0],wording[wording.size()-1],numbers);
            addContact(obj);

        }
    }

    // Destructor
     ~PhoneBook(){
        
     };
};


