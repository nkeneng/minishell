## command.h

This header file defines constants and structures used for handling commands in the minishell project.

### Constants

- `C_EXECUTE`: Flag indicating the command needs to read from a pipe.
- `C_COMMAND_BUILTIN`: Flag indicating the command is a built-in shell command.
- `C_PIPE`: Flag indicating the command needs to read from a pipe.
- `C_HERE_DOC`: Flag indicating the command needs to read from a here document.
- `C_OPEN_INFILE`: Flag indicating the command should open a file as input.
- `C_OPEN_OUT_TRUNC`: Flag indicating the command should open an output file in truncated mode.
- `C_OPEN_OUT_APP`: Flag indicating the command should open an output file in append mode.
- `C_VAR`: Flag indicating the command involves a variable assignment.
- `C_LAST_PIPE`: Flag indicating the command's output should be directed to stdout.

### Structure

#### `t_command`

This structure represents a command and contains the following fields:

- `char **cmd`: A NULL terminated array representing the command. Element 0 is name of executable, following elements are options.
- `t_redirect *redirects`: A pointer to the redirections associated with this command.
- `int flags`: Flags associated with this command, which can be a combination of the constants defined above.

### Macros

- `PIPE_OR_REDIR_MASK`: A mask combining `C_PIPE`, `C_HERE_DOC`, `C_OPEN_INFILE`, `C_OPEN_OUT_TRUNC`, and `C_OPEN_OUT_APP` flags.
