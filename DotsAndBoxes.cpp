#include<iostream>
#include<cstring>
using namespace std;
bool playerFirst;
int boxCount;
int countA,countB;
bool thisStepA;
struct edge
{
	int ebelong;//0 for player a, 1 for player b
	int box1,box2;
	edge(int b1,int b2){
		ebelong=-1;
		box1=b1;
		box2=b2;
	}
	void print(){
		cout<<this->ebelong<<endl;
	}
};
edge eset[24]={
	edge(0,-1),edge(1,-1),edge(2,-1),
	edge(0,-1),edge(0,1),edge(1,2),edge(2,-1),
	edge(0,3),edge(1,4),edge(2,5),
	edge(3,-1),edge(3,4),edge(4,5),edge(5,-1),
	edge(3,6),edge(4,7),edge(5,8),
	edge(6,-1),edge(6,7),edge(7,8),edge(8,-1),
	edge(6,-1),edge(7,-1),edge(8,-1)
};
int hinderSet[8]={4,5,7,9,14,16,18,19};
int normalSet[16]={0,1,2,3,6,8,10,11,12,13,15,17,20,21,22,23};
class box
{
	private:
		int status;//0 for 4 sides free, 1 for 1 occpied 	
	public:
		box(int s1,int s2,int s3,int s4,int b1,int b2,int b3,int b4);
		int side[4];
		int neighborBox[4];
		int getstatus(){
			return status;
		}
		void check(){
			int tempCount=0;
			for(int i=0;i<4;i++){
				if(eset[side[i]].ebelong>-1){
					tempCount++;
				}
				//cout<<tempCount<<endl;
			}
			status=tempCount;
		}
};
box::box(int s1,int s2,int s3,int s4,int b1,int b2,int b3,int b4)
{
	side[0]=s1;
	side[1]=s2;
	side[2]=s3;
	side[3]=s4;
	neighborBox[0]=b1;
	neighborBox[1]=b2;
	neighborBox[2]=b3;
	neighborBox[3]=b4;
	status=0;
}
box bset[9]=
{
	box(0,3,4,7,-1,-1,1,3),
	box(1,4,5,8,-1,0,2,4),
	box(2,5,6,9,-1,1,-1,5),
	box(7,10,11,14,0,-1,4,6),
	box(8,11,12,15,1,3,5,7),
	box(9,12,13,16,2,4,-1,8),
	box(14,17,18,21,3,-1,7,-1),
	box(15,18,19,22,4,6,8,-1),
	box(16,19,20,23,5,7,-1,-1)
};
void print()
{
	cout<<"Map:\n";
	for(int i=0;i<3;i++){
		cout<<"*\t";
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
	}
	cout<<"*\n";
	for(int i=3;i<7;i++)
	{
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
		cout<<"\t";
	}
	cout<<"\n";
	for(int i=7;i<10;i++){
		cout<<"*\t";
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
	}
	cout<<"*\n";
	for(int i=10;i<14;i++)
	{
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
		cout<<"\t";
	}
	cout<<"\n";
	for(int i=14;i<17;i++){
		cout<<"*\t";
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
	}
	cout<<"*\n";
	for(int i=17;i<21;i++)
	{
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
		cout<<"\t";
	}
	cout<<"\n";
	for(int i=21;i<24;i++){
		cout<<"*\t";
		if(eset[i].ebelong==0)
		{
			cout<<"P\t";
		}
		else if(eset[i].ebelong==1){
			cout<<"C\t";
		}
		else
		{
			cout<<i<<"\t"; 
		}
	}
	cout<<"*\n";
	cout<<"Player A Score: "<<countA<<" Player B Score: "<<countB<<endl;
	cout<<"Total Score:"<<boxCount<<endl; 
	for(int i=0;i<9;i++){
		cout<<bset[i].getstatus()<<" ";
	}
	cout<<endl;
	for(int i=0;i<24;i++){
		cout<<eset[i].ebelong<<" ";
	}
	cout<<endl;
}
void allBoxCheck(){
	int tempcount=0;
	for(int i=0;i<9;i++){
		bset[i].check();
		//cout<<bset[i].getstatus()<<endl;
		if(bset[i].getstatus()==4){
			tempcount++;
		}
	}
	boxCount=tempcount;
}
void playerStep()
{
	int temp;
	cout<<"This is your Step, please choose one edge(0-23): ";
	cin>>temp;
	while(eset[temp].ebelong!=-1){
		cout<<"Please select another vaild edge! :";
		cin>>temp;
	}
	eset[temp].ebelong=0;
	int currentCount=boxCount;
	allBoxCheck();
	if(boxCount>currentCount){
		countA+=(boxCount-currentCount);
		thisStepA=true;
	}
	else{
		thisStepA=false;
	}
}
void AIStep()
{
	bool freeEdgeExist=false;
	for(int i=0;i<9;i++){
		if(bset[i].getstatus()==1||bset[i].getstatus()==0){
			freeEdgeExist=true;
		}
	} 
	if(freeEdgeExist){
		for(int i=0;i<9;i++){
			if(bset[i].getstatus()==3){
				for(int j=0;j<4;j++){
					if(eset[bset[i].side[j]].ebelong<0){
						eset[bset[i].side[j]].ebelong=1;
						thisStepA=false;
						int currentCount=boxCount;
						allBoxCheck();
						countB+=(boxCount-currentCount);
						return;
					}
				}
			}
		}
		if(playerFirst){
			for(int i=0;i<8;i++){
				if(eset[hinderSet[i]].ebelong==-1){
					if((bset[eset[hinderSet[i]].box1].getstatus()<2)&&
					((eset[hinderSet[i]].box2==-1)||(bset[eset[hinderSet[i]].box2].getstatus()<2))){
						eset[hinderSet[i]].ebelong=1;
						thisStepA=true;
						allBoxCheck();
						return;
					}
				} 
			}
			for(int i=0;i<16;i++){
				if(eset[normalSet[i]].ebelong==-1){
					if((bset[eset[normalSet[i]].box1].getstatus()<2)&&
					((eset[normalSet[i]].box2==-1)||(bset[eset[normalSet[i]].box2].getstatus()<2))){
						eset[normalSet[i]].ebelong=1;
						thisStepA=true;
						allBoxCheck();
						return;
					}
				} 
			}
		}else{
		for(int i=0;i<16;i++){
				if(eset[normalSet[i]].ebelong==-1){
					if((bset[eset[normalSet[i]].box1].getstatus()<2)&&
					((eset[normalSet[i]].box2==-1)||(bset[eset[normalSet[i]].box2].getstatus()<2))){
						eset[normalSet[i]].ebelong=1;
						thisStepA=true;
						allBoxCheck();
						return;
					}
				} 
			}
			for(int i=0;i<8;i++){
				if(eset[hinderSet[i]].ebelong==-1){
					if((bset[eset[hinderSet[i]].box1].getstatus()<2)&&
					((eset[hinderSet[i]].box2==-1)||(bset[eset[hinderSet[i]].box2].getstatus()<2))){
						eset[hinderSet[i]].ebelong=1;
						thisStepA=true;
						allBoxCheck();
						return;
					}
				} 
			}
		}
	}
	else{
		bool openChainExist=false;
		int chainHead;
		int headEdge;
		bool checked[9];
		for(int i=0;i<9;i++){
			if(bset[i].getstatus()==4){
				checked[i]=true;
			}else{
				checked[i]=false;
			}
		}
		for(int i=0;i<9;i++){
			if(bset[i].getstatus()==3){
				openChainExist=true;
				chainHead=i;
				break;
			}
		} 
		if(openChainExist){
			int currentEdge;
			int nextBox;
			int length;
			for(int i=0;i<4;i++){
				if(eset[bset[chainHead].side[i]].ebelong<0){
					checked[chainHead]=true;
					length=1;
					currentEdge=bset[chainHead].side[i];
					headEdge=currentEdge;
					nextBox=bset[chainHead].neighborBox[i];
					break;
				}
			} 
			while(nextBox>=0){
				if(bset[nextBox].getstatus()==2&&checked[nextBox]==false){
					checked[nextBox]=true;
					length++;
					for(int i=0;i<4;i++){
						if(eset[bset[nextBox].side[i]].ebelong<0&&bset[nextBox].side[i]!=currentEdge){
							currentEdge=bset[nextBox].side[i];
							nextBox=bset[nextBox].neighborBox[i];
							break;
						}
					}			
				}else{
					nextBox=-1;
					break;
				}
			}
			if(length!=2){
				eset[headEdge].ebelong=1;
				thisStepA=false;
				int currentCount=boxCount;
				allBoxCheck();
				countB+=(boxCount-currentCount);
				return;
			}else{
				int maxlength=0;
				for(int i=0;i<9;i++){
					if(checked[i]){
						continue;
					}else{
						checked[i]=true;
						int templength=1;
						int edge1=-1;
						int edge2=-1;
						int nextbox1,nextbox2;
						for(int j=0;j<4;j++){
							if(eset[bset[i].side[j]].ebelong<0){
								if(edge1<0){
									edge1=bset[i].side[j];
									nextbox1=bset[i].neighborBox[j];
								}else{
									edge2=bset[i].side[j];
								}
							}
						}
						while(nextbox1>=0){
							if(bset[nextbox1].getstatus()==2&&checked[nextbox1]==false){
								checked[nextbox1]=true;
								templength++;
								for(int k=0;k<4;k++){
									if(eset[bset[nextbox1].side[k]].ebelong<0&&bset[nextbox1].side[k]!=edge1){
										edge1=bset[nextbox1].side[k];
										nextbox1=bset[nextbox1].neighborBox[k];
										break;
									}
								}			
							}else{
								nextbox1=-1;
								break;
							}
						}
						while(nextbox2>=0){
							if(bset[nextbox2].getstatus()==2&&checked[nextbox2]==false){
								checked[nextbox1]=true;
								templength++;
								for(int k=0;k<4;k++){
									if(eset[bset[nextbox2].side[k]].ebelong<0&&bset[nextbox2].side[k]!=edge2){
										edge2=bset[nextbox1].side[k];
										nextbox2=bset[nextbox2].neighborBox[k];
										break;
									}
								}			
							}else{
								nextbox1=-1;
								break;
							}
						}
						if(templength>maxlength){
							maxlength=templength;
						}
					}
				}
				if(maxlength>2){
					eset[currentEdge].ebelong=1;
					thisStepA=true;
					allBoxCheck();
					return;
				}else{
					eset[headEdge].ebelong=1;
					int currentCount=boxCount;
					allBoxCheck();
					countB+=(boxCount-currentCount);
					thisStepA=false;
					return;
				}
			}
		}
		else{
			int minlength=9;
			for(int i=0;i<9;i++){
				if(checked[i]){
					continue;
				}else{
					checked[i]=true;
					int templength=1;
					int tempedge=-1;
					int edge1=-1;
					int edge2=-1;
					int nextbox1,nextbox2;
					for(int j=0;j<4;j++){
						if(eset[bset[i].side[j]].ebelong<0){
							if(edge1<0){
								edge1=bset[i].side[j];
								nextbox1=bset[i].neighborBox[j];
							}else{
								edge2=bset[i].side[j];
								nextbox2=bset[i].neighborBox[j];
							}
						}
					}
					if(nextbox1>=0){
						tempedge=edge1;
					}else{
						tempedge=edge2;
					} 
					while(nextbox1>=0){
						if(bset[nextbox1].getstatus()==2&&checked[nextbox1]==false){
							checked[nextbox1]=true;
							templength++;
							for(int k=0;k<4;k++){
								if(eset[bset[nextbox1].side[k]].ebelong<0&&bset[nextbox1].side[k]!=edge1){
									edge1=bset[nextbox1].side[k];
									nextbox1=bset[nextbox1].neighborBox[k];
									break;
								}
							}			
						}else{
							nextbox1=-1;
							break;
						}
					}
					while(nextbox2>=0){
						if(bset[nextbox2].getstatus()==2&&checked[nextbox2]==false){
							checked[nextbox1]=true;
							templength++;
							for(int k=0;k<4;k++){
								if(eset[bset[nextbox2].side[k]].ebelong<0&&bset[nextbox2].side[k]!=edge2){
									edge2=bset[nextbox1].side[k];
									nextbox2=bset[nextbox2].neighborBox[k];
									break;
								}
							}			
						}else{
							nextbox1=-1;
							break;
						}
					}
					if(templength<minlength){
						minlength=templength;
						headEdge=tempedge;
					}
				}
			}
			eset[headEdge].ebelong=1;
			thisStepA=true;
			allBoxCheck();
			return;
		}
	}
}
int main(){
	string temp;
	cout<<"Choose goes first ? :(Y/N)";
	cin>>temp;
	if(temp=="Y")
	{
		playerFirst=true;
		thisStepA=true;
	}else if(temp=="N")
	{
		playerFirst=false;
		thisStepA=false;
	}
	boxCount=0;
	countA=0;
	countB=0;
	print();
	while(boxCount!=9)
	{
		if(thisStepA){
			playerStep();
		}else{
			AIStep();
		}
		print();
	}
	if(countA>countB)
	{
		cout<<"Player A win!";
	}
	else{
		cout<<"Player B win!";
	}
	system("pause");
	return 0;
}
