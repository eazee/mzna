# Syntax
```
program    := (function | assignment)*
function   := ident  (type)  (params)  block
params     := param_op   (value  type  (, value type)+)
block      := (singleblock | multiblock)
singleblock := colon statement
multiblock := colon  newline  ( statement  (newline  statement)* )  end
block      := colon  (statement)*  end
statement  := assignment | call | if | while
call       := ident  (param_op   value  (,  (value)+))
if         := "if" expression ifblock
ifblock    := colon  (statement)*  ("elif" statement*) ("else" statement*) end
while      := "while" expression  block
expression := ("(") value  binop  value (")")
value      := ident | literal | expression
assignment := value  ass_op  ident  (type)
binop      := ">" | "<" | "<=" | ">=" | "%" | "=?" | "+" | "-" | "*" | "/"
literal    := number | string | bool
string     := """ (char)* """
number     := [0-9]+ | ([0.9])*.([0-9])+
char       := any character (a, b, c, 0, 1, 2, etc.)
bool       := "true" | "false"
ident      := [a-Z]([a-Z | 0-9 | _])*
type       := "number" | "bool" | "string" | "void"

ass_op     := "->" | "+->" | "*->" | "/->" | "-->"
param_op   := "<-"
colon      := ":"
newline    := "\n"
end        := "end"
```