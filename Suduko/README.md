# 🎯 C Mini Projects
Welcome to **C Mini Projects** — a collection of small but mighty C programs that you can compile, run, and hack on!  

---

## ⚡ Getting Started
All programs here are written in **C** and are super easy to compile and run right from your terminal. Open your terminal in this project’s directory and type:

```bash
gcc <yourfile_name.c> -o <anyname>
Example:

bash
Copy code
gcc sudoku.c -o sudoku
💡 Tip: It’s best practice to keep the filename and executable name the same to avoid confusion.

▶️ Run It — Choose Your Style
Once the compiler spits out an executable, you’ve got options:

🧑 Civilian way: double-click the shiny executable on your desktop and watch it go.

😎 Hacker way: fire up the terminal and type:

bash
Copy code
./<anyname>
Example:

bash
Copy code
./sudoku
NOTE: Be sure to use the same name you chose during compilation.

⚡ Pro Mode — Do It All in One Shot
If you want to feel like a real terminal nerd, you can compile and run in a single command:

bash
Copy code
gcc <yourfile_name.c> -o <name> && ./<name>
Example:

bash
Copy code
gcc sudoku.c -o sudoku && ./sudoku
🕵️ Debugging Made Easy
Want to see detailed compiler warnings while compiling? Add the -Wall flag:

bash
Copy code
gcc -Wall sudoku.c -o sudoku && ./sudoku