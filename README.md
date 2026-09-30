# Scramble

Scramble is a small Unix-style shell I'm building from scratch in C as a learning project.

I'm using it to get more comfortable with C, Linux/POSIX APIs, processes, system calls, pointers, and the lower-level mechanics behind command-line programs.

I'm deliberately building it incrementally rather than following a complete shell tutorial, so I can understand each feature before moving on to the next one.

## Current Features

* Interactive command input using `linenoise`
* Basic command parsing
* External command execution using `fork()`, `execvp()`, and `waitpid()`
* Built-in command infrastructure
* `cd`
* `pwd`
* Command history

Example:

```text
$ pwd
/mnt/c/Users/Natha/Documents/Scramble

$ cd /tmp

$ pwd
/tmp

$ ls
...
```

## Building

Scramble currently builds with GCC:

```bash
gcc scramble.c ./lib/linenoise.c -o scramble
```

Or with additional compiler warnings:

```bash
gcc -Wall -Wextra -Wpedantic scramble.c ./lib/linenoise.c -o scramble
```

Run it with:

```bash
./scramble
```

## Current Limitations

Scramble is still very early in development. It currently doesn't support:

* Quoted arguments
* Escaped characters
* Pipes
* Input/output redirection
* Environment variable expansion
* `cd -`
* An `exit` built-in

These will be added incrementally as I continue developing the project.

## What I'm Learning

The main purpose of Scramble is to learn by building.

So far, the project has introduced me to:

* Processes and process creation
* `fork()` / `execvp()` / `waitpid()`
* POSIX system calls
* Command-line argument arrays
* Pointers and pointer-to-pointer usage
* Environment variables
* Working directories
* Basic command parsing

I'm more interested in understanding how these pieces work than trying to turn Scramble into a full Bash replacement.
