#include "settingspage.h"
#include "ui_settingspage.h"
#include "mainwindow.h"
#include "core/application.h"

#include <QDebug>
#include <QMessageBox>

/**
 * @author Brent Edington
 * @author Mustafa Yozgyur
*/

SettingsPage::SettingsPage(QWidget *parent, MainWindow* window) :
    QWidget(parent),
    ui(new Ui::SettingsPage),
    p_MainWindow(window)
{
    ui->setupUi(this);

    // Get core
    Core* core = Application::instance()->GetCore();

    // Connect dropdowns
    connect(ui->box_notify, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &SettingsPage::OnNotifyChange);
    ui->box_lang->setCurrentIndex(core->GetSettings()->lang);
    connect(ui->box_lang, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &SettingsPage::OnLangChange);

    // Connect buttons
    connect(ui->button_Back, &QPushButton::clicked, this, &SettingsPage::ProfileButtonClicked);
    connect(ui->button_logout, &QPushButton::clicked, this, &SettingsPage::LogoutButtonClicked);
    connect(ui->button_howto, &QPushButton::clicked, this, &SettingsPage::HowtoClicked);

    // Translate
    connect(p_MainWindow, &MainWindow::langChange, this, &SettingsPage::ChangeLang);
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::OnPageEnter()
{
    // Load variables and select drop downs
}

// Dropdowns

void SettingsPage::OnNotifyChange(int index)
{
    Q_UNUSED(index);

    Core* core = Application::instance()->GetCore();
    core->GetSettings()->shouldNotify = false;
}


void SettingsPage::OnLangChange(int index)
{
    // Get core
    Core* core = Application::instance()->GetCore();

    QString selectedLang = ui->box_lang->currentText();
    core->GetSettings()->lang = index;
    p_MainWindow->ChangeLang(static_cast<MainWindow::Language>(index));
}

// Button Clicks

void SettingsPage::ProfileButtonClicked()
{
    p_MainWindow->ChangePage(MainWindow::PageIndex::PROFILE_PAGE);
}

void SettingsPage::LogoutButtonClicked()
{
    p_MainWindow->ChangePage(MainWindow::PageIndex::LOGIN_PAGE);
}

void SettingsPage::HowtoClicked()
{
    QMessageBox::information(this, tr("StaySimple"), tr("To use the app, wait for a notification to post a video. Once this occurs you "
                                                        "have 3 minutes to upload a video and can see your friends videos once you upload."));
}

// Translate
void SettingsPage::ChangeLang()
{
    // Change default
    Core* core = Application::instance()->GetCore();
    ui->box_lang->setCurrentIndex(core->GetSettings()->lang);
    // Reload
    ui->retranslateUi(this);
}
