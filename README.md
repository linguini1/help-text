# help-text

A tool for turning plain-text into an include-able `#define` for C projects. The primary purpose of this utility is to
turn a help text document into printable help text from within C for command line utilities with a `--help` option.

## Building

Clone the git repository and make:

```console
git clone https://github.com/linguini1/help-text.git
cd help-text
make all
```

## Usage

For usage hints, call `help-text -h`. Yes, this utility's help text was generated using itself.

Once complete, you can include the generated help text macro in your C project. Here are two valid ways of generating
the help text macro.

```console
cat myhelptext.txt | help-text > myhelptext.h
help-text -i myhelptext.txt -o myhelptext.h
```

You can use the `-I` flag of your compiler to include your generated help text header file as part of your build
process, or you can include it directly with the `#include` directive.
