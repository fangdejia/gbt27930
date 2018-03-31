/*
 * command analysis.h
 *
 *  Created on: 2018��1��3��
 *      Author: Administrator
 */

#ifndef COMMAND_ANALYSIS_H_
#define COMMAND_ANALYSIS_H_
#include<vector>
#include<string>
#include<iostream>
#include"table field.h"
using namespace std;
class CMD_Analys{
public:
	string get_argument(int i){return string(line.getString(i));}
	int get_cmd();
	string help();
	CMD_Analys(istream&iff):in(iff),line(' ',false),cmd(){}
	~CMD_Analys(){}
	void insert_cmd(const string&c);	//��Ŵ�0��ʼ
private:
	istream& in;
	Table_field line;
	vector<string> cmd;
	vector<string> def_cmd;
};
int find_in_strings(const string&cmd,vector<string>& cmds);



#endif /* COMMAND_ANALYSIS_H_ */
