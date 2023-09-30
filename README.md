***MINISHELL 42***

**SUMMARY**

The Minishell 42 project was a significant and rewarding challenge in the 42 curriculum, pushing me to explore various aspects of software development. Despite my initial intimidation, it involved creating a command-line interpreter resembling Bash, focusing on core functionalities:

Operating exclusively in interactive mode
Executing commands with absolute or relative paths
Supporting simple commands without paths
Maintaining a command history
Implementing pipes, redirections, and here-doc functionality
Handling double and single quotes, environment variables, and signals
Including built-in commands like echo, exit, env, export, unset, cd, and pwd.
The project was divided into front-end and back-end sections. The front-end managed user input and commands, while signals were addressed later to reduce complexity. The parsing journey involved two phases: lexical analysis (tokenization) and syntax analysis (parsing). Lexical analysis transformed user input into tokens, emphasizing token types over values. Syntax analysis scanned tokens based on a predefined grammar, potentially generating an Abstract Syntax Tree. Lexing was relatively straightforward, while parsing posed a considerable challenge.

***PROJECT COMMENTARY***

This project was undoubtedly one of the most challenging and rewarding endeavors during my journey through the 42 curriculum.
It pushed me to explore diverse areas of software development, ranging from intricate topics like software architecture, system calls, and file descriptors, to the often underestimated skills of team coordination, management, and task distribution.

Initally, crafting a shell that could simulate the functionality of Bash seemed an very intimidating task My familiarity with shells was limited to basic usage for everyday tasks. The inner workings of shells were a mystery to me.
Minishell proved to be a substantial and intricate project, especially for someone relatively new to the world of software development. Getting started demanded meticulous planning and thorough research to avoid major design overhauls later on — although, as it turned out, some redesigning was inevitable.

Our task was to construct a mini shell, essentially a command-line interpreter, that emulates the functionality of Bash, albeit with a focus on the fundamental features:

The shell operates exclusively in interactive mode, meaning it doesn't handle scripts (i.e., the executable takes no arguments).
It can execute simple commands with absolute or relative paths (e.g., /bin/ls, ../bin/ls).
Simple commands without a path (e.g., ls, cat, grep) are supported.
The shell maintains a working command history, allowing navigation using up and down arrows.
It implements pipes (|), redirections (<, >, >>), and the here-doc (<<) functionality.
Double quotes ("") and single quotes ('') are handled, providing an escape mechanism for special characters, along with $ for double quotes.
Environment variables (identified by $ followed by a sequence of characters) are managed.
The shell responds to signals just like Bash (e.g., ctrl + C, ctrl + , ctrl + D).
It includes the following built-in commands:

- echo (with option -n only)

- exit

- env (without options or arguments)

- export (without options)

- unset (without options)

- cd

- pwd

Me and my partner devided the project in two macro-sections: the front-end and the back-end.

The front-end is responsible for managing user input and interaction, encompassing commands and signals such as ctrl + C. I opted to address signals later in the development process to avoid unnecessary complexity from the outset. This meant my initial focus was on handling user input.

When contemplating user input and how the shell should process it, I recognized the need for a systematic and algorithmic approach. While some colleagues may have been tempted to hard-code parsing and handle cases individually, I sought to step out of my comfort zone and explore a more structured and innovative solution.

Starting the parsing journey was initially confusing. I didn't know how to begin and was determined not to rush into it, only to realize later that I needed a major overhaul. To avoid this, I took inspiration from how Bash handles command parsing. I discovered that parsing can be broken down into two phases: lexical analysis (lexing) and syntax analysis (parsing).

**Lexical Analysis / Tokenization:** Lexical analysis involves taking user input and meticulously processing it character by character, transforming it into "tokens." To illustrate, consider building a calculator program with the input "1 + 2." This input can be converted into a stream of tokens like the following:

```
[NUMBER: 1] [PLUS] [NUMBER: 2]
```

Each token has a type and a value. For instance, the first token on the left is of type "NUMBER" and has a value of "1." Why go through this process? It's all about abstraction. When parsing according to a specific grammar, the type of lexemes or tokens—rather than their values—and the order in which they appear become the crucial focus.

**Syntax Analysis / Parsing:** Syntax analysis entails scanning the stream of tokens in accordance with a predefined grammar and determining what actions to take. This could involve generating an Abstract Syntax Tree (AST) for further processing.

Lexing involved splitting the input into tokens in a manner that made sense for the parsing phase and turned out to be a rather uneventful task. Parsing, on the other hand, proved to be quite challenging.

## 🚀 About Me
![*Full stack developer*](https://github.com/noci0001/noci0001/assets/79120220/73d4cda4-8371-4ad3-9bbb-8d556b8b33d7)
### Hi there 👋, my name is *Sam*
I am Sam from Berlin, I code for a living and I live to code. I really enjoy low level languages like C and I mostly code in CPP. 
You can checkout my LinkedIn profile at [my LinkedIn](https://linkedin.com/in/samuelnocita)
## Acknowledgements

My effort was equally complimented by my capable teammate and friend [Adam Murawski](https://github.com/MrMuras)
## Authors

@noci0001](https://www.linkedin.com/in/samuelnocita/) and [@MrMuras](https://www.github.com/MrMuras)
