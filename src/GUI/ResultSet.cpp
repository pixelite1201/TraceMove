#include "ResultSet.h"
  
 ResultSet:: ResultSet(int count=0) {
    results.resize(count);
  }
  
  void ResultSet:: add(Entry e) {
   
    if(m.find(e)==m.end())   //here we need to compare two entries hence overloaded < in Entry class
      m[e]=1;                //note that two entries are consider equal if except sketch everything else match
   else {
      m[e]=m[e]+1;//cout<<m[e]<<" "<<e.sketch<<" "<<e.imgId<<" "<<e.x<<" "<<e.y<<endl;
    }

  }
void ResultSet::sort() {
    int max = results.size();

    for(unordered_map<Entry,int,Hasher,EqualFn> :: iterator it=m.begin();it !=m.end();it++) {

     results[max-(it->second)].push_back(it->first);
    }

  }

 

