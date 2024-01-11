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

class Member{
    int memberId;
    
};

int main(){
using std::cout;
using std::endl;
    Book book1(1, "mein kamf", "Adolf", "Hitler");

    book1.setDueDate(3);

    cout << "Due Date: " << book1.getDueDateString() << endl;

}
