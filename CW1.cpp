#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>


class Book{
public:
    int bookID;
    std::string bookName, authorFirstName, authorLastName, bookType;
    std::chrono::system_clock::time_point dueDate;

    Book(int bookId, std::string nameBook, std::string FirstNameAuthor, std::string LastNameAuthor){
        bookID = bookId;
        bookName = nameBook;
        authorFirstName = FirstNameAuthor;
        authorLastName = LastNameAuthor;
        dueDate = std::chrono::system_clock::now(); 
    };

    void setDueDate(int days) {
        dueDate = std::chrono::system_clock::now() + std::chrono::hours(24 * days);
    }

    std::string getDueDateString() const {
        std::time_t dueTime = std::chrono::system_clock::to_time_t(dueDate);
        return std::ctime(&dueTime);
    } 

    int getbookID(){
        return bookID;
    }
};

class Person{
private:
    std::string name, address, email;
public:

    void setName(std::string Name){
        name = Name;
    }
    std::string getName(){
        return name;
    }
    void setAddress(std::string Address){
        address = Address;
    }
    std::string getAdrress(){
        return address;
    }
    void setEmail(std::string Email){
        email = Email;
    }
    std::string getEmail(){
        return email;
    }
};

class Member: public Person{
private:
    int memberId;
    std::vector <Book> booksLoaned;

public:
    Member(int memberID, std::string Name, std::string Address, std::string Email){
        setName(Name);
        setAddress(Address);
        setEmail(Email);
        memberId = memberID;
    }

    std::string getMemberId(){
        return std::to_string(memberId);
    }
    void setBooksBorrowed(Book){

    }

};

class Librarian: public Person{
private:
    int staffId;
    int salary;
    std::vector<Member> members;

public:

    Librarian(int staffID, std::string Name, std::string Address, std::string Email, int Salary){
        setName(Name);
        setAddress(Address);
        setEmail(Email);
        staffId = staffID;
        salary = Salary;
    };

    void addMember(int memberID, std::string Name, std::string Address, std::string Email) {
        Member newMember(memberID, Name, Address, Email);
        members.push_back(newMember);
    }

    void setStaffID(int staffID){
        staffId = staffID;
    }

    int getStaffID(){
        return staffId;
    }

    void setSalary(int Salary){
        salary = Salary;
    }

    int getSalary(){
        return salary;
    }

};

int main(){
using std::cout;
using std::endl;

    cout << "Welcome to the library" << endl;
    cout << "Please select an option from below to get started" << endl;

}
