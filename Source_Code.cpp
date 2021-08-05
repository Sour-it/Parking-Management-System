#include<iostream>
#include<vector>
#include<windows.h>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
#include<exception>
#define p_space 4

using namespace std;

int x;
class MyException : public exception{                     //accessed whenever the wrong password is entered

    public :

        const char * what() const throw()
        {
            return "Wrong Password";
        }
};

class time
{
    public:
        int hh;
        int mm;
        int ss;

        time(){}

        static int computeTimeDifference(time t1,time t2)
        {

            int sec1, sec2, totalsec;
            time t3;
            //calculate difference
            //get time in total seconds
            sec1 = t1.hh*60*60 + t1.mm*60 + t1.ss;
            sec2 = t2.hh*60*60 + t2.mm*60 + t2.ss;

            totalsec = sec2-sec1;

            //extract time in Hours, Minutes and Seconds
            t3.mm = totalsec/60;
            t3.hh = t3.mm/60;
            t3.mm = t3.mm%60;
            t3.ss = totalsec%60;

            // cout<<"Time difference:" <<hh<<":"<<mm<<":"<<ss<<endl;
            return t3.hh;
        }
};

class date
{
    public:
        int day;
        int month;
        int year;

        date(){}
};
class twheel
{
    public :

        bool b_pr;
        static int cbike;
        static float b_amt;

        twheel(bool a):b_pr(a)
        {}
};

class thwheel
{
    public :

        bool a_pr;
        static int cauto;
        static float a_amt;

        thwheel(bool a):a_pr(a)
        {}
};

class fwheel
{
    public :

        bool c_pr;
        static int ccar;
        static float c_amt;

        fwheel(bool a):c_pr(a)
        {}
};
class vehicle : public twheel ,public thwheel,public fwheel
{
    private:
        string  pltno;
        date    dt;
        time    arrive;
        time    departure;
        string  name;
        static bool del[p_space];
        static  int totalvehicle,totalamt;

    public:
        static int i;

        vehicle():twheel(false),thwheel(false),fwheel(false)
        {}

        int  type_menu();
        void addVehicle();

        int gettype()
        {
                 if(b_pr==true  && c_pr==false && a_pr==false) return 1;
            else if(b_pr==false && c_pr==false &&  a_pr==true) return 2;
            else if(b_pr==false && c_pr==true  && a_pr==false) return 3;
            else                                               return 0;
        }

        void printtype()
        {
                  if(b_pr==true  && c_pr==false && a_pr==false) cout<<"Bike";
            else if(b_pr==false && c_pr==false &&  a_pr==true)  cout<<"Auto";
            else if(b_pr==false && c_pr==true  && a_pr==false)  cout<<"Car";
            else                                                cout<<"Nigga";
        }

        static void totalveh()
        {
            cout<<"Total number of vehicle parked : "<< totalvehicle<<endl;
            cout<<"Total number of Bike parked : "<<cbike<<endl;
            cout<<"Total number of Three wheeler parked :"<<cauto<<endl;
            cout<<"Total number of Car parked : "<<ccar<<endl;
            cout<<"Total number of Available Space : "<<(p_space-1)-totalvehicle<<endl;
        }

        static void totalamount()
        {
            cout<<"Total Parking Charges Collection till now : Rs. "<<totalamt<<endl;
            cout<<"Total Parking Charges Collection of Bike parked : Rs."<<b_amt<<endl;
            cout<<"Total Parking Charges Collection of Three wheeler parked : Rs."<<a_amt<<endl;
            cout<<"Total Parking Charges Collection of Car parked : Rs."<<c_amt<<endl;
        }

        static vehicle searc(int a,vector<vehicle> v)
        {
            vehicle *vo = new vehicle;
            string pno;
            int typ;
            int flag=0;

            typ=vo->type_menu();
            cout<<"Enter vehicle number : ";
            cin>>pno;

            for(int j=0;j<=i;j++)
            {
                  int xo=v.at(j).gettype();
                  if(v.at(j).pltno==pno && xo==typ)
                  {
                      *vo=v.at(j);
                      x=j;
                      if(a==1)
                      {
                          cout<<endl<<"Vehicle Found"<<endl;
                          cout<<"Vehicle Type\t\tVehicle Number\t\t\tDriver Name\t\t\tDate\t\t\tArrival Time"<<endl;
                          v[j].printtype();
                          cout<<"\t\t\t"<<v[j].pltno<<"\t\t\t\t"<<v[j].name<<"\t\t\t"<<v[j].dt.day<<"/"<<v[j].dt.month<<"/"<<v[j].dt.year<<"\t\t\t"<< v[j].arrive.hh<<":"<<v[j].arrive.mm<<":"<<v[j].arrive.ss<<endl;
                          flag=1;
                      }
                      break;
                  }
            }
            if(a==1 && flag==0) cout<<"Vehicle Not Found";
            return *vo;
        }

        static void deleteVehicle(vector<vehicle> veh)
        {
            time depart;
            int time_diff;
            int charge=0;



              cout<<"Enter departure time in hours minutes and seconds : ";
              cin>>depart.hh>>depart.mm>>depart.ss;

              veh.at(x).departure.hh=depart.hh;
              veh.at(x).departure.mm=depart.mm;
              veh.at(x).departure.ss=depart.ss;

              time_diff=time::computeTimeDifference(veh.at(x).arrive,depart);

              if(veh.at(x).gettype()== 3)
              {
                  ccar--;
                  if(time_diff<2)
                  {
                      charge=20;
                      c_amt+=charge;
                  }
                  else
                  {
                      if((time_diff>2) && ((time_diff<5)))
                        {
                              charge=40;
                              c_amt+=charge;
                          }
                          else
                            {
                               charge=50;
                               c_amt+=charge;
                            }
                  }

              }
              else if(veh.at(x).gettype()==1)
              {
                  cbike--;

                      if( time_diff<2)
                      {
                          charge=5;
                          b_amt+=charge;
                      }
                      else
                      {
                          if((time_diff>2) && ((time_diff<5)))
                              {
                                  charge=10;
                                  b_amt+=charge;
                              }
                              else
                                {
                                   charge=20;
                                   b_amt+=charge;
                                }
                      }
              }
              else if(veh.at(x).gettype()==2)
              {
                  cauto--;

                      if( time_diff<2)
                      {
                          charge=10;
                          a_amt+=charge;
                      }
                      else
                      {
                          if((time_diff>2) && ((time_diff<5)))
                              {
                                  charge=15;
                                  a_amt+=charge;
                              }
                              else
                                {
                                   charge=30;
                                   a_amt+=charge;
                                }
                      }
              }
              cout<<"\nVehicle having vehicle number  : "<<veh.at(x).pltno<<" has left the parking after paying Rs. "<<charge<<endl;
              vehicle::del[x]=true;
             // cout<<"xx"<<x<<"yy"<<veh[x].del<<"zz";
             // i--;
              totalvehicle--;
              totalamt = totalamt+charge;
        }

        static void show(vector<vehicle> veh)
        {
          cout<<"Vehicle Type\t\tVehicle Number\t\t\tDriver Name\t\t\tDate\t\t\tArrival Time"<<endl;
          for(int j=0;j<i;j++)
          {
              //cout<<"xx"<<j<<"yy"<<veh[j].del<<"zz";
              if(vehicle::del[j]==false)
              {
                  veh[j].printtype();
                  cout<<"\t\t\t"<<veh[j].pltno<<"\t\t\t\t"<<veh[j].name<<"\t\t\t\t"<<veh[j].dt.day<<"/"<<veh[j].dt.month<<"/"<<veh[j].dt.year<<"\t\t\t"<< veh[j].arrive.hh<<":"<<veh[j].arrive.mm<<":"<<veh[j].arrive.ss<<endl;
              }
          }

        }

};

vector<vehicle> veh(p_space);


int fwheel :: ccar=0;
int thwheel :: cauto=0;
int twheel :: cbike=0;

float thwheel :: a_amt=0;
float twheel :: b_amt=0;
float fwheel :: c_amt=0;

int vehicle :: totalvehicle=0;
int vehicle ::totalamt=0;
int vehicle ::i=0;
bool vehicle :: del[p_space] =  {false};

int vehicle::type_menu(){

    int a1;

    try{
        cout<<"Choose the type of vehicle"<<'\n';
        cout<<"1. Two wheeler."<<'\n'<<"2. Three wheeler."<<'\n'<<"3. Four wheeler."<<'\n';
        cin>>a1;
             if(a1==1)
            {
                b_pr=true  ;
                c_pr=false ;
                a_pr=false;
            }
        else if(a1==2)
        {
            b_pr=false  ;
                c_pr=false ;
                a_pr=true;
        }
        else if(a1==3)
        {
            b_pr=false  ;
                c_pr=true ;
                a_pr=false;
        }
        else            throw"Invalid Input";
    }catch(const *e){
            cerr<<e<<endl<<"Enter Again";
            system("pause");
            system("cls");
        }

    return a1;
}

void vehicle::addVehicle()
{

          int a;
          vehicle *v = new vehicle;
          if(totalvehicle>=3)
          {
              cout<<"Parking Space is Full Kindly wait";
              return;
          }

          else{
                a=type_menu();
              cout<<"Enter vehicle number : ";
              cin>>v->pltno;
              cout<<"Enter arrival time in hours minutes and seconds : ";
              cin>>v->arrive.hh>>v->arrive.mm>>v->arrive.ss;
              cout<<"Enter date in day month and year: ";
              cin>>v->dt.day>>v->dt.month>>v->dt.year;
              cout<<"Enter Driver Name : ";
              cin>>v->name;

              veh.at(i).pltno=v->pltno;
              veh.at(i).arrive.hh=v->arrive.hh;
              veh.at(i).arrive.mm=v->arrive.mm;
              veh.at(i).arrive.ss=v->arrive.ss;
              veh.at(i).dt.day=v->dt.day;
              veh.at(i).dt.month=v->dt.month;
              veh.at(i).dt.year=v->dt.year;
              veh.at(i).name=v->name;
              vehicle::del[i]=false;

              i++;
              totalvehicle++;

              if(a == 1)
              {
                  cbike++;
                  cout<<"\nVehicle added successfully"<<endl;
              }
              else if(a == 2)
              {
                  cauto++;
                  cout<<"\nVehicle added successfully"<<endl;
              }
              else if(a == 3)
              {
                  ccar++;
                  cout<<"\nVehicle added successfully"<<endl;
              }
          }

}

class parkinglot{
    int choice,j;
    char ans;
    vehicle temp;
    public:
    void func()
    {
        system ( "cls" ) ;
        do
  {
     system ( "cls" ) ;
     cout<<"********************************************************************"<<endl;
     cout<<"                 VEHICLE PARKING RESERVATION SYSTEM                 "<<endl;
     cout<<"1. Arrival of a vehicle"<<endl
         <<"2. Total number of vehicles parked"<<endl
         <<"3. Departure of vehicle"<<endl
         <<"4. Total Amount collected "<<endl
         <<"5. Display "<<endl
         <<"6. Search a Vehicle"<<endl
         <<"7. Exit"<<endl
         <<"********************************************************************"<<endl
         <<"Enter your Choice : ";
         cin>>choice;

         switch(choice)
         {
             case 1: system ( "cls" ) ;
                     cout<<"Add : "<<endl;
                     veh.at(vehicle::i).addVehicle();
                     break;

             case 2: system ( "cls" ) ;
                     vehicle::totalveh();
                     break;

             case 3: system ( "cls" ) ;
                     if(vehicle::i==0)
                        cout<<endl<<"No Vehicle in Parking..."<<endl;
                     else
                     {
                        vehicle v = vehicle::searc(0,veh);
                        if(v.gettype()==0)
                            cout<<"\nWrong Entry"<<endl;
                        else
                        {
                            cout<<"Departure : "<<endl;
                            vehicle::deleteVehicle(veh);
                        }
                     }
                        break;

             case 4: system ( "cls" ) ;
                     vehicle::totalamount();
                     break;

             case 5: system ( "cls" ) ;
                     vehicle::show(veh);
                     break;

             case 6: system("cls");
                     temp = vehicle::searc(1,veh);
                     break;

             case 7: exit(0);
         }

         cout<<"\nDo you want to continue, press y/n : "<<endl;
         cin>>ans;
         if(ans=='n')
         {
             break;
         }
         else
         {
             continue;
         }

  }while(1);

    }
};
void login(){                                                            //Login System

    char ch;
    int  attempt = 0;
    string pass  ="";
    parkinglot p;
    MyException z;

    cout <<"\n\n\n\n\n\n\n\t\t\t\t\tParking Reservation System Login";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tEnter Password: ";

    ch=_getch();

    while(ch != 13){                                                    //character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch=_getch();
    }

    if(pass == "pass"){
        cout << "\n\n\n\n\t\t\t\t\t  Access Granted! Welcome To Our System \n\n";
        system("PAUSE");
        p.func();
        return;
    }

    try{
        if(pass != "pass" && attempt<3){
                cout<<endl<<"\t\t\t\t\n";
            throw z;
            cout<<endl<<"SORRY!!! PASSWORD DOES NOT MATCH...."<<endl;
            attempt++;
        }
        else{
            cout << "\n\n\n\n\t\t\t\t\tAccess Aborted...Please Try Again!!\n";
            system("PAUSE");
            system("CLS");
            exit(0);
        }
    }catch(exception& e){
            cout<<e.what()<<"\n";
            system("pause");
            system("cls");
            login();
        }
}

  int main(void)
  {
    login();
  }


