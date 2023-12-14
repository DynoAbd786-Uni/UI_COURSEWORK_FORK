#include "post.h"
#include "ui_post.h"

#include "core/user.h"
#include "core/video/video.h"

#include <iostream>
#include <QtMultimedia/QMediaPlayer>

Post::Post(QWidget *parent, User* user, Video* video)
    : QWidget(parent)
    , ui(new Ui::Post)
{
    ui->setupUi(this);

    // Connect ui signals
    connect(ui->slider_Slider, SIGNAL(valueChanged(int)), this, SLOT(SetPosition(int)));
    connect(&m_MediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(UpdateDuration(qint64)));
    connect(&m_MediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(UpdatePosition(qint64)));
    connect(&m_MediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(MediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(&m_MediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(MediaStateChanged(QMediaPlayer::State)));
    connect(&m_MediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(MediaPlayerError(QMediaPlayer::Error)));

    // Connect like button
    connect(ui->button_Like, SIGNAL(clicked()), this, SLOT(ChangeLikeButtonStatus()));

    // Connect play pause button
    connect(ui->button_PlayPause, SIGNAL(clicked()), this, SLOT(PlayPauseClicked()));

    // Setup media player
    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        m_MediaPlayer.setSource(video->GetURL());
    #else
        m_MediaPlayer.setMedia(video->GetURL());
    #endif
    m_MediaPlayer.setVideoOutput(ui->vp_MediaPlayer);

    // Set text of lables
    ui->label_Username->setText(std::string("@").append(user->GetUsername()).c_str());
    ui->label_Date->setText(video->GetDate().time().toString());
}

Post::~Post()
{
    delete ui;
}

void Post::UpdateDuration(qint64 duration)
{
    ui->slider_Slider->setMaximum(static_cast<int>(duration));
}

void Post::UpdatePosition(qint64 position)
{
    ui->slider_Slider->setValue(static_cast<int>(position));
}

void Post::MediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::MediaStatus::LoadedMedia)
    {
        // m_MediaPlayer.play();
    }
}

void Post::MediaStateChanged(QMediaPlayer::State state)
{
    switch (state)
    {
        case (QMediaPlayer::StoppedState) :
        {
            ui->button_PlayPause->setStyleSheet("border-image: url(:/assets/button_images/play_button.jpg)");
            break;
        }

    case (QMediaPlayer::PlayingState) :
        {
            ui->button_PlayPause->setStyleSheet("border-image: url(:/assets/button_images/pause_button.jpg)");
            break;
        }

    case (QMediaPlayer::PausedState) :
        {
            ui->button_PlayPause->setStyleSheet("border-image: url(:/assets/button_images/play_button.jpg)");
            break;
        }
    }
}

void Post::MediaPlayerError(QMediaPlayer::Error e)
{
    std::cout << "ERROR: " << e << std::endl;
}

void Post::SetPosition(int position)
{
    m_MediaPlayer.setPosition(static_cast<qint64>(position));
}

void Post::ChangeLikeButtonStatus()
{
    if (!ui->button_Like->isChecked())
    {
        ui->button_Like->setIcon(QIcon(":/assets/button_images/likeButtonOn.jpg"));
        ui->button_Like->setCheckable(true);
    }
    else
    {
        ui->button_Like->setIcon(QIcon(":/assets/button_images/likeButtonOff.jpg"));
        ui->button_Like->setCheckable(false);
    }
}

void Post::PlayPauseClicked()
{
    switch (m_MediaPlayer.state())
    {
        case (QMediaPlayer::State::PlayingState) : {
            std::cout << "pausing" << std::endl;
            m_MediaPlayer.pause();
            break;
        }

        case (QMediaPlayer::State::PausedState) : {
            std::cout << "playing" << std::endl;
            m_MediaPlayer.play();
            break;
        }

        case (QMediaPlayer::State::StoppedState) : {
            // restart video
            std::cout << "re playing" << std::endl;
            m_MediaPlayer.setPosition(0);
            m_MediaPlayer.play();
            break;
        }
    }
}
