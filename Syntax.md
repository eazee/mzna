# Syntax
```
program    := (function | assignment)*
function   := ident  (type)  (params)  block
params     := param_op   value+
block      := colon  statement*  end
statement  := assignment | call | if | while
if         := "if" expression ifblock
ifblock    := colon  statement*  ("elif" statement*) ("else" statement*) end
while      := "while" expression block
expression := value  binop  value
value      := ident | literal | expression
assignment := value  ass_op  ident
binop      := ">" | "<" | "==" | "+" | "-" | "*" | "/"

ass_op     := "->"
param_op   := "<-"
colon      := ":"
end        := "end"
```