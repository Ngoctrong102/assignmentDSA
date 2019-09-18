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
bool TLine::operator==(TLine a) {
	return this->id == a.id;
}
bool TLine::operator!=(TLine a) {
	return this->id != a.id;
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
	string linestring;
	string pos_st;
	while (a != NULL) {
		if (a->data.id == station_id) break;
		else a = a->pNext;
	}
	if (a != NULL) pos_st = a->data.pos;
	else return -1;
	L1Item<TTrack>* t = this->getTrack().getHead();
	while (t != NULL) {
		if (t->data.id == track_id) break;
		else t = t->pNext;
	}
	if (t != NULL) linestring = t->data.lis;
	else return -1;
	int vt = linestring.find(pos_st);
	int pos = 0;
	if (vt == -1) return -1;
	else {
		for (int i = 0; i < vt; i++) {
			if (linestring[i] == ',') pos++;
		}
	}
	return pos;
}
int* TDataset::LSC(string city, int &N) {
	TCity c(city);
	int idx = 0;
	L1Item<TCity>* ci = this->city.find(c, idx);
	if (ci == nullptr) return new int(-1);
	int id = ci->data.id;
	L1Item<TStation>* s = this->station.getHead();
	L1List<int> kq;
	while (s != NULL) {
		if (s->data.city_id == id) kq.push_back(s->data.id);
		s = s->pNext;
	}
	N = kq.getSize();
	int* r = new int[N];
	L1Item<int>* k = kq.getHead();
	int i = 0;
	while (k != NULL) {
		r[i] = k->data;
		k = k->pNext;
		i++;
	}
	return r;
}
int* TDataset::LLC(string city, int& N) {
	TCity c(city);
	int id = 0;
	L1Item<TCity>* ci = this->city.find(c, id);
	if (ci == NULL) return new int(-1); 
	id = ci->data.id;
	L1Item<TLine>* s = this->line.getHead();
	L1List<int> kq;
	while (s != NULL) {
		if (s->data.city_id == id) kq.push_back(s->data.id);
		s = s->pNext;
	}
	N = kq.getSize();
	int* r = new int[N];
	L1Item<int>* k = kq.getHead();
	int i = 0;
	while (k != NULL) {
		r[i] = k->data;
		k = k->pNext;
		i++;
	}
	return r;
}
int* TDataset::LSL(int line_id, int &N) {
	TLine a;
	a.id = line_id;
	int idx;
	L1Item<TLine>* p = this->line.find(a, idx);
	L1Item<int>* temp;
	if (p != NULL) {
		temp = p->data.list_stid.getHead();
		N = p->data.list_stid.getSize();
	}
	else return NULL;
	int* kq = new int[N];
	int i = 0;
	while (temp != NULL) {
		kq[i] = temp->data;
		temp = temp->pNext;
		i++;
	}
	return kq;
}
int TDataset::RSL(int station_id, int line_id) {
	TLine a;
	a.id = line_id;
	int idx;
	L1Item<TLine>* p = this->line.find(a, idx);
	if (p != NULL) {
		int i = 0;
		if (p->data.list_stid.find(station_id, i)) {
			p->data.list_stid.remove(i);
			return 0;
		}
		else return -1;
	}
	else return -1;
}
int TDataset::ISL(int station_id, int line_id, int pos) {
	TLine a;
	a.id = line_id;
	int idx;
	L1Item<TLine>* p = this->line.find(a, idx);
	if (p != NULL) {
		int i = 0;
		if (p->data.list_stid.find(station_id, i)) return -1;
		else {
			if (p->data.list_stid.insert(pos, station_id) == -1) return -1;
			return 0;
		}
	}
	else return -1;
}
int TDataset::RS(int station_id) {
	L1Item<TStation>* p = this->station.getHead();
	int idx = 0;
	while (p != NULL) {
		if (p->data.id == station_id) break;
		p = p->pNext;
		idx++;
	}
	if (p == NULL) return -1;
	else {
		this->station.remove(idx);
		int index = 0;
		L1Item<TLine>* l = this->line.getHead();
		while (l != NULL) {
			l->data.list_stid.find(station_id, index);
			l->data.list_stid.remove(index);
			l = l->pNext;
		}
		return 0;
	}
}
int  TDataset::US(int station_id, string name, int city_id, string pos){
	L1Item<TStation>* p = this->station.getHead();
	while (p!=NULL){
		if (p->data.id == station_id) break;
		p = p->pNext;
	}
	if (p==NULL) return -1;
	else {
		p->data.name = name;
		p->data.city_id = city_id;
		p->data.pos = pos;
		return 0;
	}
}
int  TDataset::IS( string name, string pos){
	/*L1Item<TTrack>* tra = this->track.getHead();
	while (tra!=NULL){
		if (tra->data.lis.find(pos)!=-1) break;
		tra = tra->pNext;
	}
	if (tra == NULL) return -1;*/
	

	/*L1Item<TLine>* p = this->line.getHead();
	L1Item<int>* t = NULL;
	bool timthay = false;
	while (p!=NULL){
		t = p->data.list_trid.getHead();
		while (t!=NULL){
			if (t->data == tra->data.id) {
				timthay = true;
				break;
			}
			t = t->pNext;
		}
		if (timthay == true) break;
		p = p->pNext;
	}
	if (!timthay) return -1;
	else {*/
		TStation a;
		a.name = name;
		a.id = ++this->maxIdSt;
		a.pos = pos;
		a.city_id = 0;             //p->data.city_id;
		this->station.push_back(a);
		return this->maxIdSt;
	//}
}
void ReleaseData(void*& pData) {
	//TDataset* p = static_cast<TDataset*>(pData);
	delete pData;
}