# Mp3-Tag-Reader-Editor

This project is a **command-line tool** to read and edit ID3[version 2.3] tags in MP3 files. It supports viewing and updating specific metadata fields such as title, artist, album, genre, year, and comments in which inputs are passed through Command Line Arguments.

---

### **Usage -> Commands**

1. **Help Menu**\
   To display the help menu and available options:

   ```bash
   ./a.out --help
   ```
  
   **Output**:
  
   ```
   -------------- HELP MENU ---------------
   1. -v -> to view mp3 file contents
   2. -e -> to edit mp3 file contents
            2.1. -t -> to edit song title
            2.2. -a -> to edit artist name
            2.3. -A -> to edit album name
            2.4. -g -> to edit genre
            2.5. -y -> to edit year
            2.6. -c -> to edit comment
   ```
 
2. **View MP3 File Metadata**\
   To view the contents of an MP3 file:

   ```bash
   ./a.out -v filename.mp3
   ```

3. **Edit MP3 File Metadata**\
   To edit a specific tag in an MP3 file:

   ```bash
   ./a.out -e [flag] [new content] [filename.mp3]
   ```

   **Supported Flags**:

   - `-t` -> Edit song title
   - `-a` -> Edit artist name
   - `-A` -> Edit album name
   - `-g` -> Edit genre
   - `-y` -> Edit year
   - `-c` -> Edit comment

   **Example**:

   ```bash
   ./a.out -e -t New_Song_Title filename.mp3
   ```

---

### **Topics Covered**

- **Bitwise Operations**: For Extracting and Updating Metadata sizes.
- **File Handling**: Read, write, and manipulate `.mp3` file content.
- **Arrays & Strings**: Process and manage Command Line Arguments, tags and it's content.
- **Functions and Pointers**: To maintain Modularity and manage Dynamic memory.

