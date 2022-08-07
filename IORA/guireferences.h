#ifndef GUIREFERENCES_H
#define GUIREFERENCES_H

class MainWindow;
class registerPage;
class ForgotPsw;
class mainApp;
class Dashboard;
class Channels;
class CcreateNewChannel;
class Chat;
class Calendar;

class GUIReferences
{
public:
    MainWindow* mainWindow;
    // continua aici
    // get / set pentru fiecare

private:
    GUIReferences();
    GUIReferences(const GUIReferences& ref);
    ~GUIReferences();
};

#endif // GUIREFERENCES_H
