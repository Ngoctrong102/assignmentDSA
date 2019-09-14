/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

struct TCity {
    // The structure to store city information
    /*id: integer
	- name: string
	- coords: string
	- start_year: integer
	- url_name: string
	- country: string
	- country_state: string*/
    int id;
    string name;
    //int numLine;
    TCity():id(0),name(""){}
    TCity(string name);
    bool operator==(TCity a);
    bool operator!=(TCity a);
	//~TCity();
};

struct TLine {
    // The structure to store line information
    /*- id: integer
	- city_id: integer
	- name: string
	- url_name: string
	- color: string
	- system_id: integer
	- transport_mode_id: integer*/
    int id;
    string name;
    int city_id;
    L1List<int> list_stid;
    L1List<int> list_trid;
    TLine():id(0),name(""),city_id(0),list_stid(L1List<int>()),list_trid(L1List<int>()){}
    //~TLine();
};

struct TTrack {
    // The structure to store track information
    /*- id: integer
	- geometry: string
	- buildstart: integer
	- opening: integer
	- closure: integer
	- length: integer
	- city_id: integer*/
    int id;
    string lis;
    TTrack():id(0),lis(""){}
    //~TTrack();
};
struct TStation{
    /* id: integer
	- name: string
	- geometry: string(pos)
	- buildstart: integer
	- opening: integer
	- closure: integer
	- city_id: integer*/
    int id;
    string name;
    int city_id;
    string pos;
    TStation():id(0),name(""),city_id(0),pos(""){}
    //~TStation();
};

struct ListITofLI {
	int idLI;
	L1List<int> idIT;
	ListITofLI():idLI(0),idIT(L1List<int>()){}
	ListITofLI(int a):idLI(a),idIT(L1List<int>()){}
	bool operator==(ListITofLI a) {
		return this->idLI == a.idLI;
	}
	bool operator!=(ListITofLI a) {
		return this->idLI != a.idLI;
	}
};

class TDataset {
    // This class can be a container that help you manage your tables
    private:
        //int numLine;
        L1List<TCity> city;
        L1List<TLine> line;
        L1List<TStation> station;
        L1List<TTrack> track;
    public:
        TDataset():maxIdSt(0),city(L1List<TCity>()),line(L1List<TLine>()),station(L1List<TStation>()),track(L1List<TTrack>()){}
       // ~TDataset();
		int maxIdSt;
        L1List<TCity>& getCity();
        L1List<TLine>& getLine();
        L1List<TStation>& getStation();
        L1List<TTrack>& getTrack();
        int  CL();
        int  CLcity(string city);
        int* LSC(string city);
        int* LLC(string city);
        int* LSL(int line_id);
        int  FC(string city);
        int  FS(string station);
        int  SLP(int station_id, int track_id);
        int  IS(string cvs_desc);
        int  RS(int station_id);
        int  US(int station_id, string cvs_desc);
        int  ISL(int station_id, int line_id, int pos);
        int  RSL(int station_id, int line_id);
};

L1List<ListITofLI>* doc_lines(string tenfile);
// Please add more or modify as needed

void LoadData(void* &);
void ReleaseData(void* &);
#endif //DSA191_A1_DBLIB_H