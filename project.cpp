//*********************************************************************************************************
//*                        Rental Cab Scheduling System (GROUP - 9)                                      *
//*********************************************************************************************************

#include<bits/stdc++.h>
#include<conio.h>
#include<cctype>
#include<windows.h>
#include<math.h>
using namespace std;
void CheckBookingRecord();
ofstream MYFILE;
string NewWorkerName;
string NewWorkerPassword;
string AdminName="admin";
string AdminPassword="admin";
void BookingFromISMToBANKMORE();
void BookingFromISMToOZONEGALLERIA();
void BookingFromISMToSTATION();
void BookingFromBANKMOREToOZONEGALLERIA();
void BookingFromBANKMOREToSTATION();
void BookingFromBANKMOREToISM();
void BookingFromSTATIONToBANKMORE();
void BookingFromSTATIONToISM();
void BookingFromSTATIONToOZONEGALLERIA();
void BookingFromOZONEGALLERIAToBANKMORE();
void BookingFromOZONEGALLERIAToISM();
void BookingFromOZONEGALLERIAToSTATION();
void book();
void sharing();
static double time1=0;
struct cab{
	double engage;
	pair<double,double> destination;
	pair<double,double> mid;
	pair<double,double> current;

	double T;
	double start_time1;
};
vector<cab> scab(5);
#define  ff first
#define  ss second
void update();
void prdouble(double ch);
double share_ride(double x1,double y1,double x2 ,double y2);
double cur_ts,prev_ts=-1;
 const int Size=10;
string NumberOfCab[Size]={"","215","210","456","789","123"};
int CABPOS[Size][Size]={{100000,100000},{100,100},{10,13},{20,30},{40,50},{30,15}};
int CABSTATUS[Size]={1,1,1,1,1,1};
int ChargesPerKm=5;
int countiing=4;
int counti=0;
int *PChargesPerKm=&ChargesPerKm;
void update()
{
	cur_ts=time1;
	double i,j,t=cur_ts-prev_ts,x1,x2,y1,y2,x,y;

	//cout<<"t: "<<t<<endl;

	for(i=0;i<5;i++)
	{
		if(scab[i].engage)
		{
			x1=scab[i].current.ff;
			y1=scab[i].current.ss;

			x2=scab[i].destination.ff;
			y2=scab[i].destination.ss;

			double tot=sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
			//cout<<"tot:"<<i<<"  "<<tot<<"  \n";

			if(tot<t)
			{
				scab[i].engage=0;
				scab[i].current.ff=scab[i].destination.ff;
				scab[i].current.ss=scab[i].destination.ss;
			}
			else
			{

				//cout<<"hi\n";

				x=((tot-t)*x1+t*x2)/tot;
				y=((tot-t)*y1+t*y2)/tot;

				scab[i].current.ff=x;
				scab[i].current.ss=y;
			}
		}
	}
	//prev_ts=time1;
	/*for(i=0;i<5;i++)
	{
		cout<<setprecision(1)<<scab[i].current.ff;
		cout<<"  "<<setprecision(1)<<scab[i].current.ss<<endl;
	}
	*/
	cout<<endl<<endl;
}

void prdouble(double ch)
{
	if(ch==1)
	{
		cout<<"\nwe will first reach the previous passenger's destination ! !\n";
	}
	else
	{
		cout<<"\nwe will be reaching your destination first ! !\n";
	}
}
double share_ride(double x1,double y1,double x2 ,double y2)
{
	if(prev_ts!=-1)
	update();
	double c=INT_MAX,d,var=-1;
	double second_time1=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	for(double i=0;i<5;i++)
	{
		if(scab[i].engage==0)
		{
			double x=scab[i].current.first;
			double y=scab[i].current.second;
			double z= (x1-x)*(x1-x)+(y1-y)*(y1-y);
			if(z<c)
			{
				c=z;
				d=i;
			}
		}
		else if(scab[i].engage==1)
		{
			double x=scab[i].current.first;
			double y=scab[i].current.second;
			double d1x=scab[i].destination.first;
			double d1y=scab[i].destination.second;
			double s1s2= sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
			double s2d1= sqrt((x1-d1x)*(x1-d1x)+(y1-d1y)*(y1-d1y));
			double d1d2= sqrt((x2-d1x)*(x2-d1x)+(y2-d1y)*(y2-d1y));
			double s2d2= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
			if(s2d1+d1d2<=s2d2+d1d2)
			{
				double T=scab[i].T;
				double a=time1-scab[i].start_time1;
			 	if(a+s1s2+s2d1>2*T)
			 	continue;
			 	if(s2d1+d1d2>2*second_time1)
			 	continue;
			 	else
			 	{
			 	 double z=s2d1+d1d2+s1s2;
				  if(z<c)
				  {
				  	c=z;
				  	d=i;
				  	var=2;
				  }
				}

			}
			else
			{
				double T=scab[i].T;
				double a=time1-scab[i].start_time1;
			 	if(a+s1s2+s2d2+d1d2>2*T)
			 	continue;
			 	else
			 	{
			 	 double z=s2d2+s1s2;
				  if(z<c)
				  {
				  	c=z;
				  	d=i;
				  	var=1;
				  }
				}
			}

		}

	}
	if(c==INT_MAX)
	return -1;

	if(scab[d].engage==1)
	{
		if(var==2)
		{
			scab[d].destination.first=x2;
			scab[d].destination.second=y2;

		}
	}
	else
	{
		scab[d].T=second_time1;

		scab[d].current.first=x1;
		scab[d].current.ss=y1;

		scab[d].destination.first=x2;
		scab[d].destination.second=y2;
		scab[d].start_time1=time1;

	}


	scab[d].engage++;

	cout<<"\nCongratulations, a cab has been allotted to u and will arrive to you soon !!\n"<<"Alloted cab ID is "<<d+1<<endl;

	if(scab[d].engage==1)
	cout<<"\nThe alloted  cab is not being shared till now\n----Happy Journey----\n\n";
	else
	cout<<"\nThe alloted cab is being shared by one athoer passenger\nPlease be cooperative\n----Happy Journey----\n\n";
	prev_ts=time1;
	return d;




}
bool wrong = false;
int main()
{
//************************************************************************************
//*                             DiSpLaYiNg WeLcOmE ScReEn                                                 *
//************************************************************************************
      int counti=0;
      system("color 1E");
   cout<<endl;
   cout<<"\t******************************\n";
   cout<<"\t*         Wel Come           *\n";
      cout<<"\t*            To              *\n";
      cout<<"\t*    Cab Booking System      *\n";
      cout<<"\t******************************\n";
   cout<<endl;
   cout<<endl;
   cout<<endl;
   cout<<"\tLoAdInG ";
   Sleep(100);
   cout<<"<";
   Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"<";
      Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"<";
   Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"<";
      Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"<";
      Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"<";
      Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"<";
      Sleep(100);
   cout<<">";
   Sleep(100);
   cout<<"\n\n\t SuCcEsSFuL\n";

   Sleep(2000);
   system("CLS");

//*********************************************************************************************************
//*                                      LoGiN MeNu                                                       *
//*********************************************************************************************************



 char Wish;
 string Choice;
do{

    system("CLS");
 cout<<"\t********************"<<endl;
 cout<<"\t*CaB Booking SySteM*"<<endl;
 cout<<"\t********************"<<endl;
 cout<<endl;

 cout<<"*************************"<<endl;
 cout<<"*<1>  For Login Admin   *"<<endl;
 cout<<"*************************"<<endl;
 cout<<endl;
 cout<<"**************************"<<endl;
 cout<<"*<2> For Login Customer  *"<<endl;
 cout<<"**************************"<<endl;
 cout<<endl;
 cout<<"******************"<<endl;
 cout<<"*<3> For Exit    *"<<endl;
 cout<<"******************"<<endl;
 cout<<endl;
 cout<<"SElEct: ";
 cin>>Choice;

    int choice = atoi( Choice.c_str() );
 switch(choice)
 {
  case 1:
             {
            string UserName;
                  string Password;
                  bool LoginSuccess= false;

                  do
      {
//************************************************************************************
//*                           Admin Login                                            *
//************************************************************************************
     system("CLS");
     cout<<"\t********************"<<endl;
                 cout<<"\t*  AdMiN LoGiN     *"<<endl;
                 cout<<"\t********************"<<endl;
     cout<<endl;
     Sleep(500);
     cout<<"Hint:- admin\n";
     cout<<"\nUserName: ";
     cin>>UserName;
     cout<<"Password: ";
     cin>>Password;

     if(UserName== AdminName && Password == AdminPassword)
     {
      cout<<"LOgin Successful \n";
      LoginSuccess= true;
      Sleep(2000);
      system("CLS");
      char Wish;
      do
      {
                             system("CLS");
        string Choice;
        cout<<"\t********************"<<endl;
                             cout<<"\t* AdMiNiStRaTiOn   *"<<endl;
                             cout<<"\t********************"<<endl;
                             cout<<endl;
        cout<<"<1> Customer Record"<<endl;
                             cout<<endl;
        cout<<"<2> Cab Driver Record"<<endl;
                             cout<<endl;
        cout<<"<3> Cab Status"<<endl;
                             cout<<endl;
        cout<<"<4> Canceled Booking Record"<<endl;
                             cout<<endl;
        cout<<"<5> Change The Rate Of Per Km Charges"<<endl;
                             cout<<endl;
        cout<<"<6> New Customer Account"<<endl;
        cout<<endl;
        cout<<"<7> To Log Out"<<endl<<endl;
         cout<<"<8> Update Cab Status    "<<endl;
         cout<<endl;
        cout<<"Select :";
                             cin>>Choice;
        int choice = atoi( Choice.c_str() );
                             switch(choice)
                    {case 8:
                           {

                                system("CLS");
                                string UpdatingStatus;
        char Wish;
        do{
                                cout<<"\t********************"<<endl;
                             cout<<"\t* Updating Status  *"<<endl;
                             cout<<"\t********************"<<endl;
                             cout<<endl;
                             cout<<"Enter The Cab Id Number To UPdate status: ";
        cin>>UpdatingStatus;
           long int choice = atoi( UpdatingStatus.c_str() );
                             switch(choice)
        {

        case 215:
         {
          char Statuss;
          cout<<"The Cab Id Number 215 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[1]=0;
          }
          else
          {
           CABSTATUS[1]=1;
          }
          break;
         }
         case 210:
         {
          char Statuss;
          cout<<"The Cab Id Number 210 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[2]=0;
          }
          else
          {
           CABSTATUS[2]=1;
          }
          break;
         }
         case 456:
         {
          char Statuss;
          cout<<"The Cab Id Number 456 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[3]=0;
          }
          else
          {
           CABSTATUS[3]=1;
          }
          break;
         }
         case 789:
         {
          char Statuss;
          cout<<"The Cab Id Number 789 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[4]=0;
          }
          else
          {
           CABSTATUS[4]=1;
          }
          break;
         }
         case 123:
         {
          char Statuss;
          cout<<"The Cab Id Number 123 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[5]=0;
          }
          else
          {
           CABSTATUS[5]=1;
          }
          break;
         }

         default:
          {
           cout<<"You Enter Wrong Choice."<<endl;
          }
        }
        cout<<"Do You Want To update The Another CAb Status(Y/N): ";
        cin>>Wish;
        }while(Wish=='Y' || Wish=='y');
        break;
                           }//end of case 2


                                 case 1:
                                 {
           CheckBookingRecord();
                                       break;
                                 }//end of case 1

                                 case 2:
                                 {
                                      system("CLS");
                                      ifstream InFile;
                                      char ch;
                                      InFile.open("Registration.txt");
                                      while (!InFile.eof())
                                      {
                                         InFile.get ( ch ) ;
                                         cout << ch ;
                                      }
                                      InFile.close();
                                      cout<<endl;
                                      break;
                                 }
                                 case 3:
                                 {

                                    system("CLS");
         int size=6;
         cout<<"CAB STATUS\n";
         for(int i=1;i<size;i++)
         {
                                         if(CABSTATUS[i] ==1)
                                         {
                                              cout<<"Cab "<<NumberOfCab[i]<<" IS FREE\n";
                                         }
                                         else
                                         {
                                             cout<<"Cab "<<NumberOfCab[i]<<" IS NOT FREE\n";
                                         }

         }
                                    break;
                                 }
         case 4:
                                 {
                                      system("CLS");
                                      ifstream InFile;
                                      char ch;//initiailzing
                                      InFile.open("CancelBooking.txt");
                                      while (!InFile.eof())
                                      {
                                         InFile.get ( ch ) ;
                                         cout << ch ;
                                      }
                                      InFile.close();
                                      cout<<endl;
                                      break;
                                 }//end of case 4
                                 case 5:
                                      {
               char Wish;
            do{
             //Increment  and decrement On rate
                                             system("CLS");
            cout<<"\t********************"<<endl;
            cout<<"\t*     WeL CoME     *"<<endl;
            cout<<"\t********************"<<endl;
            cout<<endl;
            int Charges;
                                             cout<<"Enter The Amount That You Want To Increment or Decrement On Km Per Charges :";
                                             do
            {
             cin>>Charges;
             wrong = cin.fail();//if type is opposite
             if(wrong)
              cout<<"Error Wrong Input\nEnter again"<<endl;
             cin.clear();
             cin.ignore(200, '\n');//ignore upto 200 characters
            }while(wrong);

            *PChargesPerKm+=Charges;
            cout<<"\nThe Changes Has Been Done SuccessFully"<<endl;
           cout<<"Do you Want TO Change The Rate Again(Y/N):  ";
           cin>>Wish;
           }while(Wish=='Y' || Wish=='y');
            break;
                                      }//end of case 4
                                 case 6:
          {
           system("CLS");
           cout<<"\t WELCOME"<<endl;
           cout<<endl;
           cout<<"Enter The New Customer User Name: ";
           cin>>NewWorkerName;
           cout<<endl;
           cout<<"Enter New Customer Password: ";
           cin>>NewWorkerPassword;
           cout<<endl;
           cout<<"The Account Has Been Made Successfully\n";
           cout<<endl;
           cout<<"\tThank YOu"<<endl;

           break;
          }
         case 7:
                                 {
          system("CLS");
                                       cout<<"\tFor Logout\n";
            break;
                                 }//end of case 5

                                 default:
                                 {
                                 cout<<"You Enter Wrong Choice"<<endl;
                                 break;
                                 }
                    }//end of switch
     if(choice==7)
     {
      break;
     }
                      cout<<"Press any key to continue...... ";
       Wish=getch();
                      }while(Wish);
                  }
                  else
                  {
                       cout<<"Incorrect User Name And Password\n"
                           <<"Please Try Again";
        Sleep(1000);
                  }
               }while(!LoginSuccess);
               break;
             }//end of case 1

             case 2:
                  {
                       string UserName="";
                       string Password="";
                       bool LoginSuccess= false;
                       do{
                       system("CLS");
        cout<<"\t********************"<<endl;
                    cout<<"\t*  CuStOmEr LoGiN     *"<<endl;
                    cout<<"\t********************"<<endl;
        cout<<"\nHint:- customer\n";
        cout<<"UserName: ";
                       cin>>UserName;
                       cout<<"Password: ";
                       cin>>Password;

                       if(UserName== "customer" && Password == "customer" || UserName== NewWorkerName && Password == NewWorkerPassword )
                       {
                            cout<<"LOgin Successful \n";
                            LoginSuccess= true;
       Sleep(2000);

                            system("CLS");

//*********************************************************************************************************
//*                             DiSpLaYiNg MeNu On The ScReEn                                             *
//*********************************************************************************************************

 char Wish;
 string Choice;
    do{
           x:
    system("CLS");
 cout<<"\t********************"<<endl;
 cout<<"\t*    Customer        *"<<endl;
 cout<<"\t********************"<<endl;
 cout<<endl;
 cout<<endl;
    cout<<"<1>Private Booking"<<endl;
 cout<<endl;
 cout<<"<2> Cab Status    "<<endl;
 cout<<endl;
 /*cout<<"<3> Customer Record    "<<endl;
 cout<<endl;*/
 cout<<"<3> Update Cab Status    "<<endl;
 cout<<endl;
 cout<<"<4> To Sign Up        "<<endl;
    cout<<endl;
cout<<"<5> To LogOut         "<<endl;
    cout<<endl;
cout<<"<6>Shared Booking"<<endl;
 cout<<endl;
 cout<<"Select :";
 cin>>Choice;
 time1++;
    int choice = atoi( Choice.c_str() );
    switch(choice)
 {   case 6:
           {

system("CLS");

        cout<<"\n\n\n\n\n Press 2 to continue or 1 to exit :  ";
		double ch;
		cin>>ch;
		if(ch==1)
		goto x;
		cout<<"\n\n\n\n Enter the coordinates of source : ";
		double x1,x2,y1,y2;
		cin>>x1>>y1;

		cout<<"\n\n Enter the coordinates of destination : ";

		cin>>x2>>y2;
		double z=share_ride(x1,y1,x2,y2);
		if(z==-1)
		{
			cout<<"\n\n\nNO Cab allocated due to unavailability\n";
		}
		//else
		//cout<<"ID of Cab allocated: "<<z<<endl;
double op=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		cout<<"\nEstimated Time req: "<<op<<"min to "<<2*op<<"min"<<endl;
		cout<<"\n Estimated fare : Rs."<<(int)((ChargesPerKm-2)*op);
		getch();

  break;

           }


     case 4:
          {
           system("CLS");
           cout<<"\t WELCOME"<<endl;
           cout<<endl;
           cout<<"Enter The New Customer User Name: ";
           cin>>NewWorkerName;
           cout<<endl;
           cout<<"Enter New Customer Password: ";
           cin>>NewWorkerPassword;
           cout<<endl;
           cout<<"The Account Has Been Made Successfully\n";
           cout<<endl;
           cout<<"\tThank YOu"<<endl;

           break;
          }
                  case 1:
                       {

                  //*************************************************************************
                  //*                       Booking                                         *
                  //*************************************************************************

         do{

       system("CLS");
                  char Wish;
                  string Choice;
               cout<<"\t********************"<<endl;
               cout<<"\t*    Booking        *"<<endl;
               cout<<"\t********************"<<endl;
               cout<<endl;
                  cout<<endl;
                  cout<<"<1> To Book Cab From ISM To Bank More"<<endl;
               cout<<endl;
               cout<<"<2> To Book Cab From ISM To OZONE GALLERIA"<<endl;
               cout<<endl;
               cout<<"<3> To Book Cab From ISM To STATION"<<endl;
               cout<<endl;
               cout<<"<4> To Book Cab From Bank More To OZONE GALLERIA"<<endl;
               cout<<endl;
                cout<<"<5> To Book Cab From Bank More To STATION"<<endl;
               cout<<endl;
                cout<<"<6> To Book Cab From Bank More To ISM"<<endl;
               cout<<endl;
                cout<<"<7> To Book Cab From STATION To OZONE GALLERIA"<<endl;
               cout<<endl;
               cout<<"<8> To Book Cab From STATION To ISM"<<endl;
               cout<<endl;
               cout<<"<9> To Book Cab From STATION To Bank More "<<endl;
               cout<<endl;
               cout<<"<10> To Book Cab From OZONE GALLERIA To Bank More "<<endl;
               cout<<endl;
               cout<<"<11> To Book Cab From OZONE GALLERIA To ISM "<<endl;
               cout<<endl;
               cout<<"<12> To Book Cab From OZONE GALLERIA To Station "<<endl;
               cout<<endl;
               cout<<"<13> To Book Cab By entering coordinates "<<endl;
               cout<<endl;
               cout<<"<14> To Go Back to Previous Menu"<<endl;
               cout<<endl;
                  cout<<"Select :";
               cin>>Choice;
               cout<<"\n Press L for Ride Later or any key for Ride Now...";
       char huj;
       cin>>huj;
       if(huj=='L' || huj=='l')
       {
           string gh;
           cout<<"\n Enter the arrival time (hh:mm format): ";
           cin>>gh;
       }
                  int choice = atoi( Choice.c_str() );
                  switch(choice)
               {
       counti++;
                        case 1:
                             {
                                   BookingFromISMToBANKMORE();
                 break;
                             }
                        case 2:
                             {
                                    BookingFromISMToOZONEGALLERIA();
            break;
                             }
                        case 3:
                             {
                                      BookingFromISMToSTATION();

                                    break;
                             }
                        case 4:
       {
       BookingFromBANKMOREToOZONEGALLERIA();
         break;
                            }
                             case 5:
       {
         BookingFromBANKMOREToSTATION();
         break;
                            }
                             case 6:
       {
         BookingFromBANKMOREToISM();
         break;
                            }
                             case 7:
       {
         BookingFromSTATIONToOZONEGALLERIA();
         break;
                            }
                             case 8:
       {
         BookingFromSTATIONToISM();
         break;
                            }
                             case 9:
       {
         BookingFromSTATIONToBANKMORE();
         break;
                            }
                             case 10:
       {
         BookingFromOZONEGALLERIAToBANKMORE();
         break;
                            }
                             case 11:
       {
         BookingFromOZONEGALLERIAToISM();
         break;
                            }
                             case 12:
       {
         BookingFromOZONEGALLERIAToSTATION();
         break;
                            }
                             case 13:
       {
         book();
         break;
                            }
                       case 14:
                            {
                                goto x;
                            }
                            default:
                                    {
                                          cout<<"You Entered Wrong Choice\n";
                                    }
                          }
       cout<<"Do you want to continue...... ";
       Wish=getch();
         }while(Wish);

                          break;
                      }
                      case 3:
                           {

                                system("CLS");
                                string UpdatingStatus;
        char Wish;
        do{
                                cout<<"\t********************"<<endl;
                             cout<<"\t* Updating Status  *"<<endl;
                             cout<<"\t********************"<<endl;
                             cout<<endl;
                             cout<<"Enter The Cab Id Number To UPdate status: ";
        cin>>UpdatingStatus;
           long int choice = atoi( UpdatingStatus.c_str() );
                             switch(choice)
        {

        case 215:
         {
          char Statuss;
          cout<<"The Cab Id Number 215 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[1]=0;
          }
          else
          {
           CABSTATUS[1]=1;
          }
          break;
         }
         case 210:
         {
          char Statuss;
          cout<<"The Cab Id Number 210 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[2]=0;
          }
          else
          {
           CABSTATUS[2]=1;
          }
          break;
         }
         case 456:
         {
          char Statuss;
          cout<<"The Cab Id Number 456 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[3]=0;
          }
          else
          {
           CABSTATUS[3]=1;
          }
          break;
         }
         case 789:
         {
          char Statuss;
          cout<<"The Cab Id Number 789 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[4]=0;
          }
          else
          {
           CABSTATUS[4]=1;
          }
          break;
         }
         case 123:
         {
          char Statuss;
          cout<<"The Cab Id Number 123 Returned Or Not(Y/N) :";
          cin>>Statuss;
          if(toupper(Statuss=='N'))
          {
           CABSTATUS[5]=0;
          }
          else
          {
           CABSTATUS[5]=1;
          }
          break;
         }

         default:
          {
           cout<<"You Enter Wrong Choice."<<endl;
          }
        }
        cout<<"Do You Want To update Another CAb Status(Y/N): ";
        cin>>Wish;
        }while(Wish=='Y' || Wish=='y');
        break;
                           }//end of case 2

                    /* case 3:
                                 {
          CheckBookingRecord();
                                       break;
                                 }//end of case 3*/
                     case 2:
                          {
                                 system("CLS");
         int size=6;
         cout<<"CAB STATUS\n";
                                 for(int i=1;i<size;i++)
                                 {
                                         if(CABSTATUS[i] ==1)
                                         {
                                              cout<<"Cab "<<NumberOfCab[i]<<" IS FREE\n";
                                         }
                                         else
                                         {
                                             cout<<"Cab "<<NumberOfCab[i]<<" IS NOT FREE\n";
                                         }

                                 }

            break;

                          }
                     case 5:
                         {
                             system("CLS");
                             cout<<"\tFor Logout\n";
                              break;
                         }
      default:
       {
        cout<<"You Enter Wrong Choice\n";
        break;
       }
    }//end of switch
                 if(choice==5)
     {
      break;
     }
 cout<<"Press any key to continue...... ";
    Wish=getch();
    }while(Wish);
                       }
                       else
                       {
                            cout<<"Incorrect User Name Or Password\n"
                                <<"Please Try Again";
       Sleep(2000);

                       }
                       }while(!LoginSuccess);
                       break;
                  }//end of case 2

            case 3:
                 {
                          system("CLS");
                          ifstream InFile;
                 char ch;
                 exit(0);
                 InFile.open("Exit.txt");
                 while (!InFile.eof())
                 {
                   InFile.get ( ch ) ;
                    cout << ch ;
                    }
                    InFile.close();
                 cout<<endl;
                 Sleep(2000);

                 break;
                 }//end of case 3

            default:
                    {
                        cout<<"You Entered Wrong Choice"<<endl;
      break;
                    }//end of default
    }//end of Switch

    cout<<"Press any key to continue...... ";
    Wish=getch();
    }while(Wish);


 return 0;

}
void BookingFromISMToBANKMORE()
{
  if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Booked..."<<endl;
   cout<<"No available cabs nearby.We Can Not Book Cab for You"<<endl;

  }
  else
  {
    int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-0)*(CABPOS[i][0]-0)+(CABPOS[i][1]-0)*(CABPOS[i][1]-0));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=12;
    CABPOS[counti][1]=14;
    system("CLS");
    ofstream MyFile;
    float Distance=40;
 float Charges;
 ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Guide Lines while entering details: |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"You Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : ISM";
 cout <<"\nDrop : BANKMORE";
 cout <<"\nDistance: 40Km";
 cout <<"\nCharges: Rs"<< Charges;
 cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";

 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
                    cout<<"Cab id Num "<<NumberOfCab[counti]<<" is Booked For You\n";
        cout<<"Your Booking Has Been Done\n";
     MyFile <<"\n\t\tCustomer Record\n";
     MyFile << "\nName : "<< Name;
     MyFile <<"\nPick : ISM";
     MyFile <<"\nDrop:BANKMORE";
     MyFile <<"\nDistance: 40Km";
     MyFile <<"\nCharges: Rs"<< Charges;
     MyFile.close();
     CABSTATUS[counti]=0;
     Sleep(1000);


 }
 else if(PaidCharges =='y')
 {
                                             cout<<NumberOfCab[counti]<<" is Booked For You\n";


   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : ISM";
   MyFile <<"\nDrop:BANKMORE";
   MyFile <<"\nDistance: 40Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : ISM";
  MYFile <<"\nDrop: BANK MORE";
  MYFile <<"\nDistance: 40Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  MYFile.close();
  counti--;
 }
 MYFILE.close();
 Sleep(2000);
}
  }


void BookingFromISMToOZONEGALLERIA()
{
 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Booked"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
  int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-0)*(CABPOS[i][0]-0)+(CABPOS[i][1]-0)*(CABPOS[i][1]-0));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=20;
    CABPOS[counti][1]=40;

     system("CLS");
 ofstream MyFile;
 ofstream MYFile;
    float Distance=50;
 float Charges;
    string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
 cout<<"--------------------------------------"<<endl;
 cout<<"|Instructions while entering details: |"<<endl;
 cout<<"--------------------------------------"<<endl;
 cout<<endl;
 cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
 cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
 cout<<"Will Not Go Further.\n";
 cout << "What is your Name : ";
 getline(cin,Name,'.');
 Charges=ChargesPerKm*Distance;
 cout <<"\nPick : ISM";
 cout <<"\nDrop : OZONE GALLERIA";
 cout <<"\nDistance: 50Km";
 cout <<"\nCharges: Rs"<< Charges;
 cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 cout<<endl;
 char PaidCharges;
 cout<<"Did You Pay The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
                                             cout<<NumberOfCab[counti]<<" is Booked For You";


   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : ISM";
   MyFile <<"\nDrop:OZONEGALLERIA";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {
                                             cout<<NumberOfCab[counti]<<" is Booked For You";


   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : ISM";
   MyFile <<"\nDrop:OZONEGALLERIA";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);



 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : ISM";
  MYFile <<"\nDrop:OZONEGALLERIA";
  MYFile <<"\nDistance: 50Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }

}
void BookingFromBANKMOREToOZONEGALLERIA()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
  int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-12)*(CABPOS[i][0]-12)+(CABPOS[i][1]-14)*(CABPOS[i][1]-14));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=20;
    CABPOS[counti][1]=40;

 system("CLS");
 ofstream MyFile;
 float Distance=45;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : BANK MORE";
 cout <<"\nDrop : OZONE GALLERIA";
 cout <<"\nDistance: 45Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : BANK MORE";
   MyFile <<"\nDrop : OZONE GALLERIA";
   MyFile <<"\nDistance: 45Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : BANK MORE";
   MyFile <<"\nDrop : OZONE GALLERIA";
   MyFile <<"\nDistance: 45Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : BANK MORE";
  MYFile <<"\nDrop : OZONE GALLERIA";
  MYFile <<"\nDistance: 45Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromISMToSTATION()
{
 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {  int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-0)*(CABPOS[i][0]-0)+(CABPOS[i][1]-0)*(CABPOS[i][1]-0));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=50;
    CABPOS[counti][1]=80;

 system("CLS");
 ofstream MYFile;
 ofstream MyFile;
 float Distance=35;
    float Charges;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
    MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
 Charges=ChargesPerKm*Distance;
    cout <<"\nPick : ISM";
    cout <<"\nDrop:STATION";
 cout <<"\nDistance: 35Km";
 cout <<"\nCharges: Rs"<< Charges;
 cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";


   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : ISM";
   MyFile <<"\nDrop:STATION";
   MyFile <<"\nDistance: 35Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);



 }
 else if(PaidCharges =='y')
 {
                                             cout<<NumberOfCab[counti]<<" is Booked For You";


   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : ISM";
   MyFile <<"\nDrop:STATION";
   MyFile <<"\nDistance: 35Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : ISM";
  MYFile <<"\nDrop:STATION";
  MYFile <<"\nDistance: 35Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  MYFile.close();
  counti--;

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromBANKMOREToSTATION()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
 int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-12)*(CABPOS[i][0]-12)+(CABPOS[i][1]-14)*(CABPOS[i][1]-14));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=50;
    CABPOS[counti][1]=80;

 system("CLS");
 ofstream MyFile;
 float Distance=50;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : BANK MORE";
 cout <<"\nDrop : STATION";
 cout <<"\nDistance: 50Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : BANK MORE";
   MyFile <<"\nDrop : STATION";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : BANK MORE";
   MyFile <<"\nDrop : STATION";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : BANK MORE";
  MYFile <<"\nDrop : STATION";
  MYFile <<"\nDistance: 50Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromBANKMOREToISM()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
 int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-12)*(CABPOS[i][0]-12)+(CABPOS[i][1]-14)*(CABPOS[i][1]-14));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=0;
    CABPOS[counti][1]=0;

 system("CLS");
 ofstream MyFile;
 float Distance=40;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : BANK MORE";
 cout <<"\nDrop : ISM";
 cout <<"\nDistance: 40Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : BANK MORE";
   MyFile <<"\nDrop : ISM";
   MyFile <<"\nDistance: 40Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : BANK MORE";
   MyFile <<"\nDrop : ISM";
   MyFile <<"\nDistance: 40Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : BANK MORE";
  MYFile <<"\nDrop : ISM";
  MYFile <<"\nDistance: 40Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromSTATIONToOZONEGALLERIA()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
   int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-50)*(CABPOS[i][0]-50)+(CABPOS[i][1]-80)*(CABPOS[i][1]-80));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=20;
    CABPOS[counti][1]=40;
 system("CLS");
 ofstream MyFile;
 float Distance=60;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : STATION";
 cout <<"\nDrop : OZONE GALLERIA";
 cout <<"\nDistance: 60Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : STATION";
   MyFile <<"\nDrop : OZONE GALLERIA";
   MyFile <<"\nDistance: 60Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : STATION";
   MyFile <<"\nDrop : OZONE GALLERIA";
   MyFile <<"\nDistance: 60Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Canceled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : STATION";
  MYFile <<"\nDrop : OZONE GALLERIA";
  MYFile <<"\nDistance: 60Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromSTATIONToISM()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
   int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-50)*(CABPOS[i][0]-50)+(CABPOS[i][1]-80)*(CABPOS[i][1]-80));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=0;
    CABPOS[counti][1]=0;
 system("CLS");
 ofstream MyFile;
 float Distance=35;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : STATION";
 cout <<"\nDrop : ISM";
 cout <<"\nDistance: 35Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : STATION";
   MyFile <<"\nDrop : ISM";
   MyFile <<"\nDistance: 35Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : STATION";
   MyFile <<"\nDrop : ISM";
   MyFile <<"\nDistance: 35Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Cancelled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : STATION";
  MYFile <<"\nDrop : ISM";
  MYFile <<"\nDistance: 35Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromSTATIONToBANKMORE()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
   int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-50)*(CABPOS[i][0]-50)+(CABPOS[i][1]-80)*(CABPOS[i][1]-80));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=12;
    CABPOS[counti][1]=14;
 system("CLS");
 ofstream MyFile;
 float Distance=50;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : STATION";
 cout <<"\nDrop : BANK MORE";
 cout <<"\nDistance: 50Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : STATION";
   MyFile <<"\nDrop : BANK MORE";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : STATION";
   MyFile <<"\nDrop : BANK MORE";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Cancelled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : STATION";
  MYFile <<"\nDrop : BANK MORE";
  MYFile <<"\nDistance: 50Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromOZONEGALLERIAToBANKMORE()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
   int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-20)*(CABPOS[i][0]-20)+(CABPOS[i][1]-40)*(CABPOS[i][1]-40));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=12;
    CABPOS[counti][1]=14;
 system("CLS");
 ofstream MyFile;
 float Distance=45;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : OZONE GALLERIA";
 cout <<"\nDrop : BANK MORE";
 cout <<"\nDistance: 45Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : OZONE GALLERIA";
   MyFile <<"\nDrop : BANK MORE";
   MyFile <<"\nDistance: 45Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : OZONE GALLERIA";
   MyFile <<"\nDrop : BANK MORE";
   MyFile <<"\nDistance: 45Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Cancelled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : OZONE GALLERIA";
  MYFile <<"\nDrop : BANK MORE";
  MYFile <<"\nDistance: 45Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromOZONEGALLERIAToISM()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
   int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-20)*(CABPOS[i][0]-20)+(CABPOS[i][1]-40)*(CABPOS[i][1]-40));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=0;
    CABPOS[counti][1]=0;
 system("CLS");
 ofstream MyFile;
 float Distance=50;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : OZONE GALLERIA";
 cout <<"\nDrop : ISM";
 cout <<"\nDistance: 50Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : OZONE GALLERIA";
   MyFile <<"\nDrop : ISM";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : OZONE GALLERIA";
   MyFile <<"\nDrop : ISM";
   MyFile <<"\nDistance: 50Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Cancelled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : OZONE GALLERIA";
  MYFile <<"\nDrop : ISM";
  MYFile <<"\nDistance: 50Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void BookingFromOZONEGALLERIAToSTATION()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
   int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-20)*(CABPOS[i][0]-20)+(CABPOS[i][1]-40)*(CABPOS[i][1]-40));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=50;
    CABPOS[counti][1]=80;
 system("CLS");
 ofstream MyFile;
 float Distance=60;
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : OZONE GALLERIA";
 cout <<"\nDrop : STATION";
 cout <<"\nDistance: 60Km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : OZONE GALLERIA";
   MyFile <<"\nDrop : STATION";
   MyFile <<"\nDistance: 60Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";

   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : OZONE GALLERIA";
   MyFile <<"\nDrop : STATION";
   MyFile <<"\nDistance: 60Km";
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Cancelled\n";
  MYFile << "\nName : "<< Name;
  MYFile <<"\nPick : OZONE GALLERIA";
  MYFile <<"\nDrop : STATION";
  MYFile <<"\nDistance: 60Km";
  MYFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}

void book()
{

 if(CABSTATUS[1]==0 && CABSTATUS[2]==0 && CABSTATUS[3]==0 && CABSTATUS[4]==0 && CABSTATUS[5]==0 )
  {
   cout<<"All The cabs Are Book"<<endl;
   cout<<"We Can Not Book Cab for You"<<endl;

  }
 else
 {
 int x,y;
 cout<<"\n Enter the coordinates of source : ";
 cin>>x>>y;
 int m,n;
 cout<<"\n Enter the coordinates of destination : ";
 cin>>m>>n;
 int min=1000;
    int dis;
   for(int i=1;i<6;i++)
   {
    if(CABSTATUS[i]==1)
    {
     dis=sqrt((CABPOS[i][0]-x)*(CABPOS[i][0]-x)+(CABPOS[i][1]-y)*(CABPOS[i][1]-y));
     if(dis<min)
     {
         min=dis;
       counti=i;}

    }

   }
    CABPOS[counti][0]=m;
    CABPOS[counti][1]=n;
 system("CLS");
 ofstream MyFile;

 float Distance;
 Distance= sqrt(((m-x)*(m-x)) + ((n-y) * (n-y)));
    float Charges;
    ofstream MYFile;
 string Name;
 ofstream MYFILE;
      MYFILE.open("CabStatus.txt",ios::app);
 MyFile.open("Customer Record.txt",ios::app);
 MYFile.open("CancelBooking.txt",ios::app);
 cout << "\t\tBooking\n";
    cout<<"--------------------------------------"<<endl;
    cout<<"|Instructions while filling the form :  |"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
    cout<<"After Entering Your Name Put FullStop After Ending The Name.\n";
    cout<<"Your Must Put Fullstop at The End If You Didn't So Program \n";
    cout<<"Will Not Go Further.\n";
    cout << "What is your Name : ";
    getline(cin,Name,'.');
    Charges=ChargesPerKm*Distance;
    cout <<"\nPick : x coordinate is " << x <<" and y coordinate is "<<y;
 cout <<"\nDrop : x coordinate is " << m <<" and y coordinate is "<<n;
 cout <<"\nDistance: "<<Distance<<"km";
    cout <<"\nCharges: Rs"<< Charges;
    cout <<"\nEstimated Arrival Time if Ride Now is your option : "<<min<<"min"<<"\n";
 char PaidCharges;
 cout<<"Did You PAy The Charges(Y/N) :- ";
 PaidCharges=getch();
 if(PaidCharges =='Y')
 {
            cout<<NumberOfCab[counti]<<" is Booked For You";
   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : x coordinate is " << x <<" and y coordinate is "<<y;
   MyFile <<"\nDrop :  coordinate is " << m <<" and y coordinate is "<<n;
   MyFile <<"\nDistance:"<<Distance<<"km";;
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else if(PaidCharges =='y')
 {

                                             cout<<NumberOfCab[counti]<<" is Booked For You";

   cout<<"Your Booking Has Been Done\n";
   MyFile <<"\n\t\tCustomer Record\n";
   MyFile << "\nName : "<< Name;
   MyFile <<"\nPick : x coordinate is " << x <<" and y coordinate is "<<y;
   MyFile <<"\nDrop :  coordinate is " << m <<" and y coordinate is "<<n;
   MyFile <<"\nDistance:"<<Distance<<"km";;
   MyFile <<"\nCharges: Rs"<< Charges;
   MyFile.close();
   CABSTATUS[counti]=0;
   Sleep(1000);


 }
 else
 {
  cout<<"Booking Has Been Canceled Due to Unpaid Charge. \n";
  MYFile <<"\n\t\tBooking Cancelled\n";
  MYFile << "\nName : "<< Name;
  MyFile <<"\nPick : x coordinate is " << x <<" and y coordinate is "<<y;
   MyFile <<"\nDrop :  coordinate is " << m <<" and y coordinate is "<<n;
   MyFile <<"\nDistance:"<<Distance<<"km";;
   MyFile <<"\nCharges: Rs"<< Charges;
  counti--;
  MYFile.close();

 }
 MYFILE.close();
 Sleep(2000);
 }
}



void CheckBookingRecord()
{
 system("CLS");
                                       ifstream InFile;
                                       char ch;
                                       InFile.open("Customer Record.txt");
                                       while (!InFile.eof())
                                       {
                                               InFile.get ( ch ) ;
                                               cout << ch ;
                                 }
                                       InFile.close();
                                       cout<<endl;
}
