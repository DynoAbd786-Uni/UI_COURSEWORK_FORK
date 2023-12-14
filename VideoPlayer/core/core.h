#ifndef CORE_H
#define CORE_H

#include "core/settings.h"
#include "core/user.h"
#include "core/videodb.h"

#include <array>
#include <string>
#include <QDateTime>

/**
 * @author Mustafa Yozgyur
*/

// Arguments to construct core
struct CoreArgs
{
    std::string m_AssetsFolderPath;
};

// Singleton class
// Implements backend apis and stuff
class Core
{

public:
    Core(const CoreArgs& args);
    ~Core();

    bool SubmitLogin(std::string email, std::string password);
    int RegisterAccount(std::string username, std::string password, std::string email, QDateTime birthday);

    // Getters
    inline Settings* GetSettings() { return m_Settings; }
    inline User* GetUser() { return m_User; }
    inline VideoDB* GetVideoDB() { return m_VideoDB; }

private:

    std::string m_AssetsPath = "";

    // Core related classes
    Settings* m_Settings;
    User* m_User;
    VideoDB* m_VideoDB;

    // Friends pool
    std::array<User, 5> m_Users;
};

// Enums for different return states for the register function
enum Register
{
    SUCCESS,
    EMPTY,
    TOOYOUNG,
    SHORTPASS,
    NOUPPER,
    NOLOWER,
    NONUM,
    NOTEMAIL,
    NOSYMBOL
};

#endif // CORE_H
