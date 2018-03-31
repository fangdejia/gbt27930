#include "canread.h"
#include "command analysis.h"
#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
using namespace std;
inline string find_name(const string&,string&);
bool trans_file(istream&file,ostream& out);
int main(){
	CANREAD canread;
	string ifname,ifnamenoex,ifex;
	ifstream input;
	CMD_Analys cmd(cin);
	cmd.insert_cmd("open");
	cmd.insert_cmd("trans");
	cmd.insert_cmd("analyze");
	cmd.insert_cmd("help");
	cmd.insert_cmd("close");
	ofstream output,output1,errout;
	do{
		string ofname;
		cout<<" [ ";
		if(!ifname.size()){
			cout<<"!#*";
		}else
			cout<<ifname;
		cout<<"]# ";
		switch(cmd.get_cmd()){
		case 0:
			ifname = cmd.get_argument(1);
			if(!ifname.size()){
				cout<<"Open �������ļ�����"<<endl;
				break;
			}else{
				cout<<"���ļ���..."<<endl;
				if(!!input){
					input.clear();
					input.close();
				}
				input.open(ifname.c_str());
				if(!input){
					cout<<"�޷����ļ�:\t"<<ifname<<endl;
					ifname.clear();
					break;
				}
				ifnamenoex = find_name(ifname, ifex);
				cout<<"�ɹ��������ļ��ļ�:\t"<<ifname<<endl;
			}
			break;
		case 1:
			if(!input){
				cout<<"δ���κ��ļ���"<<endl;
				break;
			}
			ofname = ifnamenoex+"_trans."+ifex ;
			output.open(ofname.c_str());
			if(!output){
				cout<<"���ļ�"<<ofname<<"ʧ��!"<<endl;
				break;
			}
			if(trans_file(input,output)){
				cout<<"ת���ɹ�..."<<endl<<"����ѱ�����"<<ofname<<endl;
			}else{
				cout<<"�ļ�"<<ifname<<"ת��ʧ��,�������"<<ofname<<endl;
			}
			output.close();
			break;
		case 2:
			if(!input){
				cout<<"δ���κ��ļ���"<<endl;
				break;
			}

			cout<<"������..."<<endl;
			ofname = (ifnamenoex+"����."+ifex);
			output.open(ofname.c_str());
			cout<<"�������ݽ�������ļ�"<<ofname<<"��--"<<endl;
			ofname = (ifnamenoex+"���."+ifex);
			output1.open(ofname.c_str());
			cout<<"���ķ��������������ļ�"<<ofname<<"��--"<<endl;
			ofname =(ifnamenoex+"����."+ifex);
			errout.open(ofname .c_str());
			cout<<"���ķ����з����Ĵ���������ļ�"<<ofname<<"��--"<<endl;
			try{
				canread.read_data(input,errout);
				canread.print(output,output1,errout);
				input.close();
				output.close();
			}catch(runtime_error& ex){
				std::cerr<<ex.what()<<endl;
			}
			output.close();
			output1.close();
			errout.close();
			cout<<"���ķ������!!!"<<endl;
			break;
		case 3:
			cout<<"\t open �ļ���:"<<"�������ļ���,�����ļ�����Ϊ�������ļ�.\n"<<endl;
			cout<<"\t trans :"<<"��open����򿪵�CANtestץȡ�ı���ת���ɱ�׼�����ļ�,�����Ϊ�ļ���_tran.��׺��.\n"<<endl;
			cout<<"\t analyze :"<<"��open�����Ѵ򿪵������ļ����н�����������ļ�����.\n"<<endl;
			cout<<"\t close"<<"�ر�Ŀǰ�򿪵��ļ�\n"<<endl;
			cout<<"\t help :"<<"����.\n"<<endl;
			cout<<cmd.help();
			break;
		case 4:
			cout<<"���ڹر� \t"<<ifname<<endl;
			input.clear();
			input.close();
			cout<<"�ر��ļ�"<<ifname<<"�ɹ�"<<endl;
			break;
		case -1:
			cout<<"�޷�ʶ������!!!����help�鿴������"<<endl;
			break;
		default:
			cout<<"����������޸ģ�����"<<endl;
			break;
		}
	}while(1);
	return 0;
}
inline string find_name(const string&s,string& name){
	string::size_type index = s.find_last_of('.');
		name=string(s.begin()+index + 1,s.end());
	return string(s.begin(),s.begin()+index);
}
bool trans_file(istream&file,ostream& out){
	string s1,s2;
	while(getline(file,s1)){
		int j = 0;
		s2.resize(s1.size());
		for(unsigned int i = 0; i < s1.length(); i++){
			while(i<s1.length()&&(s1[i]==' '||s1[i]=='\t')) i++;
			while(i<s1.length()&&(s1[i]!=' '&&s1[i]!='\t'))s2[j++]=s1[i++];
			s2[j++]='\t';
		}
		s2.resize(j - 1 );
		out<<s2<<endl;
	}
	return true;
}
