#include "videodb.h"

#include <QDir>
#include <QDirIterator>
#include <QString>

#include <iostream>

/**
 * @brief Helper function.
 * @param list
 * @param key
 * @return if key contains any one of the strings in list
 */
static bool ContainsString(std::vector<QString> list, const QString& key)
{
    for (auto& str : list)
    {
        if (key.contains(str))
        {
            return true;
        }
    }

    return false;
}

VideoDB::VideoDB(std::string path_to_videos) :
    m_PathToVideos(path_to_videos)
{
    // Discover videos in the directory
    // List of file extensions to look for:
    std::vector<QString> extensions;
#ifdef _WIN32
    extensions.push_back(".wmv");
#else
    extensions.push_back(".MOV");
    extensions.push_back(".mp4");
#endif


    QDir videos_dir = QDir(m_PathToVideos.c_str());
    if (!videos_dir.exists())
    {
        std::cerr << "Videos folder doesnt extist!" << std::endl;
        throw std::runtime_error("videos folder does not exist");
    }

    QDirIterator it(videos_dir);

    while (it.hasNext())
    {
        QString file_name = it.next();
        QFileInfo file_info(file_name);

        if (!ContainsString(extensions, file_name)) { continue; }

        m_Videos.push_back(Video {file_name.toStdString(), file_info.birthTime()});
    }

}

std::vector<Video> VideoDB::GetVideos()
{
    return m_Videos;
}

std::vector<Video> VideoDB::GetUserVideos()
{
    // Return an empty vector for now
    return std::vector<Video>();
}
