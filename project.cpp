#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

class student
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks,extra;
	double per;
	char grade;

	//function to calculate grade
	void calculate()
    {
        per=(((p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0)*0.7)+(extra*0.3);
        if(per>=95)
            grade='A+';
        else if(per>=90&& per<95)
            grade='A';
        else if(per>=80&&per<90)
            grade='B';
        else if(per>=70&&per<80)
            grade='C';
        else if(per>=60&& per<70)
            grade='D';
        else if(per>=40&&per<60)
            grade='E';
       else if(per<40)
            grade='F';
    }
public:
    //function to accept data from user
    void getdata()
    {
        cout<<"\nEnter The roll number of student ";
        cin>>rollno;
        cout<<"\n\nEnter The Name of student ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\nEnter The marks in Physics out of 100 : ";
        cin>>p_marks;
        cout<<"\nEnter The marks in Chemistry out of 100 : ";
        cin>>c_marks;
        cout<<"\nEnter The marks in Mathematics out of 100 : ";
        cin>>m_marks;
        cout<<"\nEnter The marks in English out of 100 : ";
        cin>>e_marks;
        cout<<"\nEnter The marks in Computer Science out of 100 : ";
        cin>>cs_marks;
        cout<<"\nEnter The marks in Extra-Curricular activities out of 100 : ";
        cin>>extra;
        calculate();
    }

	//function to show data on screen
	void showdata()
    {
        cout<<"\nRoll number of student : "<<rollno;
        cout<<"\nName of student : "<<name;
        cout<<"\nMarks in Physics : "<<p_marks;
        cout<<"\nMarks in Chemistry : "<<c_marks;
        cout<<"\nMarks in Mathematics : "<<m_marks;
        cout<<"\nMarks in English : "<<e_marks;
        cout<<"\nMarks in Computer Science :"<<cs_marks;
        cout<<"\nMarks in Extra-curricular activities :"<<extra;
        cout<<"\nPercentage of student is  :"<<per;
        cout<<"\nGrade of student is :"<<grade;
    }

	void show_tabular()
    {
        cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)
            <<e_marks<<setw(4)<<cs_marks<<setw(8)<<extra<<setw(8)<<per<<setw(6)<<grade<<endl;
    }
	int retrollno()
    {
        return rollno;
    }
}; //class ends here

void write_student();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen

//function to write in file
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}

//function to read all records from file
void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
//function to read specific record from file

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}

//function to modify record of file

void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
            int pos=(-1)*static_cast<int>(sizeof(st));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&st), sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}

//function to delete record of file

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}

//function to display all students grade report

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"=====================================================================\n";
	cout<<"R.No     Name                P   C   M   E   CS   E-C   %age   Grade"<<endl;
	cout<<"=====================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

//function to display result menu
void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\t*****RESULT MENU******";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)";
	cin>>ch;
	system("cls");
	switch(ch)
	{
        case '1' :
            class_result();
            result();
             break;
        case '2' :
            cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
            display_sp(rno);
            result();
             break;
        case '3' :
            break;
        default:
            cout<<"\a";
	}
}

void intro()
{
	cout<<"\n\n\n\t\t\t\t\t  MINI PROJECT";
	cout<<"\n\n\t\t\t\tEvaluation Of Academic Performance";
	cout<<"\n\n\n\t\t\t\t\tMade By : YASH CHAUHAN";
	cout<<"\n\t\t\t\tGraphic Era (Deemed to be University),Dehradun";
	cin.get();
}

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.MODIFY STUDENT RECORD";
	cout<<"\n\n\t4.DELETE STUDENT RECORD";
	cout<<"\n\n\t5.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-5) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':
	    write_student();
	    entry_menu();
	    break;
	case '2':
	    display_all();
	    entry_menu();
	    break;
	case '3':
	    cout<<"\n\n\tPlease Enter The roll number ";
        cin>>num;
        modify_student(num);
        entry_menu();
        break;
	case '4':
	    cout<<"\n\n\tPlease Enter The roll number ";
	    cin>>num;
        delete_student(num);
        entry_menu();
        break;
	case '5':
	    break;
	default:
	    cout<<"\a";
	    entry_menu();
	}
}
void login()
{
    cout<<"\tEnter the password to access the Entry/Edit menu !!!!!\n";
    string pass,pass1;
    cin>>pass;
    ifstream ps("password.txt");
    getline(ps,pass1);
    if(pass.compare(pass1)==0)
        entry_menu();
    else
    {
        cout<<"!!!! Wrong Password !!!!!";
        cin.ignore();
        cin.get();
    }
    ps.close();
}
int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	intro();
	ofstream pass("password.txt");
	string ps ="Admin@123";
	pass<<ps;
	pass.close();
	do
	{
		system("cls");
		cout<<"\n\n\n\t********MAIN MENU*********";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1':
                result();
				break;
			case '2':
			    login();
				break;
			case '3':
			    cout<<"\n\n\tTHANK YOU FOR USING THE SYSTEM.\n\n";
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}
