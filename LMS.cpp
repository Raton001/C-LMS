#include <iostream>
#include <cstdlib>
//#include <cstdbool>
#include <cctype>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>


// CONSTANTS //
//Pathname for customer file which helps retrieving the data while launching the process
 const char * customer_temp_filename_path = "TempCustomer.txt";

//Pathname for customer information file with decent look
 const char * book_temp_filename_path      = "TempBook.txt";

 //saves the address of temp file used for restoring data
 const char * library_temp_filename_path = "TempLibrary.txt";

//------------------------------------------------------ >> DATA STRUCTURES << ---------------------------------------------------------------- //

//list is the structure which allocate dynamic memory and stores information related to customer
typedef struct list{
	std::string  f_name;						//first name
	std::string  l_name;						//last name
	unsigned int book;							//number of books/items loaned
	std::string cust_id;						//saves the customer's  unique ID
	struct list* node;							//node to store address of next node
}l_customer;

//b_list is a list structure which stores all the information related to book
typedef struct b_list{

  std::string book_name;				//stores name of the book
  std::string author_name;				//stores author's name
  std::string book_id;					//unique id of per book
  struct b_list* node;
}l_book;

//Stack structure to store all the information regarding borrowed book
 typedef struct stack{
   std::string cust_id;				//customer id
   std::string book_id;				//book/item id
   std::string issued_date;			//item/book issued date
   std::string return_date;			//item schedule to return
}s_info;

//Queue to manage number of books issues by person
//A person can issue maximum of 10 books at a time
 typedef struct queue{
   std::string cust_id;				//customer id
   std::string book_id;             //book id
}q_loan;


// ------------------------------------------------------- >> CLASS DECLARATIONS  << -------------------------------------------------------------- //

//Customer class handles all the information related to customer
//Inherits from Library class to utilize all the features of Library class
class Customer {

public:

//Default Constructor
 Customer();

//Destructor to deallocate all the memory for l_customer
//Open's file in truncate mode and saves all the data of l_customer
 ~Customer();

//Pre : takes cid(customer id) and sets default value to "", fname(first name), lname(last name), bk(book)  as the initial arguments
//Post: Saves the new data in the m_head
//	    returns true if successfully adds the data, otherwise false
 bool AddCustomerDetails( std::string & fname, std::string & lname, std::string cid = "", unsigned int bk =0);


//Pre : takes fname(first name) and lname(last name) as the argument and search for specific customer in l_customer list
//Post: returns true if details found in l_customer and prints detail onto the screen
//      otherwise, returns false
 bool SearchCustomer( std::string fname, std::string lname, std::string& cid, char operation = ' ');
//Pre : Sort customer details in l_customer
//      Sort sorts data on two bases
//      -Sorts the data based on number of book issued by customer in ascending order
//      -If number of books found same for two person then sort them in alphabetical order
//Post: Stores the new result in the l_customer
 void SortCustomer();

//Post :Prints all the data from l_customer onto the screen
 void DisplayAll();

//Pre : method retrieves all the previous data state from file TempCustomer.txt
//Post: Open's previously saved file
//      fetches all the data and stores that in the l_customer
//      returns true if able to open file, else false
 void CustomerDataRetrieveFromFile();

//Pre : takes cid(customer's Id) as an integer and flag
//Post: increment the issued book record of customer by value 1 if flag is true else decrement 1
//      returns new value
 unsigned int UpdateCustomerBookDetails(std::string cid, bool flag);
//Pre : takes the head pointer of the l_customer list structure
//Post: sorts the l_customer based on number of book issued by person in ascending order
//      returns the new l_customer* for m_head variable
 l_customer * BookSort( l_customer* list );

protected:

//pointer to l_customer list for storing the customer's details
 l_customer* m_head;


private:

//POS: returns dynamically allocated memory node for l_customer */
 l_customer* Allocate();

//m_count helps in creating unique ID
 unsigned int m_count;

//Pre : takes fn(first name) as an argument
//Post: returns unique customerId which is a combination of
//      3 characters of fn and m_count
 std::string GenerateCustomerID(std::string fn);

};


// BOOK CLASS //
//class Book handles all the information related to book/item in the library
class Book{

public:

//Default Constructor
 Book();

//Destructor to deallocate dynamic memory allocated by l_book
 ~Book();

//Pre : takes bn(book_name), an(author_name), pb(publisher), pby(publish_year), noc(num_of_copies) as arguments
//Post: Adds all the arguments to l_book list structure
//		returns true if successfully added the data
//      otherwise returns false
 bool AddBookDetails(std::string bn, std::string an, std::string bid = "");

//Pre : takes bn(book_name) as initial argument
//Post: search book in l_book list
// 	    prints the book details if found and returns true
// 	    else returns false
 bool SearchBook(std::string& bn, std::string& bid, std::string& an, char operation = ' ');

//Pre : Retrieve previous saved data from file
//Post: Open up the file described in book_temp_filename_path variable
//      Saves all the data from file to the l_book list
 void BookDataRetrieveFromFile();

protected:

//m_book is the pointer to l_book list structure
 l_book* m_bhead;

private :

//Post: allocate dynamic memory node for m_book
//      returns the address of allocated node
 l_book * Allocate();

//Pre : takes bn(book name) as an argument
//Post: trunc first 3 char from book name
//	    returns the new unique book id
 std::string GenerateBookId(std::string bn);

//m_count variable helps in creating unique ID
 unsigned int m_count;
};


//LIBRARY CLASS//
//Library class handles all the operation
class Library {

public:

//Default constructor
 Library();

//Pre : Destructor of class Library
//Post: Deallocate all the memory taken by s_info stack
//      Opens the file and store all the previous state data inside the file
 ~Library();

//Pre : Searches the customer details passed in arguments fn( first name ), ln( last name ) , id( customer id )
//      using the Customer class 'SearchCustomer' method
//Post: returns true if details found, else false
 bool SearchCustomerDetails(std::string& fn, std::string& ln, std::string& id);

//Pre : Searches the book details passed in method argument inside the Book class
//      Uses Book class 'SearchBook' method
//Post: returns true if details found else false
 bool SearchBookDetails(std::string& book_name, std::string& book_id, std::string& author_name );

//Pre : Sets the Queue structure accordingly
//Post: increment the 'm_book_issue_record' on every single issue of a book
//      returns true on success, else false
 bool UpdateLibraryQueue(std::string bid, unsigned int value);

//Pre : Sets the Stack s_info structure accordingly
//Post: Update the s_info structure accordingly on every issue of the book
//      return true on success, else false
 bool UpdateLibraryStack(std::string bid, std::string cid, std::string idate, std::string rdate );

//Pre : Takes the cid( customer id ), bid( book id ), idate ( issue date ), cdate (current date )
//Post: Updates the s_info stack info
//      returns true if successfully updated the s_info else false
  bool SetDateInStack(std::string cid, std::string bid, std::string idate, std::string rdate);

//Pre : takes all the value from Book and Customer and sets private variable of Library
//Post:	cid(customer id) sets m_current_cust_id
//	    cname(customer name) sets m_current_cust_name;
//      bid(book id ) sets m_current_book_id
//      bname( book name) sets m_current_book_name
//      aname( author name) sets m_current_author_name
 void SetLibraryVariables(std::string cid, std::string cname, std::string bid, std::string bname, std::string aname);

//Pre : Takes cid (customer ID) and bid( book id ) as an argument
//Post: remove one entry from s_info
//      returns true if successfully deltes the s_info node else false
 bool DeleteEntryInStack(std::string cid, std::string bid );

//Pre : Function takes two argument, cid( customer id ) and bid( book id ) respectively
//Post: increment the record of book issue by per customer by calling Customer class methord
//      Updates the Library Queue( q_loan )
//      Updates the Library stack( s_inof )
//      Print the borrow receipt
//      returns true if everything works, else false
 bool LoanBook( std::string cid, std::string bid, unsigned int value);

//Pre : Function renews the book issue information, takes cid( customer id ) and book id( book id )
//Post: reset the dates of stack( s_info )
//      Print out the new receipt
//      returns true if everything works, else false
 bool RenewLoanBook( std::string cid, std::string bid);

//Pre : Takes cid( customer id) and bid (book id ) as an argument
//Post: Delete one entry from s_info stack by calling DelteEntryInStack method
// 	    Updates the queue q_loan array variable
 bool DeleteLoanBook(std::string cid, std::string bid, unsigned int value);

//Pre : takes idate and rdate as the buffer argument
//      sets system date
//Post: returns the issue date(idate) and return date(rdate ) respectively
  void Date(std::string& idate, std::string& rdate, int value);

//Pre : method retrieves all the previous data state from file TempLibrary.txt
//Post: Open's previously saved file
//      fetches all the data and stores that in the s_info
//      returns true if able to open file, else false
 void LibraryDataRetrieveFromFile();

//Post: Prints out daily report from s_info
 void DisplayDailyReport();

//Post: Prints out weekly report from s_info
 void DisplayWeekReport();

//Post: writes s_inof data in the file
 //void WriteFile();

private:

  const static int MAXBOOK =10;			//constant value for issuing number of books
  const static int MAXSTACK =100;		//maximum stack size of s_info

  s_info m_book_info[MAXSTACK]; 		//stores library activities(loan, renew, delete) of book/item
  q_loan m_book_issue_record[MAXBOOK];	//keeps record of number of book issued by per person

 unsigned int m_stack_count;			//keeps record of stack size
 unsigned int m_current_issue_book;		//saves the current value of issue book
 std::string m_current_cust_id;			//saves customer id
 std::string m_current_cust_name;		//saves customer name
 std::string m_current_book_id;			//saves book id
 std::string m_current_book_name;		//saves book name
 std::string m_current_book_author_name;//saves book's author name

 //s_info * Allocate();					//allocate memory for s_info

};


// -------------------------------------------------------------- >> INTERFACE METHODS <<----------------------------------------------------------- //

//All menu option
void Menu();
//handles input by user
void ManageMenu( Customer & customer, Book & book, Library & library );

//Ask for user input of fn(first name ). ln( last name )
void AskDetails(std::string& fn, std::string& ln );

//Work according to ManageMenu option provided by user in ManageMenu
void AccessCustomer( Customer& customer, const unsigned int option );

//Prints the top head of customer data table
void PrintCustomerHeader();

//Prints all the customer details asked stores in file
void PrintCustomerDetails(std::string& id, std::string& fname, std::string& l_name, unsigned int& book );

//Prints below line of the customer table
void PrintCustomerBelowHeader();

//Access Book class
void AccessBook( Book & book, const unsigned int option);

//Prints details on to the screen
void PrintBookDetails(std::string bid, std::string bn, std::string an);

//Access operations on Library class
void AccessLibrary(Customer& customer, Book& book, Library& library, const unsigned int  option);

//Header for printing receipt format
void PrintReceiptHeader(std::string cname, std::string idate);

//Prints the recipt on to the screen
void PrintReceipt(std::string cname, std::string bname, std::string aname, std::string idate, std::string rdate);

//prints the below line of table
void PrintLibraryBelowHeader();

//header for printing daily report
void PrintDailyReportHeader(std::string idate );

//Prints out all the information on to the screen
void PrintDailyReport(std::string bid, std::string cid, std::string cdate, std::string rdate);

//header for printing Weekly report
void PrintWeeklyReportHeader(std::string sdate, std::string cdate);

//prints all the information on to the screen
void PrintWeeklyReport(std::string bid, std::string cid, std::string sdate, std::string cdate, std::string rdate);

//Handles all error message
void Error( std::string err );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ >> MAIN << ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int main()
{

	Customer v_customer;
	Book v_book;
	Library v_library;

	//ManageMenu handles all the operation on LMS
	ManageMenu(v_customer, v_book, v_library );

 return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++>> INTERFACE DEFINITION <<+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

void Menu(){

	std::cout << "\n\t\t\tWelcome to Mini Library Management System\n"
			     "\t\t     -----------------------------------------------\n"
			     "   i. Add new customer \n"
			     "---------------------------------------------------------\n"
			     "  ii. Print information of existing customer\n"
			     "---------------------------------------------------------\n"
			     " iii. Add new book/item\n"
			     "---------------------------------------------------------\n"
			     "  iv. Search for existed book/item\n"
			     "---------------------------------------------------------\n"
				 "   v. Loan book/item\n"
				 "---------------------------------------------------------\n"
			     "  vi. Renew already borrowed book/item\n"
			     "---------------------------------------------------------\n"
			     " vii. Delete borrowed book/item\n"
			     "---------------------------------------------------------\n"
				 "viii. Calculate books as per customer bases\n"
				 "---------------------------------------------------------\n"
				 "  ix. Sort customer data\n"
				 "---------------------------------------------------------\n"
				 "   x. Print customer data\n"
				 "---------------------------------------------------------\n"
				 "  xi. Print daily transaction report\n"
				 "---------------------------------------------------------\n"
			     " xii. Print weekly report\n"
			     "---------------------------------------------------------\n"
				 "xiii. Exit\n"
				 "---------------------------------------------------------\n"
				 "      ENTER 1-13: \n"
			     "-------------------------"<< std::endl;

}// end

//HandleMenu asks for the input until user types the correct option
void ManageMenu( Customer & customer, Book & book , Library & library ){

  //Retrieving previous state from customer files
   customer.CustomerDataRetrieveFromFile();

  //Retrieving previous state from book file
   book.BookDataRetrieveFromFile();

  //Retrieving previous state from library file
   library.LibraryDataRetrieveFromFile();

   unsigned int input;

  //loop to handle user's input option
   while( true ){

    //Calling Menu
     Menu();
     std::cout << ":";
	 std::cin >> input;

	  //options for customer related object
	  if( input == 1 || input == 2 || input == 8 || input == 9 || input == 10 ){
	     AccessCustomer( customer, input );
	  }

	  //options for book related object
	  else if( input == 3 || input == 4){
	     AccessBook( book, input );
	  }

	  //options for Library relate object
	  else if( input == 5 || input == 6 || input == 7 || input == 11 || input == 12 ){
	    AccessLibrary(customer, book, library, input);
	  }

	  //option to exit from LMS
	  else if( input == 13 ){

		//explicit calls of destructor tomake sure we store data in respective files
		library.~Library();
		book.~Book();
		customer.~Customer();

		 std::cout << "Exiting...\n";
		 exit( EXIT_SUCCESS );
	  }

	  //if user type anything wrong
	  else {

		//clear istream buffer and asks again for input
		std::cin.clear();
		std::cin.ignore();
	    std::cout << "Invalid input, please re-enter. \n";
	  }
   }
}//end

/* CUSTOMER */

//takes input from user
 void AskDetails(std::string& fn, std::string& ln ){
  std::cout << "Enter First name :";
  std::cin >> fn;
  std::cout << "Enter Last name :";
  std::cin >> ln;
}// end

//handles all the operations related to Customer class
 void AccessCustomer( Customer& customer, const unsigned int option ){

  const char operation= 'P';
  std::string f_name;
  std::string l_name;
  std::string cus_id;

  if( option == 1 ){
  //calling AskDetails
   AskDetails(f_name, l_name);
   f_name[0] = toupper(f_name[0]);					//changing first character of name upper

   //AddCustomerDetails to add details on the customer's list
 	if( (customer.AddCustomerDetails(f_name, l_name)) ==false ){
 	   Error("Not able to add customer's detail.\n");
 	}
 	else
 	  std::cout << "\n\tSUCCESSFULLY ADDED\n";
  }
   else if( option == 2 || option == 8){
   //calling AskDetails
    AskDetails(f_name, l_name); getchar();
    f_name[0] = toupper( f_name[0]);

    std::cout << "Enter customer's ID(if you don't know id, press enter): ";
 	getline(std::cin, cus_id);

       //Printing below header
  	   PrintCustomerHeader();

 	//Search for the customer if found print the result else returns false
    if( (customer.SearchCustomer(f_name, l_name, cus_id, operation )) ==false ){
      Error("No details found");
    }
    else
    	PrintCustomerBelowHeader();		//if returns true print below header
  }
   else if( option == 9 ){
   //sort customer data
 	 customer.SortCustomer();
  }
   else if( option ==10 ){

	      PrintCustomerHeader();
	 //print customer data
 	customer.DisplayAll();
 	 PrintCustomerBelowHeader();
  }
}// end

//below header for customer
 void PrintCustomerHeader(){

   std::cout << "\n\t\t";
   for(unsigned int ob = 0 ; ob < 28 ; ++ob)
 	 std::cout << "--";

   std::cout << "\n\t\t| Customer ID \t\t   Name \t\t Books | \n";

   //loop to print line below the Header
   std::cout << "\t\t";
   for(unsigned int ob = 0 ; ob < 28 ; ++ob)
     std::cout << "--";
     std::cout << "\n";
 }// end

//Print out the customer details on to the screen
 void PrintCustomerDetails(std::string& id, std::string& fname, std::string& lname, unsigned int& book ){
 std::cout << "\t\t| " << " " << id << "    \t\t" <<  fname << " " << lname << "       \t"  << book  << "   |"<< std::endl;
}// end

//Print customer table below header
 void PrintCustomerBelowHeader() {

 std::cout << "\t\t";
 for(unsigned int ob = 0 ; ob < 28 ; ++ob)
   std::cout << "--";
  std::cout << "\n";
}// end

/*BOOK*/

//handles all operations related to Book class
 void AccessBook( Book & book, const unsigned int option ){

  char operation = 'P';
  std::string b_name;								//book name
  std::string a_name;								//book's author name
  std::string b_id;									//book's id

  getchar();
  std::cout << "Enter book name: ";
  getline(std::cin, b_name);
  b_name[0] = toupper(b_name[0]);

  std::cout << "Enter author name: ";
  getline(std::cin, a_name);
  a_name = toupper(a_name[0]);

  if(option == 3){
  //adds the new book data in the l_book of Book.h
   if( book.AddBookDetails(b_name, a_name) ==false )
     Error("Not able to add the book.");
   else
    std::cout << "\tSUCCESSFULLY ADDED\n";
  }
   else if( option == 4){

    std::cout << "Enter book's ID (if you don't know, press enter): ";
    getline(std::cin, b_id);

    //search for the book, if found print it on the screen else exit
    if( book.SearchBook(b_name, b_id, a_name, operation) ==false)
      Error("No book found\n");

  }
}//end

//Prints the book details on to the screen
 void PrintBookDetails( std::string bid, std::string bn, std::string an ){

	 std::cout << "\n\t\t";
     for(unsigned int ob = 0 ; ob < 28 ; ++ob)
	   std::cout << "--";

	   std::cout << "\n\t\t| Book ID \t\t   Book Name \t Author Name | \n";
	   std::cout << "\t\t| " << " " << bid << "     \t\t" << bn << "     \t   " << an << "  |" << std::endl;
	   //loop tp print line below the Header
	   std::cout << "\t\t";
	   for(unsigned int ob = 0 ; ob < 28 ; ++ob)
		 std::cout << "--";
		 std::cout << "\n";
}// end

/* LIBRARY */

 static int weak_rep_count ;
 static int daily_rep_count ;

 //Method handles all the actions done on Library class object
 void AccessLibrary(Customer& customer, Book& book, Library& library, const unsigned int input ){

   if( input == 5 || input == 6 || input == 7){

     std::string f_name;
     std::string l_name;
     std::string cus_id;
     unsigned int i_book =0;

    //calling AskDetails to ask customer's details
     AskDetails(f_name, l_name);
     f_name[0] = toupper(f_name[0]);

     //print customer's header
     PrintCustomerHeader();
     //searches for customer existence
     if( customer.SearchCustomer(f_name, l_name, cus_id, 'P') == false)
    	 Error("Not able to find customer.");
     else
    	PrintCustomerBelowHeader();

     std::string book_name;
     std::string book_id;
     std::string author_name;

     getchar();
     std::cout << "Enter book Name: ";
     getline(std::cin, book_name);
     book_name[0] = toupper(book_name[0]);

     std::cout << "Enter book ID: (press enter, if you don't know)";
     getline(std::cin, book_id);

     std::cout << "Enter author name: ";
     getline(std::cin, author_name);
     book_name[0] = toupper(book_name[0]);



     //Search book in Book class
      if( book.SearchBook(book_name, book_id, author_name) == false ){
        Error("Book is not available.");
      }
	  //std::cout << "Searching is done\n"; getchar();
      std::string name = f_name + " " + l_name;

      //Set Variables in library
      library.SetLibraryVariables(cus_id, name, book_id, book_name, author_name );

      if( input == 5 ){							//Loan Book


      //Update the customer's book record
       unsigned int value = customer.UpdateCustomerBookDetails(cus_id, true);

      //if returns true Prints the receipt else returns false
       if( library.LoanBook( cus_id, book_id, value) ==false){
    	 Error("Not able to issue the book.");
       }
       else
    	 PrintLibraryBelowHeader();
      }
      else if( input == 6){				//Renew Book

       	if( library.RenewLoanBook( cus_id, book_id ) ==false)
    	  Error("Not able to renew the book");
    	else
			PrintLibraryBelowHeader();
      }
      else if( input == 7 ){

        //Update the customer's book record
    	 unsigned int value = customer.UpdateCustomerBookDetails(cus_id, false);

    	//if returns true Prints the receipt else returns false
    	 if( library.DeleteLoanBook( cus_id, book_id, value) ==false){
    	   Error("Not able to issue the book.");
    	 }
    	 else
			 std::cout << "Successfully Deleted.\n";
      }
   }
       if ( input == 11 ){
    	//calls library method
    	library.DisplayDailyReport();
    	std::cout << " | Total entries: " << daily_rep_count  << "\n";
    	//print out the beow line
    	PrintLibraryBelowHeader();
      }
      else if( input == 12 ){
    	 //calls the library method to print weekly report
    	 library.DisplayWeekReport();
    	 std::cout << " | Total entries: " << weak_rep_count << "\n";
    	 //prints the below line
    	 PrintLibraryBelowHeader();
      }

}// end

//Prints the header of the receipt
void PrintReceiptHeader(std::string cname, std::string idate){

   std::cout << "\n +---------------------------------------------------------------------------------+\n";
   std::cout << " |\t\t\t\t Mini Library Receipt \t\t\t\t   |\n";
   std::cout << " |\t\t\t\t    Borrow Item \t\t\t\t   |\n";
   std::cout << " |---------------------------------------------------------------------------------|\n";

   std::cout << " | Customer Name: "<< cname << "      \t\t\t\t\t           |\n";
   std::cout << " | Date:" << idate << "  \t\t\t\t\t\t\t\t   |\n";
   std::cout << " |---------------------------------------------------------------------------------|\n";

   std::cout << " |  Book/Item Title     |  Max. Days Borrowed   |   Author Name     |  Due Date    |\n";
   std::cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
 }

//Prints out receipt onto the screen
 void PrintReceipt(std::string cname, std::string bname, std::string aname, std::string idate, std::string rdate){

	PrintReceiptHeader(cname, idate);
	std::cout << " |   " << bname << "        \t\t" << 07  << "     \t\t   " << aname << "              \t"  << rdate << "  |\n";
 }

//prints below line for Library printing methods
 void PrintLibraryBelowHeader(){
	 std::cout << " |_________________________________________________________________________________|\n";
 }

//Prints header of daily report
 void PrintDailyReportHeader(std::string idate ){

    std::cout << "\n +---------------------------------------------------------------------------------+\n";
    std::cout << " |\t\t\t\t Mini Library Receipt \t\t\t\t   |\n";
    std::cout << " |\t\t\t\t    Daily Summary \t\t\t\t   |\n";
    std::cout << " |---------------------------------------------------------------------------------|\n";

    std::cout << " | Date:"<< idate << "           \t\t\t\t\t\t\t   |\n";
    std::cout << " |---------------------------------------------------------------------------------|\n";

    std::cout << " |     Book/Item ID      |        Customer Id         |        Return Date         |\n";
    std::cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

}


//Prints out the daily report
 void PrintDailyReport(std::string bid, std::string cid, std::string cdate, std::string rdate){

 	 if( daily_rep_count == 0)
 	 	PrintDailyReportHeader(cdate);

 	 	daily_rep_count++;
 	 	std::cout << " |   " << bid << "        \t\t\t" << cid << "              \t\t"  << rdate << " |\n";
}// end

//prints out header of weekly report
 void PrintWeeklyReportHeader(std::string sdate, std::string cdate){

  	 std::cout << "\n +---------------------------------------------------------------------------------+\n";
  	 	  std::cout << " |\t\t\t\t Mini Library Receipt \t\t\t\t   |\n";
  	 	  std::cout << " |\t\t\t\t    Weekly Summary \t\t\t\t   |\n";
  	 	  std::cout << " |---------------------------------------------------------------------------------|\n";

  	 	  std::cout << " | Date: " << sdate << "-" << cdate << "     \t\t\t\t\t\t   |\n";
  	 	  std::cout << " |---------------------------------------------------------------------------------|\n";

  	 	  std::cout << " |     Book/Item ID      |        Customer Id         |        Return Date         |\n";
  	       std::cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

}// end

//Prints out the Weekly report
 void PrintWeeklyReport(std::string bid, std::string cid, std::string sdate, std::string cdate, std::string rdate){

  	if( weak_rep_count == 0)
  	PrintWeeklyReportHeader(sdate, cdate);

  	weak_rep_count++;
  	std::cout << " |\t   " << bid << "    \t\t\t" << cid << "              \t"  << rdate << "\t   |\n";

}// end

//Show all the error messages onto the screen
void Error(std::string err){
  std::cerr << err << std::endl;
  exit( EXIT_FAILURE );
}// end


// +++++++++++++++++++++++++++++++++++++++++++++++++ >> CUSTOMER CLASS DEFINITION << +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

//CUSTOMER //
//CONSTRUCTOR
  Customer :: Customer(){
	  m_head = NULL;
	  m_count = 1;
  }// end

//DESTRUCTOR
  Customer :: ~Customer(){

	  //Destructor will open the file and saves the data inside the file
	   std::ofstream cust_file_stream;


	   //opening two files
       cust_file_stream.open( customer_temp_filename_path, std:: ios:: out |std:: ios:: trunc);

	  //deallocating the dynamic memory allocated by l_customer
	  while( m_head != NULL ){
		  l_customer* temp = m_head;

		  //writing inside the file
		   cust_file_stream << temp->cust_id << " " << temp->f_name << " " << temp->l_name << " " << temp->book << "\n";
		   delete m_head;
		  m_head = temp->node;
	  }

	//close the open file
	 cust_file_stream.close();
}// end

//METHODS

//returns true if successfully adds details otherwise false
 bool Customer :: AddCustomerDetails(std::string& fname, std::string& lname, std::string cid, unsigned int bk ){

  bool flag;
  l_customer * temp = NULL;

  //allocate memory and data to temp node
   if( (temp =Allocate())== NULL ){
     flag = false;
  }
   else {

     temp->cust_id = GenerateCustomerID(fname);
      temp->f_name = fname;
      temp->l_name = lname;
        temp->node = NULL;
        temp->book = bk;
              flag = true;
  }

  //adds temp node to l_customer
   if( m_head == NULL && flag == true ){
     m_head = temp;
     flag   = true;
  }
   else {
     l_customer* ptr  = m_head;
     l_customer* prev = NULL;

    //loop to find the empty node
     while( ptr != NULL ){
       prev=ptr;
       ptr =ptr->node;
    }
    prev->node = temp;
     flag =true;
  }
 return flag;
}// end

//Allocate allocates the memory for l_structrue
 l_customer* Customer :: Allocate(){
   l_customer* temp = new l_customer;
 return temp;
}// end

//Search customer details in the l_customer list and prints or calls Library method accordingly
 bool Customer :: SearchCustomer(std::string fname, std::string lname, std::string& cid, char operation ){

  bool flag = false;
  l_customer * pointr = m_head;

  //loop searches data inside the l_customer
   while( pointr != NULL ){

    if( fname == pointr->f_name || lname == pointr->l_name  ){

     flag =true;
     unsigned int btemp = pointr->book;
     //calling Pint function to print details
     PrintCustomerDetails( pointr->cust_id, fname, lname, btemp);
       cid = pointr->cust_id;
       break;
    }
   pointr = pointr->node;
 }
 return flag;
}// end

//Sort customer based on number of books issued and if books issued are same then sorts alphabetically
 void Customer :: SortCustomer(){

	 l_customer * head  = m_head;

	 //method sorts in ascending order and return new node
	  l_customer * new_head = BookSort( head );

	 //setting new pointer address
	 m_head = new_head;
 }// end

//Prints all the l_customer data
 void Customer :: DisplayAll(){

   //calls SortCustomer to sort the data implicitly
    Customer::SortCustomer();

    l_customer* pointr = m_head;

      while( pointr != NULL ){

        //Calls Printing method from Driver.h
         PrintCustomerDetails( pointr->cust_id, pointr->f_name, pointr->l_name, pointr->book  );
        pointr = pointr->node;
     }

}// end

//BookSort sorts the book issued data in ascending order using recursion
 l_customer* Customer :: BookSort(l_customer* list){

	 if(list == NULL || list->node == NULL)
	 	    return list; // the list is sorted.

	 l_customer * curr;
	 l_customer *largest;
	 l_customer *largestPrev;
	 l_customer *prev;
	 l_customer * tmp;

	     curr = list;
	  largest = list;
	     prev = list;
  largestPrev = list;

    while(curr != NULL) {

  	   if(curr->book < largest->book) {
  	      largestPrev = prev;
  	          largest = curr;
  	  }
  	 prev = curr;
  	 curr = curr->node;
   }

  	if( largest != list ){
  	  largestPrev->node = list;
  	                tmp = list->node;
  	         list->node = largest->node;
  	      largest->node = tmp;
   }
  largest->node = BookSort(largest->node);
}// end

//Retrieves data from customer file
 void Customer :: CustomerDataRetrieveFromFile (){

  std::string temp;
  std::string words[4];
  unsigned int index =0;
  std::ifstream cust_file_pathname;

  //opening the file
   cust_file_pathname.open( customer_temp_filename_path);

   if( cust_file_pathname.is_open()){

   //loop to read the data from file
    for( unsigned int i =1; (cust_file_pathname >> temp) ; ++i ){

      words[index++] = temp;

      if( index ==4 ){

    	std::string cid = words[0];
    	 std::string fn = words[1];
         std::string ln = words[2];
		 std::string bk = words[3]; //std::cout << "CID : " << cid << "FN : " << fn <<std::endl;

      //converting string into integer
       unsigned int num;
       std::istringstream(bk) >> num;

      //calling AddCustomerDetails for adding details in list
       if( AddCustomerDetails(fn, ln, cid, num) ==false){
    	 Error("Not able to read data from file.");
       }

      //set index variable to 0 for further use
       index =0;
      }
    }
  }

  //closes the file
   cust_file_pathname.close();
}// end

//Create unique id for every customer
 std::string Customer :: GenerateCustomerID( std::string fn ){

   std::string temp = fn.substr(0,3);

   char buf[33];
   sprintf(buf, "%d", m_count);
   std::string id   = temp + static_cast<std::string>(buf);

     m_count++;
 return id;
}// end

//Updates and returns the issue book value of customer
 unsigned int Customer :: UpdateCustomerBookDetails(std::string cid, bool flag){

  unsigned int new_value =0;
  l_customer * pointr = m_head;

    while( pointr != NULL ){

	 if( cid == pointr->cust_id){

	  if(flag == true){  std::cout << "p : " << pointr->book ;
		pointr->book++;  std::cout << " A : " << pointr->book;
		new_value = pointr->book; std::cout << " NV : " << new_value << std::endl;
	  }
	  else{
		pointr->book--;
		new_value = pointr->book;
	  }
	  break;
    }
	 pointr = pointr->node;
  }
  return new_value;
}

// ++++++++++++++++++++++++++++++++++++++++++++++ >> BOOK CLASS DECLARATION << +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
 // BOOK //
//CONSTRUCTOR

//Default constructor assigns the default values to variables
 Book :: Book(){

   m_bhead = NULL;
   m_count = 1;
}// end

//DESTRUCTOR

//Destructor deallocate all the memory for l_book and saves data inside the file
 Book :: ~Book(){

  //ofstream open the file to saves the current state before terminating
   std::ofstream cust_file_stream;

  //opening two files
   cust_file_stream.open( book_temp_filename_path, std:: ios:: out |std:: ios:: trunc);

  //deallocating the dynamic memory allocated by l_customer
   while( m_bhead != NULL ){
	 l_book* temp = m_bhead;

	 //writing inside the file

	  cust_file_stream << temp->book_id << " " << temp->book_name << " " << temp->author_name << "\n";

	  delete m_bhead;
	   m_bhead = temp->node;
   }
    //close the open file
	 cust_file_stream.close();
}// end

//METHODS

//methods adds up the new book details
 bool Book :: AddBookDetails(std::string bn, std::string an, std::string bid){

  bool flag = false;
  l_book * temp = NULL;

   //allocates memory to temp
    if( (temp = Allocate()) == NULL ){
      flag =false;
   }
    else {
            temp->book_name = bn;
          temp->author_name = an;
              temp->book_id = GenerateBookId(bn);
                 temp->node = NULL;
                       flag = true;

   }
   //add up the temp node to appropriate location
    if( m_bhead == NULL && flag == true ){
    	  m_bhead = temp;
    	     flag = true;
   }
    else {
      l_book * curr = m_bhead;
      l_book * prev = NULL;

      //loop to check the next empty node
       while( curr != NULL ){
    	 prev = curr;
    	 curr = curr->node;
      }
    	prev->node = temp;
        flag = true;
   }
 return flag;
}// end

//allocate dynamic memory for l_book
 l_book * Book :: Allocate(){
	l_book * temp = new l_book;
 return temp;
}

//Search book inside l_book structure using Binary search algorithm
 bool Book :: SearchBook( std::string& bn, std::string& bid, std::string& an, char operation ){

   bool flag = false;
   l_book * pointr = m_bhead;

     while( pointr != NULL ){

      if( bn == pointr->book_name || bid == pointr->book_id || an == pointr->book_name ){

      //'P' prints out the book details if found
//       if(operation == 'P' || operation == 'p')
    	 PrintBookDetails( pointr->book_id, pointr->book_name, pointr->author_name);

  //     if(operation == 'S' || operation == 's'){
    	 bn = pointr->book_name;
    	bid = pointr->book_id;
    	 an = pointr->author_name;

    //   }
      flag = true;
      break;
   }
     pointr = pointr->node;
  }
 return flag;
}

//Retrieves the previous state from the file
 void Book :: BookDataRetrieveFromFile(){

   std::string temp;
   std::string a_name;										//author name
   std::string b_name;										//book name
   std::string b_id;										//book id
   unsigned int index =0;
   std::string words[3];
   std::ifstream book_file_pathname;						//ifstream to read from file

   //opening the file
   book_file_pathname.open( book_temp_filename_path);

   if( book_file_pathname.is_open()){
   //loop to read the data from file
	for( unsigned int i =1; (book_file_pathname >> temp) ; ++i ){
	  words[index++] = temp;

	  if( index ==3 ){
	   std::string   b_id = words[0];
	   std::string b_name = words[1];
	   std::string a_name = words[2];

	   //calling AddCustomerDetails for adding details in list
	   if( AddBookDetails(b_name, a_name, b_id) ==false){
	     Error("Not able to read data from file.");
	   }
	   //set index variable to 0
	   index =0;
	 }
   }
 }
 //closes the file
  book_file_pathname.close();
}// end

//create the unique book id
 std::string Book :: GenerateBookId( std::string bn ){

	 std::string temp = bn.substr(0,3);
   char buf[33];
   sprintf(buf, "%d", m_count);
   std::string id   = temp + static_cast<std::string>(buf);
	 	   m_count++;
 return id;
}// end

 // +++++++++++++++++++++++++++++++++++++++++++++++ >> LIBRARAY CLASS DEFINITION << ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

 //CONSTRUCTOR
 Library :: Library(){

   m_stack_count =0;
}// end

//DESTRUCTOR
//Deallocate all the memory and saves the previous state in the file
 Library :: ~Library (){

  //stream for opening both the file for writing purpose
   std::ofstream library_file_stream;

  //open call opens up the two files
   library_file_stream.open( library_temp_filename_path, std:: ios:: out |std:: ios:: trunc);

	unsigned int count = m_stack_count;

    //deallocating the dynamic memory allocated by l_customer
	 while( count > 0 ){
	   library_file_stream << m_book_info[count-1].cust_id << " " << m_book_info[count-1].book_id << " " << m_book_info[count-1].issued_date<< " " << m_book_info[count-1].return_date << "\n";
	   count--;
	 }
	 //close closes the open files
	 library_file_stream.close();
}// end

//METHODS

//LoanBook process the procedure of issuing the book or item
 bool Library :: LoanBook( std::string cid, std::string bid, unsigned int value ){

  bool flag = true;

  //checks if the user does not issue more than MAXBOOK
  if( value <= MAXBOOK ){

	//Updating the queue value
	 flag = UpdateLibraryQueue(bid, value);

    //variables to store date
	 std::string issue_date;
	 std::string return_date;

    //returns the current issue date and book return date in above issue_date and return_date string
	 Date(issue_date, return_date, 10);

	//Updating s_info stack
	 flag = UpdateLibraryStack(bid, cid, issue_date, return_date );


	//PrintBorrowReceipt will print out the receipt on the screen
	 PrintReceipt(m_current_cust_name, m_current_book_name, m_current_book_author_name, issue_date, return_date );
  }

 return flag;
}// end

//Renew loan book will remain the info in the stack
 bool Library :: RenewLoanBook( std::string cid, std::string bid ){

  bool flag = true;
  std::string issue_date;
  std::string return_date;

  //Retrieving the new dates
  Date(issue_date, return_date, 10);        //change 10 to any other value to increase or decrease the renew days

  //SetDateInQueue sets the date
  flag = SetDateInStack( bid, cid, issue_date, return_date );

  //Prints the receipt
   PrintReceipt(m_current_cust_name, m_current_book_name, m_current_book_author_name, issue_date, return_date );

  return true;
}


 bool Library :: DeleteLoanBook( std::string cid, std::string bid, unsigned int value ){

  bool flag = true;

  	//Updating the queue value
  	 flag = UpdateLibraryQueue(bid, value);

  	//Updating s_info stack
  	  flag = DeleteEntryInStack(bid, cid);

 return true;
}// end

//Delete an entry from s_info stack
 bool Library :: DeleteEntryInStack(std::string cid, std::string bid ){

   bool flag = true;
   unsigned int count = m_stack_count;

     while( count > 0 ){

    	 //making entry to None
    	 if( m_book_info[count-1].book_id == bid || m_book_info[count-1].cust_id == cid){
    	   m_book_info[count-1].book_id = "None";
    	   m_book_info[count-1].cust_id = "None";
    	   flag = true;
    	   break;
    	 }else flag = false;
    	count--;
     }

 return flag;
}

//searches for the cid and bid and sets the date accordingly
 bool Library :: SetDateInStack( std::string cid, std::string bid, std::string idate, std::string rdate ){

  bool flag = true;
  unsigned int count = m_stack_count;


	  //loop to access inside the stack
	  while(count  > 0 ){

		if( m_book_info[count-1].book_id == bid || m_book_info[count-1].cust_id == cid ){

		   m_book_info[count-1].issued_date = idate;
		   m_book_info[count-1].return_date = rdate;
		   flag = true;
		   break;
		}else flag = false;
		count--;
	 }
  return flag;
 }//end

//Updates the Queue structure accordingly
 bool Library :: UpdateLibraryQueue( std::string bid, unsigned int value ){

   unsigned int count = value -1;

   m_book_issue_record[count].book_id = bid;
   m_book_issue_record[count].cust_id = m_current_cust_id;
 return true;
}// end

//Updates the stack information
 bool Library :: UpdateLibraryStack( std::string bid, std::string cid, std::string idate, std::string rdate ){

  bool flag = false;

  if( m_stack_count < MAXSTACK ){
      m_book_info[m_stack_count].book_id = bid;
      m_book_info[m_stack_count].cust_id = cid;
  m_book_info[m_stack_count].issued_date = idate;
  m_book_info[m_stack_count++].return_date = rdate;
  flag = true;
 }
  else
	  Error("Stack is Full.");
 return flag;
}// end

//sets date in the idate and rdate buffer argument
 void Library :: Date(std::string & idate, std::string & rdate, int value){
	std::string date;
	 time_t t = time(0);   // get time now
	 struct tm * now = localtime( & t );

	 char dbuf[33];
	 char mbuf[33];
	 char ybuf[33];

	 sprintf(dbuf,"%d", now->tm_mday);
	 sprintf(mbuf, "%d", now->tm_mon+1);
	 sprintf(ybuf, "%d", now->tm_year +1900);

	  //generating issue date
      idate = static_cast<std::string>(dbuf) + "/" + static_cast<std::string>(mbuf) + "/" + static_cast<std::string>(ybuf);

	  //generating the return date
	  //setting dbuf memory to 0
	  //std::memset(dbuf, 0, sizeof(dbuf));
	  sprintf(dbuf, "%d", (now->tm_mday +value) );
      rdate = static_cast<std::string>(dbuf) + "/" + static_cast<std::string>(mbuf) + "/" + static_cast<std::string>(ybuf);


 }// end

//retrieves data from file
 void Library :: LibraryDataRetrieveFromFile(){

   std::string temp;
   std::string words[4];
   unsigned int index =0;
   std::ifstream library_file_pathname;

   //opening the file
	library_file_pathname.open( library_temp_filename_path);

   if( library_file_pathname.is_open()){
   //loop to read the data from file
	for( unsigned int i =1; (library_file_pathname >> temp) ; ++i ){
	  words[index++] = temp;

	  if( index ==4 ){

	   std::string  cid = words[0];
	   std::string  bid = words[1];
	   std::string idat = words[2];
	   std::string rdat = words[3];

	   //calling UpdateLibraryStack for adding details in list
	    if( UpdateLibraryStack( bid, cid, idat, rdat) ==false){
	       Error("Not able to read data from file.");
	    }
	     //set index variable to 0 for further use
	     index =0;
	  }
	}
 }
  //closes the file
   library_file_pathname.close();
}// end

//Sets the class private variable
 void Library :: SetLibraryVariables( std::string cid, std::string cname, std::string bid, std::string bname, std::string aname){
   m_current_cust_id = cid;
   m_current_cust_name = cname;
   m_current_book_id = bid;
   m_current_book_name = bname;
   m_current_book_author_name = aname;
}// end

//Display the weekly report
 void Library :: DisplayWeekReport(){

	 unsigned int count = m_stack_count;

	 std::string cdate;
	 std::string sdate;

	  //calling date to set the date values
	  Date(cdate, sdate, -7);

	 while( count > 0){

	   if( m_book_info[count-1].issued_date <= sdate && m_book_info[count-1].issued_date >= cdate ){
		 PrintWeeklyReport(  m_book_info[count-1].book_id, m_book_info[count-1].cust_id, sdate, cdate, m_book_info[count-1].return_date );
	  }
	  count--;
	}
}// end

//Display daily report
 void Library :: DisplayDailyReport(){

	 unsigned int count  = m_stack_count;

	 std::string cdate;
	 std::string sdate;

	  //calling date to set the date values
	  Date(cdate, sdate, 7);

	 while(count > 0){

	   if( m_book_info[count-1].issued_date == cdate ){
		 PrintDailyReport(  m_book_info[count-1].book_id, m_book_info[count-1].cust_id, cdate, m_book_info[count-1].return_date );
	  }
	  count--;
	}
 }

