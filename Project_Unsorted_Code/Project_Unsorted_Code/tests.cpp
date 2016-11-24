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
  list<list<long>>G = list<list<long>>(1);
  myGraph::AdjList::Read::from_plain_text(&G, "E:/Dropbox/Courses/Roughgarden_Stanford_algo_course/Week4/_f370cd8b4d3482c940e4a57f489a200b_kargerMinCut.txt", "\t");
  
  
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
int main() {
  //test_myString_Splitting();
  test_myGraph_AdjList_Reading();
  //test_myStat();
  
  myPointer::Ptr<long> SP = new long[10];

  system("pause");
  return 0;
}