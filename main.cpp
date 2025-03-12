#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;
const int MAX_USERS = 50;

// Book Class, used for storing specific book data
class Book {
public: 
	string title;
	string author;
	string isbn;
	bool available;

	// Default constructor for Book, initializes as available
	Book() : available(true) {}

};

// Parent Class for User, this will be the base class for the student and faculty classes
class User {
protected:
	static int userCounter;
public:
	string name;
	int userID;
	int borrowedBooks[MAX_BOOKS];
	int borrowedCount;

	User() : borrowedCount(0) {
		userID = ++userCounter;
		for (int i = 0; i < MAX_BOOKS; i++) {
			borrowedBooks[i] = -1;
		}
	}
};

int User::userCounter = 0;

// Derived Child class for stuents, from User Parent
class Student:public User {
public: 
	Student(string n) { name = n; }
};

// Derived Child class for Faculty, from User Parent
class Faculty :public User {
public:
	Faculty(string n) { name = n; }
};

// Library Class, Implementation of singleton method
class Library {
private:
	static Library* instance;
	Book books[MAX_BOOKS];
	User* users[MAX_USERS];
	int bookCount;
	int userCount;
	Library():bookCount(0), userCount(0) {}
public:
	static Library* getInstance() {
		if (!instance)
			instance = new Library();
		return instance;
	}

	// All Book Management Functions, Add, edit, remove, and list
	void addBook(string title, string author, string isbn) {
		if (bookCount < MAX_BOOKS) {
			books[bookCount].title = title;
			books[bookCount].author = author;
			books[bookCount].isbn = isbn;
			books[bookCount].available = true;
			bookCount++;
			cout << "\nBook added successfully!\n\n";
		}
		else {
			cout << "\nLibrary is full!\n\n";
		}

	}

	void editBook(int index, string title, string author, string isbn) {
		if (index >= 0 && index < bookCount) {
			books[index].title = title;
			books[index].author = author;
			books[index].isbn = isbn;
			cout << "Book updated successfully!\n";
		}
		else {
			cout << "Invalid book index!\n";
		}
	}

	void removeBook(int index) {
		if (index >= 0 && index < bookCount) {
			for (int i = index; i < bookCount - 1; i++) {
				books[i] = books[i + 1];
			}
			bookCount--;
			cout << "Book removed successfully!\n";
		}
		else {
			cout << "Invalid book index!\n";
		}
	}

	void listBooks() {
		for (int i = 0; i < bookCount; i++) {
			cout << "Book " << i + 1 << ": " << books[i].title << " by " << books[i].author << " - " << (books[i].available ? "Available" : "Checked out") << "\n";
		}
	}

	// Factory Method Implementation, creates User object dynamically
	void addUser(int type, string name) {
		if (userCount < MAX_USERS) {
			if (type == 1) {
				users[userCount] = new Student(name);// Create Student Object
			}
			else {
				users[userCount] = new Faculty(name);// Create Faculty Object
			}
			cout << "\nUser added with ID " << users[userCount]->userID << endl;
			userCount++;
		}
		else {
			cout << "\nUser limit has been reached!\n\n";
		}
	}

	void listUsers() {
		for (int i = 0; i < userCount; i++) {
			cout << "User " << users[i]->userID << ": " << users[i]->name << "\n";
		}
	}

	// All manage transaction functions, check in and out
	void checkoutBook(int bookIndex, int userIndex) {
		if (bookIndex >= 0 && bookIndex < bookCount && userIndex >= 0 && userIndex < userCount) {
			if (books[bookIndex].available) {
				books[bookIndex].available = false;
				users[userIndex]->borrowedBooks[users[userIndex]->borrowedCount++] = bookIndex;
				cout << "Book checked out successfully!\n";
			}
			else {
				cout << "Book is already checked out!\n";
			}
		}
		else {
			cout << "Invalid book or user index!\n";
		}
	}

	void checkInBook(int bookIndex) {
		if (bookIndex >= 0 && bookIndex < bookCount) {
			books[bookIndex].available = true;
			cout << "Book checked in successfully!\n";
		}
		else {
			cout << "Invalid book index!\n";
		}
	}
};

Library* Library::instance = nullptr;

//Main Function
int main() {
	Library* library = Library::getInstance();
	int choice;
	do {
		cout << "Welcome to the Library:\n1. Manage Books\n2. Manage Users\n3. Manage Transactions\n4. Exit\n\nEnter your choice: ";
		cin >> choice;
		cin.ignore();
		if (choice == 1) {
			int bookChoice;
			do {
				cout << "> Manage Books:\n> 1. Add a Book\n> 2. Edit a Book\n> 3. Remove a Book\n> 4. List All Books\n> 5. Go Back\n\n> Enter your choice: ";
				cin >> bookChoice;
				cin.ignore();
				if (bookChoice == 1) {
					string title, author, isbn;
					cout << "Enter Title: ";
					getline(cin, title);
					cout << "Enter Author: ";
					getline(cin, author);
					cout << "Enter ISBN: ";
					getline(cin, isbn);
					library->addBook(title, author, isbn);
				}
				else if (bookChoice == 2) {
					int index;
					string title, author, isbn;
					cout << "Enter book index to edit: ";
					cin >> index;
					cin.ignore();
					cout << "Enter new Title: ";
					getline(cin, title);
					cout << "Enter new Author: ";
					getline(cin, author);
					cout << "Enter new ISBN: ";
					getline(cin, isbn);
					library->editBook(index - 1, title, author, isbn);
				}
				else if (bookChoice == 3) {
					int index;
					cout << "Enter book index to remove: ";
					cin >> index;
					cin.ignore();
					library->removeBook(index - 1);
				}
				else if (bookChoice == 4) {
					library->listBooks();
				}
			} while (bookChoice != 5);
		}
		else if (choice == 2) {
			int userChoice;
			do {
				cout << "> Manage Users:\n> 1. Add a User\n> 2. List All Users\n> 3. Go Back\n\n> Enter your choice: ";
				cin >> userChoice;
				cin.ignore();
				if (userChoice == 1) {
					int type;
					string name;
					cout << "Enter 1 for Student or 2 for Faculty: ";
					cin >> type;
					cin.ignore();
					cout << "Enter Name: ";
					getline(cin, name);
					library->addUser(type, name);
				}
				else if (userChoice == 2) {
					library->listUsers();
				}
			} while (userChoice != 3);
		}else if (choice == 3) {
			int transChoice;
			do {
				cout << "> Manage Transactions:\n> 1. Check Out A Book\n> 2. Check In A Book\n> 3. List All Books\n> 4. List All Users\n> 5. Go Back\n\n> Enter your choice: ";
				cin >> transChoice;
				cin.ignore();
				if (transChoice == 1) {
					int bookIndex, userIndex;
					cout << "Enter Book Index: ";
					cin >> bookIndex;
					cout << "Enter User Index: ";
					cin >> userIndex;
					cin.ignore();
					library->checkoutBook(bookIndex - 1, userIndex - 1);
				}
				else if (transChoice == 2) {
					int bookIndex;
					cout << "Enter Book Index to check in: ";
					cin >> bookIndex;
					cin.ignore();
					library->checkInBook(bookIndex - 1);
				}
				else if (transChoice == 3) {
					library->listBooks();
				}
				else if (transChoice == 4) {
					library->listUsers();
				}
			} while (transChoice != 5);
		}
	} while (choice != 4);
	cout << "Thank you for using the Library System!\n";
	return 0;
}
