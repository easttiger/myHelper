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
      void from_plain_text(vector<list<long>>* G, string fullpath, string delim, long linenumBase = 1L, long LineBufferSize = 200L);
      void from_plain_text(list<list<long>>* G, string fullpath, string delim, long linenumBase = 1L, long LineBufferSize = 200L);
    }

  }
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
