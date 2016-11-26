#ifndef _MY_HELPER_H_
#define _MY_HELPER_H_
/** FRONT MATTER **/
#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdexcept>
#include<cassert>
#include<vector>
#include<list>
#include<random>
#include<cmath>
#include<cstdarg>
#include<chrono>
using namespace std;

/** DECLARES **/

namespace myAssert { //"my" is always lowercase
  /**      Helper functions facilitating flow control                                                 **/
  void asrt(string errmsg, string inWhere, bool cond1, bool cond2 = true, bool cond3 = true, bool cond4 = true);
}
using myAssert::asrt;

namespace myGraph { //"my" is always lowercase
  namespace AdjList { //from this level down all capitalized namespace names
    /**    Helper functions to deal with adj lists                                                    **/

    /*R) Topic "R"                                                                          */
    namespace Read { //myGraph::adjList::Read::
      void from_plain_text(vector<list<long>>* G, string fullpath, string delim, long LineBufferSize = 200L);
      void from_plain_text(vector<list<pair<long,double>>>* G, string fullpath, string delim, long LineBufferSize = 200L, string delimWeights = ",");
      
    }

  }
}

namespace myHeap {
  enum HeapableOperations {
    min = 0,
    max = 1
  };
  struct Heap {
  private:
    vector<std::pair<long, double>> data;
  public:
    const myHeap::HeapableOperations MaintainedOperation;
    
    Heap(myHeap::HeapableOperations OperationToBeMaintained)
      : MaintainedOperation(OperationToBeMaintained) { }
    long size() { return data.size(); }
    void print() {
      for(auto it = data.begin(); it != data.end(); ++it) {
        cout << it->first << "(" << it->second << "),";
      }
      cout << "end\n";
    }
    long pos(long key) {
      for(long i = 0; i < data.size(); ++i) {        
        if(data.at(i).first == key) return i;
      }
      return -1; //zero data.size automatically returns -1
    }
    std::pair<long, double> Root() {
      return data.front();
    }
    long Ins(std::pair<long, double> x) {
      data.push_back(x);
      long i = data.size() - 1;
      long u = (i - 1) >> 1;
      while(i > 0 && 
        ((MaintainedOperation == min && data[ u ].second > x.second) 
       ||(MaintainedOperation == max && data[ u ].second < x.second))) {
          data[ i ] = data[ u ];
          data[ u ] = x;
          i = u--;
          u >>= 1;
      }
      return i;
    }
    void Del(long key) {
      myAssert::asrt("MaintainedOperation must be initialized", 
                     "myHeap::Heap::Del(long key)", 
                      MaintainedOperation == min || MaintainedOperation == max);
      long i = pos(key); if(i < 0) return; //Case zero data.size returns here
      long n = size() - 1;
      if(n == i) {
        data.pop_back();
        return;
      }
      auto x = data[ n ];
      double y = x.second;
      data[ i ] = x;
      data.pop_back(); //data.size decremented
      if(--n == 0) return;
      //now restore heap property for element[i]
      
      while(i >= 0 && i <= n) {
        long d1 = (i + 1) * 2 - 1; // left child (down1)
        long d2 = d1 + 1;          //right child (donw2)
        if(d1 > n) d1 = -1; 
        if(d2 > n) d2 = -1; 

        long u = (i == 0) ? -1 : ((i - 1) / 2); // parent (upper)
        
        if(MaintainedOperation == min) {
          if(u >= 0 && data[ u ].second > y) {
            //the case of parent violation: swap i <-> u
            //N.B.: relationship with sibling is guaranteed via parent
            data[ i ] = data[ u ]; data[ u ] = x;
            i = u;
          } else if(d2 >= 0 && data[ d2 ].second < data[ d1 ].second) {
            // d2 is the smaller(larger) child if oper is min(max)
            //swap i <-> d2
            data[ i ] = data[ d2 ]; data[ d2 ] = x;
            i = d2;
          } else if(d1 >= 0 && data[ d1 ].second < y) {
            //swap i <-> d1
            data[ i ] = data[ d1 ]; data[ d1 ] = x;
            i = d1;
          } else {
            return;
          }
        } else if(MaintainedOperation == max) {
          if(u >= 0 && data[ u ].second < y) {
            //the case of parent violation: swap i <-> u
            //N.B.: relationship with sibling is guaranteed via parent
            data[ i ] = data[ u ]; data[ u ] = x;
            i = u;
          } else if(d2 >= 0 && data[ d2 ].second > data[ d1 ].second) {
            // d2 is the smaller(larger) child if oper is min(max)
            //swap i <-> d2
            data[ i ] = data[ d2 ]; data[ d2 ] = x;
            i = d2;
          } else if(d1 >= 0 && data[ d1 ].second > y) {
            //swap i <-> d1
            data[ i ] = data[ d1 ]; data[ d1 ] = x;
            i = d1;
          } else {
            return;
          }
        } else {
          return;
        }
        
      }
    }
  };
}

namespace myPointer {
  template<typename T> struct Ptr {
    T* p;
    Ptr(T* q) : p{ q } {} //template declaration-definition inseparable
    ~Ptr() {
      try {
        delete [] p;
      } catch(exception e) {
        try {
          delete p;
        } catch(exception e) {}
      }
    };
  };
  
}

namespace myStat {
  /**      Helper functions concerning statistics                                                     **/
  namespace OrderStats { //myStat::OrderStats::
    template<typename T> T max(int count, T x, ...);
    template<typename T> T min(int count, T x, ...);
  }
  namespace Distro { //myStat::Distro::
    /**    Helper functions re distributions                                                          **/
    std::default_random_engine& getDefaultRandomEngine();
    vector<float> runif(float a, float b, long n = 1);
    vector<double> runif(double a, double b, long n = 1);
    vector<int> runif(int a, int b, long n = 1);
    vector<long> runif(long a, long b, long n = 1);
  }
}

namespace myString {
  /**    Helper function to deal with strings                                                         **/
  /*S) Topic "S"                                                                          */
  namespace Split { //myString::Split::
    vector<string> toEqLen_vec(string s, int theEqualLength);
    list<string> toEqLen_lst(string s, int theEqualLength);
    vector<string> byDelim_vec(string s, string delim, bool excludeEmptySegments = false, bool keepEmptySegmentsOnTheTwoMargins = false);
    list<string> byDelim_lst(string s, string delim, bool excludeEmptySegments = false, bool keepEmptySegmentsOnTheTwoMargins = false);
  }
}


#endif
