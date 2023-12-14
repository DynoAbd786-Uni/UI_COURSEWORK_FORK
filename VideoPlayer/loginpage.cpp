#include "loginpage.h"
#include "ui_loginpage.h"
#include "mainwindow.h"
#include "core/application.h"

#include <QPushButton>
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QTranslator>

/**
 * @author Mustafa Yozgyur
 * @author Brent Edington
 * @author Muhammad Kashif-Khan
*/

LoginPage::LoginPage(QWidget *parent, MainWindow* main_window)
    : QWidget{parent}
    , p_MainWindow(main_window)
    , ui(new Ui::LoginPage())
{
    ui->setupUi(this);

    // Connect button
    connect(ui->button_Login, &QPushButton::clicked, this, &LoginPage::LoginButtonClicked);
    connect(ui->button_Register, &QPushButton::clicked, this, &LoginPage::RegisterButtonClicked);

    // Connect language
    Core* core = Application::instance()->GetCore();
    connect(ui->langBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &LoginPage::OnLangChange);
    connect(p_MainWindow, &MainWindow::langChange, this, &LoginPage::ChangeLang);
    ui->langBox->setCurrentIndex(core->GetSettings()->lang);
}
LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::LoginButtonClicked()
{
    // Get core
    Core* core = Application::instance()->GetCore();

    // Get strings
    std::string Email = ui->text_Email->text().toStdString();
    std::string Password = ui->text_Password->text().toStdString();

    // Test if login successful
    bool result = core->SubmitLogin(Email, Password);
    if (result)
    {
        // If login successful
        p_MainWindow->ChangePage(MainWindow::PageIndex::HOME_PAGE);
    }
    else
    {
        // Pop up to say password incorrect
        QMessageBox::critical(this, tr("Login Failed"), tr("Incorrect email or password."));
    }
}

void LoginPage::RegisterButtonClicked()
{
    // Go to register page
    p_MainWindow->ChangePage(MainWindow::PageIndex::REGISTER_PAGE);
}

void LoginPage::OnLangChange(int index)
{
    // Get core
    Core* core = Application::instance()->GetCore();

    QString selectedLang = ui->langBox->currentText();
    core->GetSettings()->lang = index;
    p_MainWindow->ChangeLang(static_cast<MainWindow::Language>(index));
}



void LoginPage::OnPageEnter()
{
    ui->text_Email->clear();
    ui->text_Password->clear();
}

void LoginPage::ChangeLang()
{
    // Change default
    Core* core = Application::instance()->GetCore();
    ui->langBox->setCurrentIndex(core->GetSettings()->lang);
    // Reload
    ui->retranslateUi(this);
}
