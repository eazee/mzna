# Syntax
```
program    := filehead  colon (function | assignment)* end
filehead   := "in"  string   "program"   string
function   := ident  (type)  (params)  block
params     := param_op   (value  type  (, value type)+)
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
type       := "number" | "bool" | "string" | ident

ass_op     := "->" | "+->" | "*->" | "/->" | "-->"
param_op   := "<-"
colon      := ":"
end        := "end"
```