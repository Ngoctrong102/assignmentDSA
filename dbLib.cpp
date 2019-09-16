/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
L1List<ListITofLI>* doc_lines(string tenfile) {
	ifstream r(tenfile, ios::in);
	if (!r.is_open()) throw new DSAException(3,"Can't open file!");
	L1List<ListITofLI>* t = new L1List<ListITofLI>;
	int tr = 0;
	int li = 0;
	string bo;
	getline(r, bo);
	while (r.good()) {
		getline(r, bo, ',');
		r >> tr;
		getline(r, bo, ',');
		r >> li;
		getline(r, bo);
		ListITofLI LI(li);
		int index = 0;
		L1Item<ListITofLI>* tam = t->find(LI, index);
		if (tam != NULL) {
			tam->data.idIT.push_back(tr);
		}
		else {
			ListITofLI* o = new ListITofLI(li);
			t->push_back(*o).data.idIT.push_back(tr);
		}
	}
	r.close();
	return t;
}
void LoadData(void* &pData){
	try {
		// đọc file cities.csv
		TDataset* p = new TDataset();
		ifstream r;
		string bo;

		// doc file city
		r.open("cities.csv", ios::in);
		if (!r.is_open()) throw DSAException(2, "Can't open file cities.csv!");
		getline(r, bo);
		while (r.good()) {
			TCity a;
			r >> a.id;
			getline(r, bo, ',');
			getline(r, a.name, ',');
			getline(r, bo);
			p->getCity().push_back(a);
		}
		r.close();
		//cout << p->getCity().getSize();
		L1List<ListITofLI>* station_lines = doc_lines("station_lines.csv");
		L1List<ListITofLI>* track_lines = doc_lines("track_lines.csv");
 		//cout << "y";
		
		r.open("lines.csv", ios::in);
		if (!r.is_open()) throw DSAException(4, "Can't open file lines.csv!");
		getline(r, bo);
		while (r.good()) {
			TLine l;
			r >> l.id;
			getline(r, bo, ',');
			r >> l.city_id;
			getline(r, bo, ',');
			getline(r, l.name, ',');
			getline(r, bo);
			ListITofLI LI(l.id);
			int index = 0;
			L1Item<ListITofLI>* tam = station_lines->find(LI, index);
			if (tam != NULL) l.list_stid = tam->data.idIT;
			tam = track_lines->find(LI, index);
			if (tam != NULL) l.list_trid = tam->data.idIT;
			p->getLine().push_back(l);
		}
		r.close();

		r.open("stations.csv", ios::in);
		if (!r.is_open()) throw DSAException(4, "Can't open file station.csv!");
		getline(r, bo);
		while (r.good()) {
			TStation s;
			r >> s.id;
			if (s.id > p->maxIdSt) p->maxIdSt = s.id;
			getline(r, bo, ',');
			getline(r, s.name, ',');
			getline(r, bo, '(');
			getline(r, s.pos, ')');
			for (int k = 0; k < 4; k++) getline(r, bo, ',');
			r >> s.city_id;
			getline(r, bo);
			p->getStation().push_back(s);
		}
		r.close();

		r.open("tracks.csv", ios::in);
		if (!r.is_open()) throw DSAException(4, "Can't open file tracks.csv!");
		getline(r, bo);
		while (r.good()) {
			TTrack tra;
			r >> tra.id;
			getline(r, bo, '(');
			getline(r, tra.lis, ')');
			getline(r, bo);
			p->getTrack().push_back(tra);
		}
		r.close();

		pData = p;
	}
	catch (DSAException e) {
		throw e;
	}
}



TCity::TCity(string name){
    this->id=0;
    this->name = name;
    // this->numLine = 0;
}

bool TCity::operator==(TCity a){
    return this->name == a.name;
}
bool TCity::operator!=(TCity a){
    return this->name != a.name;
}
bool TStation::operator==(TStation a) {
	return this->name == a.name;
}
bool TStation::operator!=(TStation a) {
	return this->name != a.name;
}
L1List<TCity>& TDataset::getCity(){
    return this->city;
}
L1List<TLine>& TDataset::getLine(){ //L1List<TLine>& getLine();
    return this->line;
}
L1List<TStation>& TDataset::getStation(){
    return this->station;
}
L1List<TTrack>& TDataset::getTrack(){
    return this->track;
}



// hàm xử lý của TDataset
int TDataset::CL(){ return this->getLine().getSize(); }
int TDataset::CLcity(string city){
	int id = this->FC(city);
	if (id == -1) return id;
    int num=0;
    L1Item<TLine>* l = this->line.getHead();
    while (l!=NULL){
        if (l->data.city_id == id){
            num++;
        }
        l = l->pNext;
    }
	return num;
}
int TDataset::FC(string city) {
	TCity a(city);
	int idx;
	L1Item<TCity>* p = this->city.find(a, idx);
	if (p == NULL) return -1;
	return p->data.id;
}
int TDataset::FS(string station) {
	TStation a(station);
	int idx;
	L1Item<TStation>* p = this->station.find(a, idx);
	if (p == NULL) return -1;
	return p->data.id;
}
int TDataset::SLP(int station_id, int track_id) {
	L1Item<TStation>* a = this->getStation().getHead();
	while (a != NULL) {
		if (a->data.id == station_id) break;
		else a = a->pNext;
	}
	if (a != NULL)string pos_st = a->data.pos;
	else return -1;
	L1Item<TTrack>* t = this->getTrack().getHead();
	while (t != NULL) {

	}
}
void ReleaseData(void*& pData) {
	//TDataset* p = static_cast<TDataset*>(pData);
	delete[] pData;
}