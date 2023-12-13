# 2811 User Interfaces Coursework3: The Process
The project is to create a beReal spoof, but for videos.
This code is a prototype for the final product. It has login, register, profile and home pages. The home page is where the user can see the videos they have uploaded and can upload new videos.

## Running the code:
### Qt
Install Qt Creator with Qt 5.15
When running the code run from the file VideoPlayer.pro
### Command Line Arguments
In QT (once folder is open) go to projects, run, Command line arguments:
```bash
# Unix
%{sourceDir}/../assets
# Windows
%{sourceDir}\..\assets
```
### Codecs
This project requires the gstreamer codecs to run as it uses the gstreamer library to play videos.
#### macos:
- install codec

#### Linux: 
Install gstreamer(needs plugins-good to run so can only install that depending on package manager)
```bash
zypper/dnf/pacman/apt install gstreamer
```
#### Windows:
No extra packages needed to run

## Contributing:
- Kanban link: https://trello.com/b/F56Kiy3C/user-interfaces-board
- Please create a branch for each feature you are working on
- Pull requests are welcome for when you are done with a feature
- Create an issue if you find a bug

### Help with git:
#### Commands to use:
```bash
git init # initialize git
git add remote origin git@github.com:sc22my/UI_COURSEWORK.git # link with ssh
git pull origin <branch> # pull from branch
git checkout <branch> # switch to branch
git checkout -b <branch> # create branch and switch to it
git branch # list branches
git branch -d <branch> # delete branch
git add <file> # add file to commit (can use . to add all files)
git commit -m "message" # commit changes
git push origin <branch> # push to branch
```
### Merging:
- Create a pull request on github and someone else will review it  
- Don't Push to main

### Formatting:
#### Inline Functions:
```cpp
void foo() {
    // code
}
```
#### Comments:
```cpp
/**
 * @brief foo
 * @param bar
 * @return
 */
void foo(int bar) {
    // code
}
```
