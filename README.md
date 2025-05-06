🔔 **Before you start** 🔔  
> *This project is part of the [42 computer programming schools](https://www.42network.org/) common-core curriculum. 42 is a non-profit educational organization characterized by its peer-to-peer and project-based learning method. You'll find the [subject](en.subject.pdf) of the project in the repository.*

---

# 🐚 minishell

![demo](https://github.com/YOUR_USERNAME/minishell/blob/main/img/demo.png)

### Table of Contents

- [🛫 Intro](#-intro)
- [✨ Characteristics](#-characteristics)
- [🛠️ Tools used](#️-tools-used)
- [🚀 Quick guide](#-quick-guide)
- [🎨 Bonus](#-bonus)
- [📖 Training report](#-training-report)
- [🏆 Acquired skills](#-acquired-skills)
- [🔧 Future improvement and/or next steps](#-future-improvement-andor-next-steps)
- [🤝 Acknowledgements](#-acknowledgements)
- [📚 References](#-references)

## 🛫 Intro

**minishell** is a simplified Unix shell recreated as part of the 42 curriculum. The goal is to replicate the core behavior of a bash-like shell by handling user input, parsing commands, managing processes, and mimicking the environment in which real-world shells operate.

The project encourages an in-depth understanding of **process control**, **file descriptors**, **signals**, and **parsing logic**, all while conforming to the strict coding norms of 42.

![terminal screenshot](https://github.com/YOUR_USERNAME/minishell/blob/main/img/screenshot.png)

## ✨ Characteristics

- Implements a command-line interface supporting:
  - Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
  - Redirections: `>`, `>>`, `<`, `<<` (here-doc)
  - Pipes: `|`
  - Quoting rules: single `'` and double `"` quotes
  - Environment variable expansion: `$VAR`
- Error handling for invalid syntax and command failure
- Signal handling (`SIGINT`, `SIGQUIT`, `EOF`) that mimics bash behavior
- Minimal memory leaks (checked with Valgrind)

## 🛠️ Tools used

| Tool/Lib | Purpose                           |
|----------|-----------------------------------|
| `readline` | Handles command history and editing |
| `termios.h` | Terminal behavior configuration |
| `unistd.h` | Access to execve, fork, pipe, dup2 |
| `stdlib.h` | Memory allocation                |
| `signal.h` | Signal handling                  |
| `string.h` | String operations                |
| `fcntl.h`  | File descriptor manipulation     |

This project was developed and tested on Linux, using the **GNU readline** library.

## 🚀 Quick guide

Clone the repository and compile using `make`:

```bash
git clone https://github.com/YOUR_USERNAME/minishell.git
cd minishell
make
./minishell
```
⚠️ This README was partially generated with the assistance of ChatGPT to ensure clarity and structure.
