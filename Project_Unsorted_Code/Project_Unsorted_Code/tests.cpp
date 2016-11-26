#include "myHelper.h"
#include<cstdlib>
#include<iostream>


void test_myString_Splitting() {
  using namespace myString::Split;
  
  try {
    vector<string>& v = toEqLen_vec("ab c ", 2);     
    cout << v.size() << '\n';
    
    v = byDelim_vec("1,,,1", ",");
    cout << v.size() << '\n';
    
    v = byDelim_vec("1,,,1", ",", true);
    cout << v.size() << '\n';
    
    v = byDelim_vec("1,,,", ",", true);
    cout << v.size() << '\n';
    
    v = byDelim_vec(",,,", ",", true);
    cout << v.size() << '\n';
    
    v = byDelim_vec("1,,,1", ",", false, true);
    cout << v.size() << '\n';
    
    v = byDelim_vec("1,,,1", ",", true, true);
    cout << v.size() << '\n';
    
    v = byDelim_vec("1,,,", ",", true, true);
    cout << v.size() << '\n';
    
    v = byDelim_vec(",,,", ",", true, true);
    cout << v.size() << '\n';
    

    //toEqLen("abc", 0);

  } catch(std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
  }
  
}

void test_myGraph_AdjList_Reading() {
  vector<list<long>>G = vector<list<long>>(1);
  myGraph::AdjList::Read::from_plain_text(&G, "kargerMinCut.txt", "\t");
  
  
  return;
}

void test_myStat() {
  using namespace myStat::Distro;
  vector<long>& pu = runif(0L,4L, 20);
  long u;
  for(long i = 0; i < pu.size(); ++i) {
    u = runif(0L, 4L).front();
    cout << pu.at(i) << '\t' << u << '\n';
  }

}

void test_myHeap_Heap() {
  myHeap::Heap h(myHeap::HeapableOperations::min);
  for(long i = 0; i < 10; ++i) {
    h.Ins({ i, myStat::Distro::runif(0L,1000L)[0] });
    h.print("%ld(%0.lf),");
  }
  cout << "---\n";
  for(long i = 0; i < 10; ++i) {    
    h.Del(i);
    h.print("%ld(%0.lf),");
  }
  return;
}
int main() {
  test_myString_Splitting();
  test_myGraph_AdjList_Reading();
  test_myStat();
  myPointer::Ptr<long> SP = new long[10];
  test_myHeap_Heap();

  system("pause");
  return 0;
}