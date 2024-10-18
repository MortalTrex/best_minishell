**minishell**

***about***

https://github.com/mcombeau/minishell/blob/main/sources/signals/signal.c

https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing

https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html

https://www.gnu.org/software/bash/manual/bash.html

shorter HOWTO
https://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html
	https://www.linuxdoc.org/HOWTO/Bash-Prog-Intro-HOWTO-9.html

https://eli.thegreenplace.net/2009/03/20/
a-recursive-descent-parser-with-an-infix-expression-evaluator

https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10

https://trove.assistants.epita.fr/docs/42sh/lexer-parser

https://www.geeksforgeeks.org/developing-linux-based-shell/

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

https://medium.com/swlh/lets-build-a-linux-shell-part-iii-a472c0102849

https://medium.com/swlh/lets-build-a-linux-shell-part-ii-340ecf471028

https://github.com/twagger/minishell

https://minishell.org/check__exitcode_8c.html

```c
git checkout feature/feature_b
git pull
git checkout feature/feature_a
git merge feature/feature_b
```

steps
1. main char **envp
2. pass path of binary files
3. fork before excve (otherwise rewrites our processes)

notes
minitalk can be used for ctrl + d and ctrl + c


 Minishell - Project Flow

     Define Grammar

     Identify Right Parsing Technique
        Research and select the most suitable parsing method (e.g., recursive descent parser).

     Lexer (Tokenization)
        Tokenize the input string into meaningful components (tokens)
        VERY IMPORTANT: Quotes: Recognize and preserve tokens within quotes as single units (e.g., "Hello World" should be a single token) also              preserve the $ variables.

     Parsing
        Parsing Validations: Ensure tokens follow the correct syntax rules.
        Handle Syntax Errors: Provide meaningful error messages.

        Expand Variables: Replace $ tokens with their corresponding values.
				Expand Variables: After tokenization, and while parsing, you should expand the variables. The order here is critical:
              Outside Quotes: If a variable appears outside of quotes, replace it with its value immediately.
              Inside Double Quotes ("): Variables inside double quotes should be expanded. For example, "Hello $USER" should expand $USER but
              preserve the other content.
              Inside Single Quotes ('): Variables inside single quotes should not be expanded. For example, '$USER' should remain as "$USER" without
              expansion.
      Remove Quotes Last: After variable expansion, remove the quotes.

        Split Commands: Divide the input into individual commands.
        Create Command List: Structure commands and arguments for execution.

     Redirections
        Check Redirections: (<, >, >>).
        File Handling: Create and manage necessary files for redirections.

     Pipes

     Built-ins

     Execution

     Heredocs

     Testing & Debugging


**bash**
pipes

The order of expansions is: brace expansion; tilde expansion, parameter and variable expansion, arithmetic expansion, and command substitution (done in a left-to-right fashion); word splitting; and pathname expansion. .... After these expansions are performed, quote characters present in the original word are removed unless they have been quoted themselves (quote removal).

https://git.kernel.org/pub/scm/utils/dash/dash.git/tree/src/parser.c
https://www.oilshell.org/blog/2019/02/07.html
https://www.oilshell.org/blog/2017/12/15.html

https://eli.thegreenplace.net/2007/11/24/the-context-sensitivity-of-cs-grammar

https://gallium.inria.fr/%7Efpottier/publis/jourdan-fpottier-2016.pdf

https://tldp.org/LDP/abs/html/exitcodes.html


