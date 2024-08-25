#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define path "data_regst.txt"
#define path_book "data_book.txt"
bool test_regst = false;
bool Book_List1_bool = false;
bool Borrow_a_Book_bool = false;
bool Add_a_Book_bool = false;
bool Return_a_Book_bool = false;
bool test_User_name_password_is_wrong=true;
string U;
enum class regst
{
    log_in = 1,
    sin_up = 2
};
enum class B
{
    Book_List = 1,
    Borrow_a_Book = 2,
    Add_a_Book = 3,
    Return_a_Book = 4,
    logout = 5,
    Exit = 6
};
class yahai;
class alkashaf_poly
{
public:
    
    virtual int print_font_regst()=0;
    virtual int print_font2_regst()=0;
};
class library
{
public:
    void print_front()
    {
        cout <<"       Holle : "
             <<U<<"\n"
             << "         Minue: \n"
             <<"      Book List (1)\n"
             << "     Borrow a Book (2)\n"
             << "     Add a Book (3)\n"
             << "     Return a Book (4)\n"
             << "     logout (5)\n"
             << "     Exit (6)\n"
             <<"     Enter Number from 1 to 6\n";
    }
};
class register_class : public library
{

public:
    library obj1;
    void user(string password, string name, string path1)
    {
        ofstream user_name(path1, ios::out | ios::app);
        if (user_name.is_open())
        {
            user_name << name << " ";
            U=name;
            try
            {
                if (password.size() < 8)
                {
                    throw "The password should  contain 8 number largest";
                }
                if (password.find(' ') != string::npos)
                {
                    throw "The password should not contain spaces";
                }
                user_name << password << endl;
                user_name.close();
                cout << "sin up is true\n";
                test_regst = true;
                obj1.print_front();
            }
            catch (char const *x)
            {

                for (int i = 0; i < 46; i++)
                {
                    cerr << x[i];
                }
                cout << '\n';
            }

            catch (char const *x)
            {

                for (int i = 0; i < 30; i++)
                {
                    cerr << x[i];
                }
                cout << '\n';
            }
            user_name.close();
        }
        else
        {
            cout << "Failed to open the file for writing." << endl;
        }
    }
    //===============================================
    void chack(string &password, string &username, string fileName)
    {
        ifstream user_name(fileName);
        if (!user_name.is_open())
        {
            cout << " error ";
            return;
        }
        string line, line1, line2;
            bool test_User_name_password=false;
        while (getline(user_name, line))
        {
            int pos = line.find_last_of(' ');
            line1 = line.substr(0, pos);
            line2 = line.substr(pos + 1);
            if (username == line1)
            {
                U=line1;
                if (password == line2)
                {
                    test_User_name_password=true;
                    user_name.close();
                    cout << "login is true\n";
                    test_regst = true;
                    obj1.print_front();
                }
            }
            }
            if(!test_User_name_password)
            {

                cout << "Username or Password is wrong\n";
                test_User_name_password_is_wrong=false;
            }
        
        user_name.close();
    }
};
class books
{
public:
    void Book_List1(string file_name)
    {
        ifstream Book_list2(file_name);
        string line;
        if (!Book_list2.is_open())
        {
            cout << "book list is imbity\n";
            return;
        }
        string Book_Title1, Author1, Property;
        int t = 1;
        while (getline(Book_list2, Book_Title1) && getline(Book_list2, Author1) && getline(Book_list2, Property))
        {
            cout << "\nnumber book " << (t++) << "\n\nBook Title : " << Book_Title1 << "\n";
            cout << "Author : " << Author1 << "\n";
            cout << "Book status : " << Property << "\n";
            cout << "*********\n";
        }
        Book_List1_bool = true;
    }
    void Book_List2_borrowed(string file_name)
    {
        ifstream Book_list2(file_name);
        string line;
        if (!Book_list2.is_open())
        {
            cout << "book list is imbity\n";
            return;
        }
        string Book_Title1, Author1, Property;
        int t = 1;
        while (getline(Book_list2, Book_Title1) && getline(Book_list2, Author1) && getline(Book_list2, Property))
        {
            if (Property == "Property")
            {
                t++;
                continue;
            }

            cout << "\nnumber book " << (t++) << "\n\nBook Title : " << Book_Title1 << "\n";
            cout << "Author : " << Author1 << "\n";
            cout << "Book status : " << Property << "\n";
            cout << "*********\n";
        }
    }
    void add_books(string file_name, string &Book_Title, string &Author)
    {
        ofstream file_book_list(file_name, ios::out | ios::app);
        if (!file_book_list.is_open())
        {
            cout << "error tec try again\n";
        }
        string stat1;
        stat1 = "Property";
        file_book_list << Book_Title << "\n"
                       << Author << "\n"
                       << stat1 << "\n";
        cout << "The book has been successfully added.\n";
        Add_a_Book_bool = true;
    }
    void Borrow_a_Books(string file_name, int &num4)
    {
        ifstream borrow_file(file_name);
        if (!borrow_file.is_open())
        {
            cout << "error tec try again\n";
            return;
        }
        vector<string> lines;
        int c1 = 1;
        string w;
        bool borro = false, test = false;
        while (getline(borrow_file, w))
        {
            if (c1 != num4)
            {
                lines.push_back(w);
            }
            else
            {
                test = true;
                if (w == "borrowed")
                {
                    cout << "The book you want to borrow is already borrowed \n";
                }
                else
                {
                    lines.push_back("borrowed");
                    borro = true;
                }
            }
            c1++;
        }
        if (!test)
        {
            cout << "please book number is wrong \n";
            return;
        }
        ofstream out_borrow_file(file_name);
        for (const string &l : lines)
        {
            out_borrow_file << l << "\n";
        }
        if (borro)
        {
            cout << "The borrowing has been successfully recorded. Don't forget to return the book on time\n";
            Borrow_a_Book_bool = true;
        }
    }
    void return_a_Books(string file_name, int &num4)
    {
        ifstream borrow_file(file_name);
        if (!borrow_file.is_open())
        {
            cout << "error tec try again\n";
            return;
        }
        vector<string> lines;
        int c1 = 1;
        string w;
        bool borro = false;
        bool test = false;
        while (getline(borrow_file, w))
        {
            if (c1 != num4)
            {
                lines.push_back(w);
            }
            else
            {
                test = true;
                if (w == "Property")
                {
                    cout << "The book you want to return is already returned \n";
                }
                else
                {
                    lines.push_back("Property");
                    borro = true;
                }
            }
            c1++;
        }
        if (!test)
        {
            cout << "please book number is wrong \n";
            return;
        }

        ofstream out_borrow_file(file_name);
        for (const string &l : lines)
        {
            out_borrow_file << l << "\n";
        }
        if (borro)
        {
            cout << "The returning  has been successfully recorded.\n";
            Return_a_Book_bool = true;
        }
    }
};
class yahai : public library, public books,public alkashaf_poly
{
public:

    int print_font_regst()
    {
        ofstream file(path_book);
        file << "oop with c++ " << "\n"
             << "yahai alkashaf" << "\n"
             << "Property" << "\n";
        file << "data structure with c++" << "\n"
             << "Eng yahai" << "\n"
             << "Property" << "\n";
        register_class obregst;
        string name;
        string password;
        int opti;
        cout << "Holle  in yahai libarary\n   log in (1) \n   sin up (2) \n  Enter number from 1 to 2 : \n";
        cin >> opti;
        if (opti == (int)regst::log_in)
        {
            cout << "Enter your Name\n";
            std::cin >> std::ws;
            getline(cin, name);
            cout << "Enter password\n";
            std::cin >> std::ws;
            getline(cin, password);
            obregst.chack(password, name, path);
            if (!test_User_name_password_is_wrong)
            {
               print_font_regst();
            }
            
        }
        else if (opti == (int)regst::sin_up)
        {
            cout << "Enter your Name\n";
            std::cin >> std::ws;
            getline(cin, name);
            cout << "Enter password\n";
            std::cin >> std::ws;
            getline(cin, password);
            obregst.user(password, name, path);
        }
        else
        {
            cout << "Invalid option selected." << endl;
            cout << "\n\n\n    ";
                    print_font_regst();
                    print_font2_regst();
        }
        return 0;
    }
    int print_font2_regst()
    {
        if (test_regst)
        {
            int num2;
            cin >> num2;
            if (num2 == (int)B::Book_List)
            {
                books ob_booK_list;
                ob_booK_list.Book_List1(path_book);
                if (Book_List1_bool)
                {
                    cout << "\n\n\n    ";
                    print_front();
                    print_font2_regst();
                }
            }
            if (num2 == (int)B::Add_a_Book)
            {
                books ob_booK_list;
                cout << "Enter Book Title : \n";
                string book_title;
                std::cin >> std::ws;
                getline(cin, book_title);
                cout << "Enter Author : \n";
                string Author;
                std::cin >> std::ws;
                getline(cin, Author);
                ob_booK_list.add_books(path_book, book_title, Author);
                if (Add_a_Book_bool)
                {
                    cout << "\n\n\n    ";
                    print_front();
                    print_font2_regst();
                }
            }
            if (num2 == (int)B::Borrow_a_Book)
            {
                books ob_booK_list;
                cout << "Choose the book you want to borrow from the following list of books : \n";
                ob_booK_list.Book_List1(path_book);
                cout << "Enter Number book that you borrow : \n";
                int num4;
                cin >> num4;
                num4 += 2 * num4;
                ob_booK_list.Borrow_a_Books(path_book, num4);
                if (Borrow_a_Book_bool)
                {
                    cout << "\n\n\n    ";
                    print_front();
                    print_font2_regst();
                }
            }
            if (num2 == (int)B::Return_a_Book)
            {
                books ob_booK_list;
                cout << "Choose the book you want to returned from the following list of books borrowed : \n";
                ob_booK_list.Book_List2_borrowed(path_book);
                int num5;
                cin >> num5;
                num5 += 2 * num5;
                ob_booK_list.return_a_Books(path_book, num5);
                if (Return_a_Book_bool)
                {
                    cout << "\n\n\n    ";
                    print_front();
                    print_font2_regst();
                }
            }
            if (num2 == (int)B::logout)
            {
                print_font_regst();
                print_font2_regst();
            }
            if (num2 == (int)B::Exit)
            {
                return 0;
            }
        }
        return 0;
    }
};

int main()
{

    yahai obj2;
    alkashaf_poly *ob;
    ob=&obj2;
    ob->print_font_regst();
    ob->print_font2_regst();
}
