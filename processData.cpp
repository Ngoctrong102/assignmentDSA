/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
	
	//N = 1;
	// TDataset* p = static_cast<TDataset*>(pData);
	// //pOutput = new int(p->FS(pRequest));
	// cout << "truoc\n";
	// TLine l;
	// l.id = 570;
	// int idx = 0;
	// L1Item<int>* a = p->getLine().find(l, idx)->data.list_stid.getHead();
	// while (a != NULL) {
	// 	cout << a->data <<" ";
	// 	a = a->pNext;
	// }
	// cout << "\n";
	// cout << "sau\n";
	// //pOutput = p->LSL(570,N);
	// pOutput = new int(p->ISL(7751,570,3));
	// a = p->getLine().find(l,idx)->data.list_stid.getHead();
	// while (a != NULL) {
	// 	cout << a->data<<" ";
	// 	a = a->pNext;
	// stringstream s;
	// s << pRequest;
	// string req = "";
	// s >> req;
	// int id =0;
	// if (req == "LSC"){
	// 	s >> id;
	// 	cout << id;
	// }
	TDataset* p = static_cast<TDataset*>(pData);
	N = 1;
	stringstream s;
	s << pRequest;
	string req = "";
	s >> req;
	if (req == "CL"){
		if (!s.good()) pOutput = new int(p->CL());
		else {
			getline(s,req);
			pOutput = new int(p->CLcity(req));
		}
	}
	else if (req == "LSC"){
		getline(s,req);
		pOutput = p->LSC(req,N);
	}
	else if (req == "LLC"){
		getline(s,req);
		pOutput = p->LLC(req,N);
	}
	else if (req == "LSL"){
		int id = 0;
		s >> id;
		pOutput = p->LSL(id,N);
	}
	else if (req == "FC"){
		getline(s,req);
		pOutput = new int(p->FC(req));
	}
	else if (req == "FS"){
		getline(s,req);
		pOutput = new int(p->FS(req));
	}
	else if (req == "SLP"){
		int station_id = 0;
		int track_id = 0;
		s >> station_id;
		s >> track_id;
		pOutput = new int(p->SLP(station_id,track_id));
	}
	// còn cái này 
	else if (req == "IS"){
		string name = "";
		string pos = "";
		getline(s,name,',');
		getline(s,pos,'(');
		getline(s,pos,')');
		pOutput = new int(p->IS(name,pos)); 
	}
	else if (req == "RS"){
		int id = 0;
		s >> id;
		pOutput = new int(p->RS(id));
	}
	// còn cái này 
	else if (req == "US"){
		int station_id = 0;
		string name = "";
		int city_id = 0;
		string pos = "";
		string bo = "";
		s >> station_id;
		getline(s,name,',');
		getline(s,pos,'(');
		getline(s,pos,')');
		for (int i=0; i<4;i++) getline(s,bo,',');
		s >> city_id;
		pOutput = new int(p->US(station_id,name,city_id,pos));
	}
	else if (req == "ISL"){
		int station_id = 0;
		int line_id = 0;
		int pos = 0;
		s >> station_id;
		s >> line_id;
		s >> pos;
		pOutput = new int(p->ISL(station_id,line_id,pos));
	}
	else if (req == "RSL"){
		int station_id = 0;
		int line_id = 0;
		s >> station_id;
		s >> line_id;
		pOutput = new int(p->RSL(station_id,line_id));
	}
}

