#ifndef CustomerDetails_H_
#define CustomerDeatils_H_
#include<string>

class CustomerDetails
{
public:
    CustomerDetails();
    void addCustomer();
    void deleteCustomer();
    void searchCustomer();
    std::string changeCase(std::string str);
    ~CustomerDetails();

};

#endif // CustomerDetails_H_
