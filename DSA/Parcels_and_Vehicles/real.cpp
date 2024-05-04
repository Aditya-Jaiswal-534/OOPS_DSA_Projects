#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
using namespace std;

class Parcel {
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority) {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap {
public:
    std::vector<Parcel*> heap;

    int parent(int i) {
        // fill in this function
        return i/2;
    }

    int left(int i) {
        // fill in this function
        return 2*i;
    }

    int right(int i) {
        // fill in this function
        return 2*i+1;
    }

    Parcel* get_max() {
        // fill in this function
         return heap[1];
    }

    Parcel* extract_max() {
        // function that returns the max element and removes it from the heap
         Parcel *p= heap[1];
        swap(heap[1],heap[heap.size()-1]);
        heap.pop_back();
        max_heapify(1);
        return p;
    }

    void max_heapify(int i) {
        // function that maintains the max heap property
         // function that maintains the max heap property
        int mov= heap[i]->priority;
        int l;
        int r;
        int p;
        int maxi;
        if(i==1)
        {
            //deletion wala case
            l= 2*i;
            r= 2*i+1;
            if(!(l<heap.size() && !r< heap.size()))
            return ;
            maxi = max(heap[l]->priority,heap[r]->priority);
            while(mov<maxi){
               
                if(maxi== heap[l]->priority){
                    swap(heap[l],heap[i]);
                    i=l;
                }
                else{
                    swap(heap[r],heap[i]);
                    i=r;
                }
                mov= heap[i]->priority;
                l=2*i;
                r=2*i+1;
                if(!(l<heap.size() && !r< heap.size()))
                    return ;
                 maxi = max(heap[l]->priority,heap[r]->priority);
                
            }
        }
        if(i==heap.size()-1){
            p= parent(i);
            while(heap[i]->priority> heap[p]->priority && p!=0){
                swap(heap[p],heap[i]);
                i=p;
                p= parent(i);
            }


        }
    }

    void insert(Parcel* item) {
        // function that inserts item into the heap
        if(heap.empty())
        {
            Parcel * p = new Parcel();
            heap.push_back(p);
        }
        heap.push_back(item);
        max_heapify(heap.size()-1);
    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    unordered_map<string , int> c;
    int max_parcel_capacity;
    std::vector<Parcel*> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;
    bool stranded = false;
    

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel* parcel) {
        // load parcel
        this->c[current_location]=1;
        if(parcels.size()<max_parcel_capacity)
        parcels.push_back(parcel);
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
        if(parcels.size()== max_parcel_capacity)
        return true ;
        else return false;
    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
         current_location= destination; 
    }
};

class Vertex {
public:
    std::string name;
    std::vector<FreightCar*> freight_cars;
    std::vector<Vertex*> neighbors;
    vector<FreightCar*> stranded;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar*>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap*> parcel_destination_heaps;
    std::vector<FreightCar*> sealed_freight_cars;
    std::vector<Parcel*> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity) {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    void add_neighbor(Vertex* neighbor) {
        // add neighbor to neighbors vector
        neighbors.push_back(neighbor);
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        return this->neighbors;
    }

    std::vector<Parcel*> get_all_current_parcels() {
        // get all parcels from all destination heaps
         vector<Parcel*> p;
        for(int i=0;i<all_parcels.size();i++){
            p.push_back(all_parcels[i]);
        }
        return p;
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
        for(int i=0;i<freight_cars.size();i++){
            if(freight_cars[i]->parcels.size()<max_parcel_capacity )
            {
                for(int j=0;j<freight_cars[i]->parcels.size();j++)
               { parcel_destination_heaps[freight_cars[i]->destination_city]->insert(freight_cars[i]->parcels[j]);
              // cout<<freight_cars[i]->parcels[j]->destination<<endl;
               }
                freight_cars.erase(freight_cars.begin()+i);
                i=i-1;
            }
        }
        // for(auto it:freight_cars){
        //     cout<<it->destination_city<<endl;
        // }
    }

    void loadParcel(Parcel* parcel) {
        // load parcel into heap
         all_parcels.push_back(parcel);
         if(parcel_destination_heaps[parcel->destination]==nullptr)
        parcel_destination_heaps[parcel->destination] = new MaxHeap();
        parcel_destination_heaps[parcel->destination]->insert(parcel);
    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        for(auto it: parcel_destination_heaps){
            MaxHeap* mheap = it.second;
            // if(it.first=="AHMEDABAD"){
            //     cout<<mheap->heap.size()<<endl;
            // }
            int nc=0;
            nc= mheap->heap.size();
            nc= nc/max_parcel_capacity;
            while(mheap->heap.size()>=max_parcel_capacity+1){
                FreightCar* fcar= new FreightCar(max_parcel_capacity);
                fcar->current_location=this->name;
                for(int j=0;j<max_parcel_capacity;j++){
                    fcar->load_parcel(mheap->extract_max());
                }
                fcar->destination_city= it.first;
                fcar->sealed= true;
                freight_cars.push_back(fcar);
                
                sealed_freight_cars.push_back(fcar);
                
            }
             FreightCar* fdcar= new FreightCar(max_parcel_capacity);
            while(mheap->heap.size()>1){
                fdcar->current_location=this->name;
                fdcar->load_parcel(mheap->extract_max());
                fdcar->destination_city= it.first;
                freight_cars.push_back(fdcar);
              
            }

        }
        // for(auto it: freight_cars){
        //     cout<<it->destination_city<<" "<<it->parcels.size()<<endl;
        // }
    }

    // void print_parcels_in_freight_cars() {
    //     for (auto& [destination, heap] : this->parcel_destination_heaps) {
    //         for (auto& parcel : heap.heap) {
    //             std::cout << "Parcel ID: " << parcel->parcel_id << ", Parcel origin: " << parcel->origin << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
    //         }
    //     }
    // }
};

class Graph {

public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        if(source == destination)
        return ;
        Vertex* sor=nullptr;
        Vertex* desti= nullptr;
      
      for(auto it:vertices){
        if(it->name== source){
            sor= it;
        }
        if(it->name == destination)
        {  
        desti = it;
        }

      }
      pair<Vertex*,Vertex*> p = {sor,desti};
      pair<Vertex*,Vertex*>q= {desti,sor};
      if(sor!=nullptr && desti !=nullptr){
        for(int i=0;i<edges.size();i++){
            if(edges[i] == p || edges[i]==q){
                return ;
            }
        }
        edges.push_back(p);
        sor->add_neighbor(desti);
        desti->add_neighbor(sor);
        return ;
      }
     if(sor==nullptr){
        sor = new Vertex (source,min_freight_cars_to_move,max_parcel_capacity);
        vertices.push_back(sor);
     }
     if(desti == nullptr){
        desti = new Vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
        vertices.push_back(desti);

     }
     p={sor,desti};
     sor->add_neighbor(desti);
     desti->add_neighbor(sor);
     edges.push_back(p);

    }

    void print_graph() {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto& vertex : this->vertices) {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto& neighbor : vertex->neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }
         void breadthFirst(string source, string destination, vector<string> & v, unordered_map<Vertex*,bool> &m){
        unordered_map<string,string> path;
        stack<string> st;
        Vertex* sor =nullptr;
        for(auto it:vertices){
            if(it->name == source){
                sor= it;
                break;
            }
        }
        bool f=0;
        if(sor==nullptr)
        return ;
        queue<Vertex*> q;
        m[sor]= 1;
        q.push(sor);
        while(!q.empty() && f==0){
            Vertex * front = q.front();
            q.pop();
            for(int i=0;i<front->neighbors.size();i++)
            {
                if(m[front->neighbors[i]]==0)
               { q.push(front->neighbors[i]);
                m[front->neighbors[i]]=1;
                path[front->neighbors[i]->name] = front->name;
                if(front->neighbors[i]->name == destination)
                {f=1;
                break;
                }
               }

            }
            if(f==1){
                while(destination != source){
                    st.push(destination);
                    destination= path[destination];

                }
                st.push(destination);
                while(!st.empty()){
                    v.push_back(st.top());
                    st.pop();
                }

            }
        }

         

    }

    std::vector<std::string> bfs(std::string source, std::string destination) {
        // function to return path from source to destination using bfs
          unordered_map<Vertex*,bool> m;
        for(auto it:vertices){
            m[it]=0;
        }
        vector<string> v;
        breadthFirst(source,destination,v,m);
       
        return v;
        }
 void depthfirst(string source, string destination,vector<string> &p,vector<string> &v, unordered_map<Vertex*,int> &m){
   
    Vertex* sor =nullptr;
        for(auto it:vertices){
            if(it->name == source){
                sor= it;
                break;
            }
        }
        m[sor]=1;
        p.push_back(source);
        Vertex* cv= sor;
        vector<Vertex*> nei= cv->neighbors;
        for(auto it:nei){
             if(!v.empty())
                 return ;
            if(m[it]==0 && destination!= it->name){
                //p.push_back(it->name);

                depthfirst(it->name,destination,p,v,m);
                p.pop_back();

            }
            else if(destination == it->name){
                p.push_back(it->name);
                v=p;
               // v.push_back(p);
                p.pop_back();
                return ;
            }
        }
       // p.pop_back();

}

    std::vector<string> dfs(std::string source, std::string destination) {
       // function to return path from source to destination using dfs
        // function to return path from source to destination using dfs
       unordered_map<Vertex*,int> m;
        for(auto it:vertices){
            m[it]=0;
        }
         vector<string> v;
        vector<string> p;
        depthfirst(source,destination,p,v,m);
         int min;
        // for(int i=0;i<v.size()-1;i++){
          
        //     for(int j=i;j<v.size();j++){
        //         if(v[i].size()>v[j].size()){
        //             swap(v[i],v[j]);
        //         }

        //     }
        // }
       // v.erase(v.begin());
       //sort(v.begin(),v.end());
        return v;
       }

    void groupFreightCars() {
        // for every vertex, group freight cars by links

        for(auto it:vertices){
            unordered_map<string,vector<FreightCar*>>m;
            Vertex* ver = it;
            for(int i=0;i<ver->sealed_freight_cars.size();i++){
                vector<string> b= bfs(ver->name,ver->sealed_freight_cars[i]->destination_city);
                ver->sealed_freight_cars[i]->next_link= b[1];
                //cout<<b[1]<<endl;
                m[ver->sealed_freight_cars[i]->next_link].push_back(ver->sealed_freight_cars[i]);
                // cout<<ver->sealed_freight_cars[i]->max_parcel_capacity<<endl;
                // cout<<ver->min_freight_cars_to_move<<endl;
                //vector<string> d = dfs(ver->name,ver->sealed_freight_cars[i]->destination_city)[0];
                

            }
          //  cout<<m.size()<<endl;
            // for(auto it:m){
            //    for(auto i:it.second){
            //     cout<<i->destination_city<<i->max_parcel_capacity<<endl;
            //    }
            // }
            //cout<<m.size();
            for(auto ite: m){
               // cout<<"Hi the fucking bastard";
            //    cout<<ite.second.size()<<endl;
            //    cout<<ver->min_freight_cars_to_move<<endl;
               int i1=ite.second.size();
               int i2= ver->min_freight_cars_to_move;
               bool f=false;
               if(i1== max(i1,i2))
               f=true;
               
                if(f){
                    //cout<<"Hellow"<<endl;
                    ver->trains_to_move[ite.first]=ite.second;
                    m.erase(ite.first);
                }
                if(m.empty())
                break;
            }
            for(auto itt: m){
                for(int i=0;i<itt.second.size();i++ ){
                    vector<string> d = dfs(ver->name, itt.second[i]->destination_city);
                    itt.second[i]->next_link= d[1];
                    // if one of the vertex is already visisted then fcar will remain stranded at the same postition
                    for(int k=1;k<d.size();k++){
                        if(itt.second[i] ->c[d[k]]==1){
                            itt.second[i]->stranded= true;
                            ver->stranded.push_back(itt.second[i]);
                            break;

                        }
                    }
                    if(itt.second[i]->stranded== true)
                    continue;
                    else if(itt.second[i]->stranded==false && itt.first!=d[1]){
                    //itt.second.erase(itt.second.begin()+i);
                    m[itt.second[i]->next_link].push_back(itt.second[i]);
                    }
                   
                }
            }
            for(auto jm:m){
                for(int i=0;i<jm.second.size();i++){
                    if(jm.second[i]->stranded== true){
                        jm.second.erase(jm.second.begin()+i);
                        i=i-1;
                    }
                }
            }
            for(auto itl:m){
                if(itl.second.size()>=ver->min_freight_cars_to_move){
                    ver->trains_to_move[itl.first]=itl.second;
                }
                // else{
                //     for(int i=0;i<itl.second.size();i++){
                //         itl.second[i]->stranded= true;
                //         ver->stranded.push_back(itl.second[i]);
                //     }
                // }
            }
            

        }
    }

    void moveTrains() {
        // for every vertex, move freight cars to next link
        for(auto it: vertices){
            for(auto i :it->trains_to_move){
                 Vertex* desti = nullptr;
                        for(auto it:vertices){
                            if(it->name== i.first)
                           { desti = it;
                           }
                        }
                for(int j=0;j<i.second.size();j++){
                    if(i.first == i.second[j]->destination_city){
                        i.second[j]->c[i.first]=1 ;
                        i.second[j]->current_location= i.first;
                        for(int k=0;k<i.second[j]->parcels.size();k++){
                            i.second[j]->parcels[k]->delivered = true;
                            desti->all_parcels.push_back(i.second[j]->parcels[k]);
                           
                            //cout<<i.second[j]->parcels[k]->delivered<<endl;
                             i.second[j]->parcels[k]->current_location = i.first;
                              remove(it->all_parcels.begin(),it->all_parcels.end(),i.second[j]->parcels[k]);
                        }
                       
                      //  remove(i.second.begin(),i.second.end(),i.second[j]);
                        //remove this car from frieght cars of vertex,trains to mmove and then also form sealed car
                         desti->freight_cars.push_back(i.second[j]);
                        remove(it->freight_cars.begin(),it->freight_cars.end(),i.second[j]);
                        remove(it->sealed_freight_cars.begin(),it->sealed_freight_cars.end(),i.second[j]);
                         i.second.erase(i.second.begin()+j);
                        j=j-1;
                    }
                    else{
                       
                        i.second[j]->c[i.second[j]->current_location]=1;
                        i.second[j]->current_location= i.first;
                         for(int k=0;k<i.second[j]->parcels.size();k++){
                            remove(it->all_parcels.begin(),it->all_parcels.end(),i.second[j]->parcels[k]);
                           
                             i.second[j]->parcels[k]->current_location = i.first;
                              desti->all_parcels.push_back(i.second[j]->parcels[k]);
                            
                        }
                        //cout<<i.second[j]->current_location<<endl;
                        i.second[j]->c[i.second[j]->current_location]=1;

                        i.second[j]->next_link="";
                        desti->sealed_freight_cars.push_back(i.second[j]);
                        desti->freight_cars.push_back(i.second[j]);
                         remove(it->freight_cars.begin(),it->freight_cars.end(),i.second[j]);
                        remove(it->sealed_freight_cars.begin(),it->sealed_freight_cars.end(),i.second[j]);
                         
                    }
                }
            }
           
        }
    }



};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar*> freight_cars;
    std::map<std::string, Parcel*> parcels;
    std::map<int, std::vector<Parcel*>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;
    vector<map<string,Parcel*>> status;


    PRC(int max_parcel_capacity, int min_freight_cars_to_move) {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};

    }

    void create_graph(std::string graph_file_name) {

        // read graph.txt file and create graph
        // read graph.txt file and create graph
        ifstream Inputfile(graph_file_name);
        string line,word="";
        while(getline(Inputfile,line)){
            stringstream tt(line);
            vector<string> v;
            while(getline(tt,word,' ')){
                v.push_back(word);
               // cout<<word<<endl;

            }
            this->graph.add_edge(v[0],v[1],min_freight_cars_to_move,max_parcel_capacity);

        }

    }

    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
         // read parcels.txt file and create parcels
        ifstream InputFile(parcels_file_name);
        string line,word;
        

        while(getline(InputFile,line)){
            vector<string> v;
            stringstream tt(line);
            while(getline(tt,word,' ')){
                v.push_back(word);
            }
            int tti= stoi(v[0]);
            int prio = stoi(v[4]);
            Parcel* parcel = new Parcel(tti,v[1],v[2],v[3],prio);
            parcels[v[1]] = parcel;
            parcels_with_time_tick[tti].push_back(parcel); 
    }
   //cout<<parcels.size()<<endl;
    // for(auto it:parcels){
    //     cout<<it.first<<" "<<it.second->origin<<endl;
    // }
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel*> get_bookings(int time_tick, std::string vertex) {
        list<Vertex*>v= graph.vertices;
       Vertex * find = nullptr;
       for(auto it : v){
           if(it->name== vertex)
          { find = it;
            break;
          }

       }
       if(find == nullptr)
       return {};
       vector<Parcel*> p;
       for(int i=0;i<find->all_parcels.size();i++){
        if(find->all_parcels[i]->time_tick == time_tick){
            p.push_back(find->all_parcels[i]);
        }
       }
       return p;
        
    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        for(auto it: this->parcels){
            state[it.first]= it.second->current_location;
            //cout<<it.second->current_location<<endl;
        }
       // cout<<endl<<endl;

        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {
        if(run_till_time_tick==-1 || run_till_time_tick>= max_time_tick){
            run_till_time_tick= max_time_tick;

        }
       // time_tick=1;
        status.push_back(parcels);
        status.push_back(parcels);
       // cout<<run_till_time_tick<<endl;
        while(time_tick<run_till_time_tick){
            old_state= get_state();
            // cout<<"hi runsimultion"<<endl;
            for(auto it: parcels_with_time_tick[time_tick]){
                Vertex* ver= nullptr;
                if(it->origin==it->current_location){
                    for(auto tt:graph.vertices){
                        if(tt->name==it->origin){
                            ver = tt;
                            break;
                        }
                    }
                   // cout<<it->origin<<endl;
                    ver->loadParcel(it);
                   
                }
               // cout<<ver->all_parcels.size()<<endl;
            }
           
            for(auto it:graph.vertices){
                it->loadFreightCars();
                it->clean_unmoved_freight_cars();
            }
            graph.groupFreightCars();
            graph.moveTrains();
            new_state= get_state();
            //  for(auto it:old_state){
            //     cout<<it.second<<endl;
            // }
            // cout<<endl<<endl;
            // for(auto it:new_state){
            //     cout<<it.second<<endl;
            // }
           // cout<<time_tick<<endl;
           // cout<<convergence_check()<<endl;
           status.push_back(parcels);
            if(!convergence_check())
            time_tick++;
            else break;
        }

        // function to run simulation
    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
        if(old_state == new_state){
            return true;

        }
        else{
            return false;
        }
    }

    bool all_parcels_delivered() {
        for (auto& parcel_pair : this->parcels) {
            Parcel& parcel = *parcel_pair.second;
            if (!parcel.delivered) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels() {
         vector<string> v;
        //cout<<parcels.size()<<endl;
        for(auto ite:parcels_with_time_tick){
            //cout<<it.second->delivered<<endl;
            for(auto it:ite.second){
            if(it->delivered==false)
            v.push_back(it->parcel_id);
            }
        }
        return v;

        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
        vector<string> v;
        //cout<<parcels.size()<<endl;
        for(auto ite:parcels_with_time_tick){
            //cout<<it.second->delivered<<endl;
            for(auto it:ite.second){
            if(it->delivered==true)
            v.push_back(it->parcel_id);
            }
        }
        return v;
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
        vector<string > c;
        for(auto it:status[t]){
            string s= it.first+" "+it.second->current_location+" "+ to_string(it.second->delivered)+"\n";
            c.push_back(s);
        }
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
        string s;
        for(auto it:status[t]){
            if(it.first == parcel_id)
           { s = it.first+" "+it.second->current_location+" "+ to_string(it.second->delivered)+"\n";
               break ;
           }
        }
        return s;

    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
        vector<string> v;

        for(auto it:parcels){
            if(it.second->delivered==true)
            v.push_back(it.first);

        }
        return v;
    }

};


//  int main() {

//     PRC prc(2, 2);
//     // create a graph
//      prc.create_graph("samples/2/graph.txt");
//     prc.process_parcels("samples/2/bookings.txt");
//     prc.run_simulation(3);
//     prc.run_simulation(4);
//     cout<<prc.time_tick<<endl;
//     cout<<prc.get_stranded_parcels().size()<<endl;
//   //  prc.graph.print_graph();
   
// //    prc.run_simulation(3);
// //    prc.get_stranded_parcels();

//     return 0;
// }

#include <cassert>
#include <iostream>
#include <fstream>

int main(){
        // create a PRC object
    PRC prc(2, 2);
    // create a graph
    prc.create_graph("samples/9/graph.txt");
    prc.process_parcels("samples/9/booking.txt");
    std::ofstream resultFile("test_results.txt", std::ios::app);

    prc.run_simulation(2);

    std::map<std::string, std::string> status = prc.get_state();

    //cout all  parcels in the status
    for (auto parcel : status) {
        std::cout << parcel.first << " " << parcel.second << std::endl;
    }

    if (status["P1"] == "A") {
        resultFile << "Test Case 9: Passed\n";
        
    }
    else{
        resultFile << "Test Case 9: Failed\n";
        
    }


    return 0;
}