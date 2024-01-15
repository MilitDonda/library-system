#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>

class Member;

struct Date{
    int day;
    int month;
    int year;
};

Date getDateFromUser(){
    Date inputDate;
    std::cout<<"enter date in DD MM YYYY format: " << std::endl;

    std::cout <<"DAY: ";
    std::cin >> inputDate.day;

    std::cout <<"MONTH: ";
    std::cin >> inputDate.month; 

    std::cout <<"YEAR: ";
    std::cin >> inputDate.year;

    std::cout<<"The date you issued this book is " <<inputDate.day << "/" << inputDate.month << "/" << inputDate.year << std::endl;

    return inputDate;
}

Date addDaysToDate(Date currentDate, int daysToAdd) {

    const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    currentDate.day += daysToAdd;

    while (currentDate.day > daysInMonth[currentDate.month - 1]) {
        currentDate.day -= daysInMonth[currentDate.month - 1];
        currentDate.month++;
        if (currentDate.month > 12) {
            currentDate.month = 1;
            currentDate.year++;
        }
    }

    return currentDate;
}

int dateDifference(const Date& date1, const Date& date2) {
    std::tm tm1 = {0, 0, 0, date1.day, date1.month - 1, date1.year - 1900};
    std::tm tm2 = {0, 0, 0, date2.day, date2.month - 1, date2.year - 1900};

    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    const int secondsPerDay = 24 * 60 * 60;
    double difference = std::difftime(time2, time1) / secondsPerDay;

    return static_cast<int>(difference);
}


class Book{
public:

    struct BooksWithDueDate{
    int bookID;
    int memberID;
    Date issueDate;
    Date dueDate;
    };

    int bookID;
    std::string bookName, authorFirstName, authorLastName, bookType;
    Date dueDate;
    Member* borrower;

    Book(int bookId, std::string nameBook, std::string FirstNameAuthor, std::string LastNameAuthor){
        bookID = bookId;
        bookName = nameBook;
        authorFirstName = FirstNameAuthor;
        authorLastName = LastNameAuthor;
    };

    std::string getbookID(){
        return std::to_string(bookID);
    }

    std::string getbookName(){
        return bookName;
    }

    std::string getAuthorFirstName(){
        return authorFirstName;
    }

    std::string getAuthorLastName(){
        return authorLastName;
    }

    void setDueDate(Date DueDate) {
        dueDate = DueDate;
    }

    Date getDueDate(){
        return dueDate;
    }

    void returnBook(){
        //code to add set the flag to true in the csv file when the book is returned
    }

    BooksWithDueDate bookInfo;

    /*void borrowBook(Member& borrower, Date DueDate){
        dueDate = DueDate;
        bookInfo.memberID = borrower.getMemberIdInt();
        bookInfo.bookID = this->bookID;
        bookInfo.dueDate = DueDate;
    }*/
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

    int getMemberIdInt(){
        return memberId;
    }

    void setBooksBorrowed(Book){
        //code to set books borrowed goes here
    }

    std::vector <Book> getBooksBorrowed(){
        return booksLoaned;
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

    bool memberExists(int memberID, std::string Name, std::string Address, std::string Email){
        for(Member member : members){
            if(member.getMemberId() == std::to_string(memberID) ||
                (member.getName() == Name && member.getAdrress() == Address && member.getEmail() == Email)){
                    return true;
                }
       }
       return false;
    };

    void addMember(int memberID, std::string Name, std::string Address, std::string Email) {
        if (!memberExists(memberID, Name, Address, Email)) {
            Member newMember(memberID, Name, Address, Email);
            members.push_back(newMember);
            std::cout << "New member added successfully.\n";
        } else {
            std::cout << "Member already exists.\n";
        }
    };

    void displayLibraryBooks(){
        std::fstream myFile;
        myFile.open("library_books.csv", std::ios::in);
        if(myFile.is_open()){
            std::string line;
            while(getline(myFile, line)){
                std::cout << line << std::endl;
                std::cout << std::endl;
            }
            myFile.close();
            }
    }

    struct IssuedBooks{
        int bookID;
        int memberID;
        Date dueDate;
    };

    std::vector<IssuedBooks> issuedBooks;

    bool isBookIssued(int bookId){
        for (IssuedBooks issuedBook : issuedBooks){
            if(issuedBook.bookID == bookId){
                return true;
            }
        }
        return false;
    };

    void issueBook(int memberId, int bookId){
        if (isBookIssued(bookId)) {
            std::cout << "Book is already issued." << std::endl;
        return;
    }

    Date issueDate = getDateFromUser();
    Date dueDate = addDaysToDate(issueDate, 3);
    IssuedBooks newIssuedBook = {bookId, memberId, dueDate};
    issuedBooks.push_back(newIssuedBook);
    std::cout << "Book issued successfully." << std::endl;
}

    void returnBook(int memberId, int bookId){
        for (int i = 0; i < issuedBooks.size(); ){
            if(issuedBooks[i].memberID == memberId && issuedBooks[i].bookID == bookId){
            issuedBooks.erase(issuedBooks.begin() + i);
            } else {
                ++i;
            }

        }
    }

    void displayBorrowedBooks(int memberID){
        std::cout<<"Books borrowed by member " << memberID << std::endl; 
        bool hasBooksIssued = false;

        for(IssuedBooks issuedBook: issuedBooks){
            if(issuedBook.memberID == memberID){
                std::cout<<"Book ID: " << issuedBook.bookID << std::endl;
                hasBooksIssued = true;
            }
        }

        if(!hasBooksIssued) {
            std::cout<<"No books issued by this member."<< std::endl;
        }
    }

void calculateFine(int memberID) {
    int totalFine = 0;
    Date currentDate = getDateFromUser(); // Implement this to get the current date

    for (const auto& issuedBook : issuedBooks) {
        if (issuedBook.memberID == memberID) {
            int daysOverdue = dateDifference(issuedBook.dueDate, currentDate);
            if (daysOverdue > 0) {
                totalFine += daysOverdue * 1; // Assuming £1 fine per day
            }
        }
    }

    if (totalFine > 0) {
        std::cout << "Total fine for member " << memberID << " is £" << totalFine << std::endl;
    } else {
        std::cout << "No fine for member " << memberID << std::endl;
    }
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

Librarian librarian(1, "Milit", "21 blackwell place", "militdonda3@gmail.com", 100);

    int userChoice;
    int i = 0;
    while(i < 2){
        int memberID;
        std::string Name;
        std::string Address;
        std::string Email;
        int bookID;
        Date issueDate, DueDate;

        cout << "---------------------------------------------------" << endl;
        cout << "Welcome to the library" << endl;
        cout << "Please select an option from below to get started" << endl;
        cout << "[1] Add/Register members" << endl;
        cout << "[2] issue a book (requires you to be registered)" << endl;
        cout << "[3] return a book" << endl;
        cout << "[4] Display all your borrowed books" << endl;
        cout << "[5] calculate fine (if the due date was missed)" << endl;
        cout << "[6] Exit" <<endl;
        cout << "---------------------------------------------------" << endl;

        std::cin >> userChoice;  
        switch(userChoice){
            case 1:
                cout << "Enter memberID: " << endl;
                std::cin >> memberID;
                cout << "Enter your name: " << endl;
                std::cin >> Name;
                cout << "Enter your address: " << endl;
                std::cin >> Address;
                cout << "Enter Email address: " << endl;
                std::cin >> Email;
                librarian.addMember(memberID, Name, Address, Email);
            break;

            case 2:
                cout<<"Please have a look through our collection of books and note the BookID of the book you would like to issue"<<endl;
                cout <<endl;
                librarian.displayLibraryBooks();
                cout <<"Enter memberID: " << endl;
                std::cin >> memberID;
                cout <<"Enter bookID: " << endl;
                std::cin >> bookID;
                librarian.issueBook(memberID, bookID);
            break;

            case 3:
                cout << endl;
                cout<< "Enter bookID of the book you would like to return: "<<endl;
                std::cin >> bookID;
                cout << "Enter your memberId: " << endl;
                std::cin >> memberID;
                librarian.returnBook(memberID, bookID);
            break;

            case 4:
                cout << "Enter your memberID: " << endl;
                std::cin >> memberID;
                librarian.displayBorrowedBooks(memberID);
            break;

            case 5:
            cout << "Enter you memberID: " << endl;
            std::cin>> memberID;
            librarian.calculateFine(memberID);
            break;
            case 6:
            i = 2;
            break;
        }   

    }
}
