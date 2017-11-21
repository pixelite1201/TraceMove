#include "IndexStorage.h"
void IndexStorage::write(string filename, Index index,string path){
	stringstream ss;
	ofstream ofs (path+"info");
	ofs<<index.total_sketch<<endl;
	ofs<<index.total_hashf<<endl;
	ofs<<index.bitsPerHash<<endl;
	ofs<<index.Descriptorbits<<endl;
	ofs<<filename<<endl;
	ofs.close();
	ofstream ofs2(path+"imageNames");
        for(int i=0;i<index.imageNames.size();i++)
		ofs2<<index.imageNames[i]<<endl;
	ofs2.close();
	for(int i = 0; i < index.tables.size(); i++) {ss<<path<<"table"<<i;
		ofstream ofs(ss.str().c_str());
		Table table = index.tables[i];
		for(int x=0;x<table.entries.size();x++) {
			Entry e=table.entries[x];
			ofs<<e.sketch<<" "<<e.imgId<<" "<<e.x<<" "<<e.y<<endl;
		}
		ofs.close();ss.str("");
	}

	for(int i = 0; i < index.tables.size(); i++) {ss<<path<<"hash"<<i;
		ofstream ofs(ss.str().c_str());
		Hash hash = index.tables[i].hash;
		for(int j = 0; j < hash.indices.size(); j++) {
			for(int k = 0; k < hash.indices[j].size(); k++) {
				ofs<<hash.indices[j][k]<<" ";
			}
			ofs<<endl;
		}
		ofs.close();ss.str("");
	}
}
Index IndexStorage:: read(string path){
	stringstream ss;
	ifstream ifs (path+"info");
	int sPI,hPS,bPS,bPD;
	int sketch,imgId,x,y;
	ifs>>sPI;ifs>>hPS;ifs>>bPS;ifs>>bPD;ifs.close(); 
	Index index(sPI,hPS,bPD);
	ifs.close();
	ifstream ifs2 (path+"imageNames");
	string img;
	while(!ifs2.eof()){
        ifs2>>img;
	index.imageNames.push_back(img);
	}
	ifs2.close();
	for(int i = 0; i < index.tables.size(); i++) {ss<<path+"table"<<i;
		ifstream ifs(ss.str().c_str());
		while(!ifs.eof()){
			ifs>>sketch>>imgId>>x>>y;
			index.tables[i].entries.push_back(Entry(sketch,imgId,x,y));
		}index.tables[i].buildMap();
		ifs.close();ss.str("");
	}

	//for(int i=0;i<index.tables.size();i++){
	//for(int j=0;j<index.tables[i].entries.size();j++){
	//cout<<index.tables[i].entries[j].x<<endl;
	//}
	//}
	string line;

	int temp;

	for(int i = 0; i < index.tables.size(); i++) {ss<<path+"hash"<<i;
		vector<vector<int> > indices;

		indices.resize(index.total_hashf);
		ifstream ifs(ss.str().c_str());
		int j=0;
		while(getline(ifs,line)){
			stringstream ssh(line);
			while(ssh){
				ssh>>temp;
				indices[j].push_back(temp);
			}j++;ssh.str("");

		} 
Hash *h = new Hash(indices);
index.tables[i].hash= *h;
//index.tables[i]=Table(Hash(indices));

		ifs.close();ss.str("");
	}
	return index;
}
