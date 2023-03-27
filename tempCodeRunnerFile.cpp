void loginPage()
{
    clear();
    string title = "LOG IN";
    string username;
    string password;
    int box_size = 20;

    
    GoTo(0, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(4, (WinColumn - 10 - box_size) / 2);
    cout << "Username: ";
    drawCell(" ", 3, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", 6, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);
}