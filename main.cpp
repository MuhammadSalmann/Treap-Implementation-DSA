#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <ctime>
#define SPACE 10
using namespace std;
 
class TeacherNode {		//Treap
    string Name, Subject;	  	int id, priority;
	TeacherNode* right;   	  	TeacherNode* left;
    public:
    TeacherNode() { id=0; 	 priority = rand() % 100;  	 right = left = NULL; 	}
    	
    	void setPriority(int priority) 				{ this->priority = priority; }
		int getPriority()  							{ return priority; 			 }
    	void setid(int id) 							{ this->id = id; 			 }
		int getid()  								{ return id; 			     }
		void setName(string Name) 					{ this->Name = Name; 		 }
		string getName()  							{ return Name; 			     }
		void setSubject(string Subject) 			{ this->Subject = Subject; 	 }
		string getSubject()  						{ return Subject; 			 }
		
		void setRight(TeacherNode* right) 			{  this->right=right;   	 }
		TeacherNode* getRight()    					{  return right;        	 }
        void setLeft(TeacherNode* left) 			{  this->left=left;     	 }
		TeacherNode* getLeft()     					{  return left;         	 }
}; 

class Teachers {
	TeacherNode* Root;
	TeacherNode* CN;
	TeacherNode* NN;
	TeacherNode* LCN;
	public:
		Teachers()							{ Root = CN = LCN = NULL;	}
		void SetRoot(TeacherNode* Root) 	{ this->Root = Root; 		}
		TeacherNode* GetRoot() 				{ return Root; 				}

		void AddTeachers() {
        	fstream file;	int size;
        	cout<<"How Many Teachers You Want In the Tree:  ";   	cin>>size;
        	for(int j = 1;j <= size; j++) {
            	cout<<"\n*****Enter Teacher#"<<j<<" Details*****\n";  
				
				file.open("Teachers.txt", ios :: out | ios :: app );  
			
				int i;		cout<<"\nEnter The Teacher ID    :   ";	cin>>i;	file<<endl<<setw(20)<<i;
				string n;	cout<<"\nEnter The Teacher Name  :   ";	cin>>n;	file<<setw(20)<<n;
				string t;	cout<<"\nEnter The Teacher Type  :   ";	cin>>t;	file<<setw(20)<<t;
				//int c;		cout<<"\nEnter The Priority 	 :   ";	cin>>c;	
				Add(i, n, t);
				file.close();
        	}
    	}

		void Add(int v, string n, string t) {
			NN = new TeacherNode;    	
			NN->setid(v);			NN->setName(n);
			NN->setSubject(t);		//NN->setPriority(c);
            NN->setLeft(NULL);  	NN->setRight(NULL);

    		if (Root == NULL) {		Root = NN;		}
    
    		else{
				CN = Root;
				while(CN != NULL){
				
					LCN = CN;
					
					if(v < CN->getid())			CN = CN->getLeft();
					
					else 						CN = CN->getRight();
				}
					if(v < LCN->getid()) 		LCN->setLeft(NN);
					else                    	LCN->setRight(NN);
					CheckHeap(NN);
			}              
		}

		void CheckHeap(TeacherNode* N) {

			CN = Root;	int flag=0;
			while(CN != NULL && CN->getid() != N->getid()) {
				
				LCN = CN;
				
				if(N->getid() < CN->getid())	CN = CN->getLeft();

				else 							CN = CN->getRight();
			}
			
			if(LCN != NULL) {
				
				if (LCN->getLeft() != NULL && LCN->getLeft()->getPriority() > LCN->getPriority()) {
					rotateRight(LCN);		flag++;
				}
            	if (LCN->getRight() != NULL && LCN->getRight()->getPriority() > LCN->getPriority())	{
            		rotateLeft(LCN);		flag++;
				}		
			}
			if(flag != 0) CheckHeap(LCN);		
		}

		void Deletion() {
			int id;		cout<<"Enter Teacher ID:  ";   	cin>>id;	
			SetRoot(Delete(id));
		}

		TeacherNode* Delete(int val) {
	
			SearchForDelete(val);		//Other search due to recursion
			TeacherNode* temp   = NULL;
			
			if(CN != NULL) {
				if(CN->getLeft() == NULL || CN->getRight() == NULL) {
					
					if(CN->getLeft() == NULL)				{  temp = CN->getRight();  }
					else									{  temp = CN->getLeft();   }
		    
					if(LCN == NULL)		{	SaveFile(Root);		UpdateFile();   return temp;   	}
			
					if(LCN->getLeft() == CN) 	{  LCN->setLeft(temp);	}
					else 						{  LCN->setRight(temp); }
					free(CN);
				}
				else {
					
					if(CN->getLeft()->getPriority() > CN->getRight()->getPriority()) 	
							rotateRight(CN);
		
					else  	rotateLeft(CN);
					
					Delete(CN->getid());
				}
			}
			SaveFile(Root);		UpdateFile();
			return Root;
		}

		void rotateRight(TeacherNode* root) {
			
    		TeacherNode* C = root->getLeft();
    		TeacherNode* CR = C->getRight();
    		// rotate
    		C->setRight(root);
    		root->setLeft(CR);
    
    		if(root != Root) {
    	
    			CN = Root;		TeacherNode* GP;
    			
   				while(CN != NULL && CN->getid() != root->getid()){
			
				GP = CN;
				
				if(root->getid() < CN->getid())		CN = CN->getLeft();
				
				else 								CN = CN->getRight();
			}
			
			if(GP->getLeft() == root) 		GP->setLeft(C);
	
			else 							GP->setRight(C);
	
    		LCN = C;
			}
    		else  Root = C;
		}

		void rotateLeft(TeacherNode* root) {
			
			TeacherNode* C = root->getRight();
    		TeacherNode* CL = C->getLeft();
    		// rotate
    		C->setLeft(root);
    		root->setRight(CL);
 	
 			if(root != Root) {
 		
 				CN = Root;		TeacherNode* GP;
 				
    			while(CN != NULL && CN->getid() != root->getid()){
				
				GP = CN;
				
				if(root->getid() < CN->getid())		CN = CN->getLeft();
		
				else 								CN = CN->getRight();
				}
				
				if(GP->getLeft() == root)	GP->setLeft(C);
	
				else 		GP->setRight(C);
			
    			LCN = C;
			}
 			else  Root = C;
		}


		void DisplayTree(TeacherNode* r, int space) {
			if (r == NULL)  return;
    		space += SPACE; 
    		DisplayTree(r->getRight(), space); 
    		cout << endl;
    		for (int i = SPACE; i < space; i++)     cout << " ";  
    		cout << r->getid() << "\n";
    		for (int i = SPACE; i < space; i++)     cout << " ";  
    		cout << r->getName() << "\n"; 
    		for (int i = SPACE; i < space; i++) 	cout << " "; 
    		cout << r->getSubject() << "\n";
    		for (int i = SPACE; i < space; i++)     cout << " ";  
    		cout << r->getPriority() << "\n";
    		DisplayTree(r->getLeft(), space); 
		}
		
		void DisplayAll() {
			fstream file;
			file.open("Teachers.txt", ios :: in);
	
			if (!file) {      cout<<"\n****** No File Created ******\n";         }
	
			else {
				string view;
				
				cout<<"\n\t_______________________________________________________"<<"\n\n";
  				cout<<"\t"<<setw(10)<<"ID"<<setw(18)<<"NAME"<<setw(19)<<"SUBJECT";
  				cout<<"\n\t_______________________________________________________";
				getline(file, view);		//to ignore the first blank line in file
				while (!file.eof()) {
					getline(file, view);
					cout<<"\n\n"<<view;
				} 
				file.close();	
			}
		}
		
		void Update() {
			Search();		char choice;		
			if(CN != NULL) {
				int id;		string name, subject; 		
				do {
					cout<<"\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		      			  "\n\t\t        Main Menu               \n"
		      			  "\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n"
		      			  "\t1-> UPDATE NAME\n"
             	 		  "\t2-> UPDATE SUBJECT\n"
              			  "\t3-> MAIN MENU\n"
              			  "\t\t\t Choice = ";   cin>>choice;  system("cls");
            		switch(choice) {
                		case '1':	cout<<"\nEnter New Name    = ";  cin>>name;   CN->setName(name);	  	   break;
                		case '2':	cout<<"\nEnter New SUBJECT = ";  cin>>subject;   CN->setSubject(subject);     break;    
            		}   system("cls");
				}while(choice != '3');
				SaveFile(Root);		UpdateFile();
			}
		}

		void Search() {
    		int search;		cout<<"Enter Teacher ID:  ";   	cin>>search;
    		CN = Root;		LCN = NULL;
    		while(CN != NULL && CN->getid() != search) {
    			LCN = CN;
    			if(search < CN->getid()) 		{  CN = CN->getLeft();   }
    			else								{  CN = CN->getRight();  }
			}
			if(CN != NULL) {
				cout<<"\n*****Teacher Found*****\n\n";
				cout<<"NAME     :   "<<CN->getName()<<endl;
				cout<<"SUBJECT  :   "<<CN->getSubject()<<endl;
				cout<<"PRIORITY :   "<<CN->getPriority()<<endl;
				cout<<"\n***********************\n";
			}  
			else { cout<<"\n*****Not Found*****\n"; } 
		}
		
		void SearchForDelete(int search) {
    		CN = Root;		LCN = NULL;
    		while(CN != NULL && CN->getid() != search) {
    			LCN = CN;
    			if(search < CN->getid()) 			{  CN = CN->getLeft();   }
    			else								{  CN = CN->getRight();  }
			}
			if(CN == NULL) { cout<<"\n*****Not Found*****\n"; } 
		}
		
		void SaveFile(TeacherNode* A){
			fstream file;
			if( A != NULL) {
				int id, priority;		string name, subject;	
				file.open("Teachers1.txt", ios :: out | ios :: app );
				file<<endl<<setw(20)<<A->getid();
				file<<setw(20)<<A->getName();
				file<<setw(20)<<A->getSubject();
				file<<setw(20)<<A->getPriority();
				file.close();
				SaveFile(A->getLeft());
				SaveFile(A->getRight());	
			}
		}
		
		void UpdateFile() {
			DeleteFile();
			rename("Teachers1.txt", "Teachers.txt");
		}
		
		void UpdateTree() {
			fstream file;
			file.open("Teachers.txt", ios :: in);
			if (file) {     
				int id;		string name, subject;	
				//getline(file, name);		//to ignore the first blank line in file
				while (!file.eof()) {
					file >> id >> name >> subject;// >> priority;
					Add(id, name, subject);
				}
				file.close();
			}
		}	
		
		void DeleteFile() 		{		remove("Teachers.txt");		}
		
		void DeleteTree() {
			if(Root == NULL)	return;	
			
			TeacherNode* temp;		CN = Root->getLeft();
			while(CN != NULL) {
				temp = CN;
				CN = CN->getLeft();
				delete temp;
			}
			CN = Root->getRight();
			while(CN != NULL) {
				temp = CN;
				CN = CN->getRight();
				delete temp;
			}
			CN = Root;			delete CN;		
			DeleteFile();		Root = NULL;
		}
	
};

int main()
{
    Teachers C;		char choice;
	C.UpdateTree();
	while(1) {
        cout<<"\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		      "\n\t\t        Main Menu               \n"
		      "\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n"
		      "\t1-> Add Teachers\n"
              "\t2-> Display All Teachers\n"
              "\t3-> Display Tree\n"
              "\t4-> Search Teachers\n"
              "\t5-> Update Teachers\n"
              "\t6-> Delete Teachers\n"
              "\t7-> Delete All\n"
              "\t8-> Exit\n"
              "\t\t\t Choice = ";   cin>>choice;  system("cls");
            switch(choice) {
                case '1':   C.AddTeachers();     						break;
                case '2':   C.DisplayAll();     						break;
                case '3':   C.DisplayTree(C.GetRoot(), 5);  			break;
                case '4':   C.Search();   								break;
                case '5':   C.Update();        							break;
                case '6':   C.Deletion(); 								break;
                case '7':   C.DeleteTree();								break;
                case '8':   exit(0);
                default:   system("cls");
            }
    }
 
    return 0;
}

