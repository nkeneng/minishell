import subprocess
import difflib
from typing import Tuple

def run_command(shell: str, command: str) -> Tuple[str, int]:
    try:
        process = subprocess.Popen(
            [shell, '-c', command],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        stdout, stderr = process.communicate()
        return (stdout + stderr), process.returncode
    except Exception as e:
        return str(e), -1

def compare_outputs(test_name: str, command: str, bash_shell: str, mini_shell: str):
    bash_output, bash_rc = run_command(bash_shell, command)
    mini_output, mini_rc = run_command(mini_shell, command)
    
    output_match = bash_output == mini_output
    rc_match = bash_rc == mini_rc
    
    if output_match and rc_match:
        print(f"✅ {test_name}: PASS")
    else:
        print(f"❌ {test_name}: FAIL")
        if not output_match:
            print("Output difference:")
            diff = difflib.unified_diff(
                bash_output.splitlines(True),
                mini_output.splitlines(True),
                fromfile='bash',
                tofile='minishell'
            )
            print(''.join(diff))
        if not rc_match:
            print(f"Return code difference: bash={bash_rc}, minishell={mini_rc}")

# Example usage
test_cases = [
    ("Simple echo", "echo hello"),
    ("Pipeline", "ls | grep .txt"),
    ("Pipe only builtins", "env | pwd")
    ("Variable setting using export", "export X=42"),
    ("Variable expansion", "echo $X"),
    ("Variable expansion with quotes", 'echo "$X"'),
    ("Variable expansion with single quotes", "echo '$X'"),
    ("Variable expansion with other words in quotes", 'echo " the name of the school i $X you know $USER?"'),
    ("input = output file", ">out cat <out"),
    ("output = input file", "<out cat >out"),
    ("operators seperated by spaces", "echo hello > out | cat < out"),
    ("operators not seperated by spaces", "echo hello>out|cat<out"),
    ("quotes in instructuion", "p\"w\"d"),
]

print("Starting tests...")  # Debug print
for name, cmd in test_cases:
    compare_outputs(name, cmd, "/bin/bash", "./minishell")
