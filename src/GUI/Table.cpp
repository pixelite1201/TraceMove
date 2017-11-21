#include "Table.h"
#include<algorithm>
Table::Table(){

}
Table::Table(Hash hash_) {
	hash = hash_;
}

void Table::fillEntry(vector<bool>& descriptor, int imgId, int x, int y) {
	Entry entry(hash.calcSketch(descriptor), imgId, x, y);
	entries.push_back(entry);
}

bool myfunction (Entry i,Entry j) { return (i.sketch<j.sketch); }
void Table::reverseIndex() {

	sort(entries.begin(),entries.end(),myfunction);
	buildMap();
}

void Table:: buildMap() {
	hashmap.clear();
	int lastSketch = -1;
	for(int i = 0; i < entries.size(); i++) {
		Entry e = entries[i];
		if(e.sketch != lastSketch) {
			lastSketch = e.sketch;
			hashmap[e.sketch]=i;
		}
	}
}
void Table::show(){
	for(vector<Entry> :: iterator it=entries.begin();it!=entries.end();it++)
		cout<<(*it).sketch<<endl;
}
void Table::find(vector<bool>& descriptor, ResultSet* found, int max) {
	int sig=hash.calcSketch(descriptor);
	if(hashmap.find(sig)==hashmap.end()){

		return;} // if not found, return
	// if found, add everything from the bucket
	else{
		int index = hashmap[sig];
		int i = index, j = 0;
		Entry e = entries[i];
		int sketch = e.sketch;
		while(e.sketch == sketch && j < max) {
			found->add(e);
			i++; j++;//cout<<e.sketch<<" "<<e.imgId<<" "<<e.x<<" "<<e.y<<endl;
			if(i >= entries.size()) break;
			e = entries[i];
		}
	}
}

