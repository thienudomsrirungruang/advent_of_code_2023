(* Too lazy to write a nonlinear solver... *)

input = OpenRead["parsed.txt"];
data = ReadList[input, Word, WordSeparators -> {" ", "\n"}];

m = ToExpression[data[[1]]];
Assert[m > 3];
n = 3;
nums = Partition[data[[2;;]], 6];

pi = Table[ToExpression[nums[[i, 1 ;; 3]]], {i, 1, n}];
vi = Table[ToExpression[nums[[i, 4 ;; 6]]], {i, 1, n}];

p0 = Array[p, 3];
v0 = Array[v, 3];
ti = Array[t, n];

equations = Table[p0 + ti[[i]]*v0 == pi[[i]] + ti[[i]]*vi[[i]], {i, 1, n}];
solution = Solve[equations, Flatten[{p0, v0, ti}]];
Print[solution];
p0 = Table[p[i] /. solution[[1]], {i, 1, 3}];
Print[p0];
Print[p0[[1]] + p0[[2]] + p0[[3]]];

