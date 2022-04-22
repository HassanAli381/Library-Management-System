#include <bits/stdc++.h>

using namespace std;

int rand_id = 100;
set <int> ids;
map <string , vector<string> > books_boorwed;
void cin_fail() {
    cout << "Invalid Number\n";
    cin.clear();
    cin.ignore(10000000, '\n');
}
struct user {
    int id;
    string name;
};

struct book {
    int id, quantity;
    string name;
};

bool sort_book_by_name(book &b1, book &b2)
{
    return (b1.name < b2.name);
}
bool sort_book_by_id(book &b1, book &b2) {
    return (b1.id < b2.id);
}

bool sort_users_by_name(user &u1, user &u2) {
    return (u1.name < u2.name);
}
struct library_system {
    vector <user> v_user;
    vector <book> v_book;

    void run_program() {
        while(true) {
            int choise = show_list();

            /// Add Book
            if(choise == 1) {
                cout << "Enter id and name and quantity of book\n";
                int b_id = 0, b_quantity = 1;
                cout << "Id= ";
                cin >> b_id;
                if(cin.fail() || !b_id) {
                    cin_fail();
                    cout << "Id= ";
                    cin >> b_id;
                }
                else {
                    auto it = ids.find(b_id);
                    if(it == ids.end())
                    {
                        ids.insert(b_id);
                    }
                    else {
                        cout << "Id Should be unique\n";
                        while(true) {
                            cout << "Id= ";
                            cin >> b_id;
                            auto it = ids.find(b_id);
                            if(it==ids.end())
                            {
                                ids.insert(b_id);
                                break;
                            }
                            else
                            {
                                cout << "Id Should be unique\n";
                            }
                        }
                    }
                }

                cout << "Name= ";
                string b_name; cin >> b_name;
                cout << "Quantity= ";
                cin >> b_quantity;
                if(cin.fail() || b_quantity == 0) {
                    cin_fail();
                    cout << "Quantity= ";
                    cin >> b_quantity;
                }
                book b1;
                b1.id = b_id;
                b1.name = b_name;
                b1.quantity = b_quantity;
                v_book.emplace_back(b1);
            }

            /// Search Book by Prefix
            else if(choise == 2) {
                string searched_prefix;
                cout << "Enter Word to search for: ";
                cin >> searched_prefix;
                map <char, int> frq_of_searchedword;
                int word_size = searched_prefix.size();
                for(int i = 0;i < word_size; ++i)
                {
                    if(searched_prefix[i] >= 'A' && searched_prefix[i] <= 'Z') {
                        frq_of_searchedword[ searched_prefix[i] ]++;
                        frq_of_searchedword[ searched_prefix[i] + 32 ]++;
                    }
                    else {
                        frq_of_searchedword[ searched_prefix[i] ]++;
                        frq_of_searchedword[ searched_prefix[i] - 32 ]++;
                    }
                }
                vector <pair<int, string>> search_results;
                int books_size = v_book.size();
                for(int i = 0; i < books_size; ++i)
                {
                    int word_size = v_book[i].name.size(), frequency = 0;
                    bool add = 0;
                    for(int j = 0; j < word_size; ++j) {
                        char current = v_book[i].name[j];
                        if(frq_of_searchedword[current]) {
                            add = 1;
                            ++frequency;
                            break;
                        }
                    }
                    if(add) {
                        search_results.emplace_back(make_pair(frequency, v_book[i].name));
                    }
                }
                cout << "Search Results:\n";
                if(search_results.size() == 0) {
                    cout << "No Results Found\n";
                    continue;
                }
                sort(search_results.rbegin(), search_results.rend());
                for(auto word : search_results)
                    cout << word.second << '\n';
            }


            /// Print Users who Borrowd Book by name
            else if(choise == 3) {
                string book_name;
                cout << "Book Name : ";
                cin >> book_name;
                sort(v_book.begin(), v_book.end(), sort_book_by_name);
                bool check_book  = 0;
                for(auto elem : books_boorwed) {
                    if(elem.first == book_name)
                    {
                        check_book = 1;
                        break;
                    }
                }
                if(check_book) {
                    cout << "Users Borrowed " << book_name << " : " << endl;
                    for(auto usr_nm : books_boorwed[book_name]) {
                        cout << usr_nm << endl;
                    }
                }
                else {
                    cout << "NO Users found\n";
                }
            }


            /// print Library Books by Name
            else if(choise == 4) {
                int books_size = v_book.size();
                if(!books_size) {
                    cout << "Library is empty Go and Add some Books\n";
                    continue;
                }
                sort(v_book.begin(), v_book.end(), sort_book_by_name);
                cout << "-----------All Books We have Sorted By Name--------------\n";
                cout << "ID\t" << "Name\t" << "Quantity\n";
                for(int i = 0; i < books_size; ++i) {
                    cout << v_book[i].id << '\t' << v_book[i].name << '\t' << v_book[i].quantity << endl;
                }
                cout << "-------------------------------------------------------\n";
            }


            /// print Library Books by Id
            else if(choise == 5) {
                int books_size = v_book.size();
                if(!books_size) {
                    cout << "Library is empty Go and Add some Books\n";
                    continue;
                }
                sort(v_book.begin(), v_book.end(), sort_book_by_id);
                cout << "-----------All Books We have Sorted By Id--------------\n";
                cout << "ID\t" << "Name\t" << "Quantity\n";
                for(int i = 0; i < books_size; ++i) {
                    cout << v_book[i].id << '\t' << v_book[i].name << '\t' << v_book[i].quantity << endl;
                }
                cout << "-------------------------------------------------------\n";
            }

            /// Add User
            else if(choise == 6) {
                string user_name;
                cout << "Name: ";
                cin >> user_name;
                v_user.push_back( {rand_id+100 , user_name} );
                ++rand_id;
                cout << "User Added Successfully\n";
            }

            /// User borrow book
            else if(choise == 7)
            {
                string user_name;
                cout << "Your Name: ";
                cin >> user_name;
                v_user.push_back({rand_id+100 , user_name});
                ++rand_id;
                string book_name;
                cout << "Book name: ";
                cin >> book_name;

                int book_id;
                cout << "Book Id: \n";
                cin >> book_id;
                v_book.push_back( {book_id, rand_id++, book_name} );
                books_boorwed[user_name].emplace_back(book_name);
                cout << "Book Added Sucssefully\n";

            }

            ///User want to Return a Book
            else if(choise == 8) {
                string user_name;
                cout << "Your Name: ";
                cin >> user_name;
                bool it = books_boorwed.count(user_name);
                if(!it) {
                    cout << "NO Such User Found\n";
                }
                else {
                    string book_name;
                    cout << "Book name: ";
                    cin >> book_name;
                    int ind = 0;
                    bool found = 0;
                    for(auto nm : books_boorwed[user_name]) {
                        ++ind;
                        if(nm == book_name) {
                            found = 1;
                            books_boorwed[user_name].erase(books_boorwed[user_name].begin() + ind);
                            cout << "Book Returned Succssfully\n";
                        }
                    }
                    if(!found) {
                        cout << "NO Books Found\n";
                    }
                }

            }

            ///Print Users
            else if(choise == 9) {
                int users_size = v_user.size();
                if(users_size == 0) {
                    cout << "No Users Found Go and Add Users\n";
                    continue;
                }
                sort(v_user.begin(), v_user.end(), sort_users_by_name);
                cout << "-----------Users Sorted By name--------------\n";
                for(int i = 0; i < users_size; ++i) {
                    cout << v_user[i].name << endl;
                }
                cout << "---------------------------------------------\n";
            }
            /// Exit
            else if(choise == 10) {
                v_user.clear();
                v_book.clear();
                cout << "*************************\n";
                cout << "*Developed By Hassan Ali*\n";
                cout << "*   See You Soon ^^\t*\n";
                cout << "*************************\n";
                return ;
            }
        }
    }
    int show_list() {
        int choise = 0;
        while(!choise) {
            cout << "*******************************\n";
            cout << "*Choose one of the Menu\n";
            cout << "1- Add Book \n";
            cout << "2- Search Book by name\n";
            cout << "3- print Users who Borrowd Book by name\n";
            cout << "4- print Library Books by name\n";
            cout << "5- print Library Books by Id\n";
            cout << "6- Add User\n";
            cout << "7- User Want to Borrow a Book\n";
            cout << "8- User Want to Return a Book\n";
            cout << "9- Print Users\n";
            cout << "10- Exit\n";
            cout << "*******************************\n";
            cout << "Choise= ";
            cin >> choise;
            if(cin.fail()) {
                cin_fail();
                cout << "Choise= ";
                cin >> choise;
            }
            if(choise > 10 || choise < 1) {
                cout << "Invalid Choise\n";
                choise = 0;
            }
            else {
                return choise;
            }
        }
    }

};
int main()
{
    library_system library;
    library.run_program();

    return 0;
}
