#include<iostream>
#include<iomanip>
#include<mysql.h>
#include<stdio.h>
#include<string>
#include<fstream>
#include<sstream>
#include<CustomerDetails.h>
#include<regex>

using namespace std;

#define SERVER "127.0.0.1"
#define USER "root"
#define PASSWORD "Qwerty123456@"
#define DATABASE "file1"
#define DATABASE1 "file2"


class inventory{
public:
    void display_all_medicines(){
        MYSQL *connect;
        connect=mysql_init(NULL);
        if(!connect){
            cout<<"MySQL initialization failed in class inventory display_all_medicines function"<<endl;
        }
        else{
            connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
            if(connect){
                MYSQL_RES *res;
                MYSQL_ROW row;
                int result;
                result=mysql_query(connect,"SELECT * FROM inventory");
                if(result!=0){
                    cout<<"error in query parsing"<<endl;
                }
                else{
                    res= mysql_store_result(connect);
                    //unsigned int numrows = mysql_num_rows(res);
                    //cout<<numrows<<endl;
                    cout<<setw(15)<<left<<"MEDICINE_NAME"<<"|"<<setw(15)<<left<<"BATCH_CODE"<<"|"<<setw(15)<<left<<"HSN_NUMBER"<<"|"<<setw(15)<<left<<"QUANTITY"<<"|"<<setw(15)<<left<<"SELLING_RATE"<<"|"<<setw(15)<<left<<"PURCHASED_RATE"<<"|"<<setw(15)<<left<<"MRP"<<"|"<<endl;
                    cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
                    while ((row= mysql_fetch_row(res))){
                        cout<<setw(15)<<left<<row[0]<<"|"<<setw(15)<<left<<row[1]<<"|"<<setw(15)<<left<<row[2]<<"|"<<setw(15)<<left<<row[3]<<"|"<<setw(15)<<left<<row[4]<<"|"<<setw(15)<<left<<row[5]<<"|"<<setw(15)<<left<<row[6]<<"|"<<setw(15)<<left<<row[7]<<endl;
                    }
                }
                mysql_close(connect);
            }
            else{
                cout<<"Connection failed"<<endl;
            }
        }
    }
    void search_medicine(){
        MYSQL *connect;
        connect=mysql_init(NULL);
        if(!connect){
            cout<<"MySQL initialization failed in class inventory display_all_medicines function"<<endl;
        }
        else{
            connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
            if(connect){
                MYSQL_RES *res;
                MYSQL_ROW row;
                int result;
                string query_command,name;
                getchar();
                cout<<"Medicine name : ";
                getline(cin,name);
                query_command = "select * from inventory where medicine_name ='"+name+"'";
                result=mysql_query(connect,query_command.c_str());
                if(result!=0){
                    cout<<"error in query parsing"<<endl;
                }
                else{
                    res=mysql_store_result(connect);
                    (row=mysql_fetch_row(res));
                    if(row==NULL)
                        cout<<"Not found"<<endl;
                    else{
                    cout<<setw(15)<<left<<"MEDICINE_NAME"<<"|"<<setw(15)<<left<<"BATCH_CODE"<<"|"<<setw(15)<<left<<"HSN_NUMBER"<<"|"<<setw(15)<<left<<"QUANTITY"<<"|"<<setw(15)<<left<<"SELLING_RATE"<<"|"<<setw(15)<<left<<"PURCHASED_RATE"<<"|"<<setw(15)<<left<<"MRP"<<"|"<<endl;
                    cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
                    cout<<setw(15)<<left<<row[0]<<"|"<<setw(15)<<left<<row[1]<<"|"<<setw(15)<<left<<row[2]<<"|"<<setw(15)<<left<<row[3]<<"|"<<setw(15)<<left<<row[4]<<"|"<<setw(15)<<left<<row[5]<<"|"<<setw(15)<<left<<row[6]<<"|"<<setw(15)<<left<<row[7]<<endl;
                    }
                }
            }
            mysql_close(connect);
        }
    } 
    void input_medicine(){
        MYSQL *connect;
        connect=mysql_init(NULL);
        if(!connect){
            cout<<"MySQL initialization failed in class inventory input_medicine function"<<endl;
        }
        else{
            connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
            if(connect){
                string name,batch,hsn,query_text,quantity;
                string selling_rate,purchased_rate,market_rate;
                getchar();
                cout<<"Medicine name : ";
                getline(cin,name);
                cout<<"Batch Code : ";
                getline(cin,batch);
                cout<<"Hsn Number : ";
                getline(cin,hsn);
                cout<<"Quantity : ";
                cin>>quantity;
                cout<<"Selling Rate : ";
                cin>>selling_rate;
                cout<<"Purchased Rate : ";
                cin>>purchased_rate;
                cout<<"MRP : ";
                cin>>market_rate;
                query_text="INSERT into `inventory` (`medicine_name`,`Batch_code`,`Hsn_number`,`Quantity`,`Selling_Rate`,`Purchased_Rate`,`mrp`) VALUES ('"+name+"','"+batch+"','"+hsn+"','"+quantity+"','"+selling_rate+"','"+purchased_rate+"','"+market_rate+"')";
                mysql_query(connect,query_text.c_str());
            }
        }
        mysql_close(connect);
    }
    void delete_medicine(){
        MYSQL *connect;
        connect=mysql_init(NULL);
        if(!connect){
            cout<<"MySQL initialization failed in class inventory display_all_medicines function"<<endl;
        }
        else{
            connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
            if(connect){
                int result;
                string query_command,name;
                cout<<"Medicine name : ";
                getchar();
                getline(cin,name);
                query_command = "DELETE from inventory where medicine_name ='"+name+"'";
                result=mysql_query(connect,query_command.c_str());
                if(result!=0){
                    cout<<"error in query parsing"<<endl;
                }
                cout<<"Successfully Deleted"<<endl;
            }
            mysql_close(connect);
        }
    }
    void update_stock(){
        MYSQL *connect;
        connect=mysql_init(NULL);
        if(!connect){
            cout<<"MySQL initialization failed in class inventory display_all_medicines function"<<endl;
        }
        else{
            connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
            if(connect){
                int result;
                string query_command,name,quantity;
                getchar();
                cout<<"Medicine name : ";
                getline(cin,name);
                cout<<"Enter what you want to update\n1.Quantity\n2.Selling Rate\n3.Purchased Rate\n4.MRP"<<endl;
                int choice;
                cin>>choice;
                if(choice==1)
                {
                    cout<<"Enter updated quantity : ";
                    getchar();
                    getline(cin,quantity);
                    query_command = "UPDATE inventory SET Quantity ='"+quantity+"' WHERE medicine_name ='"+name+"'";
                }
                else if(choice==2){
                    cout<<"Enter updated Selling Rate : ";
                    getchar();
                    getline(cin,quantity);
                    query_command = "UPDATE inventory SET Selling_Rate ='"+quantity+"' WHERE medicine_name ='"+name+"'";
                }
                else if(choice==3){
                    cout<<"Enter updated Purchased Rate : ";
                    getchar();
                    getline(cin,quantity);
                    query_command = "UPDATE inventory SET Purchased_Rate ='"+quantity+"' WHERE medicine_name ='"+name+"'";
                }
                else{
                    cout<<"Enter MRP : ";
                    getchar();
                    getline(cin,quantity);
                    query_command ="UPDATE inventory SET mrp ='"+quantity+"' WHERE medicine_name ='"+name+"'";
                }
                result=mysql_query(connect,query_command.c_str());
                if(result!=0){
                    cout<<"error in query parsing"<<endl;
                }
                cout<<"Successfully Updated";
            }
            mysql_close(connect);
        }
    }
};
class sales{
public:
    void new_sale(){
        string customer_name;
        char ch;
        do{
            MYSQL *connect;
            MYSQL *connect1;
            connect1=mysql_init(NULL);
            connect=mysql_init(NULL);
            if(!connect){
            cout<<"MySQL initialization failed in class inventory display_all_medicines function"<<endl;
            }
            else{
                connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,3306,NULL,0);
                connect1=mysql_real_connect(connect1,SERVER,USER,PASSWORD,DATABASE1,3306,NULL,0);
                if(connect){
                    MYSQL_RES *res;
                //MYSQL_RES *res1;
                    MYSQL_ROW row;
                    int result,result1,result2;
                    getchar();
                    string query,query1,query2,name,batch,quan,mp,selling,medi_name,amt;
                    cout<<"Medicine Name : ";
                    getline(cin,medi_name);
                    query1="SELECT * from inventory where medicine_name ='"+medi_name+"'";
                    result=mysql_query(connect,query1.c_str());
                    if(result!=0){
                        cout<<"error in query1 parsing"<<endl;
                    }
                    else{
                        res= mysql_store_result(connect);
                        (row= mysql_fetch_row(res));
                        cout<<"Enter Quantity : ";
                        int q2;
                        cin>>q2;
                        name=row[0];
                        batch=row[1];
                        quan=row[3];
                        mp=row[6];
                        selling=row[4];
                        stringstream q(quan);
                        stringstream w(selling);
                        int q1=0;
                        int w1=0;
                        q>>q1;
                        w>>w1;
                        float a {0};
                        if(q2>q1)
                            cout<<"Insufficient Quantity"<<endl;
                        else{
                            a=q2*w1;
                            int q4=q1-q2;
                            string q5=to_string(q4);
                            amt=to_string(a);
                            quan=to_string(q2);
//                            cout<<name<<"\t"<<batch<<"\t"<<quan<<"\t"<<mp<<"\t"<<selling<<endl;
                            query="INSERT into `sale` (`medicine_name`,`Batch_code`,`Quantity`,`Selling_Rate`,`Amount`,`mrp`) VALUES ('"+name+"','"+batch+"','"+quan+"','"+selling+"','"+amt+"','"+mp+"')";
                            query2="UPDATE inventory SET Quantity = '"+q5+"' WHERE medicine_name = '"+name+"'";
                            result1=mysql_query(connect1,query.c_str());
                            result2=mysql_query(connect,query2.c_str());
                            if(result1!=0)
                                cout<<"error in query parsing"<<endl; 
                        }
                    }
                    mysql_close(connect);
                    mysql_close(connect1);
                }
                else{
                    cout<<"Connection failed"<<endl;
                }
            }
            cout<<"Enter 'C' to continue or 'Q' to quit : ";
            cin>>ch;
            getchar();
        }while(ch!='q');
    }
    void print_sale(){
        MYSQL *connect;
        connect=mysql_init(NULL);
        if(!connect){
            cout<<"MySQL initialization failed in class sale print sale function"<<endl;
        }
        else{
            connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE1,3306,NULL,0);
            if(connect){
                MYSQL_RES *res;
                MYSQL_ROW row;
                int result;
                result=mysql_query(connect,"SELECT * FROM sale");
                if(result!=0){
                    cout<<"error in query parsing"<<endl;
                }
                else{
                    res= mysql_store_result(connect);
                    cout<<setw(15)<<left<<"NAME"<<"|"<<setw(15)<<left<<"BATCH CODE"<<"|"<<setw(15)<<left<<"QUANTITY"<<"|"<<setw(15)<<left<<"SELLING RATE"<<"|"<<setw(15)<<left<<"AMOUNT"<<"|"<<setw(15)<<left<<"MRP"<<"|"<<endl;
                    cout<<"-------------------------------------------------------------------------------------------------"<<endl;
                    while ((row= mysql_fetch_row(res))){
                        cout<<setw(15)<<left<<row[0]<<"|"<<setw(15)<<left<<row[1]<<"|"<<setw(15)<<left<<row[2]<<"|"<<setw(15)<<left<<row[3]<<"|"<<setw(15)<<left<<row[4]<<"|"<<setw(15)<<left<<row[5]<<"|"<<setw(15)<<left<<row[6]<<"|"<<endl;
                    }
                }
                result=mysql_query(connect,"DELETE FROM sale");
                res=mysql_store_result(connect);
                mysql_close(connect);
            }
            else{
                cout<<"Connection failed"<<endl;
            }
        }
    }
};
int main()
{
/*    int choice{0};
    cout<<"----------------------WELCOME TO MEDICAL STORE MANAGEMANT SYSTEM----------------------------"<<endl;
    do{
        cout<<"Choose option from below"<<endl<<"1.Display All Medicines\n2.Search Medicines\n3.Add New Medicines\n4.Delete Medicine\n5.Update Stock\n6.Create New Sale\n7.Print Sale\n8.Quit\n";
        //int choice{0};
        cout<<"Your Choice : ";
        cin>>choice;
        inventory obj;
        sales obj1;
        switch(choice){
            case 1:cout<<"\n**************************************************************\n";
                         obj.display_all_medicines();
                         cout<<"\n**************************************************************\n";
                         break;
            case 2:cout<<"\n**************************************************************\n";
                         obj.search_medicine();
                         cout<<"\n**************************************************************\n";
                         break;
            case 3:cout<<"\n**************************************************************\n";
                         obj.input_medicine();
                         cout<<"\n**************************************************************\n";
                         break;
            case 4:cout<<"\n**************************************************************\n";
                         obj.delete_medicine();
                         cout<<"\n**************************************************************\n";
                         break;
            case 5:cout<<"\n**************************************************************\n";
                         obj.update_stock();
                         cout<<"\n**************************************************************\n";
                         break;
            case 6:cout<<"\n**************************************************************\n";
                         obj1.new_sale();
                         cout<<"\n**************************************************************\n";
                         break;
            case 7:cout<<"\n**************************************************************\n";
                         obj1.print_sale();
                         cout<<"\n**************************************************************\n";
                         break;
            default:
                             if(choice!=8)
                                 cout<<"Wrong choice"<<endl; 
        }
    }while(choice!=8);*/
    CustomerDetails obj;
    obj.addCustomer();
    return 0;
}
