#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int c=0;
    MetroStop* temp=node;
    while(temp != nullptr)
    {
        c++;
        temp=temp->getNextStop();
    }
    return c;

    //write your own logic here

}

void MetroLine::populateLine(std::string filename) {
   
    ifstream Inputfile(filename);
    string line,word;
    while(getline(Inputfile,line))
    {
        MetroStop* temp= node;
        vector<string> name;
        stringstream bb(line);
        while(getline(bb,word,' ')){
            name.push_back(word);

        }
        name.erase(name.end()-1);
        if(word[word.size()-1]==',')
        word.erase(word.end()-1);
        string names="";
        for(int i=0;i<name.size();i++)
        {
            names=names+name[i];
            names=names+' ';
        }
        
        names.erase(names.end()-1);
         MetroStop * obj= new MetroStop(names,this,stoi(word));
         if(node==nullptr)
         node= obj;
         else{
            while(temp->getNextStop()!=nullptr){
                temp=temp->getNextStop();
            }
            temp->setNextStop(obj);
            obj->setPrevStop(temp);
         }
         //  cout<<obj->getStopName()<<" "<<obj->getFare()<<endl;

    }

    // Read the file and populate the line
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() ;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
    // void setheight(int height){
    //     this->height=height;

    // }
    // int getheight(){
    //     return height;
    // }
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent=nullptr;
    
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent()  {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root=nullptr;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode*node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node==nullptr)
    return 0;
    else
    {
        return 1+max(height(node->getLeft()),height(node->getRight()));}
    //write your own logic here
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str()); 

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    
    if(node!=nullptr)
   {
   
   
    return (height(node->getLeft())-height(node->getRight()));
   }
    else return 0;
    //write your own logic here
}

void AVLTree::rotateLeft(AVLNode*node) {
    AVLNode* temp= node->getRight();
    temp->setRight(node->getRight()->getRight());
    AVLNode* temp1= temp->getLeft();
   //  temp1->setRight(node->getRight()->getLeft()->getRight());
   // temp1->setLeft(temp->getLeft()->getLeft());
    if(node->getParent()!=nullptr){
        if(node->getParent()->getLeft()==node)
        {
            node->getParent()->setLeft(temp);
        }
        else{
            node->getParent()->setRight(temp);
        }
    }
    else{
        this->setRoot(temp);
    }
    temp->setParent(node->getParent());
    temp->setLeft(node);
     node->setParent(node->getRight());
    node->setRight(temp1);
   
    if(temp1!=nullptr)
    temp1->setParent(temp->getLeft());
    // temp->setheight(height(temp));
    // temp1->setheight(height(temp1));
    // node->setheight(height(node));

    //write your own logic here
}

void AVLTree::rotateRight(AVLNode* node) {
    AVLNode* temp = node->getLeft();
    temp->setLeft(node->getLeft()->getLeft());
    //temp->setRight(node->getLeft()->getRight());
    AVLNode* temp1 = temp->getRight();
   // temp1->setRight(temp->getRight()->getRight());
    //temp1->setLeft(temp->getRight()->getLeft());
    if(node->getParent()!=nullptr)
    {
        if(node->getParent()->getLeft()==node)
        {
            node->getParent()->setLeft(temp);
        }
        else{
            node->getParent()->setRight(temp);
        }
        
    }
    else {
        this->setRoot(temp);

    }
    temp->setParent(node->getParent());
    temp->setRight(node);
    node->setParent(node->getLeft());
    node->setLeft(temp1);
    if(temp1!=nullptr)
    {
        temp1->setParent(temp->getRight());
    }
   
    // temp->setheight(height(temp));
    // temp1->setheight(height(temp1));
    // node->setheight(height(node)); 

    //write your own logic here
}

void AVLTree::balance(AVLNode*node) {
    int k= balanceFactor(node);
    
    int k1= balanceFactor(node->getLeft());
    int k2= balanceFactor(node->getRight());
    
    if(k>1){
       // cout<<"123"<<endl;
            if(k1>0)
            rotateRight(node);
            else {
                rotateLeft(node->getLeft());
                rotateRight(node);

            }
    }
    if(k<-1)
    {
        //cout<<"321"<<endl;
        if(k2<0)
        {
            rotateLeft(node);
        }
        else{
            rotateRight(node->getRight());
            rotateLeft(node);
        }
    }
    
    //write your own logic here
}

void AVLTree::insert(AVLNode*   node, MetroStop* metroStop) {
    
   
    if(stringCompare(metroStop->getStopName(),node->getStopName())<0 && node->getLeft()!=nullptr)
    {
        AVLNode*temp=node->getLeft();
        insert(temp,metroStop);
        //cout<<"beforel"<<endl;
       balance(node);
        
    }
    else if(stringCompare(metroStop->getStopName(),node->getStopName())>0 && node->getRight()!=nullptr){
        AVLNode* temp=node->getRight();
        insert(temp,metroStop);
        // cout<<"beforer"<<endl;
        balance(node);
        
        

    }
    else if (stringCompare(metroStop->getStopName(),node->getStopName())<0 && node->getLeft()==nullptr){
        AVLNode*obj=new AVLNode(metroStop->getStopName());
        node->setLeft(obj);
        obj->setParent(node);
        node->getLeft()->addMetroStop(metroStop);
      // cout<<"abc"<<endl;
        balance(node);
        
    }
    else if(stringCompare(metroStop->getStopName(),node->getStopName())>0 && node->getRight()==nullptr){
        AVLNode*obj=new AVLNode(metroStop->getStopName());
        node->setRight(obj);
        obj->setParent(node);
         node->getRight()->addMetroStop(metroStop);
        // cout<<"def"<<endl;
        balance(node);
       
    }
    else if(metroStop->getStopName().compare(node->getStopName())==0){
      // cout<<"ghi"<<endl;
     // vector<MetroStop*> v =(node->getStops());
      
        node->addMetroStop(metroStop );}
   
    //write your own logic here
}

void AVLTree::populateTree(MetroLine* metroLine) {
    MetroStop* temp;
    if(this->getRoot()==nullptr)
    {this->setRoot(new AVLNode (metroLine->getNode()->getStopName()));
   
    }
     
    //  
    temp = metroLine->getNode();
   // AVLNode* temp1=this->getRoot();
    while(temp)
    {
       // cout<<"I am here"<<endl;
        insert(this->getRoot(),temp);
       // cout<<height(getRoot())<<endl;
        temp = temp->getNextStop();
    }

    //write your own logic here
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* temp= this->getRoot();
   
    if(temp==nullptr)
    return nullptr;
    while(temp->getStopName()!=stopName && (temp->getLeft()!=nullptr || temp->getRight()!=nullptr))
    {
        
        if(stringCompare(stopName,temp->getStopName())<0 && temp->getLeft()!=nullptr)

        temp=temp->getLeft();
        else if(stringCompare(stopName,temp->getStopName())>0 &&temp->getRight()!=nullptr)
        temp=temp->getRight();
    }
    if(temp->getStopName()!=stopName)
    temp=nullptr;
    
    
   
    return temp;
   
    // write your own logic here
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);
 bool trav;
    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();
   

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    for(int i=0;i<getLines().size();i++)
    {
       // cout<<"in"<<endl;
        getTree()->populateTree(getLines()[i]);
       // cout<<"out"<<endl;
    }
    // we have to create avl tree 
}
 vector<Trip*> result;
bool searchingtrip(Trip* trip){
    for(int i=0;i<result.size();i++)
    {
        if(result[i]->getNode()==trip->getNode())
        return true;
    }
    return false;

}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    if(origin==destination){
        Path * path= new Path();
        path->setTotalFare(0);
        AVLNode* temp= getTree()->searchStop(origin);
        path->addStop(temp->getStops()[0]);
        return path;
    }
    //write your own logic here
   
    Trip* check_jun;
   AVLNode* temp= getTree()->searchStop(origin);
   
   AVLNode* temp1= getTree()->searchStop(destination);
   if(temp==nullptr||temp1==nullptr)
   return nullptr;
   Trip* triph;
   Trip* tripf;
    Exploration* exp= new Exploration();
   
    for(int i=0;i<temp->getStops().size();i++){
     triph=new Trip(temp->getStops()[i],nullptr);
     tripf=new Trip(temp->getStops()[i],nullptr);
     if(!searchingtrip(triph))
     {exp->enqueue(triph);
     result.push_back(triph);}
     exp->enqueue(tripf);
     //result.push_back(tripf);
     
   }
  
  int indi=0;
   int flagt=1;
   queue<Trip*> q= exp->getTrips();
    MetroStop* search_forward= q.front()->getNode();
   MetroStop* search_backward = q.front()->getNode();
   unordered_map<Trip*,MetroStop*> mpp;
        //    cout<<q.size()<<endl;
    //    cout<<search_backward->getStopName()<<endl;
    //    cout<< search_forward->getStopName()<<endl;
   while(!(q.empty())&& (search_forward->getStopName()!=destination && search_backward->getStopName() != destination))
   {
    //cout<<"i am ghain in"<<endl;
      
    if(flagt==1)
    flagt=0;
    else flagt=1;
    //cout<<flagt<<endl;
        search_backward = q.front()->getNode();
        search_forward = q.front()->getNode();
        //q.pop();

        if(flagt==0)
        {
            q.front()->trav=false;
          
            while(search_backward!=nullptr && search_backward->getStopName()!=destination)
            {
                
               // cout<<"abc"<<endl;
                AVLNode* jun;
                jun=getTree()->searchStop(search_backward->getStopName());
               
                vector<MetroStop*>v= jun->getStops();
                
                if(v.size()>1)
                {
                   
                    for(int i=0;i<v.size();i++){
                        Trip* trip= new Trip(v[i],q.front());
                        if(v[i]!=search_backward&& !(searchingtrip(trip)))
                            {
                                 mpp[trip]=search_backward;
                            q.push(trip);
                            exp->enqueue(trip);
                            q.push(trip);
                            exp->enqueue(trip);
                            result.push_back(trip);
                            }
                    }
                }
                search_backward = search_backward ->getPrevStop();
               // cout<<"def"<<endl;
                
            }
        }
        else if(flagt==1){
            // cout<<"i am in"<<endl;
             while(search_forward!=nullptr && search_forward->getStopName()!=destination)
            {
               q.front()->trav=true;
                AVLNode * jun= getTree()->searchStop(search_forward->getStopName());
                vector<MetroStop*>v= jun->getStops();
                // cout<<"derf"<<endl;
                // cout<<v.size()<<endl;
                if(v.size()>1)
                {
                    
                    for(int i=0;i<v.size();i++){
                        Trip* trip= new Trip(v[i],q.front());
                        if(v[i]!=search_forward&& (!searchingtrip(trip)))
                            {
                                mpp[trip]=search_forward;
                                q.push(trip);
                                exp->enqueue(trip);
                                q.push(trip);
                                exp->enqueue(trip);
                                result.push_back(trip);
                                 
                            }
                    }
                }
               
                search_forward = search_forward ->getNextStop();
                // cout<<search_forward->getStopName()<<endl;
            }

        }
       // cout<<search_backward->getStopName()<<endl;
       if(search_backward==nullptr)
       search_backward=search_forward;
       if(search_forward==nullptr)
       search_forward=search_backward;
       if((search_backward->getStopName()==destination )|| (search_forward -> getStopName()==destination))
       check_jun=q.front();
       // cout<<"popped"<<endl;
       exp->dequeue();
        q.pop();

   }
   if(search_backward==nullptr&& search_forward== nullptr)
   return nullptr;

   {
     
    MetroStop*ptr;
    Path * path = new Path();
    if(search_backward->getStopName()==destination)
    {
        ptr=search_backward;
        
    }
    else ptr= search_forward;
    int fare =0;
    int f1=0;
    int f2=0;
    Trip * chalo= check_jun;
    while(chalo->getPrev()!=nullptr){
        f1= ptr->getFare();
        //cout<<chalo->getNode()->getStopName()<<endl;
        while(ptr!=chalo->getNode()){
            path->addStop(ptr);
           // cout<<ptr->getStopName()<<endl;
            if(chalo->trav==true)
            ptr= ptr ->getPrevStop();
            else
            ptr= ptr->getNextStop();
            
        
        }
      //  path->addStop(ptr);
        f2= ptr->getFare();
        fare= fare+ abs(f1-f2);
         ptr= mpp[chalo];
        chalo = chalo->getPrev();
        //cout<<ptr->getStopName()<<endl;
       

    }
   
    f1=ptr->getFare();
    while(ptr->getStopName()!=origin){
         path->addStop(ptr);
            if(chalo->trav==true)
            ptr= ptr ->getPrevStop();
            else
            ptr= ptr->getNextStop();

    }
    path->addStop(ptr);
    f2= ptr->getFare();
        fare= fare+ abs(f1-f2);
        path->setTotalFare(fare);
        return path;
    
   }
}
vector<MetroLine*> lines;