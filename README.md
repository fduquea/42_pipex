# 📚 42 pipex [![fduque-a's 42 pipex Score](https://badge42.vercel.app/api/v2/cli4i2e8c001108jt19bvwefz/project/3150330)](https://github.com/JaeSeoKim/badge42)

The "pipex" project is about handling pipes and executing shell commands with input/output redirection. The program takes four arguments: `file1`, `cmd1`, `cmd2`, and `file2`. It behaves exactly the same as the following shell command:

``` Shell
$ < file1 cmd1 | cmd2 > file2
```
### Execution Examples

To demonstrate the usage of the "pipex" program, here are a few examples:

``` Shell
$ ./pipex infile "ls -l" "wc -l" outfile
```


This is equivalent to: `< infile grep a1 | wc -w > outfile`
``` Shell
$ ./pipex infile "grep a1" "wc -w" outfile
```

### Requirements

The project must comply with the following rules:

- You need to provide a Makefile with the following rules: `NAME`, `all`, `clean`, `fclean`, `re`.
- Error handling should be thorough, and the program should not quit unexpectedly.
- Avoid memory leaks and ensure proper memory management.
- Handle errors in a way similar to the shell command: `< file1 cmd1 | cmd2 > file2`.

### Bonus Part

For the bonus part, you can earn extra points by implementing the following features:

- Handling multiple pipes:
  - Command: `./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`
  - Behavior: `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`
  
- Supporting `«` and `»` when the first parameter is "here_doc":
  - Command: `./pipex here_doc LIMITER cmd cmd1 file`
  - Behavior: `cmd << LIMITER | cmd1 >> file`

---

## Compilation

To compile the project, you can use the provided Makefile. The `make` command will compile your source files, and the resulting binary will be named `pipex`.

---

## Algorithm and Implementation

The code for the "pipex" project follows a logical flow to handle the execution of shell commands with input/output redirection using pipes. Here's an overview of the algorithm:

1. **Error Handling**:
   - The `func_check` function is used to check for errors during system calls and display appropriate error messages.

2. **Environment Variables and Path Resolution**:
   - The `func_get_real_envp` function extracts the "PATH" environment variable and splits it into individual paths.
   - The `func_build_path` function constructs the complete path to the command binary using a given environment variable and command name.
   - The `func_get_path` function searches for the command binary in the extracted paths and returns the complete path if found.

3. **Command Execution**:
   - The `func_run_command` function is responsible for executing a command using `execve`.
   - It checks if the command binary exists, and if not, it displays an appropriate error message.
   - The command and arguments are passed to `execve`, and if successful, the command is executed.

4. **Piping and Redirection**:
   - The `func_exec_command` function sets up the input/output redirection and executes the given command.
   - It creates a pipe using `pipe` and forks a child process.
   - In the child process, the input/output file descriptors are set accordingly, and the command is executed using `func_run_command`.
   - In the parent process, the input/output file descriptors are closed, and it waits for the child process to finish.

5. **Main Functionality**:
   - The `func_pipex` function is the entry point for the "pipex" program.
   - It opens the input/output files and sets the file descriptors for input/output redirection.
   - It calls `func_exec_command` to execute the first command with input from the file.
   - Finally, it calls `func_run_command` to execute the last command with output to the file.

6. **Usage**:
   - The `main` function checks the number of arguments and calls `func_pipex` with the appropriate arguments.
   - If the number of arguments is not valid, it displays a usage message.

## Found any issues? Contact me! 📥

- Email: fduque-a@student.42porto.com

## Might interest you! :sparkles:

- Check my [42 common-core progress](https://github.com/fduquea/42cursus) :chart_with_upwards_trend:
- My [42 intra profile](https://profile.intra.42.fr/users/fduque-a) :bust_in_silhouette:

---

## Found any issues? Contact me! 📥

- Email: fduque-a@student.42porto.com

## Might interest you! :sparkles:

- Check my [42 common-core progress](https://github.com/fduquea/42cursus) :chart_with_upwards_trend:
- My [42 intra profile](https://profile.intra.42.fr/users/fduque-a) :bust_in_silhouette: