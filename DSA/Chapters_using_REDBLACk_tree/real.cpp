#include <bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "black";    // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};
HybridNode* get_Uncle(HybridNode* node){
    HybridNode* uncle=nullptr;
    if(node->parent==nullptr||node->parent->parent==nullptr)
      return uncle;
    HybridNode* par= node->parent;
    HybridNode* gp = node->parent->parent;
    if(gp->left_child== par){
        uncle = gp->right_child;
    }
    else{
        uncle = gp->left_child;
    }
    return uncle;
}
HybridNode* get_Sibling(HybridNode* node){
    if(node->parent==nullptr)
    return nullptr;
    if(node->parent->left_child==node){
        return node->parent->right_child;
    }
    else{
        return node->parent->left_child;
    }


}

class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }
     void Left_Rotate(HybridNode* node){
        if(node ==nullptr)
        return ;
        HybridNode* x = node->right_child;
        x->parent = node->parent ;
        if(x->parent == nullptr){
            this->root = x;
           // cout<<x->color<<endl;

        }
        else{
            if(node->parent->right_child== node)
            node->parent ->right_child= x;
            else{
                node->parent ->left_child= x;
            }
        }
        HybridNode* y = x-> left_child;
        x->left_child= node;
        node->right_child= y;
        node->parent = x;
        if(y!=nullptr)
        {
            y->parent = node;
        }
      

    }
    void  Right_Rotate(HybridNode* node){
        HybridNode* x = node ->left_child;
         x->parent = node->parent ;
        if(x->parent == nullptr){
            this->root = x;

        }
        else{
            if(node->parent->right_child== node)
            node->parent ->right_child= x;
            else{
                node->parent ->left_child= x;
            }
        }
        HybridNode* y = x -> right_child;
        x->right_child = node;
        node->left_child = y;
        node->parent = x;
        if(y!=nullptr){
            y->parent = node;
        }
        
    }
    void Maintain_Prop(HybridNode* obj){
        if(obj==root){
            obj->color="black";
            return ;
        }
         HybridNode* temp = obj;
       HybridNode * uncle = nullptr;
       HybridNode* pr=nullptr;
       HybridNode * gp=nullptr;
       if(obj==nullptr)
       return ;
       if(obj->parent==nullptr)
      { //obj->color= "black";
      return ;
      }

       else pr= obj->parent;
       if(obj->parent->parent==nullptr)
       return ;
       else gp = obj->parent->parent;
       if(gp->left_child== pr){
        uncle = gp->right_child;
       }
       else{
        uncle = gp->left_child;
       }
       if(pr->color!="black"){
       
       if(uncle!=nullptr && uncle->color == "red"){
        pr->color="black";
        uncle->color= "black";
        gp->color="red";
        Maintain_Prop(gp);
       
       }
       else {
        
        if(gp->left_child == pr && pr->left_child== obj){
         swap(gp->color,pr->color);
             Right_Rotate(gp);
           
        }
        else if(gp->left_child==pr && pr->right_child== obj){
           
            
            Left_Rotate(pr);
             swap(gp->color,obj->color);
            Right_Rotate(gp);
        }
        else if(gp->right_child == pr && pr->right_child== obj){
            swap(gp->color,pr->color);
           Left_Rotate(gp);

        }
        else if (gp->right_child == pr && pr->left_child== obj){
             swap(gp->color,obj->color);
            Right_Rotate(pr);
           Left_Rotate(gp);
        }
        
       }
       }
      
      return;

    }

    HybridNode* insert(string key, string element) {
        // Implement Red-Black Tree insertion
         HybridNode * temp = root;
        HybridNode * prev = nullptr;
        int flag =0;
    
       if(this->root==nullptr){
      this->root= new HybridNode(key,element);
       return this-> root;
       }
    
       string s= temp->key;
       while(key.compare(s)!=0 && temp){
        if(key.compare(s)<0)
        {
            prev = temp;
            flag =0;
            temp = temp ->left_child;
        }
        else{
            prev = temp;
            flag =1;
            temp = temp ->right_child;

        }
        if(temp!=nullptr)
        s= temp->key;
       }
        HybridNode*obj=new HybridNode(key,element);
        obj->color="red";
       if(temp){
        
                return root;
       }
       else if(!temp && flag ==0){
        prev->left_child= obj;
        obj->parent= prev;
       }
       else if(!temp && flag==1){
        prev->right_child= obj;
        obj->parent = prev;
       }
     Maintain_Prop(obj);
      return root;
    }
    HybridNode* getmin(HybridNode * node){
        HybridNode* temp = node;
        if(node==nullptr)
        return nullptr;
        while(temp->left_child!=nullptr){
            temp = temp ->left_child;

        }
        return temp;

    }
    HybridNode* getSuc(HybridNode* node, string s){
        HybridNode* required = nullptr;
       while(node!=nullptr){
        if(node->key==s){
            if(node->right_child)
            required= getmin(node->right_child);
            //cout<<re
            break;
        }
        else if(s.compare(node->key)>0){
            node = node->right_child;

        }
        else{
            required= node;
            node = node->left_child;

        }
       }
       return required;
        

    }
    void Fix_Double_Black(HybridNode* node){
        if(node == root)
        return ;
        HybridNode * s = get_Sibling(node);
        HybridNode* par = node->parent;
        if(s==nullptr)
        {
            Fix_Double_Black(par);
            return ;
        }
        if(s->color == "red"){
             par->color="red";
             s->color="black";
            if(par->right_child==s){
              Left_Rotate(par);
            }
            else{
               Right_Rotate(par);
            }
            Fix_Double_Black(node);
        }
        else{
            
            if((( s->right_child==nullptr||s->right_child->color=="black" ) && ( s->left_child==nullptr||s->left_child->color=="black" ))){
                  s->color="red";
                    if(par->color == "red"){
                        par->color = "black";
                    }
                    else{
                        Fix_Double_Black(par);
                    }
            }
            else {
                if(s->right_child!=nullptr&&node->parent->right_child==s && s->right_child->color=="red"){
                    s->right_child->color= s->color;
                s->color=par->color;
                Left_Rotate(par);
                }
                else if(node->parent->right_child == s && s->left_child!= nullptr && s->left_child->color=="red"){
         
                     s->left_child->color = par->color;
                    Right_Rotate(s);
                 Left_Rotate(par);
                }
                else if(node->parent->left_child == s && s->left_child!= nullptr && s->left_child->color=="red"){
            
                     s->left_child->color= s->color;
                s->color = par->color;
                 //par->color="black";
                Right_Rotate(par);
                }
                
                else if(node->parent->left_child == s && s->right_child!= nullptr && s->right_child->color=="red"){
                    cout<<"Hi"<<endl;
                    s->right_child->color= par->color;
               
                 //swap(s->color,par->color);
                 // par->color="black";
                 Left_Rotate(s);
                Right_Rotate(par);

                }
                par->color="black";
            }
        }
    

    }
    // void Fix_E_Red(){

    // }

    bool deleteNode(string key) {
        HybridNode * node = search(key);
        if(node==nullptr)
        return false;
        
        if(node -> right_child== nullptr && node->left_child == nullptr){
            if(node == root ){
                root = nullptr;
                return true;
            }
             HybridNode* sibling = get_Sibling(node);
            
            if(node->color == "black"){
                Fix_Double_Black(node);
            }
           else if(sibling!=nullptr){
            sibling ->color = "red";

            }
            if(node->parent->right_child==node){
                node->parent->right_child = nullptr;
                node->parent = nullptr;
            }
            else{
                node->parent->left_child = nullptr;
                 node->parent = nullptr;
            }
            delete node;
             return true ;
        }
        if(node->right_child!=nullptr && node->left_child==nullptr){
            if(node == root){
                node->key= node->right_child->key;
                node->element = node->right_child->element;
                node->left_child = node->right_child = nullptr;
                delete node->right_child;
                return true;
            }
             if(node->parent->right_child==node){
                
                node->parent->right_child = node->right_child;
                node->right_child->parent = node->parent;
            }
            else{
                node->parent->left_child = node->right_child;
                node->right_child ->parent = node->parent;
            }
            if(node->color=="black" && node->right_child->color=="black")
            Fix_Double_Black(node->right_child);
            else{
                node->right_child->color="black";
            }
            delete node ;
            return true;

        }
        if(node->left_child!=nullptr && node ->right_child==nullptr){
             if(node == root){
                node->key= node->left_child->key;
                node->element = node->left_child->element;
                node->left_child = node->right_child = nullptr;
                delete node->left_child;
                return true;
            }
             if(node->parent->right_child == node){
                node->parent->right_child = node->left_child;
                node->left_child ->parent = node->parent;
            }
            else{
                node->parent->left_child = node-> left_child;
                 node->left_child ->parent= node->parent;
            }
             if(node->color=="black" && node->left_child->color=="black")
            Fix_Double_Black(node->left_child);
            else{
                node->left_child->color="black";
            }
            delete node;
            return true;
        }
        if(node->right_child!= nullptr && node->left_child!=nullptr){
            HybridNode* temp = getSuc(this->root,node->key);
            string k= temp->key;
            string e= temp->element;
            bool f= deleteNode(temp->key);
            node->key=k;
            node->element= e;
            if(f==false){
                
                return false;
            }
           else return true;


        }
        
        

       
        // Implement Red-Black Tree deletion
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
         vector <HybridNode*> v;
          HybridNode* temp= node;
        HybridNode * par = node->parent;
        while(par!=nullptr){
            v.push_back(temp);
            temp= par;
            par= temp->parent;
        }
        
        return v;
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
         HybridNode* temp= node;
         vector<HybridNode*> v;
        for(int i=0;i<bit_sequence.length();i++){
            if(temp== nullptr)
            break; 
                v.push_back(temp);
                if(bit_sequence[i]=='1')
                temp= temp->left_child;
                else{
                    temp = temp ->right_child;
                }
        }
        return v;
    }
    int kahatak=0;
    void preod(HybridNode* node , vector<HybridNode*> & t,int depth){
        if(node!=nullptr&&kahatak<=depth)
         t.push_back(node);
        if(node->left_child && kahatak<=depth){
            kahatak++;
             preod(node->left_child,t,depth);
            kahatak--;
        }
       
        if(node->right_child && kahatak<=depth){
            kahatak++;
             preod(node->right_child,t,depth);
            kahatak--;
        }

    }

    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        // Perform pre-order traversal staying within specified depth
        kahatak=0;
          if(node == nullptr)
        return {};
        vector<HybridNode*> v;
        preod(node,v,depth);
        
        return v;
    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
       // cout<<key<<" ";
         if(this->root==nullptr)
        return nullptr;
        HybridNode * temp = this->root;
        while(temp&& temp->key.compare(key)!=0  ){
             //cout<<temp->key<<endl;
            if(key.compare(temp->key)<0)
            temp = temp ->left_child;
            else 
            temp = temp -> right_child;
           
            if(temp==nullptr)
            break;

        }
        //cout<<temp->key<<endl;
        return temp;
    }
    
    int blackheight(HybridNode* node){
        // Implement blackheight
         int c=0;
        HybridNode* temp = node;
        while(temp!=nullptr){
            if(temp->color== "black")
            c++;
            temp = temp ->left_child;

        }
        return c;
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};
int no_ch;
vector<IndexEntry*> ie;
class Lexicon {
private:
    RedBlackTree red_black_tree= *(new RedBlackTree());  // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        no_ch=chapter_names.size();
        red_black_tree.setRoot(nullptr);
    for(int i=0;i<chapter_names.size();i++){
       
       
         ifstream InputFile(chapter_names[i]);
        string line,word;
        string element= chapter_names[i];
        for(int i=0;i<4;i++){
        element.erase(element.end()-1);
        }
       // cout<<element<<endl;
       
        while(getline(InputFile,line)){
        
            stringstream bb(line);
            while(getline(bb,word,' ')){
              
                transform(word.begin(),word.end(),word.begin(),::tolower);
            red_black_tree.setRoot(red_black_tree.insert(word,element));
              IndexEntry * entry = nullptr;
              for(int i=0;i<ie.size();i++){
                if(ie[i]->getWord()== word)
                {
                    entry = ie[i];
                    break;
                }
              }
              if(entry==nullptr)
              {entry = new IndexEntry(word);
                ie.push_back(entry);
                }
                vector<pair<string , int>> p;
                p= entry->getChapterWordCounts();
                if(p.empty()){
                    p={{"Chapter1",0},{"Chapter2",0},{"Chapter3",0}};
                    pair <string,int> t={element,1};
                    if(element=="Chapter1")
                    p[0]=t;
                    else if(element=="Chapter2"){
                        p[1]=t;

                    }
                    else{
                        p[2]=t;
                    }

                }
                else{
                for(int i=0;i<p.size();i++){
                    if(p[i].first== element)
                    {p[i].second= p[i].second+1;
                    break;}

                }
                }
                entry->setChapterWordCounts(p);
            }
        }
    
    }
     
    }
     
     HybridNode* InorderTraversal(HybridNode *node ,vector<HybridNode*>&v){
        if(node == nullptr)
        return nullptr;
        if(node){
        if(node->left_child!=nullptr){
            node->left_child=InorderTraversal(node->left_child,v);
        }
       v.push_back(node);
       if(node->parent!=nullptr){
    //    if(node->color=="red" && node->parent->color=="red")
    //    cout<<"redredconflict"<<endl;
       }
        if(node->right_child){
            node->right_child = InorderTraversal(node->right_child,v);
        }
        }
        return node;


    }
    void pruneRedBlackTree() {
        vector<HybridNode*> v;
        int indicator;
        bool th;
        InorderTraversal(this->getRedBlackTree().getRoot(),v);
       vector<pair<string,int>> entry;
        for(int i=0;i<v.size();i++){
             indicator=0;

            for(int j=0;j<ie.size();j++){
                if(v[i]->key== ie[j]->getWord())
                {
                    entry= ie[j]->getChapterWordCounts();
                    for(auto it:entry){
                        if(it.second>0)
                        indicator++;
                    }
                    if(indicator==3)
                     th = this->getRedBlackTree().deleteNode(ie[j]->getWord());
                    break;
                }
            }
        }
        // Prune the Red-Black Tree by deleting common words
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
       pruneRedBlackTree();
        vector<IndexEntry> result;
        vector<HybridNode*> v;
        InorderTraversal(this->getRedBlackTree().getRoot(),v);
        for(int i=0;i<v.size();i++){
            for(int j=0;j<ie.size();j++){
                if(v[i]->key== ie[j]->getWord()){
                    result.push_back(*ie[j]);
                }
            }
            
        }
        return result;
    }
};
