#include<bits/stdc++.h>
//code:gzrosefinch
using namespace std;
int ab[8][25]={0};	//����ĳ��������0Ϊ���ڣ�1Ϊȱ��
int rd[8]={0};	//������ 
int mark[8]={0};	//��¼���ڴ��� 
void read_csv(string filename) //�������ݼ� 
{
    ifstream inFile(filename);
    string lineStr;
    getline(inFile,lineStr);
    int i=0,j;
    while(getline(inFile,lineStr)) //�����ѭ����ÿ�ζ�ȡһ���е�����,�ѽ��������lineStr�У�lineStr���ö��ŷָ��
    {
        stringstream ss(lineStr); //����stringstream��һ���ַ��������ͣ���lineStr����ʼ������ ss
        string str;
        //���ն��Ž��зָʣ�༨�㼰���� 
        for(j=0;j<3;j++) 
        {
        	getline(ss,str,',');	
        }
        for(j=0;j<20;j++){
        	getline(ss,str,',');
        	ab[i][j] = atoi(&str[0]);
		}
		i++;
		if(i>7) break;
    }
    //��ӡһ�¿���
//    for(i=0;i<7;i++){
//    	for(j=0;j<20;j++){
//    		cout<<ab[i][j]<<" ";
//		}
//		cout<<endl;
//	}
}
 
double algorithm(char *fn)
{
	srand((unsigned)time(NULL));
	int i,j;
	int x=0,y=0;	//xΪ��Ч����������yΪ�ܵ������� 
	for(i=0;i<7;i++){
		rd[i] += 4;
	}
    //��ȡ�����ļ�
    char filename[50]={'\0'};
    strcat(filename,fn);
    strcat(filename,"���ڱ�.csv");
    read_csv(filename);
    //��һ��
	for(i=0;i<7;i++){
		ab[i][0]--;
		if(ab[i][0] < 0) rd[i] += 20;	//����Ϊ3 
		else x++;
		y++;
	}
	//�ڶ����������� 
	int total = 25;
	for(j=1;j<4;j++){
		for(i=0;i<7;i++){
			if(rand()%total<rd[i]){
				ab[i][j]--;
				if(ab[i][j] > 0) rd[i] += 20;
				else{
					 x++;
					 mark[i]++;
				}
				y++;
			}
		}
		total += 10;
	}  
	//���������ڶ�ʮ��
	int target = -1,surplus = 0;
	for(j=5;j<20;j++){
		for(i=0;i<7;i++){
			if(rand()%total<rd[i]){
				ab[i][j]--;
				if(ab[i][j] > 0) rd[i] += 10;
				else{
					x++;
					mark[i]++;
					if(mark[i] == 4){
						surplus = 19 - j;
						j = 20;
						break;
					}
				}
				y++;
			}
		}
	}
	x += surplus;
	y += surplus;
    return x*0.1/y*10;
}

int main()
{
	char fn[50];
	double sum_E = 0,rs;
	for(int i=0;i<5;i++){
		printf("��������Ҫ�����Ŀγ̣�"); 
		scanf("%s",fn);
		rs = algorithm(fn);
		sum_E += rs;
		cout<<rs<<endl;
	}
	sum_E /= 5;
	cout<<"----------------------------------------"<<endl; 
	cout<<"��㷽����"<<endl;
	cout<<"1. ��һ�ε㼨����͵�7���ˣ����ȱ��ѧ���ĳ�����"<<endl;
	cout<<"�ڶ��μ�֮���ڴ�7���г�㣬�������ȱ��ѧ���ĳ����ʣ�����������ΪS1��ֱ����4��"<<endl;
	cout<<"����μ�֮�󣬽��ͳ���������ΪS2������¼ѧ�����ڴ��������е��ڴ�������4�ε�ѧ��������ֻ���ѧ��"<<endl;
	cout<<"���ſγ�Eֵ��ֵΪ��"<<sum_E;
}
