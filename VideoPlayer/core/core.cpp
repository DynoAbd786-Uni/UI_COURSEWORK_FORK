#include "core.h"
#include "application.h"
#include "mainwindow.h"

#include <QString>
#include <iostream>
#include <QDateTime>
#include <regex>
#include <QTranslator>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    #include <QRegularExpression>
#else
    #include <QRegExp>
#endif

/**
 * @author ...
 * @author Brent Edington
 * @author ...
*/

Core::Core(const CoreArgs& args)
{
    std::cout << "Path to assets: " << args.m_AssetsFolderPath << std::endl;
    // Set assets folder path
    m_AssetsPath = args.m_AssetsFolderPath;

    // Initialise user
    m_User = new User();
    m_User->SetUsername("Test");
    m_User->SetEmail("test@test.com");
    m_User->SetPassword("password");

    // Init user pool
    m_Users[0] = User();
    m_Users[0].SetUsername("Muhammad");
    m_Users[0].SetEmail("muhammad@example.com");

    m_Users[1] = User();
    m_Users[1].SetUsername("Gamer");
    m_Users[1].SetEmail("gamer@gamermail.com");

    m_Users[2] = User();
    m_Users[2].SetUsername("Sarah");
    m_Users[2].SetEmail("sarah@example2.com");

    m_Users[3] = User();
    m_Users[3].SetUsername("Mustafa");
    m_Users[3].SetEmail("my@example.com");

    m_Users[4] = User();
    m_Users[4].SetUsername("Oliver");
    m_Users[4].SetEmail("olly@yandex.ru");

    // Add friends to user
    m_User->AddFriend(&m_Users[0]);
    m_User->AddFriend(&m_Users[1]);
    m_User->AddFriend(&m_Users[2]);
    m_User->AddFriend(&m_Users[3]);
    m_User->AddFriend(&m_Users[4]);

    // Initialise video player
#ifdef _WIN32
    m_VideoDB = new VideoDB(m_AssetsPath.append("\\videos"));
#else
    m_VideoDB = new VideoDB(m_AssetsPath.append("/videos"));
#endif

    // Initialise settings
    m_Settings = new Settings();
}

Core::~Core()
{
    delete m_User;
    delete m_VideoDB;
    delete m_Settings;
}

// Account Authication
bool Core::SubmitLogin(std::string email, std::string password)
{

    // Checks if strings are the same (returns 0) and sends to login screen
    if(email.compare(m_User->GetEmail()) == 0 && password.compare(m_User->GetPassword()) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Account Modification
int Core::RegisterAccount(std::string username, std::string password, std::string email, QDateTime birthday)
{
    // Check if all fields were given
    if (username.empty() || password.empty() || email.empty() || birthday.isNull())
    {
        return Register::EMPTY;
    }

    // Check if age is 13 or above
    QDateTime today = QDateTime::currentDateTime();
    int yearsDiff = birthday.daysTo(today) / 365;
    if (yearsDiff < 13)
    {
        return Register::TOOYOUNG;
    }

    // Check if email is valid
    // Create email formatting (requreing and @ and .)

    bool isEmail = false;
    // If not an email
    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        QString emailStr = QString::fromStdString(email);
        QRegularExpression mailFormat("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailFormat.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatchIterator matchIterator = mailFormat.globalMatch(emailStr);
        if (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            isEmail = match.hasMatch();
        }
    #else
        QRegExp mailFormat("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailFormat.setCaseSensitivity(Qt::CaseInsensitive);
        mailFormat.setPatternSyntax(QRegExp::RegExp);

        // If not an email
        isEmail = mailFormat.exactMatch(QString::fromStdString(email));
    #endif
    if (!isEmail)
    {
        return Register::NOTEMAIL;
    }

    // Create all the regex for passwords (to give personalised errors)
    std::regex contUppercase("[A-Z]");
    std::regex contLowercase("[a-z]");
    std::regex containsNum("[0-9]");
    std::regex containsSymbol("[!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>\\/?]");

    // Check password strength
    if (password.length() < 8)
    {
        // If password length is less then 8
        return Register::SHORTPASS;
    }
    else if (!std::regex_search(password, contUppercase))
    {
        // If password does not contain uppercase
        return Register::NOUPPER;
    }
    else if (!std::regex_search(password, contLowercase))
    {
        // If password does not contain lowercase
        return Register::NOLOWER;
    }
    else if (!std::regex_search(password, containsNum))
    {
        // If password does not contain a number
        return Register::NONUM;
    }
    else if (!std::regex_search(password, containsSymbol))
    {
        // If password does not contain a symbol
        return Register::NOSYMBOL;
    }

    // After all checks, change user information and return 0 to change page
    m_User->SetUsername(username);
    m_User->SetEmail(email);
    m_User->SetPassword(password);
    return Register::SUCCESS;
}
