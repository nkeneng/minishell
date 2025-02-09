# Minishell

## Description
Minishell is a simple, lightweight shell implementation written in C. It aims to provide a minimalistic and efficient command-line interface for Unix-like operating systems.
This project challenges us to create a bash-like application that runs in the terminal 

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)
- [Contact Information](#contact-information)

## Features

Minishell provides a variety of functionalities that simulate a basic shell environment:

- **Command Execution**:
  - Execute programs using their absolute paths (e.g., `/bin/ls`).
  - Execute programs using their relative paths.

- **File Redirections**:
  - Redirect input using `<`.
  - Redirect output using `>`.
  - Append output using `>>`.

- **Heredoc Support**:
  - Use a heredoc (`<<`) to take input from a file until a specified delimiter is reached.

- **Piping Commands**:
  - Pipe the output of one command to the input of another using `|`.

- **Environment Variables**:
  - Use environment variables in commands.
  - Set environment variables.
  - Unset environment variables.

- **Signal Handling**:
  - Handle standard signals such as `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).

- **Built-in Shell Functions**:
  - **`echo`**: Display a line of text.
  - **`cd`**: Change the current directory.
  - **`pwd`**: Print the current working directory.
  - **`export`**: Set environment variables.
  - **`unset`**: Unset environment variables.
  - **`env`**: Display the environment variables.
  - **`exit`**: Exit the shell.

These features provide a basic yet functional shell experience, allowing for a variety of tasks directly from the command line.
### building a mini-bash

This project challenges us to create a bash-like application that runs in the terminal and enables the user to use the prompt to
- execute programs with absolute path (e.g /bin/ls)
- execute programs with relative path
- use file redirections < > and >>
- use a heredoc as an input (>>)
- pipe commands
- use, set and unset environment variables
- use standard signals
- use builtin shell-function 
  - echo
  - cd
  - pwd
  - export
  - unset
  - env
  - exit

#### shell functions

The linux shell is very expansive and has many functions, of which this implementation just does a small part. 
We discovered a lot of shell functions and behaviour in the progress of this project, but decided against implementing certain shell features such as full support for shellscripts.

## Installation
To install Minishell, follow these steps:

1. Clone the repository:
	```sh
   git clone https://github.com/nkeneng/minishell.git
```
