# Syntax
```
program    := filehead (function | assignment)* end
filehead   := in 
function   := ident  (type)  (params)  block
params     := param_op   (value)+
block      := colon  (statement)*  end
statement  := assignment | call | if | while
if         := "if" expression ifblock
ifblock    := colon  (statement)*  ("elif" statement*) ("else" statement*) end
while      := "while" expression  block
expression := ("(") value  binop  value (")")
value      := ident | literal | expression
assignment := value  ass_op  ident
binop      := ">" | "<" | "<=" | ">=" | "%" | "==" | "+" | "-" | "*" | "/"
literal    := number | """ (char)* """
number     := [0-9]+ | ([0.9])*.([0-9])+
char       := any character (a, b, c, 0, 1, 2, etc.)
ident      := [a-Z]([a-Z | 0-9 | _])*

ass_op     := "->"
param_op   := "<-"
colon      := ":"
end        := "end"
```