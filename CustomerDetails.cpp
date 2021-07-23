#include "CustomerDetails.h"
#include<iostream>
#include<string>
#include<mysql.h>
#include<stdc-predef.h>
#include<cstring>
#include<regex>

#define SERVER "127.0.0.1"
#define USER "root"
#define PASSWORD "Qwerty123456@"
#define DATABASE2 "USER"

using namespace std;

CustomerDetails::CustomerDetails()
{
}

CustomerDetails::~CustomerDetails()
{
}

void CustomerDetails::addCustomer(){
    string customer_name, customer_address, shop_name, license_number, phone_number, query_text, total_amount, amount_in_debt;
    MYSQL *connect;
    int counter=0;
    connect=mysql_init(NULL);
    if(!connect)
    {
        cout<<"MySQL initialization failed in class User :- addUser()"<<endl;
    }
    else
    {
        connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE2,3306,NULL,0);
        if(connect)
        {
            //getchar();
            cout<<"Customer Name : ";
            getline(cin,customer_name);
            customer_name=changeCase(customer_name);
            cout<<"Address : ";
            getline(cin,customer_address);
            customer_address=changeCase(customer_address);
            cout<<"Shop Name : ";
            getline(cin,shop_name);
            shop_name=changeCase(shop_name);
            cout<<"License Number : ";
            getline(cin,license_number);
            std::regex re("[\\d]{0,3}?[- ]?\\d{10}");
            do{
                cout<<"Phone Number : ";
                getline(cin,phone_number);
                if(std::regex_match(phone_number, re))
                    counter=0;
                else
                    counter=1;
//               counter=0;
//                int l=phone_number.length();

            }while(counter==1);
            total_amount="0.0";
            amount_in_debt="0.0";
            query_text="INSERT into `Customer_Details` (`User_Name`,`Phone_Number`,`Address`,`Shop_Name`,`License_Number`,`Amount`,`Amount_in_Debt`) VALUES ('"+customer_name+"','"+phone_number+"','"+customer_address+"','"+shop_name+"','"+license_number+"','"+total_amount+"','"+amount_in_debt+"')";
            mysql_query(connect,query_text.c_str());
        }
    }
    mysql_close(connect);
}

//void User::deleteCustomer(){
//    string customer_name;
//    cout<<"Enter customer name you want to delete : ";
//    getline(cin,customer_name);
//    MYSQL *connect;
//    connect=mysql_init(NULL);
//    if(!connect){
//        cout<<"MySQL initialization failed in class inventory display_all_medicines function"<<endl;
//    }
//    else{
//        connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
//        if(connect){
//            MYSQL_RES *res;
//            MYSQL_ROW row;
//            int result;
//            string query_command,name;
//            getchar();
//            cout<<"Medicine name : ";
//            getline(cin,name);
//            query_command = "select * from inventory where medicine_name ='"+name+"'";
//            result=mysql_query(connect,query_command.c_str());
//            if(result!=0){
//                cout<<"error in query parsing"<<endl;
//            }
//            else{
//                res=mysql_store_result(connect);
//                (row=mysql_fetch_row(res));
//                if(row==NULL)
//                    cout<<"Not found"<<endl;
//                else{
//                cout<<setw(15)<<left<<"MEDICINE_NAME"<<"|"<<setw(15)<<left<<"BATCH_CODE"<<"|"<<setw(15)<<left<<"HSN_NUMBER"<<"|"<<setw(15)<<left<<"QUANTITY"<<"|"<<setw(15)<<left<<"SELLING_RATE"<<"|"<<setw(15)<<left<<"PURCHASED_RATE"<<"|"<<setw(15)<<left<<"MRP"<<"|"<<endl;
//                cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
//                cout<<setw(15)<<left<<row[0]<<"|"<<setw(15)<<left<<row[1]<<"|"<<setw(15)<<left<<row[2]<<"|"<<setw(15)<<left<<row[3]<<"|"<<setw(15)<<left<<row[4]<<"|"<<setw(15)<<left<<row[5]<<"|"<<setw(15)<<left<<row[6]<<"|"<<setw(15)<<left<<row[7]<<endl;
//                }
//            }
//        }
//        mysql_close(connect);
//    }
//} 

string CustomerDetails::changeCase(string str){
    int length=str.length();
    for(int i=0;i<length;i++)
    {
        str[i]=toupper(str[i]);
    }
    return str;
}