#define HELP_TEXT \
"help-text\nMatteo Golin, 2024\n\nDESCRIPTION:\n    help-text is a command li" \
"ne utility for generating C macro `#define`\n    substitutions for plain-tex" \
"t input, most commonly help text.\n\n    Generated macros can then be includ" \
"ed within a C project and\n    printed/manipulated easily as the program req" \
"uires.\n    \n    This program's source is freely available on GitHub under " \
"the MIT license.\n\nUSAGE:\n    help-text [options]\n\nOPTIONS:\n    -h     " \
"            Display this help message and quit.\n    -i <input file>    Spec" \
"ify the input file to get the help text from. If no\n                       " \
"input file is provided, help-text will read from stdin.\n    -o <output file" \
">   Specify the output file to write the help text macro to.\n              " \
"         If no output file is provided, help-text will print its\n          " \
"             output to stdout.\n    -l <width>         Specify the line widt" \
"h to conform the macro to. Default\n                       is 80 columns.\n " \
"   -n <name>          Change the name of the macro being generated. Default " \
"is\n                       \"HELP_TEXT\".\n"
