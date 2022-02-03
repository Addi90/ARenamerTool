# A-RenamerTool

The A (or Adrian’s) – Renamer is a tool for bulk renaming files in various ways. Its graphical user interface (GUI) lets the user easily select a file directory and then select the files to bulk rename. In the file selection view it also provides a live preview of the new filename for each selected file. It is written in C++ and utilizes the Qt-Framework.

The user has various ways adding, removing and replacing content to a filename with the help of different modifiers that also can be used at the same time:

- adding (append, prepend, insert at pos.)
- removing any number of characters (front, back, given pos.)
- replacing a sequence of characters/RegEx
- simple conditional modifying (IF has/has not -> THEN append/prepend/insert)
- adding a date (creation, last modified, today, custom) to files
- adding a count
