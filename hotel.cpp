#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Declare functions
void services(), report(), foodAndDrink(), hotelService();

// Rooms Variables
list<int> rooms = { 101, 101, 103, 104, 105, 106, 107, 108, 109, 110, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310 };
int choose_room;

// Report Variables
string report_description;

// Food and Drink Variables
// Struct (Structure) or you can say Model of MenuInfo
struct MenuInfo {
    string id;
    string nama;
    string type;
    double harga;
};

// Struct (Structure) or you can say Model of CartMenu
struct CartMenu {

    string id;
    int total;
};
list<MenuInfo> menus = {};
list<CartMenu> cart_menus = {};

// Hotel Service Variables
// Struct (Structure) or you can say Model of ServiceInfo
struct ServiceInfo {
    string id;
    string nama;
    string type;
    double harga;
};

// Struct (Structure) or you can say Model of CartService
struct CartService {
    string id;
    int total;
};
list<ServiceInfo> menu_services = {
    { "1", "Laundry Kiloan", "Kilogram", 15000 },
    { "2", "Laundry Satuan", "Item", 15000 },
    { "3", "Fitness GYM", "Hour", 50000 },
    { "4", "Pijat", "Hour", 100000 },
    { "5", "Antar Jemput", "Kilometer", 10000 },
};
list<CartService> cart_services = {};

void hotelService()
{
    string pilih;
    int total;
    int currentPage = 1;
    int perpage = 10;
menu:
    int count = 0;
    double maxPage = static_cast<double>(menu_services.size()) / static_cast<double>(perpage);
    cout << "Page " << currentPage << " of " << static_cast<int>(std::ceil(maxPage)) << endl;
    cout << "/====================================================================================="
            "============\\"
         << endl;
    cout << "|" << std::setw(5) << "id" << std::setw(5) << "|" << std::setw(21) << "Name Service" << std::setw(21) << "|" << std::setw(10) << "Each Type" << std::setw(10) << "|" << std::setw(15)
         << "Price per Each" << std::setw(10) << "|" << endl;
    cout << "|====================================================================================="
            "============|"
         << endl;

    for (const auto& row : menu_services) {
        count++;
        if (count <= (currentPage - 1) * perpage) {
            continue;
        } else if (count > (currentPage)*perpage) {
            break;
        }
        cout << "|" << std::setw(5) << row.id << std::setw(5) << "|" << std::setw(21) << row.nama << std::setw(21) << "|" << std::setw(10) << row.type << std::setw(10) << "|" << std::setw(13)
             << "Rp." + std::to_string(static_cast<int>(row.harga)) << std::setw(13) << "|" << endl;
    }
    cout << "\\===================================================================================="
            "=============/\n"
         << endl;

    cout << "Choose to interact" << endl;
    cout << "<id> = Select Services | < = Previous Page | > = Next Page | V = Done | B = Back to "
            "Service | X = Exit & Cancel Orders"
         << endl;

    cin >> pilih;
    system("cls");

    auto select_service = std::find_if(menu_services.begin(), menu_services.end(), [pilih](const ServiceInfo& element) { return element.id == pilih; });

    auto check_cart = std::find_if(cart_services.begin(), cart_services.end(), [pilih](const CartService& element) { return element.id == pilih; });

    if (select_service != menu_services.end()) {
        if (check_cart != cart_services.end()) {
        edit_menu:
            cout << "You already had order ( " << check_cart->total << " | " << select_service->nama << ")" << endl;
            cout << "Do you want to change total of the value? (Y/N)" << endl;
            cin >> pilih;
            if (pilih == "Y" || pilih == "y") {
                cout << "Okay, how much do you want to change it?" << endl;
                cin >> total;
                int old_total = check_cart->total;
                check_cart->total = total;
                cout << "You have been change the total " << old_total << " to " << total << endl;
            } else if (pilih == "N" || pilih == "n") {
                cout << "Okay, is that so!" << endl;
            } else {
                cout << "Invalid input" << endl;
                goto edit_menu;
            }
            goto menu;
        }
        cout << "How much do you want? (1-99)" << endl;
        cin >> total;
        cart_services.push_back({ select_service->id, total });
        system("cls");
        goto menu;
    } else if (pilih == "v" || pilih == "V") {
    
    } else if (pilih == ">") {
        if (currentPage >= maxPage) {
            cout << "You cant go any further" << endl;
            goto menu;
        }
        cout << "Move to next page" << endl;
        currentPage++;
        goto menu;
    } else if (pilih == "<") {
        if (currentPage <= 1) {
            cout << "You cant go back any further" << endl;
            goto menu;
        }
        cout << "Move to previous page" << endl;
        currentPage--;
        goto menu;
    } else if (pilih == "b" || pilih == "B") {
        cout << "Back to view services!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        services();
    } else if (pilih == "x" || pilih == "X") {
        cout << "You have been canceled the orders!!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cout << "Invalid input!!" << endl;
        goto menu;
    }
}

void foodAndDrink()
{
    string pilih;
    int total;
    int currentPage = 1;
    int perpage = 10;
menu:
    int count = 0;
    double maxPage = static_cast<double>(menus.size()) / static_cast<double>(perpage);
    cout << "Page " << currentPage << " of " << static_cast<int>(std::ceil(maxPage)) << endl;
    cout << "/====================================================================================="
            "============\\"
         << endl;
    cout << "|" << std::setw(5) << "id" << std::setw(5) << "|" << std::setw(21) << "Name Menu" << std::setw(21) << "|" << std::setw(10) << "Type" << std::setw(10) << "|" << std::setw(13) << "Price"
         << std::setw(13) << "|" << endl;
    cout << "|====================================================================================="
            "============|"
         << endl;

    for (const auto& row : menus) {
        count++;
        if (count <= (currentPage - 1) * perpage) {
            continue;
        } else if (count > (currentPage)*perpage) {
            break;
        }
        cout << "|" << std::setw(5) << row.id << std::setw(5) << "|" << std::setw(21) << row.nama << std::setw(21) << "|" << std::setw(10) << row.type << std::setw(10) << "|" << std::setw(13)
             << "Rp." + std::to_string(static_cast<int>(row.harga)) << std::setw(13) << "|" << endl;
    }
    cout << "\\===================================================================================="
            "=============/\n"
         << endl;

    cout << "Choose to interact" << endl;
    cout << "<id> = Select Menus | < = Previous Page | > = Next Page | V = Done | B = Back to "
            "Service | X = Exit & Cancel Orders"
         << endl;

    cin >> pilih;
    system("cls");

    auto select_menu = std::find_if(menus.begin(), menus.end(), [pilih](const MenuInfo& element) { return element.id == pilih; });

    auto check_cart = std::find_if(cart_menus.begin(), cart_menus.end(), [pilih](const CartMenu& element) { return element.id == pilih; });

    if (select_menu != menus.end()) {
        if (check_cart != cart_menus.end()) {
        edit_menu:
            cout << "You already had order ( " << check_cart->total << " | " << select_menu->nama << ")" << endl;
            cout << "Do you want to change total of the value? (Y/N)" << endl;
            cin >> pilih;
            if (pilih == "Y" || pilih == "y") {
                cout << "Okay, how much do you want to change it?" << endl;
                cin >> total;
                int old_total = check_cart->total;
                check_cart->total = total;
                cout << "You have been change the total " << old_total << " to " << total << endl;
            } else if (pilih == "N" || pilih == "n") {
                cout << "Okay, is that so!" << endl;
            } else {
                cout << "Invalid input" << endl;
                goto edit_menu;
            }
            goto menu;
        }
        cout << "How much do you want? (1-99)" << endl;
        cin >> total;
        cart_menus.push_back({ select_menu->id, total });
        system("cls");
        goto menu;
    } else if (pilih == "v" || pilih == "V") {
    list_order:
        double subTotalServices = 0;
        double subTotalFoodDrinks = 0;
        cout << "Here's your total order!!" << endl << endl;
        // Cart Food and Drinks
        if (cart_menus.size() > 0) {

            cout << "Cart Food and Drinks : " << endl;
            cout << "/============================================================================="
                    "==========================================\\"
                 << endl;
            cout << "|" << std::setw(5) << "id" << std::setw(5) << "|" << std::setw(21) << "Name Menu" << std::setw(21) << "|" << std::setw(10) << "Type" << std::setw(10) << "|" << std::setw(14)
                 << "Price per Each" << std::setw(7) << "|" << std::setw(10) << "Total Item" << std::setw(10) << "|" << std::setw(13) << "Total" << std::setw(13) << "|" << endl;
            cout << "|============================================================================="
                    "==========================================|"
                 << endl;
            for (const auto& cart : cart_menus) {
                string id = cart.id;
                auto cart_menu = std::find_if(menus.begin(), menus.end(), [id](const MenuInfo& element) { return element.id == id; });

                if (cart_menu != menus.end()) {
                    cout << "|" << std::setw(5) << cart_menu->id << std::setw(5) << "|" << std::setw(21) << cart_menu->nama << std::setw(21) << "|" << std::setw(10) << cart_menu->type << std::setw(10)
                         << "|" << std::setw(11) << "Rp." + std::to_string(static_cast<int>(cart_menu->harga)) << std::setw(11) << "|" << std::setw(10) << std::to_string(static_cast<int>(cart.total))
                         << std::setw(10) << "|" << std::setw(13) << "Rp." + std::to_string(static_cast<int>(cart.total * cart_menu->harga)) << std::setw(13) << "|" << endl;

                    subTotalFoodDrinks += cart.total * cart_menu->harga;
                }
            }
            cout << "|============================================================================="
                    "==========================================|"
                 << endl;
            cout << "|" << std::setw(36) << "Subtotal" << std::setw(36) << "|" << std::setw(24) << "Rp." + std::to_string(static_cast<int>(subTotalFoodDrinks)) << std::setw(24) << "|" << endl;
            cout << "\\============================================================================"
                    "===========================================/\n"
                 << endl;
        }
        if (cart_services.size() > 0) {
            // Cart Services

            cout << "Cart Services : " << endl;
            cout << "/============================================================================="
                    "==========================================\\"
                 << endl;
            cout << "|" << std::setw(5) << "id" << std::setw(5) << "|" << std::setw(21) << "Name Menu" << std::setw(21) << "|" << std::setw(10) << "Type" << std::setw(10) << "|" << std::setw(14)
                 << "Price per Each" << std::setw(7) << "|" << std::setw(10) << "Total Item" << std::setw(10) << "|" << std::setw(13) << "Total" << std::setw(13) << "|" << endl;
            cout << "|============================================================================="
                    "==========================================|"
                 << endl;
            for (const auto& cart : cart_services) {
                string id = cart.id;
                auto cart_service = std::find_if(menu_services.begin(), menu_services.end(), [id](const ServiceInfo& element) { return element.id == id; });

                if (cart_service != menu_services.end()) {
                    cout << "|" << std::setw(5) << cart_service->id << std::setw(5) << "|" << std::setw(21) << cart_service->nama << std::setw(21) << "|" << std::setw(10) << cart_service->type
                         << std::setw(10) << "|" << std::setw(11) << "Rp." + std::to_string(static_cast<int>(cart_service->harga)) << std::setw(11) << "|" << std::setw(10)
                         << std::to_string(static_cast<int>(cart.total)) << std::setw(10) << "|"
                         << "|" << std::setw(13) << "Rp." + std::to_string(static_cast<int>(cart.total * cart_service->harga)) << std::setw(13) << "|" << endl;

                    subTotalServices += cart.total * cart_service->harga;
                }
            }
            cout << "|============================================================================="
                    "==========================================|"
                 << endl;
            cout << "|" << std::setw(36) << "Subtotal" << std::setw(36) << "|" << std::setw(24) << "Rp." + std::to_string(static_cast<int>(subTotalServices)) << std::setw(24) << "|" << endl;
            cout << "\\============================================================================"
                    "===========================================/\n"
                 << endl;
        }
        cout << "/================================================================================="
                "======================================\\"
             << endl;
        cout << "|" << std::setw(36) << "All Total" << std::setw(36) << "|" << std::setw(24) << "Rp." + std::to_string(static_cast<int>(subTotalFoodDrinks + subTotalServices)) << std::setw(24) << "|"
             << endl;
        cout << "\\================================================================================"
                "=======================================/\n"
             << endl;

        if (report_description != "") {
            cout << "Report Meessage: " << endl;
            cout << "/============================================================================="
                    "==========================================\\"
                 << endl;
            cout << "|" << std::setw(60) << report_description << std::setw(60) << "|" << endl;
            cout << "\\============================================================================"
                    "===========================================/\n"
                 << endl;
        }
        cout << "Are you finish ordering? (Y/N)" << endl;

        cin >> pilih;
        if (pilih == "y" || pilih == "Y") {
            cout << "Thankyou for purchasing our service!!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPress any enter to close..." << endl;
            cin.get();
        } else if (pilih == "n" || pilih == "N") {
            cout << "Sure freely to look around first" << endl;
            system("cls");
            goto menu;
        } else {
            cout << "Invalid Input!!";
            system("cls");
            goto list_order;
        }
    } else if (pilih == ">") {
        if (currentPage >= maxPage) {
            cout << "You cant go any further" << endl;
            goto menu;
        }
        cout << "Move to next page" << endl;
        currentPage++;
        goto menu;
    } else if (pilih == "<") {
        if (currentPage <= 1) {
            cout << "You cant go back any further" << endl;
            goto menu;
        }
        cout << "Move to previous page" << endl;
        currentPage--;
        goto menu;
    } else if (pilih == "b" || pilih == "B") {
        cout << "Back to view services!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        services();
    } else if (pilih == "x" || pilih == "X") {
        cout << "You have been canceled the orders!!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cout << "Invalid input!!" << endl;
        goto menu;
    }
}
void report()
{
    string input_report;
report_menu:
    int select_report;
    string yes_no_report;
    cout << "/========================================\\" << endl;
    cout << "|                 Reports                |" << endl;
    cout << "|                                        |" << endl;
    cout << "|  1. View Report                        |" << endl;
    cout << "|  2. Input Report                       |" << endl;
    cout << "|  3. Finish Report (Just Report)        |" << endl;
    cout << "|  4. Finish & Back (With an ordering)   |" << endl;
    cout << "|                                        |" << endl;
    cout << "\\========================================/" << endl;
    cout << "\nSelect number to continue : " << endl;

    cin >> select_report;

    switch (select_report) {
    case 1:
        system("cls");
        if (report_description != "") {
            cout << "Your Report Message : " << endl;
            cout << report_description << endl;
        } else {
            cout << "You don't have any report" << endl;
        }
        goto report_menu;
        break;
    case 2:
        system("cls");
        cout << "What do you want to report?" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        char input[1000]; // Adjust the size as per your requirement
        cin.getline(input, sizeof(input));
        cout << "Your Report Message : " << endl;
        cout << input << endl;
        report_description = input;

        goto report_menu;
        break;
    case 3:
        system("cls");
        cout << "Do you finish? (Y/N)" << endl;
        cin >> yes_no_report;

        if (yes_no_report == "Y" || yes_no_report == "y") {
            cout << "Thank you for reporting\n" << endl;
            cout << "Recap of your report : " << endl;
            cout << report_description << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto report_menu;
        }
        break;
    case 4:
        system("cls");
        cout << "Do you finish? (Y/N)" << endl;
        cin >> yes_no_report;

        if (yes_no_report == "Y" || yes_no_report == "y") {
            cout << "Thank you for reporting\n" << endl;
            cout << "Recap of your report : " << endl;
            cout << report_description << endl;
            services();
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto report_menu;
        }
        break;

    default:
        cout << "Invalid input" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto report_menu;
        break;
    }
}

void services()
{
select_service:
    int select_service;
    cout << "/==============================\\" << endl;
    cout << "|  List of our Hotel Services  |" << endl;
    cout << "|                              |" << endl;
    cout << "|  1. Food and Drinks          |" << endl;
    cout << "|  2. Hotel Services           |" << endl;
    cout << "|  3. Report                   |" << endl;
    cout << "|                              |" << endl;
    cout << "\\==============================/" << endl;

    cout << "\nSelect services by numbers" << endl;
    cin >> select_service;

    switch (select_service) {
    case 1:
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        foodAndDrink();
        break;
    case 2:
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        hotelService();
        break;
    case 3:
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        report();
        break;

    default:
        system("cls");
        cout << "Invalid input" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto select_service;
        break;
    }
}

int main()
{
// Data Statis Rooms
room_menu:
    int index_room = 1;
    cout << "List of hotel room numbers: " << endl;
    cout << "/===========================================================\\" << endl;
    for (int roomNumber : rooms) {
        cout << "| " << roomNumber << " ";
        if (index_room % 10 == 0) {
            cout << "|" << endl;
            if (index_room >= rooms.size()) {
                cout << "\\===========================================================/" << endl;
            } else {
                cout << "|=====|=====|=====|=====|=====|=====|=====|=====|=====|=====|" << endl;
            }
        }

        index_room += 1;
    }
    cout << "Choose a hotel room : " << endl;
    cin >> choose_room;

    auto check_room = find(rooms.begin(), rooms.end(), choose_room);
    if (check_room != rooms.end()) {
        system("cls");
        cout << "Room " << choose_room << " is available." << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        services();
    } else {
        system("cls");
        cout << "Room " << choose_room << " is not available." << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto room_menu;
    }
}