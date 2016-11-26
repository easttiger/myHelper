#include "myHelper.h"

void myAssert::asrt(string errmsg, string inWhere, bool cond1, bool cond2, bool cond3, bool cond4) {

  bool jointCondition = (cond1 && cond2 && cond3 && cond4);

#ifndef USE_CASSERT

  if(jointCondition) return;

  ostringstream ss;
  ss << "#Error[" << errmsg << "] in " << inWhere;
  std::cerr << ss.str() << '\n';
  system("pause");
  throw std::logic_error(ss.str());

#else

  assert(jointCondition);  

#endif
}

vector<string> myString::Split::toEqLen_vec(string s, int theEqualLength) {
  asrt("argin:theEqualLength must be positive", "myString::Split::toEqLen", theEqualLength > 0);
  vector<string> vRes;
  for(size_t i = 0L; i < s.size(); i += theEqualLength) {
    vRes.push_back(s.substr(i, theEqualLength));  //string::substr guarantees if the super string is shorter than the substring, then as many chars as possible are used.
  }
  return vRes;
}

list<string> myString::Split::toEqLen_lst(string s, int theEqualLength) {
  asrt("argin:theEqualLength must be positive", "myString::Split::toEqLen", theEqualLength > 0);
  list<string> vRes;
  for(size_t i = 0L; i < s.size(); i += theEqualLength) {
    vRes.push_back(s.substr(i, theEqualLength));  //string::substr guarantees if the super string is shorter than the substring, then as many chars as possible are used.
  }
  return vRes;
}

vector<string> myString::Split::byDelim_vec(string s, string delim, bool excludeEmptySegments, bool keepEmptySegmentsOnTheTwoMargins) {
  long delimWidth = delim.size();
  assert(delimWidth >= 0); //fail then illogical system
  if(delimWidth == 0) return toEqLen_vec(s, 1);
  //now on non-empty delim
  vector<string> vRes;
  long i = 0;
  for(long j = 0; j < s.size();) {
    if(s.compare(j, delimWidth, delim) == 0) {
      if(j > i || !excludeEmptySegments || (keepEmptySegmentsOnTheTwoMargins && i == 0)) {
        vRes.push_back(s.substr(i, j - i));
      }
      j += delimWidth;
      i = j;
    } else {
      ++j;
    }
  }
  assert(i >= 0 && i <= s.size());  //fail then illogical system
  if(i < s.size() || !excludeEmptySegments || keepEmptySegmentsOnTheTwoMargins) {
    vRes.push_back(s.substr(i, s.size() - i));
  }
  return vRes;
}

list<string> myString::Split::byDelim_lst(string s, string delim, bool excludeEmptySegments, bool keepEmptySegmentsOnTheTwoMargins) {
  long delimWidth = delim.size();
  assert(delimWidth >= 0); //fail then illogical system
  if(delimWidth == 0) return toEqLen_lst(s, 1);
  //now on non-empty delim
  list<string> vRes;
  long i = 0;
  for(long j = 0; j < s.size();) {
    if(s.compare(j, delimWidth, delim) == 0) {
      if(j > i || !excludeEmptySegments || (keepEmptySegmentsOnTheTwoMargins && i == 0)) {
        vRes.push_back(s.substr(i, j - i));
      }
      j += delimWidth;
      i = j;
    } else {
      ++j;
    }
  }
  assert(i >= 0 && i <= s.size());  //fail then illogical system
  if(i < s.size() || !excludeEmptySegments || keepEmptySegmentsOnTheTwoMargins) {
    vRes.push_back(s.substr(i, s.size() - i));
  }
  return vRes;
}

void myGraph::AdjList::Read::from_plain_text(vector<list<long>>* G, string fullpath, string delim, long LineBufferSize) {
  asrt("argin:G should be list initialized with 1 dummy element, argin:Delim must contain at least 1 character.", "myGraph::adjList::Read::from_plain_text", G->size() == 1, delim.size() > 0);
  if(LineBufferSize < 200L) LineBufferSize = 200L;
  long linenum = 1;
  vector<string> vs;
  char* line = new char[ LineBufferSize ];
  ifstream ifs(fullpath, ifstream::in);

  while(ifs.getline(line, LineBufferSize).good()){
    vs = myString::Split::byDelim_vec(string(line), delim, true, false);
    long n = stol(vs.front());    
    asrt("The " + to_string(linenum) + "-th line in the input file " + fullpath + " doesn't start with " + to_string(linenum), "", "myGraph::adjList::Reading::from_plain_text", linenum == n);
    
    if(vs.size() > 0) {
      //get node label            
      if(vs.size() > 1) { //the node has at least 1 adjacent node
        list<long> li;
        vector<string>::iterator it = vs.begin();
        ++it;
        for(; it != vs.end(); ++it) {
          li.push_back(stol(*it));
        }
        assert(n == G->size()); //fail then illogical system
        G->push_back(li);
      }
    }
    ++linenum;
  }
  
  delete[ ] line;
  return;
}


void myGraph::AdjList::Read::from_plain_text(vector<list<pair<long, double>>>* G, string fullpath, string delim, long LineBufferSize, string delimWeights) {
  asrt("argin:G should be list initialized with 1 dummy element. Both argin:delim argin:delimWeights must contain at least 1 character. Both must not be the decimalpoint and not equal to each other.", "myGraph::adjList::Read::from_plain_text", G->size() == 1, delim.size() > 0 && delimWeights.size() > 0, delim != delimWeights, delim != "." && delimWeights != ".");
  if(LineBufferSize < 200L) LineBufferSize = 200L;
  long linenum = 1;
  vector<string> vs;
  char* line = new char[ LineBufferSize ];
  ifstream ifs(fullpath, ifstream::in);

  while(ifs.getline(line, LineBufferSize).good()) {
    vs = myString::Split::byDelim_vec(string(line), delim, true, false);
    long n = stol(vs.front());
    asrt("The " + to_string(linenum) + "-th line in the input file " + fullpath + " doesn't start with " + to_string(linenum), "", "myGraph::adjList::Reading::from_plain_text", linenum == n);

    if(vs.size() > 0) {
      //get node label            
      if(vs.size() > 1) { //the node has at least 1 adjacent node
        list<std::pair<long,double>> li;
        vector<string>::iterator it = vs.begin();
        ++it;
        for(; it != vs.end(); ++it) {          
          auto x = myString::Split::byDelim_vec(*it, delimWeights);
          pair<long, double> y;
          y.first = stol(x[ 0 ]);
          y.second = stod(x[ 1 ]);           
          li.push_back(y);
        }
        assert(n == G->size()); //fail then illogical system
        G->push_back(li);
      }
    }
    ++linenum;
  }

  delete[ ] line;
  return;
}

template<typename T> T myStat::OrderStats::max(int count, T x, ...) {
  T y;
  va_list ap;
  va_start(ap, x);
  for(int i = 0; i < count; ++i) {
    y = va_arg(ap, T);
    if(y > x) x = y;
  }
  va_end(ap);
  return x;
}

template<typename T> T myStat::OrderStats::min(int count, T x, ...) {
  T y;
  va_list ap;
  va_start(ap, x);
  for(int i = 0; i < count; ++i) {
    y = va_arg(ap, T);
    if(y < x) x = y;
  }
  va_end(ap);
  return x;
}

std::default_random_engine& myStat::Distro::getDefaultRandomEngine() {
  static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  return generator;
}

vector<float> myStat::Distro::runif(float a, float b, long n) {
  asrt("a must be strictly less than b and n must be at least 1", "myStat::Distro::runif", a < b, n >= 1L);

  vector<float> vRes;
  std::default_random_engine& generator = myStat::Distro::getDefaultRandomEngine();
  std::uniform_real_distribution<float> distribution(a, b);
  for(long i = 0L; i < n; ++i) {
    vRes.push_back(distribution(generator));
  }
  return vRes;
}


vector<double> myStat::Distro::runif(double a, double b, long n) {
  asrt("a must be strictly less than b and n must be at least 1", "myStat::Distro::runif", a < b, n >= 1L);
  
  vector<double> vRes;
  std::default_random_engine& generator = myStat::Distro::getDefaultRandomEngine();
  std::uniform_real_distribution<double> distribution(a, b);
  for(long i = 0L; i < n; ++i) {
    vRes.push_back(distribution(generator));
  }
  return vRes;
}

vector<int> myStat::Distro::runif(int a, int b, long n) {
  asrt("a must be strictly less than b and n must be at least 1", "myStat::Distro::runif", a < b, n >= 1L);

  vector<int> vRes;
  std::default_random_engine& generator = myStat::Distro::getDefaultRandomEngine();
  std::uniform_int_distribution<int> distribution(a, b);
  for(long i = 0L; i < n; ++i) {
    vRes.push_back(distribution(generator));
  }
  return vRes;
}

vector<long> myStat::Distro::runif(long a, long b, long n) {
  asrt("a must be strictly less than b and n must be at least 1", "myStat::Distro::runif", a < b, n >= 1L);

  vector<long> vRes;
  std::default_random_engine& generator = myStat::Distro::getDefaultRandomEngine();
  std::uniform_int_distribution<long> distribution(a, b);
  for(long i = 0L; i < n; ++i) {
    vRes.push_back(distribution(generator));
  }
  return vRes;
}

long myHeap::Heap::size() { return data.size(); }

void myHeap::Heap::print(string formatWithDelim, string termination) {
  for(auto it = data.begin(); it != data.end(); ++it) {
    printf(formatWithDelim.c_str(), it->first, it->second);
  }
  printf("%s", termination.c_str());
}

long myHeap::Heap::pos(long key) {
  for(long i = 0; i < data.size(); ++i) {
    if(data.at(i).first == key) return i;
  }
  return -1; //zero data.size automatically returns -1
}

std::pair<long, double> myHeap::Heap::Extract() {
  return data.front();
}

long myHeap::Heap::Ins(std::pair<long, double> x) {
  data.push_back(x);
  long i = data.size() - 1;
  long u = (i - 1) >> 1;
  while(i > 0 &&
        ((MaintainedOperation == min && data[ u ].second > x.second)
        || (MaintainedOperation == max && data[ u ].second < x.second))) {
    data[ i ] = data[ u ];
    data[ u ] = x;
    i = u--;
    u >>= 1;
  }
  return i;
}

void myHeap::Heap::Del(long key) {
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
