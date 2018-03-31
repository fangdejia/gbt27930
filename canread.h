/*
 * canread.h
 *
 *  Created on: 2017��12��5��
 *      Author: Administrator
 */

#ifndef CANREAD_H_
#define CANREAD_H_
#include<iostream>
#include<vector>
#include"CANdata.h"
class CANREAD{
	vector<Basic_CAN_frame*> canframes;
	vector<Basic_CAN_frame*> oldframes;
	vector<Multi_frame*> oldmulframes;
	Multi_frame *multiframe;
	bool autoindex; //�Ƿ��Զ���ţ�Ϊ�����ȡ�ĵ��б��
	UINT indexcol ; //������Զ���ţ���ȡ�ĵ��еĵڼ�����Ϊ��ţ�Ĭ��Ϊ0
	BYTE ifs,ofs;
public:
	vector<Basic_CAN_frame*>::iterator findOldframe(Basic_CAN_frame*);
	vector<Multi_frame*>::iterator findOldframe(Multi_frame*);
	CANREAD():canframes(),oldframes(),oldmulframes(),multiframe(NULL),autoindex(false),indexcol(0),ifs('\t'),ofs('\t'){}
	VOID read_data(istream& in,ostream&errout=std::cerr, bool ignorefirstline=true);	//ignorefirstline��ʾ�Ƿ���Ե�һ��
	VOID set_index(vector<UINT>& where,bool auto_index = false, UINT indexc = 0){CANID_BASE=where[0 ];LENGTH_BASE=where[1]; DATA_BASE = where[2];autoindex= auto_index ; indexcol =indexc;} //��ȡ�ĵ��У�canid�����ݳ��Ⱥ�����֡���ڵ��У���0��ʼ����Ĭ��Ϊ��3����6�͵�7��
	VOID set_iofs(BYTE is='\t',BYTE os='\t'){ifs=is; ofs =os;}
	VOID print(ostream&,ostream&out1=std::cout ,ostream&errout=std::cerr);
	~CANREAD(){if(multiframe)delete multiframe; for(vector<Basic_CAN_frame*>::iterator it = canframes.begin();it !=canframes.end(); ++it)delete *it;for(vector<Multi_frame*>::iterator it = oldmulframes.begin();it !=oldmulframes.end(); ++it)delete *it;}
};




#endif /* CANREAD_H_ */
